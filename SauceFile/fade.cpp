//================================================================================================================================================================
//
//�v���C���[����[player.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "manager.h"
#include "fade.h"
#include "scene.h"

//================================================================================================================================================================
//�}�N����`
//================================================================================================================================================================
#define	PLEYER_WIDE   (1280.f * 0.5f)                //�v���C���[�̉����a
#define	PLEYER_HEIGHT (SCREEN_HEIGHT * (0.5f * 0.5f))      //�v���C���[�̏c���a

//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CFade::CFade()
{
}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CFade::~CFade()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CFade::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
		"data\\TEXTURE\\fade.jpg",
		&m_pTexture);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = D3DXVECTOR2(PLEYER_WIDE,0.f - PLEYER_HEIGHT - 100.f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_endpos = D3DXVECTOR2(0.0f, 0.0f);
	m_fWidth = PLEYER_WIDE;
	m_fHeight = PLEYER_HEIGHT + 10.f;

	//���_���W�̎w��
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CFade::Uninit()
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
}

//================================================================================================================================================================
//�X�V�����i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CFade::Update()
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bFadeMode = CManager::GetInstance()->GetScene()->GatFadeMode();

	switch (bFadeMode)
	{
		//�t�F�[�h�ڍs���[�h
	case false:
	
		//�[�܂œ��B���ĂȂ�������
		m_move.y = -m_speed;

		if (m_pos.y <= (float)NULL - m_fHeight- 100.f) {
			m_move.y = 0.f;
			CManager::GetInstance()->GetMiddleLeft()->SetRot(0.f);
		}

		break;

		//�t�F�[�h�X�^���o�C���[�h
	default:

		//�[�܂œ��B���ĂȂ�������
		m_move.y = m_speed;

		if (m_pos.y >= SCREEN_HEIGHT * 0.25f) {
			m_move.y = 0.f;
			CManager::GetInstance()->GetMiddleLeft()->SetRotAnim(0.02f);

			if (CManager::GetInstance()->GetMiddleLeft()->GetRot().z >= D3DX_PI * 0.5f){
				CManager::GetInstance()->GetMiddleLeft()->SetRot(D3DX_PI * 0.5f);
			}
		}

		break;
	}

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CFade::Draw()
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


//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CFade2::CFade2()
{
}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CFade2::~CFade2()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CFade2::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
		"data\\TEXTURE\\fade.jpg",
		&m_pTexture);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = D3DXVECTOR2(PLEYER_WIDE, SCREEN_HEIGHT + PLEYER_HEIGHT + 100.f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_endpos = D3DXVECTOR2(0.0f, 0.0f);
	m_fWidth = PLEYER_WIDE;
	m_fHeight = PLEYER_HEIGHT + 10.f;

	//���_���W�̎w��
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CFade2::Uninit()
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
}

//================================================================================================================================================================
//�X�V�����i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CFade2::Update()
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bFadeMode = CManager::GetInstance()->GetScene()->GatFadeMode();

	switch (bFadeMode)
	{
		//�t�F�[�h�ڍs���[�h
	case false:

		//�[�܂œ��B���ĂȂ�������
		m_move.y = m_speed;

		if (m_pos.y >= SCREEN_HEIGHT + m_fHeight +100.f) {
			m_move.y = 0.f;
		}

		break;

		//�t�F�[�h�X�^���o�C���[�h
	default:

		//�[�܂œ��B���ĂȂ�������
		m_move.y = -m_speed;

		if (m_pos.y <= SCREEN_HEIGHT * 0.749f) {
			m_move.y = 0.f;
		}

		break;
	}

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CFade2::Draw()
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


//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CFadeMiddleLeft::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
		"data\\TEXTURE\\fade_middle.png",
		&m_pTexture);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_fWidth = 100.f;
	m_fHeight = 200.f;
	m_pos = CManager::GetInstance()->GetFade()->GetFadePos();
	m_rot = { 0.f,0.f,0.f };

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f,0.f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CFadeMiddleLeft::Uninit()
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
}

//================================================================================================================================================================
//�X�V�����i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CFadeMiddleLeft::Update()
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bFadeMode = CManager::GetInstance()->GetScene()->GatFadeMode();

	m_pos.x = CManager::GetInstance()->GetFade()->GetFadePos().x;
	m_pos.y = CManager::GetInstance()->GetFade()->GetFadePos().y + SCREEN_HEIGHT * 0.25f;

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

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CFadeMiddleLeft::Draw()
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