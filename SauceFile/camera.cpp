//================================================================================================================================================================
//
//�J��������[camera.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "camera.h"
#include "manager.h"
#include <cmath>  // abs�֐��̂��߂ɕK�v

//================================================================================================================================================================
//�}�N����`
//================================================================================================================================================================

//================================================================================================================================================================
//�O���[�o���ϐ�
//================================================================================================================================================================

//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CCamera::CCamera()
{

}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CCamera::~CCamera()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 200.f, -300); //���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  //������x�N�g��
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fCloseDistance = 400.f;
	m_nShakeLate = 0;
	m_fShakeSum = 0.0f;
	m_nDirectionTime = NULL;
	m_nDirectionMaxTime = NULL;
	m_bDirectionMode = false;
	m_bBack = false;

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CCamera::Uninit()
{
}

//================================================================================================================================================================
//�X�V�����i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CCamera::Update(){

	if (m_bDirectionMode){
		EndDirectionTime();
	}
}

//================================================================================================================================================================
//���΋����J����
//================================================================================================================================================================
void CCamera::FollowCameraTargetEnem(D3DXVECTOR3 playerPos, D3DXVECTOR3 enemyPos, D3DXVECTOR3 rot) {

	if (!m_bDirectionMode){
		// �v���C���[�ƓG�̈ʒu����J�����̌������v�Z
		float x = enemyPos.x - playerPos.x;  // ���̍���
		float z = enemyPos.z - playerPos.z;  // �c�̍���
		float y = enemyPos.y - playerPos.y;  // �㉺�̍���

		float angleToEnemy = atan2f(x, z);   // �G�ւ̊p�x

		// �v���C���[�̌����Ɋ�Â��ăJ�����𒲐�
		const float cameraHeight = 170.0f;   // �����̃I�t�Z�b�g

		// �v���C���[�̌����Ɋ�Â��ăJ�����ʒu���v�Z
		const float cameraAngle = rot.y + D3DX_PI;  // �v���C���[�̉�]����J�����������v�Z

		// �ڕW�ʒu���v�Z
		D3DXVECTOR3 targetPos;

		//�ڕW�ʒu�ݒ�
		targetPos.x = playerPos.x - (m_fCloseDistance * sinf(cameraAngle));
		targetPos.z = playerPos.z - (m_fCloseDistance * cosf(cameraAngle));

		//�J���������܂ňڂ������������߂�
		float midpointY;
		//�J�����̒����_�𒆊Ԃ�
		midpointY = (playerPos.y + enemyPos.y) * 0.5f;

		targetPos.y = midpointY; // ���ԍ�����ڕW�ʒu�ɔ��f

		//�X���[�W���O�W��
		float smoothingFactor = 0.075f;

		// �J�����ʒu���Ԃ��ăX���[�Y�ɓ�����
		m_posV.x += (targetPos.x - m_posV.x) * smoothingFactor;
		m_posV.z += (targetPos.z - m_posV.z) * smoothingFactor;

		// �v���C���[�Ƃ̍ŏ�������ۂ��߂̐���
		float minDistance = 350.0f;
		float currentDistance = sqrtf((m_posV.x - playerPos.x) * (m_posV.x - playerPos.x) +
			(m_posV.z - playerPos.z) * (m_posV.z - playerPos.z));

		//�J�����̍ŏ��ʒu�ɕ⊮����
		if (currentDistance < minDistance) {
			float scale = minDistance / currentDistance;
			m_posV.x = playerPos.x + (m_posV.x - playerPos.x) * scale;
			m_posV.z = playerPos.z + (m_posV.z - playerPos.z) * scale;
		}

		//���݂̃J�����̕�����ۑ�
		float fAngle = atan2f(x, z);
		D3DXVECTOR3 AngleY = GetRot();
		AngleY.y = fAngle + D3DX_PI;

		//�ʒu�ݒ�
		CManager::GetInstance()->GetCamera()->SetRot(AngleY);

		// �ŏI�I�ȃJ������������
		m_posV.y = playerPos.y;

		// �����_�̈ʒu��ݒ�i�v���C���[�̈ʒu�j
		m_posR.x = playerPos.x;
		m_posR.y = playerPos.y;
		m_posR.z = playerPos.z;
	}
}

//================================================================================================================================================================
//�Ώۂ̌���ǂ�������ݒ�
//================================================================================================================================================================
void CCamera::FollowCameraTargetPlayer(D3DXVECTOR3 playerPos, D3DXVECTOR3 rot) {

	if (!m_bDirectionMode){

		// �v���C���[�̌��Ɉʒu���邽�߂̃I�t�Z�b�g���`
		float height;   // �v���C���[�̍�������̃I�t�Z�b�g

		if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_TITLE) {
			height = 250.f;
		}
		else {
			height = 170.f;
		}

		height = 170.f;

		// �v���C���[�̌����Ă����������J�����̈ʒu���v�Z
		float fAngle = rot.y + D3DX_PI; // �v���C���[�̌����Ɋ�Â��p�x�v�Z

		// �ڕW�ʒu���v�Z
		D3DXVECTOR3 targetPos;
		targetPos.x = playerPos.x - (m_fCloseDistance * sinf(fAngle));
		targetPos.y = playerPos.y + height; // �v���C���[�̏���ɔz�u
		targetPos.z = playerPos.z - (m_fCloseDistance * cosf(fAngle));

		// �J�����̈ʒu���Ԃ��ăX���[�Y�ɓ�����
		float smoothingFactor = 0.085f; // �X���[�W���O�̌W���i0.0f�`1.0f�j

		// �S�̊��������X�ɋ삯�Ă���
		m_posV.x += (targetPos.x - m_posV.x) * smoothingFactor;
		m_posV.z += (targetPos.z - m_posV.z) * smoothingFactor;

		// �J�����̈ʒu�𒲐��i�ő吧���ƍŏ�������������j
		float maxY = 1200.f; // �ő卂��
		float minY = 100.f;  // �ŏ�����

		// �v���C���[�̑��x�ɉ����ăJ�����̈ʒu�𒲐�
		float newY = m_posV.y + (targetPos.y - m_posV.y);

		//�������炵���ۂɈ�a�����Ȃ���
		m_posV.y = newY - rot.x;

		// �v���C���[�Ƃ̋���������K�p
		float minDistance = 350.f; // �v���C���[�Ƃ̍ŏ�����
		float currentDistance = sqrt((m_posV.x - playerPos.x) * (m_posV.x - playerPos.x) +
			(m_posV.z - playerPos.z) * (m_posV.z - playerPos.z));

		//���ȏ�J�������߂Â������Ȃ�����
		if (currentDistance < minDistance) {
			// �J�������v���C���[������̋�����������
			float scale = minDistance / currentDistance;
			m_posV.x = playerPos.x + (m_posV.x - playerPos.x) * scale;
			m_posV.z = playerPos.z + (m_posV.z - playerPos.z) * scale;
		}

		// ����ʒu���v���C���[�ɐݒ�iy���̉�]���Œ�j
		m_posR.x = playerPos.x;
		m_posR.y = playerPos.y + rot.x; // �v���C���[��y�ʒu�����̂܂܎g�p
		m_posR.z = playerPos.z;
	}
}

//================================================================================================================================================================
//�G�̍s���ɍ��킹�����o�ݒ�
//================================================================================================================================================================
void CCamera::DirectionCamera(D3DXVECTOR3 tergetpos, D3DXVECTOR3 rot,float distance){

	if (m_bDirectionMode){

	        // �v���C���[�̌��Ɉʒu���邽�߂̃I�t�Z�b�g���`
	        float height = 170.f;   // �v���C���[�̍�������̃I�t�Z�b�g
	        
	        // �v���C���[�̌����Ă����������J�����̈ʒu���v�Z
	        float fAngle = rot.y; // �v���C���[�̌����Ɋ�Â��p�x�v�Z
	        
	        // �ڕW�ʒu���v�Z
	        D3DXVECTOR3 targetPos;
	        targetPos.x = tergetpos.x - (m_fCloseDistance * sinf(fAngle));
	        targetPos.y = tergetpos.y + height; // �v���C���[�̏���ɔz�u
	        targetPos.z = tergetpos.z - (m_fCloseDistance * cosf(fAngle));
	        
	        // �J�����̈ʒu���Ԃ��ăX���[�Y�ɓ�����
	        float smoothingFactor = 0.085f; // �X���[�W���O�̌W���i0.0f�`1.0f�j
	        
	        // �S�̊��������X�ɋ삯�Ă���
	        m_posV.x += (targetPos.x - m_posV.x) * smoothingFactor;
	        m_posV.z += (targetPos.z - m_posV.z) * smoothingFactor;
	        
	        // �J�����̈ʒu�𒲐��i�ő吧���ƍŏ�������������j
	        float maxY = 1200.f; // �ő卂��
	        float minY = 100.f;  // �ŏ�����
	        
	        // �v���C���[�̑��x�ɉ����ăJ�����̈ʒu�𒲐�
	        float newY = m_posV.y + (targetPos.y - m_posV.y);
	        
	        //�������炵���ۂɈ�a�����Ȃ���
	        m_posV.y = newY - rot.x;
	        
	        // �v���C���[�Ƃ̋���������K�p
	        float minDistance = distance; // �v���C���[�Ƃ̍ŏ�����
	        float currentDistance = sqrt((m_posV.x - tergetpos.x) * (m_posV.x - tergetpos.x) +
	        	(m_posV.z - tergetpos.z) * (m_posV.z - tergetpos.z));
	        
	        //���ȏ�J�������߂Â������Ȃ�����
	        if (currentDistance < minDistance) {
				// �J�������v���C���[������̋�����������
				float scale = minDistance / currentDistance;
	        	m_posV.x = tergetpos.x + (m_posV.x - tergetpos.x) * scale;
	        	m_posV.z = tergetpos.z + (m_posV.z - tergetpos.z) * scale;
	        }
	        
	        // ����ʒu���v���C���[�ɐݒ�iy���̉�]���Œ�j
	        m_posR.x = tergetpos.x;
	        m_posR.y = tergetpos.y + rot.x; // �v���C���[��y�ʒu�����̂܂܎g�p
	        m_posR.z = tergetpos.z;
	}
}

//================================================================================================================================================================
//�J�����̐ݒ�
//================================================================================================================================================================
void CCamera::SetCamera(){

	CRenderer* pRenderer = nullptr;
	pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 100.0f, 8000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	RendererDivice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posv = m_posV;
	D3DXVECTOR3 posr = m_posR;

	//�h�ꏈ��
	if (m_nShakeLate > 0){

		--m_nShakeLate;

		//�U���l���
		adjust.x += m_fShakeSum;
		adjust.z += m_fShakeSum;

		//�V�F�C�N�����ݒ�
		adjust.x = (float)(rand() % 50) * m_fShakeSum;
		adjust.z = (float)(rand() % 50) * m_fShakeSum;

		//�^���J�����ɑ��
		posv += adjust;
		posr += adjust;
	}

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &posv, &posr, &m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	RendererDivice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//================================================================================================================================================================
//�J�����U���ݒ�
//================================================================================================================================================================
void CCamera::SetShake(int shakeLate, float shakesum){
	m_nShakeLate = shakeLate;
	m_fShakeSum = shakesum;
}

