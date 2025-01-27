//================================================================================================================================================================
//
//�v���C���[����[player3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "player_3d.h"
#include "enemy_boss.h"
#include "manager.h"
#include "effect_backpack.h"
#include "effect_explosion.h"
#include "effect_charge.h"
#include "effect_cool.h"
#include "field.h"
#include "damageeff.h"

bool CPlayer3D::m_bOeSkillBreak = false;

//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CPlayer3D::CPlayer3D():CXcharacter(3),m_bRushAtk(false),m_nRushCoolTime(NULL), m_nOeSkillBreakTime(NULL), m_bRecovery(false){

}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CPlayer3D::~CPlayer3D()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CPlayer3D::Init()
{
	CXcharacter::Init();

	LoadParts();
	LoadMotion();
	SetPos(0.0f,(float)NULL,1500.f);
	SetLife(100);
	SetState(STATEMODE::NONE);

	m_fChargeSum = (float)NULL;

	m_GageBack[0] = CGage_Back::Create(D3DXVECTOR2(SCREEN_WIDTH*0.5f, 576.f),130.f, 15.f,false);
	m_GageBack[1] = CGage_Back::Create(D3DXVECTOR2(200.f, 680.f), 130.f, 15.f, true); //�q�[�g
	m_GageBack[2] = CGage_Back::Create(D3DXVECTOR2(200.f, 620.f), 130.f, 15.f, true); //���C�t

	m_ChargeGage = Charge_Gage::Create();

	m_GageHeat  = CGage_Heat::Create();

	m_PlayerLifeGage = CGage_Player_Life::Create();

	m_GearSpeed = CSpeedgear::Create();

	m_GearAtk = CAtkgear::Create();

	m_Oeskill_Cool = COeSkill_Cool::Create();

	m_Oeskill_Repair = COeSkill_Jamming::Create();

	m_TargerPnt = CTarget_Pointer::Create();

	m_OldPos = D3DXVECTOR3((float)NULL, (float)NULL, (float)NULL);

	m_CameraRot = D3DXVECTOR3((float)NULL, D3DX_PI * 0.01f, (float)NULL);

	m_nKeyCnt = NULL;

	m_nFrameCnt = NULL;

	m_bFlowEnemMode = false;

	m_bAtk = false;

	m_nStepCnt = NULL;

	m_bStepMode = false;

	m_fHeatSum = (float)NULL;

	m_bStepVec = false;

	m_MotionSet = NONE;

	m_nGap = NULL;

	m_nAtkTime = NULL;

	m_bAtkPanchi = false;

	m_Step = { 0.f,0.f,0.f };

	m_vVelocity = { 0.f,0.f,0.f };

	m_bOverheat = false;

	m_bUseOeSkill = false;

	m_nAtkSum = NULL;

	m_PowerRank = FIRST;

	m_nOeSkillTime = NULL;

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CPlayer3D::Uninit()
{
	m_ChargeGage->Uninit();
	m_ChargeGage = nullptr;

	m_GageHeat->Uninit();
	m_GageHeat = nullptr;

	for (int i = 0; i < MAX_GAGE_BACK; i++)
	{
		m_GageBack[i]->Uninit();
		m_GageBack[i] = nullptr;
	}

	m_GearSpeed->Uninit();
	m_GearSpeed = nullptr;

	m_GearAtk->Uninit();
	m_GearAtk = nullptr;

	m_Oeskill_Cool->Uninit();
	m_Oeskill_Cool = nullptr;

	m_Oeskill_Repair->Uninit();
	m_Oeskill_Repair = nullptr;

	m_TargerPnt->Uninit();
	m_TargerPnt = nullptr;

	m_PlayerLifeGage->Uninit();
	m_PlayerLifeGage = nullptr;


	for (int i = 0; i < NUM; i++)
	{
		m_PlayerParts[i]->Uninit();
		m_PlayerParts[i]=nullptr;
	}

	CManager::GetInstance()->GetScene()->FadeTrigger();

	CXcharacter::Uninit();
}

//================================================================================================================================================================
//�X�V����
//================================================================================================================================================================
void CPlayer3D::Update()
{
	//���o�����ǂ���
	if (CManager::GetInstance()->GetCamera()->GetPlayStay()) {
		//�ȉ��̏��������X�L�b�v
		return;
	}

	//����ł���ꍇ
	if (GetLife()<=NULL){

		CManager::GetInstance()->GetScene()->SetLodeResult(false);
		return;
	}

	//�ʒu�擾
	D3DXVECTOR3* pPos = CObjectX::GetPos();
	//�p�x�擾
	D3DXVECTOR3* pRot = CObjectX::GetRot();
	//���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//�p�b�h���͏��
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();
	// ���C�t�Q�[�W
	m_PlayerLifeGage->GageAnim((float)GetLife());
	//�I�[�o�[�q�[�g�Ǘ�����
	OverHeatManagement(*pPos);
	//�J�������[�h�Ǘ�����
	CameraManagement(*pPos,*pRot);
	//�J��������
	Rotation();

	//�M�A�V�t�g����
	if (pJoy->GetTrigger(CInputJoypad::JOYKEY_LB)&&!m_bAtk) {
		m_GearSpeed->FlagShift();
	}

	//�I�v�e�B�}�X�G�l���M�[�Ǘ�����
	OeSkillManagement(*pPos);

	//�`���[�W�x���Q�[�W��
	m_ChargeGage->GageAnim(m_fChargeSum);
	//�X���X�^�[�M�ʃQ�[�W��
	m_GageHeat->GageAnim(m_fHeatSum);

	//�ړ�����
	if (!m_bStepMode) {
		//�`���[�W���Ă��Ȃ�
		MoveMent(*pRot,*pPos);
	}
	// �j���[�g�����������␳
	if (!MoveMent(*pRot,*pPos)) {
		//�ړ����Ă��Ȃ��Ƃ�
		SetRot(D3DXVECTOR3(0.f, 0.f, 0.f));
	}

	//�U���S�ʂ��Ǘ�
	AtkManagement(*pPos,*pRot);

	// ����s��
	if ((pKeyboard->GetTrigger(DIK_LSHIFT) || pJoy->GetTrigger(CInputJoypad::JOYKEY_B))
		&& !m_bAtk && !m_bOverheat
		&& GetState() != STATEMODE::DAMAGE) {
		// �X�e�b�v���
		m_bStepMode = true;
	}

	//���[�V�����X�e�C�g�Ǘ�����
	MotionStateManagement(*pPos,*pRot);

	//���[�V�������s
	Motion();

	//�O�̈ʒu��ݒ�
	m_OldPos = *pPos;

	m_ChargeGage->SetDraw(m_bAtk);
	m_GageBack[0]->SetDraw(m_bAtk);

	CXcharacter::Update();
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CPlayer3D::Draw()
{
	//�ʒu�擾
	D3DXVECTOR3* pPos = CObjectX::GetPos();
	//�ʒu�擾
	D3DXVECTOR3* pRot = CObjectX::GetRot();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	CRenderer* pRenderer = nullptr;
	pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pRot->y, pRot->x, pRot->z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pPos->x, pPos->y, pPos->z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	RendererDivice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int i = 0; i < NUM; i++){
		m_PlayerParts[i]->Draw();
	}
}

//================================================================================================================================================================
// �I�[�o�[�q�[�g�Ǘ�����
//================================================================================================================================================================
void CPlayer3D::OverHeatManagement(D3DXVECTOR3 pos) {

	// �I�[�o�[�q�[�g
	if (m_fHeatSum >= 100.f && !m_bOverheat) {
		//�I�[�o�[�q�[�g���[�h�˓�
		m_bOverheat = true;
		CExplosion_Effect::Create(pos);
	}

	//�@�I�[�o�[�q�[�g����
	if (m_bOverheat) {
		//��p����
		float fCoolvalue = 0.3;
		CoolThruster(fCoolvalue);
		SetMotion(OVERHEAT);
		if (m_fHeatSum <= 0.f) {
			m_bOverheat = false;
		}
	}
}

//================================================================================================================================================================
// �J�������[�h�Ǘ�����
//================================================================================================================================================================
void CPlayer3D::CameraManagement(D3DXVECTOR3& pos, D3DXVECTOR3& rot) {

	//���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//�p�b�h���͏��
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//�ǐՃ��[�h��
	if (m_bFlowEnemMode) {
		//�G�̕����Ɍ�������
		SearchRot(rot, pos);
		DistanceSum(rot, pos);
	}

	//���ӃT�[�`���[�h
	else {
		//�v���C���[�̌�����ɒǂ�
		CManager::GetInstance()->GetCamera()->FollowCameraTargetPlayer(pos, m_CameraRot);

		if (m_TargerPnt->GetDraw()) {
			m_TargerPnt->SetDraw(false);
		}
	}

	//�J�������[�h�ϊ�
	if (pKeyboard->GetTrigger(DIK_L) || pJoy->GetTrigger(CInputJoypad::JOYKEY_R3)) {
		m_bFlowEnemMode = m_bFlowEnemMode ? false : true;
	}

}

//================================================================================================================================================================
// �I�v�e�B�}�X�G�l���M�[�Ǘ�����
//================================================================================================================================================================
void CPlayer3D::OeSkillManagement(D3DXVECTOR3 pos) {

	//���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//�p�b�h���͏��
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//�ő�㌄�̎���
	const int nMaxBreakSkillTime = 600;

	//�X�L���V�t�g����
	if (pJoy->GetTrigger(CInputJoypad::JOYKEY_RB) && !m_bUseOeSkill) {
		m_Oeskill_Cool->FlagShift();
	}

	//�I�v�e�B�}�X�G�l���M�[�X�L���g�p
	if (pJoy->GetRTrigger().y >= 0.7f && !m_bUseOeSkill && !m_bOeSkillBreak) {
		//�X�L���g�p���
		m_bUseOeSkill = true;
	}

	//�I�v�e�B�}�X�G�l���M�[��������
	if (m_bUseOeSkill) {
		//�X�L���g�p����
		OeSkill(pos);
	}

	//�g�p����ĂȂ��ۂɃ��Z�b�g����
	else {
		m_GageBack[1]->SetCollar(255, 255, 255, 255);
	}

	//�X�L���g�p������̃N�[���^�C��
	if (m_bOeSkillBreak && !m_bUseOeSkill){
		++m_nOeSkillBreakTime;
		OeSkillBreakTime(600);
	}

}

//================================================================================================================================================================
// �I�v�e�B�}�X�G�l���M�[�g�p����
//================================================================================================================================================================
void CPlayer3D::OeSkill(D3DXVECTOR3 pos) {

	//�X�L���p�����ԃC���N��
	++m_nOeSkillTime;

	//�I�v�e�B�}�X�G�l���M�[�ϐ�
	bool bOeSkill = m_Oeskill_Cool->GetOeSkillMode();
	const int nLife = GetLife();
	const int nMaxLife = GetMaxLife();

	//���y�A�X�L������
	if (bOeSkill){
		if (nLife < nMaxLife || m_bRecovery){
			OeSkill_Repair(pos);
		}
		else {
			m_bUseOeSkill = false;
		}
	}

	//�X���X�^�[��p�X�L��
	else {
		OeSkill_CoolThruster(pos);
	}
}

//================================================================================================================================================================
// �X���X�^�[��p�X�L������
//================================================================================================================================================================
void CPlayer3D::OeSkill_CoolThruster(D3DXVECTOR3 pos){

	//���ʌp������
	int nTimeLimit = 60;
	//�X���X�^�[����p����
	D3DXVECTOR3 TargetPos = { pos.x,pos.y + m_PlayerParts[0]->GetPos().y,pos.z };//�ڕW�n�_�v�Z
	//�G�t�F�N�g����
	CCool_Effect::Create(TargetPos);
	//�M�ʒቺ
	CoolThruster(0.5f);
	//�ꎞ�I�ɃQ�[�W�𐅐F��
	m_GageBack[1]->SetCollar(0, 255, 255, 255);
	//�I�v�e�B�}�X�G�l���M�[�X�L���X�e�[�^�X���Z�b�g����
	OeSkillStatusrReset(nTimeLimit);
}

//================================================================================================================================================================
// ���y�A�X�L������
//================================================================================================================================================================
void CPlayer3D::OeSkill_Repair(D3DXVECTOR3 pos) {

	//���ʌp������
	int nTimeLimit = 800;
	//�X���X�^�[����p����
	D3DXVECTOR3 TargetPos = { pos.x,pos.y + m_PlayerParts[0]->GetPos().y,pos.z };//�ڕW�n�_�v�Z
	//�G�t�F�N�g����
	CCool_Effect::Create(TargetPos);
	//�I�v�e�B�}�X�G�l���M�[�X�L���X�e�[�^�X���Z�b�g����
	OeSkillStatusrReset(nTimeLimit);

	if (m_bRecovery){
		return;
	}

	const int nRecoveryValue = 20;

	RecoveryLife(nRecoveryValue);

	m_bRecovery = true;
}

//================================================================================================================================================================
// �U���Ǘ�����
//================================================================================================================================================================
void CPlayer3D::AtkManagement(D3DXVECTOR3& pos, D3DXVECTOR3& rot) {

	// ���b�V���U��
	if (!m_GearSpeed->GetFlagGear()){
		RushAtk(pos, rot);
	}

	// �`���[�W�U��
	else {
		ChargeAtkManagement(pos,rot);
	}
}

//================================================================================================================================================================
// ���b�V���U���Ǘ�����
//================================================================================================================================================================
void CPlayer3D::RushAtk(D3DXVECTOR3 pos , D3DXVECTOR3& rot) {

	//���b�V���U���N�[���^�C���ݒ�
	const int nMaxRushCoolTime = 20;
	//���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//�p�b�h���͏��
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//�N�[���^�C������
	if (m_bRushAtk){
		++m_nRushCoolTime;
		//�N�[���^�C���I������
		if (m_nRushCoolTime > nMaxRushCoolTime) {
			m_nRushCoolTime = NULL;
			m_bRushAtk = false;
		}
	}

	// �A�łōU��
	if ((!pKeyboard->GetTrigger(DIK_SPACE) && !pJoy->GetTrigger(CInputJoypad::JOYKEY_X))||
		m_bRushAtk) {
		return;
	}

	m_bRushAtk = true;

	//�q�b�g����̈ʒu
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_PlayerParts[0]->GetPos().y, pos.z };
	//���X�g�̐擪�I�u�W�F�N�g����J�n
	CObject* pObject = CObject::GetTop();
	//�q�b�g����
	bool bAtkHit = false;
	//�U�����l�ݒ�
	const int nAtkValue = 1;

	while (pObject != nullptr)
	{
		CObject::TYPE type = pObject->GetType();

		// �{�X�^�C�v�̃`�F�b�N
		if (type == CObject::TYPE::BOSS)
		{
			// ���S�Ƀ_�E���L���X�g
			CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

			// �_�E���L���X�g�ɐ��������ꍇ
			if (pBoss)
			{
				// �������Ă��邩���f
				if (CManager::GetInstance()->GetCollision()->HitCircleCollision(HitPos, *pBoss->GetPos(),
					m_PlayerParts[0]->GetPartsRadhiusu(),{ 50.f,50.f,50.f })) {
					// �U�����]ON
					bAtkHit = true;
				}

				// �A�^�b�N���[�h����
				if (bAtkHit) {
					// �G�Ƀ_���[�W��^����
					pBoss->Damage(nAtkValue);
					pBoss->SetState(STATEMODE::DAMAGE);
				}
				break; // ��̃{�X�ɓ��������烋�[�v�𔲂���
			}

		}
		// ���̃I�u�W�F�N�g�Ɉړ�
		pObject = pObject->GetNext();
	}
	rot.y = CManager::GetInstance()->GetCamera()->GetRot().y;
}

//================================================================================================================================================================
// �`���[�W�U���Ǘ�����
//================================================================================================================================================================
void CPlayer3D::ChargeAtkManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot) {

	D3DXVECTOR3 pPos = pos;

	//���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//�p�b�h���͏��
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//�`���[�W�s��
	if ((pKeyboard->GetPress(DIK_SPACE) || pJoy->GetPress(CInputJoypad::JOYKEY_X))
		&& GetState() != STATEMODE::DAMAGE
		&& !m_bStepMode) {
		// �`���[�W����
		Charge(rot);

		// �ڕW�n�_�v�Z
		D3DXVECTOR3 TargetPos = { pPos.x, pPos.y + m_PlayerParts[0]->GetPos().y, pPos.z };

		// �`���[�W�p�G�t�F�N�g
		for (int i = 0; i < m_PowerRank; i++) {
			CCharge_Effect::Create(TargetPos, m_PowerRank);
		}
	}

	else if (!pJoy->GetPress(CInputJoypad::JOYKEY_X)
		&& m_fChargeSum > 0.0f && m_bAtk) {
		// �`���[�W���Ă��Ȃ��ꍇ
		m_bAtkPanchi = true;
	}
}

//================================================================================================================================================================
// ���[�V�������s����
//================================================================================================================================================================
void CPlayer3D::MotionStateManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot) {

	//�`���[�W�U��
	if (m_bAtkPanchi) {
		ChargeAtk(pos,rot);
	}

	//�`���[�W��
	else if (m_bAtk) {
		SetMotion(CHARGE);
	}

	//�X�e�b�v
	else if (m_bStepMode && !m_bAtk && !m_bOverheat) {
		Step(rot);
	}

	//�����Ă�����
	else if (MoveMent(rot, pos)) {
		SetMotion(WALK);
	}

	//�ҋ@��
	else {
		SetMotion(NONE);
	}
}

//================================================================================================================================================================
// �ړ������i�����t���A�d�݂̂���ړ��ŋ}�Ɏ~�܂�Ȃ��悤�ɒ����j
//================================================================================================================================================================
bool CPlayer3D::MoveMent(D3DXVECTOR3& rot ,D3DXVECTOR3 pos)
{
	if (GetState() == STATEMODE::DAMAGE){
		return false;
	}

	// ���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	// �J�����̕������
	D3DXVECTOR3 CameraRot = m_CameraRot;

	// �X���X�^�[�{���ϐ�
	float fThruster = 1.f;

	// �X���X�^�[�{���ϐ�
	float fHeat = 0.05f;

	// �d�� (�������ďd��������������)
	float fGrav = m_fGav * 1.2f;  // ���̏d�͂�1.2�{�̏d�݂�ǉ�

	// �ړ������m�F
	bool bMove = false;

	// �X���X�^�[�g�p�m�F
	bool bUseThruster = false;

	// ���݂̃M�A���[�h�̔���
	bool bGearMode = m_GearSpeed->GetFlagGear();

	// ���x�{��
	float fSpeedSplit;

	// ���C�W���i�����𑝂₵�ďd���Ȍ����Ɂj
	float fFriction = 0.925f; // ���C�ɂ�鑬�x���������Ȃ����āA���������������悤��

	// �ő呬�x�̐ݒ�
	float fMaxSpeed; // �ő�ړ����x�̏�������������ďd��������

	// �J�����p�x���
	float fCameraSpeed = CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI;

	// �t�F�[�h�ʒu�擾
	D3DXVECTOR2 pFpos = CManager::GetInstance()->GetFade()->GetFadePos();

	// �p���`����t�F�[�h�������͈ړ��ł��Ȃ�
	if (pFpos.y > 0.f - SCREEN_HEIGHT * 0.25f || m_bAtkPanchi || m_bStepMode|| m_bOverheat){
		m_vVelocity.x = 0.f;
		m_vVelocity.z = 0.f;
		SetMove({0.f,fGrav,0.f});
		return false;
	}

	// �M�A���[�h�ɂ��X�s�[�h����
	if (bGearMode) {
		fSpeedSplit = 6.f;  // �����x�����ďd�݂�����
		fMaxSpeed = 7.f;
		if (m_bAtk){
			fMaxSpeed = 2.f;
		}
	}

	else {
		fSpeedSplit = 6.f;
		fMaxSpeed = 12.f;
	}

	// ���͂Ɋ�Â��ړ�����
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W) || pJoy->GetPress(CInputJoypad::JOYKEY_UP) == true) { // ��
		vecDirection.z = 0.5f;
		bMove = true;
	}
	if (pKeyboard->GetPress(DIK_S) || pJoy->GetPress(CInputJoypad::JOYKEY_DOWN) == true) { // ��
		vecDirection.z = -0.5f;
		bMove = true;
	}
	if (pKeyboard->GetPress(DIK_A) || pJoy->GetPress(CInputJoypad::JOYKEY_LEFT) == true) { // ��
		vecDirection.x = 0.5f;
		bMove = true;
	}
	if (pKeyboard->GetPress(DIK_D) || pJoy->GetPress(CInputJoypad::JOYKEY_RIGHT) == true) { // �E
		vecDirection.x = -0.5f;
		bMove = true;
	}

	// ���X�Ɍ�����]���x�̐ݒ�
	float rotationSpeed = 0.25f; // ��]���x�𒲐��i0.1 = ��������], 1.0 = �����ɉ�]�j

	// �ړ�����������ꍇ�A���������X�ɍX�V����
	if (bMove) {
		// �ړ������̊p�x���擾
		float targetDirection = atan2f(-vecDirection.x, vecDirection.z) + fCameraSpeed;

		// �ڕW�����ƌ��݂̕����̍����v�Z
		float delta = targetDirection - rot.y - D3DX_PI;

		// -�΁`�΂͈̔͂Ɏ��߂邽�߁A�����𐳋K��
		if (delta > D3DX_PI) {
			delta -= D3DX_PI * 2;
		}
		else if (delta < -D3DX_PI) {
			delta += D3DX_PI * 2;
		}

		// �p�x����`���
		rot.y += rotationSpeed * delta;

		// �p�x�� -�� �` �� �͈̔͂ɐ��K������
		if (rot.y > D3DX_PI) {
			rot.y -= D3DX_PI * 2.0f;
		}
		else if (rot.y < -D3DX_PI) {
			rot.y += D3DX_PI * 2.0f;
		}
	}

	// �X���X�^�[�@�����u
	if (pKeyboard->GetPress(DIK_P) || (pJoy->GetLTrigger().y >= 0.3f && bMove && !m_bAtk)) {
		bUseThruster = true;
		fThruster = 2.f;
		fGrav = 0.f;  // �X���X�^�[�g�p���͏d�͂𖳌���
	}

	// �X���X�^�[�㏸����
	if (pKeyboard->GetPress(DIK_M) && !m_bAtk || (pJoy->GetLTrigger().y >= 0.7f && 
		vecDirection.x == 0.f && vecDirection.z == 0.f)) {
		bUseThruster = true;
		fGrav = 5.f; // �d�͖���
	}

	// �U����X�e�b�v���̈ړ�����
	if (m_bStepMode) {
		vecDirection.x = 0.f;
		vecDirection.z = 0.f;
	}

	// �X���X�^�[���g�p���̃q�[�g����
	if (!bUseThruster && m_fHeatSum > 0.f) {
		//�X���X�^�[��p����
		CoolThruster(fHeat);
	}

	// �X���X�^�[�g�p���̃q�[�g����
	else if (bUseThruster){
		//�q�[�g�Q�[�W��������
		HeatThruster(fHeat);
		// �M�A���[�h�ɂ��X�s�[�h����
		if (bGearMode) {
			fMaxSpeed = 10.f;
		}
		else {
			fMaxSpeed = 17.f;
		}
		CBack_Effect::Create(pos, rot);
	}

	// �����ɂ�鑬�x����
	if (bMove) {
		// �������O�����ɕϊ�
		float rotMoveY = atan2f(-vecDirection.x, vecDirection.z);  // x�������t�]������
		float sin = sinf(rotMoveY + fCameraSpeed);
		float cos = cosf(rotMoveY + fCameraSpeed);

		// ���������i�������x�������Ⴍ�j
		m_vVelocity.x += sin * fSpeedSplit * fThruster * 0.05f;  // �����W����Ⴍ���ďd������ǉ�
		m_vVelocity.z += cos * fSpeedSplit * fThruster * 0.05f;
	}

	//��~������������
	else {
		// ���͂��Ȃ��ꍇ�͖��C�ɂ�錸������
		m_vVelocity.x *= fFriction;
		m_vVelocity.z *= fFriction;
	}

	// ���݂̑��x�̑傫�����v�Z
	float speed = sqrtf(m_vVelocity.x * m_vVelocity.x + m_vVelocity.z * m_vVelocity.z);

	// ���x���ő呬�x�𒴂��Ă����琧������
	if (speed > fMaxSpeed) {
		float scale = fMaxSpeed / speed;
		m_vVelocity.x *= scale;
		m_vVelocity.z *= scale;
	}

	// �v���C���[�����S�ɒ�~�����ꍇ�̏���
	if (fabs(m_vVelocity.x) < 0.2f && fabs(m_vVelocity.z) < 0.2f) {
		m_vVelocity.x = 0.0f;
		m_vVelocity.z = 0.0f;
		SetMove({ 0.f, fGrav, 0.f });
		return false;
	}

	// ���������������ړ�����
	D3DXVECTOR3 MoveValue = { m_vVelocity.x, fGrav, m_vVelocity.z };

	//�@�ړ��l���
	SetMove(MoveValue);

	return bMove;
}

//================================================================================================================================================================
//�p���[�`���[�W����
//================================================================================================================================================================
void CPlayer3D::Charge(D3DXVECTOR3 &rot)
{
	int nAtk = 0;
	float fHeat = 0.025f;
	float fChargeTime = 1.5f;
	//���݂̃M�A���[�h�̔���

	if (m_fChargeSum <= 100.1f){

		//5�i�K
		if (m_fChargeSum >= (float)80){

			m_fChargeSum += 0.1f * fChargeTime;
			nAtk = 20;
			m_ChargeGage->SetCollar(255, 255, 0,255);
			m_PowerRank = FIVE;
		}

		//�S�i�K
		else if (m_fChargeSum >= (float)60){
			m_fChargeSum += 0.15f * fChargeTime;
			nAtk = 13;
			m_ChargeGage->SetCollar(255, 0, 255,255);
			m_PowerRank = FORTH;
		}

		//3�i�K
		else if (m_fChargeSum >= (float)40){
			m_fChargeSum += 0.2f * fChargeTime;
			nAtk = 8;
			m_ChargeGage->SetCollar(0, 0, 255,255);
			m_PowerRank = THIRD;
		}

		//2�i�K
		else if (m_fChargeSum >= (float)20){
			m_fChargeSum += 0.25f * fChargeTime;
			nAtk = 4;
			m_ChargeGage->SetCollar(0,255, 0,255);
			m_PowerRank = SECOND;
		}

		//�����i�K
		else if (m_fChargeSum >= (float)0){
			m_fChargeSum += 0.3f * fChargeTime;
			nAtk = 1;
			m_ChargeGage->SetCollar(255, 0, 0,255);
			m_PowerRank = FIRST;
		}
	}

	//�t���`���[�W
	else{
		nAtk = 35;
		m_ChargeGage->SetCollar(0, 255, 255, 255);
		m_PowerRank = FULLPOWER;
	}

	rot.y = CManager::GetInstance()->GetCamera()->GetRot().y;

	m_bAtk    = true;
	m_nAtkSum = nAtk;
}

//================================================================================================================================================================
// �U������
//================================================================================================================================================================
void CPlayer3D::ChargeAtk(D3DXVECTOR3 pos, D3DXVECTOR3 &rot)
{
	CBack_Effect::Create(pos, rot);

	// ���݂̃M�A���[�h�̔���
	bool bGearMode = m_GearSpeed->GetFlagGear();

	// ���x�{��
	float fSpeedSplit = 16.f;

	// �U������q�b�g��
	bool bAtk = false;

	//�^�C���I�[�o�[
	bool bEnd = false;
	
	// �J�����p�x���
	float fCameraRotY = CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI;

	// �U���͕ۑ��ϐ�
	int nAtkValue = m_nAtkSum;

	int nMaxAtkTime;

	if (m_PowerRank == FULLPOWER)
	{
		nMaxAtkTime = 120;
	}

	else if (m_PowerRank == FIVE)
	{
		nMaxAtkTime = 100;
	}

	else if (m_PowerRank == FORTH)
	{
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == THIRD)
	{
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == SECOND)
	{
		nMaxAtkTime = 40;
	}

	else {
		nMaxAtkTime = 20;
	}

	// �A�^�b�N�p������
	m_nAtkTime++;
	
	CManager::GetInstance()->GetCamera()->SetCameraCloseDistance(550.f);

	//�^�C���I�[�o�[
	if (m_nAtkTime > nMaxAtkTime) {
		bEnd = true;
	}

	//�q�b�g����̈ʒu
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_PlayerParts[0]->GetPos().y, pos.z };

	CObject* pObject = CObject::GetTop(); // ���X�g�̐擪�I�u�W�F�N�g����J�n

	while (pObject != nullptr)
	{
		CObject::TYPE type = pObject->GetType();

		// �{�X�^�C�v�̃`�F�b�N
		if (type == CObject::TYPE::BOSS)
		{
			// ���S�Ƀ_�E���L���X�g
			CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

			// �_�E���L���X�g�ɐ��������ꍇ
			if (pBoss)
			{
				if (pBoss->GetState()!=DAMAGE)
				{
					//CModelParts BossParts = pBoss->GetBossParts();

					// �������Ă��邩���f
					if (CManager::GetInstance()->GetCollision()->HitCircleCollision(HitPos, *pBoss->GetPos(),
						m_PlayerParts[0]->GetPartsRadhiusu(), /*BossParts.GetPartsRadhiusu())*/{50.f,50.f,50.f})) {
						// �U�����]ON
						bAtk = true;
					}

					// �A�^�b�N���[�h����
					if (bAtk) {

						if (bAtk) {
							// �G�Ƀ_���[�W��^����
							pBoss->Damage(nAtkValue);
							pBoss->SetState(STATEMODE::DAMAGE);
							bEnd = true;
						}
					}

					// �v���C���[�̈ړ�����
					if (!m_bFlowEnemMode) {
						// �J�����̌������l�����Ĉړ�
						float moveSpeedX = fSpeedSplit * sinf(fCameraRotY);
						float moveSpeedZ = fSpeedSplit * cosf(fCameraRotY);
						SetMove({ moveSpeedX, 0.f, moveSpeedZ });
						rot.y = fCameraRotY + D3DX_PI;
					}

					else {
						// �G�Ƃ̋����̍����v�Z
						float dx = pBoss->GetPos()->x - pos.x; // x���W�̍�
						float dz = pBoss->GetPos()->z - pos.z; // z���W�̍�
						float dy = pBoss->GetPos()->y - pos.y; // y���W�̍�

						// �����̕��������g���Đ��K��
						float distance = sqrtf(dx * dx + dz * dz + dy * dy);

						// �����̊p�x���v�Z�ixy���ʂł̊p�x�j
						float fAngle = atan2f(dz, dx);

						// �ړ��ʂ̌v�Z
						float mx = cosf(fAngle) * fSpeedSplit;    // x����
						float my = (dy / distance) * fSpeedSplit; // y�����̈ړ�
						float mz = sinf(fAngle) * fSpeedSplit;    // z����

						// �ړ��l��ݒ�
						SetMove({ mx, my, mz });


						// �i�߂鋗�����v�Z: nMaxAtkTime�ɉ������ړ�����
						float moveDistance = fSpeedSplit * nMaxAtkTime;  // nMaxAtkTime�̊Ԃɐi�ދ���

						// �����x�N�g�����v�Z
						D3DXVECTOR3 direction = { pBoss->GetPos()->x - pos.x,pBoss->GetPos()->y - pos.y,pBoss->GetPos()->z - pos.z, };

						float dist = D3DXVec3Length(&direction);

						// �i�ނׂ��������ړI�n�Ɍ����Đi�߂鋗�����傫���ꍇ
						if (dist > moveDistance) {
							m_TargerPnt->SetCollar(255, 0, 0, 255);
						}

						else {
							m_TargerPnt->SetCollar(0, 255, 0, 255);
						}
					}
					break; // ��̃{�X�ɓ��������烋�[�v�𔲂���
				}
			}
				
		}
		// ���̃I�u�W�F�N�g�Ɉړ�
		pObject = pObject->GetNext();
	}

	if (bEnd)
	{
		// �U���Ɋւ���ϐ��̃��Z�b�g
		m_fChargeSum = NULL; //�`���[�W�i�K
		m_bAtk = false;		 //�`���[�W���
		m_bAtkPanchi = false;//�p���`���
		m_nAtkTime = NULL;	 //���v�ړ�����
		m_nAtkSum = NULL;	 //���v�U���l
		CManager::GetInstance()->GetCamera()->SetCameraCloseDistance(400.f);
	}

	else {
		rot.y = CManager::GetInstance()->GetCamera()->GetRot().y;
	}
}

//================================================================================================================================================================
// �U������
//================================================================================================================================================================
void CPlayer3D::DistanceSum(D3DXVECTOR3 pos, D3DXVECTOR3& rot)
{
	// ���݂̃M�A���[�h�̔���
	bool bGearMode = m_GearSpeed->GetFlagGear();

	// ���x�{��
	float fSpeedSplit = bGearMode ? 8.f : 16.f;

	// �J�����p�x���
	float fCameraRotY = CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI;

	// �U���͕ۑ��ϐ�
	int nAtkValue = m_nAtkSum;

	// �ő�U���p�����ԕϐ�
	int nMaxAtkTime;

	if (m_PowerRank == FULLPOWER){
		nMaxAtkTime = 120;
	}

	else if (m_PowerRank == FIVE){
		nMaxAtkTime = 100;
	}

	else if (m_PowerRank == FORTH){
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == THIRD){
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == SECOND){
		nMaxAtkTime = 40;
	}

	else {
		nMaxAtkTime = 20;
	}

	//�q�b�g����̈ʒu
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_PlayerParts[0]->GetPos().y, pos.z };

	CObject* pObject = CObject::GetTop(); // ���X�g�̐擪�I�u�W�F�N�g����J�n

	while (pObject != nullptr){

		CObject::TYPE type = pObject->GetType();

		// �{�X�^�C�v�̃`�F�b�N
		if (type == CObject::TYPE::BOSS)
		{
			// ���S�Ƀ_�E���L���X�g
			CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

			// �_�E���L���X�g�ɐ��������ꍇ
			if (pBoss)
			{
				// �G�Ƃ̋����̍����v�Z
				float dx = pBoss->GetPos()->x - pos.x; // x���W�̍�
				float dz = pBoss->GetPos()->z - pos.z; // z���W�̍�
				float dy = pBoss->GetPos()->y - pos.y; // y���W�̍�

				// �����̕��������g���Đ��K��
				float distance = sqrtf(dx * dx + dz * dz + dy * dy);

				// �����̊p�x���v�Z�ixy���ʂł̊p�x�j
				float fAngle = atan2f(dz, dx);

				// �ړ��ʂ̌v�Z
				float mx = cosf(fAngle) * fSpeedSplit;    // x����
				float my = (dy / distance) * fSpeedSplit; // y�����̈ړ�
				float mz = sinf(fAngle) * fSpeedSplit;    // z����

				// �i�߂鋗�����v�Z: nMaxAtkTime�ɉ������ړ�����
				float moveDistance = fSpeedSplit * nMaxAtkTime;  // nMaxAtkTime�̊Ԃɐi�ދ���

				// �����x�N�g�����v�Z
				D3DXVECTOR3 direction = { pBoss->GetPos()->x - pos.x,pBoss->GetPos()->y - pos.y,pBoss->GetPos()->z - pos.z, };

				float dist = D3DXVec3Length(&direction);

				// �i�ނׂ��������ړI�n�Ɍ����Đi�߂鋗�����傫���ꍇ
				if (dist > moveDistance) {
					m_TargerPnt->SetCollar(0, 255, 0, 255);
				}
				else {
					m_TargerPnt->SetCollar(255, 0, 0, 255);
				}
				break; // ��̃{�X�ɓ��������烋�[�v�𔲂���
			}
		}
		// ���̃I�u�W�F�N�g�Ɉړ�
		pObject = pObject->GetNext();
	}
}

//================================================================================================================================================================
// �GSearch����
//================================================================================================================================================================
void CPlayer3D::SearchRot(D3DXVECTOR3& rot, D3DXVECTOR3 pos)
{
	CObject* pObject = CObject::GetTop(); // ���X�g�̐擪�I�u�W�F�N�g����J�n

	while (pObject != nullptr)
	{
		// nullptr�`�F�b�N�͕s�v�Bwhile���[�v�� pObject != nullptr ���ۏ؂����

		// �I�u�W�F�N�g�̎�ގ擾
		CObject::TYPE type = pObject->GetType();

			if (type == CObject::TYPE::BOSS)
			{
				// ���S�Ƀ_�E���L���X�g
				CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

				// �_�E���L���X�g�ɐ��������ꍇ
				if (pBoss)
				{
					float x = pBoss->GetPos()->x - pos.x; //�G�Ƃ̋����̍����v�Z�i���j
					float z = pBoss->GetPos()->z - pos.z; //�G�Ƃ̋����̍����v�Z�i�c�j

					float fAngle = atan2f(x, z);

					m_CameraRot.y = fAngle + D3DX_PI;

					//�ʒu�ݒ�
					CManager::GetInstance()->GetCamera()->SetRot(m_CameraRot);

					D3DXVECTOR3 LocalPos = {pos.x,pos.y+ m_PlayerParts[0]->GetPos().y,pos.z};

					//�G����ɒǐՂ��A�v���C���[�̌���ǂ�
					CManager::GetInstance()->GetCamera()->FollowCameraTargetEnem(LocalPos, *pBoss->GetPos(), m_CameraRot);
				}
			}
		// ���̃I�u�W�F�N�g�Ɉړ�
		pObject = pObject->GetNext();
	}

	//�^�[�Q�b�g�|�C���^�[�\�L
	if (!m_TargerPnt->GetDraw())
	{
		m_TargerPnt->SetDraw(true);
	}
}

//================================================================================================================================================================
// ��������
//================================================================================================================================================================
void CPlayer3D::Rotation() {
	// ���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	// �|����̎Q�ƒl
	float fStickSum = 100.f;
	// �������ϐ�
	float fRot = 0.0f;
	float fRotx = 0.0f;

	// �J�������x
	const float fRotSpeed = 0.025f;
	const float fRotSpeedx = 0.75f;
	const float fRotFirstSp = 2.5f;

	const float min = -90.0f; // �㉺��]�̐���
	const float max = 90.0f;

	// �㉺���E�̓��͂ɂ��J������]
	if (pKeyboard->GetPress(DIK_I) || pJoy->GetRInputState().x <= -fStickSum) { // ��
		fRot -= fRotSpeed * fRotFirstSp;
	}
	if (pKeyboard->GetPress(DIK_O) || pJoy->GetRInputState().x >= fStickSum) { // ��
		fRot += fRotSpeed * fRotFirstSp;
	}
	if (pKeyboard->GetPress(DIK_UP) || pJoy->GetRInputState().y >= fStickSum) { // ��
		if (m_CameraRot.x <= max) {
			fRotx += fRotSpeedx * fRotFirstSp;
		}
	}
	if (pKeyboard->GetPress(DIK_DOWN) || pJoy->GetRInputState().y <= -fStickSum) { // ��
		if (m_CameraRot.x >= min) {
			fRotx -= fRotSpeedx * fRotFirstSp;
		}
	}

	// ��]�l�̓K�p
	m_CameraRot.y += fRot; // ������]
	m_CameraRot.x += fRotx; // ������]

	// y���̉�]�� -�� �` +�� �͈̔͂Ɏ��܂�悤�ɕ␳
	if (m_CameraRot.y > D3DX_PI) {
		m_CameraRot.y -= D3DX_PI * 2; // +�� �𒴂����ꍇ�A-�� �֕␳
	}
	if (m_CameraRot.y < -D3DX_PI) {
		m_CameraRot.y += D3DX_PI * 2; // -�� ����������ꍇ�A+�� �֕␳
	}

	// �J�����̉�]���Z�b�g
	CManager::GetInstance()->GetCamera()->SetRot(D3DXVECTOR3(m_CameraRot.x, m_CameraRot.y, m_CameraRot.z));
}

//================================================================================================================================================================
//�X�e�b�v�������
//================================================================================================================================================================
void CPlayer3D::Step(D3DXVECTOR3 rot) {

	//���͏��m��
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//�J�����̕������
	D3DXVECTOR3 CameraRot = m_CameraRot;

	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//�X���X�^�[�{���ϐ�
	const float fHeat = 0.85f;
	//�d��
	const float fGrav = m_fGav;
	//�X�e�b�v�W��
	const float fStepSum = 17.f;
	//�X�e�b�v��
	const float fStepMoveVec = 150.0f;

	m_nStepCnt++;

	//�X�e�b�v��ԊǗ�
	if (m_nStepCnt >= 60)
	{
		m_bStepMode = false;
		m_bStepVec = false;
		m_Step = { 0.f,0.f, 0.f };
		m_nStepCnt = NULL;
		return;
	}

	//�X�e�b�v��
	if (m_nStepCnt <= 20)
	{
		HeatThruster(fHeat);

		SetMotion(STEP);

		//�ړ��������O�����ŋ��߂܂��傤
		if (!m_bStepVec)
		{
			if (pKeyboard->GetPress(DIK_W) || pJoy->GetPress(CInputJoypad::JOYKEY_UP))
			{ //��
				m_Step.z += fStepMoveVec;
				m_bStepVec = true;
			}

			if (pKeyboard->GetPress(DIK_S) || pJoy->GetPress(CInputJoypad::JOYKEY_DOWN))
			{ //��
				m_Step.z -= fStepMoveVec;
				m_bStepVec = true;

			}

			if (pKeyboard->GetPress(DIK_A) || pJoy->GetPress(CInputJoypad::JOYKEY_LEFT))
			{ //��
				m_Step.x -= fStepMoveVec;
				m_bStepVec = true;

			}

			if (pKeyboard->GetPress(DIK_D) || pJoy->GetPress(CInputJoypad::JOYKEY_RIGHT))
			{ //�E
				m_Step.x += fStepMoveVec;
				m_bStepVec = true;
			}

			//���͂Ȃ�
			if (!m_bStepVec)
			{
				m_Step.z -= fStepMoveVec;
				m_bStepVec = true;
			}
		}

		//�������O�����ɕϊ�
		float rotMoveY = atan2f(m_Step.x, m_Step.z);

		//�ړ��l���
		if (m_bFlowEnemMode){
			//�Ǐ]���[�h
			SetMove(D3DXVECTOR3(sinf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum,
				fGrav,
				cosf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum));
		}

		else{
			//����g�����[�h
			SetMove(D3DXVECTOR3(sinf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum,
				fGrav,
				cosf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum));
		}
	}

	else{
		SetMotion(NONE);
	}
}

//================================================================================================================================================================
//���f���ǂݍ��ݏ���
//================================================================================================================================================================
void CPlayer3D::LoadParts()
{
	const int nMaxData = 2048;
	char Datacheck[nMaxData];	// �f�[�^����
	char cModelPath[nMaxData];	// �f�[�^����
	int nCnt = 0;				//�g�p���̃f�[�^��
	int PlayerModelNumSeve = 0;			//�ǂݎ�������f������ۑ�����
	int Id = NULL;
	int nPair = NULL;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen("data\\MODEL\\player\\file.txt", "r");

	//�t�@�C�������݂��Ȃ����Ǖ����܂�
	if (pFile == NULL)
	{
		return;
	}

	// END��������܂œǂݍ��݂܂�
	while (1)
	{
		fscanf(pFile, "%s", Datacheck);	// �����ō��G����

		if (!strcmp(Datacheck, "END_SCRIPT"))
		{// �S�Ă�ǂݍ��񂾂̂Ń��[�h���I��
			fclose(pFile);
			break;
		}

		if (Datacheck[0] == '#')
		{// �߂�܂�
			continue;
		}

		//�p�[�c����ݒ�
		if (!strcmp(Datacheck, "NUM_PARTS"))
		{
			fscanf(pFile, "%s", Datacheck);
			fscanf(pFile, "%d", &PlayerModelNumSeve);
		}

		//���f���̖��O������
		if (!strcmp(Datacheck, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", Datacheck);
			fscanf(pFile, "%s", cModelPath);
			m_FileModel[PlayerModelNumSeve] = cModelPath;
			m_PlayerParts[PlayerModelNumSeve] = CModelParts::Create({0.f,0.f,0.f}, m_FileModel[PlayerModelNumSeve]);
			PlayerModelNumSeve++;
		}

		//�e�p�[�c�̐ݒ�
		if (!strcmp(Datacheck, "PARTSSET"))
		{
			// ���ڂ��ƂɃf�[�^����
			while (1)
			{
				fscanf(pFile, "%s", Datacheck); //	���G

				if (!strcmp(Datacheck, "END_PARTSSET"))
				{
					// �ǂݍ��݂��I��
					break;
				}

				//�e�q��ݒ�
				else if (!strcmp(Datacheck, "INDEX"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &Id);
				}

				//�p�[�c�̎��
				else if (!strcmp(Datacheck, "PARENT"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &nPair);
				}

				//�e�p�[�c�̈ʒu
				else if (!strcmp(Datacheck, "POS"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);
				}

				//�e�p�[�c�̊p�x 
				else if (!strcmp(Datacheck, "ROT"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%f", &rot.x);
					fscanf(pFile, "%f", &rot.y);
					fscanf(pFile, "%f", &rot.z);
				}
			}

			m_PlayerParts[nCnt]->SetPos(pos);
			m_PlayerParts[nCnt]->SetRot(rot);

			m_PlayerParts[nCnt]->SetDeffalt();
			m_PlayerParts[nCnt]->SetId(Id);
			m_PlayerParts[nCnt]->ModelSizeSum();

			if (nPair != -1)
			{
				m_PlayerParts[nCnt]->SetParent(m_PlayerParts[nPair]);
			}
	
			nCnt++;	// �f�[�^�����Z
		}
	}
}

//================================================================================================================================================================
//���[�V�����ǂݍ��ݏ���
//================================================================================================================================================================
void CPlayer3D::LoadMotion()
{
	char Datacheck[2048];	// �f�[�^����
	int MotionCnt = 0;		//���[�V�����J�E���g
	int keysetcnt = 0;		//���[�V�����J�E���g
	int KeyCnt = 0;			//�L�[�J�E���g

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen("data\\MODEL\\player\\file.txt", "r");

	//�t�@�C�������݂��Ȃ����Ǖ����܂�
	if (pFile == NULL){
		return;
	}

	while (1){

		fscanf(pFile, "%s", Datacheck);	// �����ō��G����

		if (!strcmp(Datacheck, "END_SCRIPT"))
		{// �S�Ă�ǂݍ��񂾂̂Ń��[�h���I��
			fclose(pFile);
			break;
		}

		if (Datacheck[0] == '#')
		{// �߂�܂�
			continue;
		}

		//���[�V������Ԃ̐ݒ�
		if (!strcmp(Datacheck, "MOTIONSET"))
		{
			while (1)
			{
				fscanf(pFile, "%s", Datacheck); //	���G

				if (!strcmp(Datacheck, "END_MOTIONSET"))
				{
					// �ǂݍ��݂��I��
					break;
				}
				//���[�v�̔��f
				else if (!strcmp(Datacheck, "LOOP"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &m_Motion[MotionCnt].LoopCheck);
				}

				//�S�̃L�[�̓ǂݍ���
				else  if (!strcmp(Datacheck, "NUM_KEY"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &m_Motion[MotionCnt].NumKey);
				}

				//���݂̃L�[�̐ݒ�
				if (!strcmp(Datacheck, "KEYSET"))
				{
					while (1)
					{
						fscanf(pFile, "%s", Datacheck); //	���G

						if (Datacheck[0] == '#')
						{// �߂�܂�
							fgets(Datacheck, 100, pFile);
							continue;
						}

						if (!strcmp(Datacheck, "END_KEYSET"))
						{
							// �ǂݍ��݂��I��
							break;
						}

						//�S�̃L�[�̓ǂݍ���
						else if (!strcmp(Datacheck, "FRAME"))
						{
							fscanf(pFile, "%s", Datacheck);
							fscanf(pFile, "%d", &m_Motion[MotionCnt].KeySet[keysetcnt].FrameRate);
						}

						//���݂̃L�[�̐ݒ�
						if (!strcmp(Datacheck, "KEY"))
						{
							while (1)
							{
								fscanf(pFile, "%s", Datacheck); //	���G

								if (!strcmp(Datacheck, "END_KEY"))
								{
									// �ǂݍ��݂��I��
									break;
								}

								//�e�p�[�c�̃��[�V����pos�l
								else if (!strcmp(Datacheck, "POS"))
								{
									fscanf(pFile, "%s", Datacheck);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.x);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.y);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.z);
								}

								//�e�p�[�c�̃��[�V����rot�l
								else if (!strcmp(Datacheck, "ROT"))
								{
									fscanf(pFile, "%s", Datacheck);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_rot.x);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_rot.y);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_rot.z);
								}
							}
							KeyCnt++;
						}
					}
					KeyCnt = 0;
					keysetcnt++;
				}
			}
			keysetcnt = 0;
			MotionCnt++;
		}
	}
}

//================================================================================================================================================================
//���[�V�����������揈��
//================================================================================================================================================================
void CPlayer3D::Motion()
{
	//���[�V�����ړ��ʂ̌v�Z�p�֐�
	D3DXVECTOR3 Mpos[NUM];
	D3DXVECTOR3 Mrot[NUM];

	int nKey = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey; //���̃L�[�Ƃ̌����̈ʒu�̍������v�Z���邽�߂�int�֐�

	for (int i = 0; i < NUM; i++)
	{
		D3DXVECTOR3 pGetRot = m_PlayerParts[i]->GetRot();

		//���߂�������S�̃t���[�����[�g�Ŋ��邱�Ƃ�1�t���[���̓��슄����K��������
		Mrot[i] = ((m_Motion[m_MotionSet].KeySet[nKey].Key[i].Motion_rot)
			- (m_PlayerParts[i]->GetRot()))	
			/ (float)m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate;

		pGetRot += Mrot[i];

		m_PlayerParts[i]->SetRot(pGetRot);
	}

	//���t���[���̉��Z���������܂��傤
	m_nFrameCnt++;

	//�����ŏo�����t���[�����[�g�����t���[�����[�g�J�E���g����������
	if (m_nFrameCnt >= m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate) 
	{
		//�t���[�����Z�b�g
		m_nFrameCnt = 0;

		//�g�p���̃��[�V����������Ȃ��֐i�߂܂�
		m_nKeyCnt = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey;
	}
}

//================================================================================================================================================================
//���[�V�����ݒ菈��
//================================================================================================================================================================
void CPlayer3D::SetMotion(TYPE g_Motions)
{
	if (m_MotionSet != g_Motions)
	{
		m_nFrameCnt = 0;
		m_MotionSet = g_Motions;
		m_nKeyCnt = 0;
	}
}

//================================================================================================================================================================
//�v���C���[����
//================================================================================================================================================================
CPlayer3D* CPlayer3D::Create()
{
	CPlayer3D* pCPlayer3D = new CPlayer3D();
	pCPlayer3D->Init();
	pCPlayer3D->SetType(CObject::TYPE::PLAYER);
	return pCPlayer3D;
}

//================================================================================================================================================================
//�_���[�W����
//================================================================================================================================================================
void CPlayer3D::PlayerDamage(int damage)
{
	if (GetState() != DAMAGE){

		CDamage_Eff::Create();
		CManager::GetInstance()->GetCamera()->CCamera::SetShake(30, 1.f);
		Damage(damage);
		SetState(DAMAGE);
		m_bFlowEnemMode = false;
		// �U���Ɋւ���ϐ��̃��Z�b�g
		m_fChargeSum = NULL; //�`���[�W�i�K
		m_bAtk = false;		 //�`���[�W���
		m_bAtkPanchi = false;//�p���`���
		m_nAtkTime = NULL;	 //���v�ړ�����
		m_nAtkSum = NULL;	 //���v�U���l
	}
}