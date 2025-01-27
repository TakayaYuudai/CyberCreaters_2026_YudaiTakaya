//================================================================================================================================================================
//
//�I�u�W�F�N�g����[object.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "object2D.h"
#include "manager.h"

//================================================================================================================================================================
//�R���X�g���N�^�i�������g�̓o�^�j
//================================================================================================================================================================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{

}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CObject2D::~CObject2D()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CObject2D::Init()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_fSplit = 1.0f;
	m_nTime = 0;
	m_nAnimationId = 0;
	m_bRev = false;
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_rot = {0.f,0.f,0.f};
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_fSplitLeft = 0.0f;
	m_fSplitRight = 1.0f;
	m_nRed = 255;
	m_nGreen = 255;
	m_nBlue = 255;
	m_nAlpha = 255;
	m_bDraw = true;

	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�Ίp���̒������Z�o����
	m_fLengthPlayer = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / (float)2;
	//�Ίp���̊p�x���Z�o����
	m_fAnglePlayer = atan2f(m_fWidth, m_fHeight);

	//���_���W�̎w��
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fSplitLeft, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fSplitRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_fSplitLeft, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fSplitRight, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CObject2D::Uninit()
{
	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Deathflag();
}

//================================================================================================================================================================
//�X�V����
//================================================================================================================================================================
void CObject2D::Update()
{
	if (m_pVtxBuff != nullptr)
	{
		//���_�X�V����
		UpdatepVtx();

		//���W�X�V����
		UpdateUVtex();

		//Animation����
		if (m_bRev)
		{
			UpdateAnim();
		}
	}
	//�ړ��l���
	m_pos += m_move;
}

//================================================================================================================================================================
//�`�揈��
//================================================================================================================================================================
void CObject2D::Draw()
{
	if (m_bDraw)
	{
		CRenderer* pRenderer = nullptr;

		pRenderer = CManager::GetInstance()->GetRenderer();

		LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

		//���_�o�b�t�@���f�[�^�X�g���[���֐ݒ�
		RendererDivice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		RendererDivice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���ݒ�
		RendererDivice->SetTexture(0, m_pTexture);

		//�|���S���`��
		RendererDivice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//�v���~�e�B�u�̎��
	}
}

//================================================================================================================================================================
//Object2D���W�ݒ�
//================================================================================================================================================================
void CObject2D::SetPos(float x, float y)
{
	m_pos = D3DXVECTOR2(x, y);
}

//================================================================================================================================================================
//�ʒu��Ԃ�
//================================================================================================================================================================
D3DXVECTOR2* CObject2D::GetPos()
{
	return &m_pos;
}

//================================================================================================================================================================
//�ʒu��Ԃ�
//================================================================================================================================================================
D3DXVECTOR3* CObject2D::GetRot()
{
	return &m_rot;
}

//================================================================================================================================================================
//�T�C�Y��Ԃ�
//================================================================================================================================================================
D3DXVECTOR2* CObject2D::GetSize()
{
	m_size = D3DXVECTOR2(m_fWidth, m_fHeight);

	return &m_size;
}

//================================================================================================================================================================
//�A�j���[�V�����ݒ�
//================================================================================================================================================================
void CObject2D::SetAnimation(float fSplit, int nTime)
{
	if (fSplit > 0)
	{
		m_fSplit = fSplit;
		m_nTime = nTime;
		m_bRev = true;
	}
}

//================================================================================================================================================================
//�A�j���[�V�����̍X�V
//================================================================================================================================================================
void CObject2D::UpdateAnim()
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	float fSplitSize = 1.0f / m_fSplit;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	{
		m_nextTime++;

		pVtx[0].tex = D3DXVECTOR2(fSplitSize * (float)(m_nAnimationId + 1.0f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fSplitSize * (float)m_nAnimationId, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fSplitSize * (float)(m_nAnimationId + 1.0f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fSplitSize * (float)m_nAnimationId, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �A�j���[�V�����i�s����
	{
		if (m_nextTime >= m_nTime)
		{
			m_nAnimationId++;

			m_nextTime = 0;

			if (m_nAnimationId >= m_fSplit)
			{
				m_nAnimationId = 0;
			}
		}
	}
}

//================================================================================================================================================================
//�e�N�X�`���̐ݒ�
//================================================================================================================================================================
void CObject2D::SetTexture(std::string sPath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//�����̃t�@�C���p�X���Q�Ƃ��ăe�N�X�`���ǂݍ���

	//c_str�֐��̕⑫?NULL�ŏI��镶���z��ւ̃|�C���^��Ԃ�(���ƕ֗��ł�����)
	D3DXCreateTextureFromFile(pDevice, sPath.c_str(), &m_pTexture);
}

//================================================================================================================================================================
//�T�C�Y�ݒ�
//================================================================================================================================================================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fHeight = fHeight*2.f;
	m_fWidth = fWidth* 2.f
		;
}

//================================================================================================================================================================
//UVtex���W�ݒ�
//================================================================================================================================================================
void CObject2D::SetUVtex(float fSplitLeft, float fSplitRight)
{
	m_fSplitLeft = fSplitLeft;
	m_fSplitRight = fSplitRight;
}

//================================================================================================================================================================
//UVtex���W�X�V����
//================================================================================================================================================================
void CObject2D::UpdateUVtex()
{
	VERTEX_2D* pVtx; //���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fSplitLeft, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fSplitRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_fSplitLeft, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fSplitRight, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//pVtx�̍X�V
//================================================================================================================================================================
void CObject2D::UpdatepVtx()
{
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	m_fLengthPlayer = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / (float)2;

	//�Ίp���̊p�x���Z�o����
	m_fAnglePlayer = atan2f(m_fWidth, m_fHeight);

	//���_���W�̎w��
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	UpdateCollar();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
// �~�`�Q�[�W�̃A�j���[�V��������
//================================================================================================================================================================
void CObject2D::CircleGageAnim(float fGageStatus)
{
//	VERTEX_2D* pVtx;
//
//	// ���_�o�b�t�@�����b�N
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	// �Q�[�W�̍ő�Z�O�����g�� (1�������������邩)
//	const int kMaxSegments = 36; // 1����36���� (10�x����)
//
//	// ���ۂɕ`�悷��Z�O�����g�� (fGageStatus�Ɋ�Â�)
//	int activeSegments = static_cast<int>(kMaxSegments * (fGageStatus * 0.01f));
//
//	// ���a
//	float fRadius = m_fWidth * 0.5f; // ������ɐݒ� (�K�X�ύX�\)
//
//	// ���S�_�̐ݒ�
//	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
//	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f); // ���S�_�̓e�N�X�`���̒���
//
//	// �Z�O�����g���Ƃ̊p�x (���W�A��)
//	float fSegmentAngle = D3DXToRadian(360.0f / kMaxSegments);
//
//	// ���_�̐ݒ� (���S�_ + �Z�O�����g���Ƃ̒��_)
//	for (int i = 0; i <= activeSegments; ++i)
//	{
//		// ���݂̊p�x
//		float fAngle = fSegmentAngle * i;
//
//		// �~����̒��_�̍��W���v�Z
//		float x = m_pos.x + cosf(fAngle) * fRadius;
//		float y = m_pos.y - sinf(fAngle) * fRadius; // Y���͔��]
//		pVtx[i + 1].pos = D3DXVECTOR3(x, y, 0.0f);
//
//		// �e�N�X�`�����W���v�Z
//		float u = 0.5f + cosf(fAngle) * 0.5f;
//		float v = 0.5f - sinf(fAngle) * 0.5f; // �e�N�X�`����Y�������]
//		pVtx[i + 1].tex = D3DXVECTOR2(u, v);
//	}
//
//	// �O�p�`�̍\�z (���S�_�Ɗe�Z�O�����g������)
//	for (int i = 0; i < activeSegments; ++i)
//	{
//		// �Z�O�����g���\�����钸�_�C���f�b�N�X
//		int index0 = 0;         // ���S�_
//		int index1 = i + 1;     // ���݂̃Z�O�����g�̎n�_
//		int index2 = i + 2;     // ���̃Z�O�����g�̏I�_
//
//		// �O�p�`���\�� (�����ł̓C���f�b�N�X���Ǘ�����z��ŋL�q)
//		// ���ۂ̕`��ŃC���f�b�N�X�o�b�t�@���K�v�ȏꍇ�́A�ʓr�ݒ肵�Ă��������B
//		// ex: pIndexBuffer[triIndex++] = {index0, index1, index2};
//	}
//
//	UpdateCollar();
//
//	// ���_�o�b�t�@���A�����b�N����
//	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//���݂̃|�X�g�A�j���[�V����
//================================================================================================================================================================
void CObject2D::GageAnim(float fGageStatus)
{
	VERTEX_2D* pVtx;

	  // ���_�o�b�t�@�����b�N
	  m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	   
	//���W�ʒu����
	float fWidth = m_fWidth * 2 * 0.01 * fGageStatus;

	//�e���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y + m_fHeight, 0.0f);

	//���݂�tex���W�ʒu����
	float TexWidth = 1.0 * 0.01 * fGageStatus;

	//�ő�l���o
	if (TexWidth > 1.f) {
		TexWidth = 1.f;
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexWidth, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(TexWidth, 1.0f);

	UpdateCollar();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//�ォ��c�ɃA�j���[�V��������
//================================================================================================================================================================
void CObject2D::UpdateCooldownGauge(float fGageStatus) {

	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���W�ʒu����
	float fHeight = m_fHeight * 2 * 0.01 * fGageStatus;

	//�e���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, (m_pos.y + m_fHeight * 2.f)  - fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, (m_pos.y + m_fHeight * 2.f)  - fHeight, 0.0f);
														  
	//���݂�tex���W�ʒu����
	float TexfHeight = 1.0 * 0.01 * fGageStatus;

	//�ő�l���o
	if (TexfHeight > 1.f){
		TexfHeight = 1.f;
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.f,0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f,0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f,TexfHeight);
	pVtx[3].tex = D3DXVECTOR2(1.f,TexfHeight);

	UpdateCollar();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//��������O����
//================================================================================================================================================================
void CObject2D::InsideOutTex(float fGageStatus)
{
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��W�ݒ�
	float fWidth = m_fWidth * 0.01f * fGageStatus;  // �X�P�[�����O
	float fHeight = m_fHeight * 0.01f * fGageStatus; // y���W���X�P�[�����O

	// �ʒu�𒆉���ɏC��
	float xOffset = fWidth / 2.0f;  // ���̔���
	float yOffset = fHeight / 2.0f; // �����̔���

	// �X�P�[�����O��̒��_�ʒu���v�Z
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - xOffset, m_pos.y - yOffset, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + xOffset, m_pos.y - yOffset, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - xOffset, m_pos.y + yOffset, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + xOffset, m_pos.y + yOffset, 0.0f);

	// �e�N�X�`�����W���������O���ɍL����悤�Ɍv�Z
	float fTexCenter = 0.5f;  // �e�N�X�`���̒��S
	float fTexRange = (fGageStatus / 100.0f) * 0.5f; // fGageStatus �� 0�`100 �͈̔͂� 0�`1 �ɃX�P�[��
	float fTexStart = fTexCenter - fTexRange;
	float fTexEnd = fTexCenter + fTexRange;

	// �e�N�X�`�����W�̐ݒ�
	float fTexVStart = fTexCenter - fTexRange; // y�����̊J�n�ʒu
	float fTexVEnd = fTexCenter + fTexRange;   // y�����̏I���ʒu

	pVtx[0].tex = D3DXVECTOR2(fTexStart, fTexVStart);
	pVtx[1].tex = D3DXVECTOR2(fTexEnd, fTexVStart);
	pVtx[2].tex = D3DXVECTOR2(fTexStart, fTexVEnd);
	pVtx[3].tex = D3DXVECTOR2(fTexEnd, fTexVEnd);

	UpdateCollar();

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//================================================================================================================================================================
//�X�V����
//================================================================================================================================================================
void CObject2D::UpdateCollar()
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//Object2D����
//================================================================================================================================================================
CObject2D* CObject2D::Create(int nPriority)
{
	CObject2D* pCObject2D = new CObject2D(nPriority);
	pCObject2D->Init();
	return pCObject2D;
}