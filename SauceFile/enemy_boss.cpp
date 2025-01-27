//================================================================================================================================================================
//
//�{�X�G�l�~�[����[enemy_boss.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "enemy_boss.h"
#include "effect_backpack.h"
#include "player_3d.h"
#include "manager.h"
#include "sound.h"
#include "nova_eff.h"
#include "nova.h"
#include "missile.h"
#include "atk_time_effect.h"

//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CEnemy_Boss::CEnemy_Boss():CXcharacter(8)
{

}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CEnemy_Boss::~CEnemy_Boss()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CEnemy_Boss::Init()
{
	const int nMaxLife = 200;

	CXcharacter::Init();
	SetPos(100.0f, 0.f,-500.0f);
	SetLife(nMaxLife);
	LoadParts();
	LoadMotion();
	m_EnemyHp_Gage = CGage_Enemy_Hp::Create();
	m_GageBack = CGage_Back::Create({SCREEN_WIDTH *0.503f+50.f,30.f}, 65.f*4.f, 15.f, true);

	//�U���֌W�̎��ԑS��
	m_nAtkCnt = NULL, m_nStayCnt = NULL, m_nMaxStayCnt = NULL;
	m_bAtk = true;
	m_MotionSet = STAY;
	m_AtkStay = TACKLE;
	m_bTutorial = false;

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CEnemy_Boss::Uninit()
{
	m_EnemyHp_Gage->Uninit();
	m_EnemyHp_Gage = nullptr;

	m_GageBack->Uninit();
	m_GageBack = nullptr;

	if (!m_bTutorial) {
		CManager::GetInstance()->GetScene()->FadeTrigger();
	}

	CXcharacter::Uninit();
}

//================================================================================================================================================================
//�X�V����
//================================================================================================================================================================
void CEnemy_Boss::Update()
{
	if (GetLife() <= NULL){
		
		DelParts();

		//�`���[�g���A���͖�������
		if (m_bTutorial){
			Create(true);
		}

		CManager::GetInstance()->GetScene()->SetLodeResult(true);

		return;
	}

	//����̎c�胉�C�t�ʂ��Q�[�W��
	m_EnemyHp_Gage->GageAnim((float)GetLife());

	D3DXVECTOR3* pPos = GetPos();
	D3DXVECTOR3* pRot = GetRot();

	//�d��
	SetMove({ 0.f,-5.f,0.f });

	if (!m_bTutorial)
	{
		//�U���܂ł̃C���^�[�o�����
		if (!m_bAtk) {
			SetMotion(STAY);
			m_nAtkCnt = NULL;
			++m_nStayCnt;

			//�X�e�C����U�����[�h��
			if (m_nStayCnt >= m_nMaxStayCnt) {
				m_nStayCnt = NULL;
				m_bAtk = true;
				//�U���̐���m�点��SE
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_ATTACK_SE);

				D3DXVECTOR3 PosBody = { pPos->x,pPos->y + 100.f,pPos->z };

				//�^�b�N��
				if (m_AtkStay == TACKLE) {
					CAtk_Time_Effect::Create(300, 0.35f);
				}
				//�m���@
				else if (m_AtkStay == NOVA) {
					CAtk_Time_Effect::Create(420, 0.25f);
					CNova_Eff::Create(PosBody);
				}
				//�~�T�C��
				else if (m_AtkStay == SNIPER) {
					CAtk_Time_Effect::Create(120, 0.8f);
				}
			}
		}

		//�U���̐�
		else {
			//�O���C���N�������g
			++m_nAtkCnt;
			if (m_AtkStay == TACKLE) {
				Tackle(*pPos, *pRot);
			}
			else if (m_AtkStay == NOVA) {
				Nova(*pPos, *pRot);
			}
			else if (m_AtkStay == SNIPER) {
				Sniper(*pPos);
			}
		}
	}

	Motion();

	CXcharacter::Update();
}

//================================================================================================================================================================
// �U������
//================================================================================================================================================================
void CEnemy_Boss::Tackle(D3DXVECTOR3 pos, D3DXVECTOR3& rot)
{
	SetMotion(TACKLE);

	// �{�X�̃^�b�N�����x
	const float fBaseSpeed = 5.f;
	const float fDamping = 0.95f; // �����W��
	const float fRatio = 0.5f;    // �����x�����ϐ�
	const int nTackleStay = 300;
	const int nEndTackleTime = 420;
	const int nTackleAttackWindow = 60;
	const int nIntervalTime = 180;

	// �U���ʒu��ݒ�i�{�X�̃p�[�c�̍����������j
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_EnemBossParts[0]->GetPos().y, pos.z };

	// �U���G�t�F�N�g���쐬
	CBack_Effect::Create(HitPos, rot);

	// �^�b�N�����̑��x��ێ�����ϐ�
	static D3DXVECTOR3 velocity = { 0.f, 0.f, 0.f }; // �������ʗp�̑��x�x�N�g��

	// �I�u�W�F�N�g���X�g�𑖍�
	CObject* pObject = CObject::GetTop(); // ���X�g�̐擪�I�u�W�F�N�g����J�n

	while (pObject != nullptr)
	{
		CObject::TYPE type = pObject->GetType();

		// �v���C���[�^�C�v�̃I�u�W�F�N�g���ǂ����`�F�b�N
		if (type == CObject::TYPE::PLAYER)
		{
			CPlayer3D* pPlayer = dynamic_cast<CPlayer3D*>(pObject);

			if (pPlayer)
			{
				// �{�X�̊p�x���v���C���[��
				if (m_nAtkCnt < nTackleStay)
				{
					float dx = pPlayer->GetPos()->x - HitPos.x;
					float dz = pPlayer->GetPos()->z - HitPos.z;
					float dy = pPlayer->GetPos()->y - HitPos.y;
					float distance = sqrtf(dx * dx + dz * dz + dy * dy);

					float fAngleY = atan2f(dx, dz);
					float fAngleX = asinf(dy / distance);

					const float fMinPitch = -30.f * (D3DX_PI / 180.f);
					const float fMaxPitch = 30.f * (D3DX_PI / 180.f);

					if (fAngleX < fMinPitch) {
						fAngleX = fMinPitch;
					}

					if (fAngleX > fMaxPitch) {
						fAngleX = fMaxPitch;
					}

					rot.y = fAngleY + D3DX_PI;
					rot.x = fAngleX;
					rot.z = 0.0f;
				}

				else if (m_nAtkCnt > nEndTackleTime){
					SetIntervalTime(nIntervalTime);
					rot = { 0.f, rot.y, 0.f };
					velocity = { 0.f, 0.f, 0.f }; // ���������Z�b�g
				}

				else if (m_nAtkCnt > nTackleStay && m_nAtkCnt < nTackleStay + nTackleAttackWindow){
					CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_FIRING_SE);

					// �v���C���[�Ɍ������ĉ���
					float mx = sinf(rot.y + D3DX_PI) * fBaseSpeed;
					float my = sinf(rot.x) * fBaseSpeed;
					float mz = cosf(rot.y + D3DX_PI) * fBaseSpeed;

					D3DXVECTOR3 acceleration = { mx, my, mz }; // �����x�N�g��
					velocity += acceleration * fRatio;                  // ���x�ɉ��Z
				
				// �v���C���[�ɏՓ˔���
				CModelParts PlayerParts = pPlayer->GetPlayerParts();
				D3DXVECTOR3 HitPlayerPos = { pPlayer->GetPos()->x,
					pPlayer->GetPos()->y + PlayerParts.GetPartsRadhiusu().y,
					pPlayer->GetPos()->z };

				//�@�q�b�g����
				if (CManager::GetInstance()->GetCollision()->HitCircleCollision(
					HitPos, HitPlayerPos, m_EnemBossParts[0]->GetPartsRadhiusu(), PlayerParts.GetPartsRadhiusu()*0.5f))
				{
					D3DXVECTOR3 knockbackDir = D3DXVECTOR3(pPlayer->GetPos()->x - HitPos.x,
						pPlayer->GetPos()->y - HitPos.y,
						pPlayer->GetPos()->z - HitPos.z);

					D3DXVec3Normalize(&knockbackDir, &knockbackDir);

					float knockbackSpeed = 30.f;
					D3DXVECTOR3 knockbackForce = knockbackDir * knockbackSpeed;

					pPlayer->SetMove(knockbackForce);
					pPlayer->PlayerDamage(10);

					m_nAtkCnt = NULL;
					velocity = { 0.f, 0.f, 0.f }; // ���������Z�b�g

					SetIntervalTime(nIntervalTime);

					break;
				}

				}
			}
		}

		pObject = pObject->GetNext();
	}

	// ���������������ړ��ʂ�ݒ�
	velocity *= fDamping;        // ������K�p
	SetMove(velocity);           // ���݂̑��x�ňړ�
}

//================================================================================================================================================================
//�����U��
//================================================================================================================================================================
void CEnemy_Boss::Nova(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	
	//SetMotion(NOVA);
	SetMove({ 0.f,0.f,0.f });

	//�e�X�g���o
	if (m_nAtkCnt < 120) {
		CManager::GetInstance()->GetCamera()->SetDirectionTime(120);
		CManager::GetInstance()->GetCamera()->DirectionCamera(pos,rot,1000.f);
	}

	//�m���@����
	if (m_nAtkCnt >= 420){
		pos.y = pos.y + 100;
		CNova::Create(pos,1000.f,240);
		CManager::GetInstance()->GetCamera()->SetShake(240,1.f);
		SetIntervalTime(600);
	}
}

//================================================================================================================================================================
//�~�T�C���e���U��
//================================================================================================================================================================
void CEnemy_Boss::Sniper(D3DXVECTOR3 pos) {

	D3DXVECTOR3 PosBody = { pos.x,pos.y + 100.f,pos.z };
	
	if (m_nAtkCnt > 120){
		CMissile::Create(PosBody, 5.f, true);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_FIRING_SE);
		CMissile::Create(PosBody, 8.f, false);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_FIRING_SE);
		SetIntervalTime(360);
	}
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CEnemy_Boss::Draw()
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
		m_EnemBossParts[i]->Draw();
	}
}

//================================================================================================================================================================
//�{�X�̎��̍s�������߂�
//================================================================================================================================================================
void CEnemy_Boss::ShiftAtkState() {

	bool bEscapLoop = false;

	while(1)
	{
		//���̍s����I��
		int randomAttack = (rand() % MAX) + 1;

		//���ʂ�����̍s���ƈقȂ�
		if (randomAttack != m_AtkStay){

			if (randomAttack == TACKLE){
				m_AtkStay = TACKLE;
				bEscapLoop = true;
			}

			else if (randomAttack == NOVA){
				m_AtkStay = NOVA;
				bEscapLoop = true;
			}

			else if (randomAttack == SNIPER){
				m_AtkStay = SNIPER;
				bEscapLoop = true;
			}
		}

		if (bEscapLoop){
			break;
		}
	}
}

//================================================================================================================================================================
//�p�[�c���폜
//================================================================================================================================================================
void CEnemy_Boss::DelParts() {

	for (int i = 0; i < NUM; i++) {

		if (m_EnemBossParts[i] != nullptr) {
			m_EnemBossParts[i]->Uninit();
			delete m_EnemBossParts[i];
			m_EnemBossParts[i] = nullptr;
		}
	}
}

//================================================================================================================================================================
//���f���ǂݍ��ݏ���
//================================================================================================================================================================
void CEnemy_Boss::LoadParts(){

	char Datacheck[2048];	            // �f�[�^����
	char cModelPath[2048];	            // �f�[�^����
	int nCnt = 0;				        // �g�p���̃f�[�^��
	int PlayerModelNumSeve = 0;			// �ǂݎ�������f������ۑ�����
	int Id = NULL;
	int nPair = NULL;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen("data\\MODEL\\enemy\\enemydata.txt", "r");

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
			m_EnemBossParts[PlayerModelNumSeve] = CModelParts::Create({ 0.f,0.f,0.f }, m_FileModel[PlayerModelNumSeve]);
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

			m_EnemBossParts[nCnt]->SetPos(pos);
			m_EnemBossParts[nCnt]->SetRot(rot);

			m_EnemBossParts[nCnt]->SetDeffalt();
			m_EnemBossParts[nCnt]->SetId(Id);
			m_EnemBossParts[nCnt]->ModelSizeSum();

			if (nPair != -1)
			{
				m_EnemBossParts[nCnt]->SetParent(m_EnemBossParts[nPair]);
			}

			nCnt++;	// �f�[�^�����Z
		}
	}
}

//================================================================================================================================================================
//���[�V�����ǂݍ��ݏ���
//================================================================================================================================================================
void CEnemy_Boss::LoadMotion()
{
	char Datacheck[2048];	// �f�[�^����
	int MotionCnt = 0;		//���[�V�����J�E���g
	int keysetcnt = 0;		//���[�V�����J�E���g
	int KeyCnt = 0;			//�L�[�J�E���g

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen("data\\MODEL\\enemy\\enemydata.txt", "r");

	//�t�@�C�������݂��Ȃ����Ǖ����܂�
	if (pFile == NULL)
	{
		return;
	}

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
void CEnemy_Boss::Motion()
{
	//���[�V�����ړ��ʂ̌v�Z�p�֐�
	D3DXVECTOR3 Mpos[NUM];
	D3DXVECTOR3 Mrot[NUM];

	int nKey = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey; //���̃L�[�Ƃ̌����̈ʒu�̍������v�Z���邽�߂�int�֐�

	for (int i = 0; i < NUM; i++)
	{
		D3DXVECTOR3 pGetRot = m_EnemBossParts[i]->GetRot();

		//���߂�������S�̃t���[�����[�g�Ŋ��邱�Ƃ�1�t���[���̓��슄����K��������
		Mrot[i] = ((m_Motion[m_MotionSet].KeySet[nKey].Key[i].Motion_rot)
			- (m_EnemBossParts[i]->GetRot()))
			/ (float)m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate;

		pGetRot += Mrot[i];

		m_EnemBossParts[i]->SetRot(pGetRot);
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
void CEnemy_Boss::SetMotion(STATE g_Motions)
{
	if (m_MotionSet != g_Motions){
		m_nFrameCnt = 0;
		m_MotionSet = g_Motions;
		m_nKeyCnt = 0;
	}
}

//================================================================================================================================================================
//�v���C���[����
//================================================================================================================================================================
CEnemy_Boss* CEnemy_Boss::Create(bool t){

	CEnemy_Boss* pCEnemy_Boss = new CEnemy_Boss();
	pCEnemy_Boss->Init();
	pCEnemy_Boss->SetType(CObject::TYPE::BOSS);
	pCEnemy_Boss->m_bTutorial = t;
	return pCEnemy_Boss;
}