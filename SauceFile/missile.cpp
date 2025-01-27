//================================================================================================================================================================
//
//�ʏ�G�l�~�[����[normal_enemy.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "manager.h"
#include "player_3d.h"
#include "nova.h"
#include "effect_backpack.h"
#include "missile.h"

//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CMissile::CMissile() :CObjectX(0){
}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CMissile::~CMissile(){
}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CMissile::Init(){
	CObjectX::Init();
	ModelFilePath("data\\MODEL\\enemy_weapon\\missile.x");
	m_Move = { 0.f,0.f,0.f };
    m_fSpeed = (float)NULL;
    m_nUpTime = 120;
    m_bFirst = false;
	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CMissile::Uninit(){
	CObjectX::Uninit();
}

//================================================================================================================================================================
//�X�V����
//================================================================================================================================================================
void CMissile::Update(){
    // �~�T�C���̌��݂̍��W�Ɖ�]�p�x���擾
    D3DXVECTOR3* pPos = CObjectX::GetPos();
    D3DXVECTOR3* pRot = CObjectX::GetRot();

    // ���e�����i�n�ʂɓ��B�����ꍇ�j
    if (pPos->y <= 10.f){
        CNova::Create(*pPos, 300.f, 120); // ���e�G�t�F�N�g�𐶐�
        Uninit();                         // �~�T�C�����폜
        return;                           // �������I��
    }

    // �v���C���[�q�b�g����(�j
    if (HitPlayer(*pPos)) {
        CNova::Create(*pPos, 150.f, 60); // ���e�G�t�F�N�g�𐶐�
        Uninit();                         // �~�T�C�����폜
        return;                           // �������I��
    }

    HitPlayer(*pPos);

    // �㏸���Ԃ��c���Ă���ꍇ
    if (m_nUpTime > NULL){
        //�@�~�T�C���㏸����
        UpMissile(*pPos,*pRot);
    }

    // �㏸���o�I����
    else {
      //�@�ړI�Ɍ�����
        TergetMove(*pPos, *pRot);
    }

    // �~�T�C���̈ʒu���X�V
    pPos->x += m_Move.x;
    pPos->y += m_Move.y;
    pPos->z += m_Move.z;
    
    // �e�N���X�̍X�V�������Ăяo��
    CObjectX::Update();
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CMissile::Draw(){
	CObjectX::Draw();
}

//================================================================================================================================================================
// �~�T�C���㏸����
//================================================================================================================================================================
void CMissile::UpMissile(D3DXVECTOR3 pos, D3DXVECTOR3& rot){

    D3DXVECTOR3 pPos = pos;

    --m_nUpTime;

    // �G�̉�]�p�x����Ɏ΂ߏ�������v�Z
    const float moveSpeed = 10.0f;  // �ړ����x

    // �p�x�⊮�ϐ�
    const float radian = 36.f;
    const float f = 0.2f;

    // �㏸�p�x�itiltAngle�j�����R�ɐݒ�
    const float tiltAngle = 90.0f * (D3DX_PI / 180.0f);  // �㏸�p�x��x���@���烉�W�A���ɕϊ��i90�j

    // ���΂ߏ�̈ړ��������v�Z
    float leftMoveX = sinf(rot.y - D3DX_PI / radian) * moveSpeed * f;   // X�����̈ړ��i���E�j
    float leftMoveY = sinf(tiltAngle) * moveSpeed;                    // Y�����i�㏸�j�̊p�x�𒲐�
    float leftMoveZ = cosf(rot.y - D3DX_PI / radian) * moveSpeed * f;   // Z�����̈ړ��i�O��j

    // �E�΂ߏ�̈ړ��������v�Z
    float rightMoveX = sinf(rot.y + D3DX_PI / radian) * moveSpeed * f;  // X�����̈ړ��i���E�j
    float rightMoveY = sinf(tiltAngle) * moveSpeed;                       // Y�����i�㏸�j�̊p�x�𒲐�
    float rightMoveZ = cosf(rot.y + D3DX_PI / radian) * moveSpeed * f;  // Z�����̈ړ��i�O��j

    // �ړ��l�����E�ǂ��炩�ɐݒ�i�����_���őI�������j
    if (m_bFirst) {
        m_Move.x = leftMoveX;
        m_Move.y = leftMoveY;
        m_Move.z = leftMoveZ;

        rot.x = D3DX_PI * 0.65f;
        rot.y = D3DX_PI * 0.5f;

        if (m_nUpTime > 60) {
            CManager::GetInstance()->GetCamera()->SetDirectionTime(60);
            CManager::GetInstance()->GetCamera()->DirectionCamera(pPos,rot, 1000.f);
        }
    }

    else {
        m_Move.x = rightMoveX;
        m_Move.y = rightMoveY;
        m_Move.z = rightMoveZ;

        rot.x = D3DX_PI * 0.65f;
        rot.y = -D3DX_PI * 0.5f;

        if (m_nUpTime <= 60) {
            CManager::GetInstance()->GetCamera()->SetDirectionTime(60);
            CManager::GetInstance()->GetCamera()->DirectionCamera(pPos, rot, 1000.f);
        }
    }

    //�G�t�F�N�g�֌W
    D3DXVECTOR3 Pos = { pPos.x, pPos.y - 50.f,pPos.z };  // �o���ꏊ
    CBack_Effect::Create(Pos,rot);                       // ����
}

//================================================================================================================================================================
// �ړI�ɍ��킹�Ēǐ�
//================================================================================================================================================================
void CMissile::TergetMove(D3DXVECTOR3 pos, D3DXVECTOR3& rot) {

    // �v���C���[�̃|�W�V�������i�[���郍�[�J���ϐ�
    D3DXVECTOR3 playerPos(0.0f, 0.0f, 0.0f);

    //�~�T�C���G�t�F�N�g�����ʒu�iY�j
    const float EffCreateY = -50.f;

    // �I�u�W�F�N�g���X�g�𑖍�
    CObject* pObject = CObject::GetTop();

    while (pObject != nullptr) {

        // �v���C���[�^�C�v�̃I�u�W�F�N�g��T��
        if (pObject->GetType() == CObject::TYPE::PLAYER) {

            CPlayer3D* pPlayer = dynamic_cast<CPlayer3D*>(pObject);

            if (pPlayer) {
                // �v���C���[�Ƃ̋����̍������v�Z
                float dx = pPlayer->GetPos()->x - pos.x; // x���W�̍�
                float dz = pPlayer->GetPos()->z - pos.z; // z���W�̍�
                float dy = pPlayer->GetPos()->y - pos.y; // y���W�̍�

                // �v���C���[�Ƃ̋������v�Z�i3D��ԁj
                float distance = sqrtf(dx * dx + dz * dz + dy * dy);

                // �v���C���[�����ւ̊p�x���v�Z
                float targetAngleY = atan2f(dx, dz);       // y���i�����j��]
                float targetAngleX = asinf(dy / distance); // x���i�㉺�j��]

                // �s�b�`�i�㉺�p�x�j�ɂ���ɉ������̃I�t�Z�b�g��ǉ�
                const float pitchOffset = 0.2f * (D3DX_PI / 180.f); // ������15����ǉ�
                targetAngleX -= pitchOffset;

                // ��]�����i�s�b�`�p�x�͈̔͂𐧌��j
                const float fMinPitch = -45.f * (D3DX_PI / 180.f); // -45�������W�A���ɕϊ�
                const float fMaxPitch = 30.f * (D3DX_PI / 180.f);  // +30�������W�A���ɕϊ�

                // fAngleX�i�s�b�`�j�̐���
                if (targetAngleX < fMinPitch) {
                    targetAngleX = fMinPitch;
                }
                else if (targetAngleX > fMaxPitch) {
                    targetAngleX = fMaxPitch;
                }

                // ���݂̉�]�������^�[�Q�b�g�����ɕ�Ԃ��ăX���[�Y�ɉ�]
                const float rotationSpeed = 0.85f; // ��]���x
                rot.y += (targetAngleY - rot.y + D3DX_PI) * rotationSpeed;
                rot.x += (targetAngleX - rot.x) * rotationSpeed;
                rot.z = 0.0f; // z���̉�]�̓[���ɌŒ�

                // �~�T�C���̈ړ��x�N�g�����v�Z
                float mx = sinf(rot.y + D3DX_PI) * m_fSpeed; // x�����̈ړ�
                float my = sinf(rot.x) * m_fSpeed;           // y�����̈ړ�
                float mz = cosf(rot.y + D3DX_PI) * m_fSpeed; // z�����̈ړ�

                // m_Move��ݒ�
                m_Move = { mx, my, mz };

                break; // �v���C���[�����������烋�[�v�𔲂���
            }
        }
        // ���̃I�u�W�F�N�g��
        pObject = pObject->GetNext();
    }

    //���o�����ǂ���
    if (CManager::GetInstance()->GetCamera()->GetPlayStay()) {
        //�����X�g�b�v
        m_Move = { (float)NULL,(float)NULL, (float)NULL };
    }

    //�@���o�ł͂Ȃ��ꍇ
    if (!CManager::GetInstance()->GetCamera()->GetPlayStay()) {
        D3DXVECTOR3 Pos = { pos.x,pos.y+EffCreateY,pos.z };
        CBack_Effect::Create(Pos,rot);
    }
}

//================================================================================================================================================================
//�@�v���C���[�Ƃ̏Փ˔���
//================================================================================================================================================================
bool CMissile::HitPlayer(D3DXVECTOR3 pos) {

    // �I�u�W�F�N�g���X�g�𑖍�
    CObject* pObject = CObject::GetTop();

    D3DXVECTOR3 Size = {20.f,20.f,20.f};

    while (pObject != nullptr) {

        // �v���C���[�^�C�v�̃I�u�W�F�N�g��T��
        if (pObject->GetType() == CObject::TYPE::PLAYER) {

            CPlayer3D* pPlayer = dynamic_cast<CPlayer3D*>(pObject);

            // �L���X�g�_�E��������
            if (pPlayer) {
                 // �v���C���[�ɏՓ˔���
                 CModelParts PlayerParts = pPlayer->GetPlayerParts();

                 D3DXVECTOR3 HitPlayerPos = { pPlayer->GetPos()->x,
                                              pPlayer->GetPos()->y + PlayerParts.GetPartsRadhiusu().y,
                                              pPlayer->GetPos()->z 
                                            };
                 //�@�q�b�g����
                 if (CManager::GetInstance()->GetCollision()->HitCircleCollision(
                     pos, HitPlayerPos, Size, PlayerParts.GetPartsRadhiusu()))
                 {
                     D3DXVECTOR3 knockbackDir = D3DXVECTOR3(pPlayer->GetPos()->x - pos.x,
                         pPlayer->GetPos()->y - pos.y,
                         pPlayer->GetPos()->z - pos.z);

                     D3DXVec3Normalize(&knockbackDir, &knockbackDir);
                 
                     float knockbackSpeed = 30.f;
                     D3DXVECTOR3 knockbackForce = knockbackDir * knockbackSpeed;
                 
                     pPlayer->SetMove(knockbackForce);
                     pPlayer->PlayerDamage(10);

                     return true;
                 }
            }
        }
        // ���̃I�u�W�F�N�g��
        pObject = pObject->GetNext();
    }
    return false;
}

//================================================================================================================================================================
//����
//================================================================================================================================================================
CMissile* CMissile::Create(D3DXVECTOR3 pos,float s,bool bFirst){
	CMissile* pCMissile = new CMissile();
	pCMissile->Init();
	pCMissile->SetType(TYPE::MISSILE);
	pCMissile->SetPos(pos.x, pos.y, pos.z);
    pCMissile->m_fSpeed = s;
    pCMissile->m_bFirst = bFirst;
	return pCMissile;
}