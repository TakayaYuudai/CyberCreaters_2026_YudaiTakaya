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
#include "player_3d.h"
#include "nova.h"

//================================================================================================================================================================
//�}�N����`
//================================================================================================================================================================
#define MAX_SIZE (1000) //�n�ʂ̔����̃T�C�Y
#define HALFFIELDSIZE (MAX_SIZE * 0.5f) //�n�ʂ̔����̃T�C�Y
#define MAX_MESH_Z (50) //���b�V���t�B�[���hZ���̍ő咸�_��
#define MAX_MESH_X (50) //���b�V���t�B�[���hX���̍ő咷�_��
#define MAX_INDEX  (MAX_MESH_X * MAX_MESH_Z * 2 + 4 * (MAX_MESH_Z - 1)) //�ő�C���f�b�N�X�̐�
#define MAX_POS (MAX_MESH_Z * MAX_MESH_Z)    //�ő咸�_��
#define MAX_PLIMITIB (MAX_INDEX - 2)  //�ő�v���~�e�B�u��

//================================================================================================================================================================
//�O���[�o���ϐ�
//================================================================================================================================================================

///////////////////////////////////////////////////////////////////////////////
//�R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////
CNova::CNova() :CObject(5)
{

}

///////////////////////////////////////////////////////////////////////////////
//�f�X�g���N�^
///////////////////////////////////////////////////////////////////////////////
CNova::~CNova()
{

}

///////////////////////////////////////////////////////////////////////////////
//�����ݒ�
///////////////////////////////////////////////////////////////////////////////
HRESULT CNova::Init()
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    m_rot = { (float)NULL, (float)NULL, (float)NULL };
    m_size = (float)NULL;
    m_fMaxSize = (float)NULL;
    m_sizepluts = (float)NULL;
    m_nAlpha = 255;

    // ���_�o�b�t�@�̐���
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_POS,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &m_pVtxBuff,
        NULL))) {
        return E_FAIL;
    }

    // �e�N�X�`���̐���
    if (FAILED(D3DXCreateTextureFromFile(pDevice,
        "data\\TEXTURE\\nova.png",
        &m_pTexture))) {
        return E_FAIL;
    }

    // �C���f�b�N�X�o�b�t�@�̐���
    if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDEX,
        D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &m_pidxBuffMeshField,
        NULL))) {
        return E_FAIL;
    }

    // �C���f�b�N�X�o�b�t�@�����b�N���ăf�[�^��ݒ�
    WORD* pidx = nullptr;
    if (SUCCEEDED(m_pidxBuffMeshField->Lock(0, 0, (void**)&pidx, 0))) {
        for (int iz = 0; iz < MAX_MESH_Z - 1; iz++) {
            for (int ix = 0; ix < MAX_MESH_X; ix++) {
                // �e�s�̃C���f�b�N�X��ݒ�
                *pidx++ = ix + (iz * MAX_MESH_X);
                *pidx++ = ix + ((iz + 1) * MAX_MESH_X);
            }
            // ���̂̂��߂̃C���f�b�N�X�ڑ�
            if (iz < MAX_MESH_Z - 2) {
                *pidx++ = ((iz + 1) * MAX_MESH_X) + (MAX_MESH_X - 1);
                *pidx++ = (iz + 1) * MAX_MESH_X;
            }
        }
        m_pidxBuffMeshField->Unlock();
    }

    // ���_�o�b�t�@�����b�N���Ē��_�f�[�^��ݒ�
    VERTEX_3D* pVtx = nullptr;
    if (SUCCEEDED(m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0))) {
        for (int iz = 0; iz < MAX_MESH_Z; iz++) {
            for (int ix = 0; ix < MAX_MESH_X; ix++) {
                // �������̊p�x (0 �` 2��)
                float theta = 2.0f * D3DX_PI * ((float)ix / (MAX_MESH_X - 1));
                // �c�����̊p�x (-��/2 �` ��/2)
                float phi = D3DX_PI * ((float)iz / (MAX_MESH_Z - 1)) - D3DX_PI / 2;
                // ���a
                float r = m_size;
                // �f�J���g���W�֕ϊ��i���S�́j
                float x = r * cosf(phi) * cosf(theta);
                float y = r * sinf(phi);
                float z = r * cosf(phi) * sinf(theta);
                // ���_���W��ݒ�
                pVtx[ix + (iz * MAX_MESH_X)].pos = D3DXVECTOR3(x, y, z);
                // �@���x�N�g����ݒ�
                D3DXVECTOR3 normal = D3DXVECTOR3(x, y, z);
                D3DXVec3Normalize(&normal, &normal);
                pVtx[ix + (iz * MAX_MESH_X)].nor = normal;
                // �e�N�X�`�����W��ݒ�
                float u = (float)ix / (MAX_MESH_X - 1);
                float v = (float)iz / (MAX_MESH_Z - 1); // ���S�̂ɍ��킹�� v �l
                pVtx[ix + (iz * MAX_MESH_X)].tex = D3DXVECTOR2(u, v);
                // ���_�J���[��ݒ�
                pVtx[ix + (iz * MAX_MESH_X)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            }
        }
        m_pVtxBuff->Unlock();
    }

    CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_EXPLOSION_SE);

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//�I������
///////////////////////////////////////////////////////////////////////////////
void CNova::Uninit()
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

    if (m_pidxBuffMeshField != nullptr)
    {
        m_pidxBuffMeshField->Release();
        m_pidxBuffMeshField = nullptr;
    }

    Deathflag();
}

///////////////////////////////////////////////////////////////////////////////
//�X�V�����i�S�I�u�W�F�N�g�j
///////////////////////////////////////////////////////////////////////////////
void CNova::Update()
{
    if (CManager::GetInstance()->GetCamera()->GetPlayStay()){
        return;
    }

    if (m_nAlpha <= NULL)
    {
        Uninit();
        return;
    }

    --m_nLife;

    if (m_nLife <= NULL)
    {
        m_nAlpha -= 5;
    }

    m_sizepluts += 0.5f;

    m_size += 0.5f + m_sizepluts;

    m_rot.y += 0.05f;

    if (m_size > m_fMaxSize)
    {
        m_size = m_fMaxSize;
    }


    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // ���_�o�b�t�@�����b�N���Ē��_�f�[�^��ݒ�
    VERTEX_3D* pVtx = nullptr;
    if (SUCCEEDED(m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0))) {
        for (int iz = 0; iz < MAX_MESH_Z; iz++) {
            for (int ix = 0; ix < MAX_MESH_X; ix++) {
                // �������̊p�x (0 �` 2��)
                float theta = 2.0f * D3DX_PI * ((float)ix / (MAX_MESH_X - 1));
                // �c�����̊p�x (-��/2 �` ��/2)
                float phi = D3DX_PI * ((float)iz / (MAX_MESH_Z - 1)) - D3DX_PI / 2;

                // �f�J���g���W�֕ϊ��i���S�́j
                float x = m_size * cosf(phi) * cosf(theta);
                float y = m_size * sinf(phi);
                float z = m_size * cosf(phi) * sinf(theta);
                // ���_���W��ݒ�
                pVtx[ix + (iz * MAX_MESH_X)].pos = D3DXVECTOR3(x, y, z);
                // �@���x�N�g����ݒ�
                D3DXVECTOR3 normal = D3DXVECTOR3(x, y, z);
                D3DXVec3Normalize(&normal, &normal);
                pVtx[ix + (iz * MAX_MESH_X)].nor = normal;
                // �e�N�X�`�����W��ݒ�
                float u = (float)ix / (MAX_MESH_X - 1);
                float v = (float)iz / (MAX_MESH_Z - 1); // ���S�̂ɍ��킹�� v �l
                pVtx[ix + (iz * MAX_MESH_X)].tex = D3DXVECTOR2(u, v);
                // ���_�J���[��ݒ�
                pVtx[ix + (iz * MAX_MESH_X)].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
            }
        }
        m_pVtxBuff->Unlock();
    }

    if (m_nLife > NULL){
        HitPlayer();
    }
}

///////////////////////////////////////////////////////////////////////////////
//�`�揈���i�S�I�u�W�F�N�g�j
///////////////////////////////////////////////////////////////////////////////
void CNova::Draw()
{
    CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
    LPDIRECT3DDEVICE9 RendererDevice = pRenderer->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans;
    float fDown = 0.f;

    // �J�����O�𖳌���
    RendererDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // ���[���h�}�g���b�N�X�̐ݒ�
    D3DXMatrixIdentity(&m_mtxWorldMeshfield);
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxWorldMeshfield, &m_mtxWorldMeshfield, &mtxRot);

    // ���s�ړ��s��ɃI�t�Z�b�g��ǉ����Ĉʒu�𒲐�
    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y + fDown, m_pos.z);
    D3DXMatrixMultiply(&m_mtxWorldMeshfield, &m_mtxWorldMeshfield, &mtxTrans);

    RendererDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshfield);

    // ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@��ݒ�
    RendererDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
    RendererDevice->SetIndices(m_pidxBuffMeshField);
    RendererDevice->SetFVF(FVF_VERTEX_3D);

    // �e�N�X�`���̐ݒ�
    RendererDevice->SetTexture(0, m_pTexture);

    // ���̂̕`��
    RendererDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
        0,
        0,
        MAX_POS,
        0,
        (MAX_MESH_X * 2) * (MAX_MESH_Z - 1));

    // �J�����O�����ɖ߂��i�ʏ��CW��CCW�j
    RendererDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

///////////////////////////////////////////////////////////////////////////////
//��
///////////////////////////////////////////////////////////////////////////////
void CNova::HitPlayer() {
    // �I�u�W�F�N�g���X�g�𑖍�
    CObject* pObject = CObject::GetTop(); // ���X�g�̐擪�I�u�W�F�N�g����J�n

    while (pObject != nullptr)
    {
        CObject::TYPE type = pObject->GetType();

        // �v���C���[�^�C�v�̃I�u�W�F�N�g���ǂ����`�F�b�N
        if (type == CObject::TYPE::PLAYER)
        {
            // �v���C���[�I�u�W�F�N�g�����S�Ƀ_�E���L���X�g
            CPlayer3D* pPlayer = dynamic_cast<CPlayer3D*>(pObject);

            // �_�E���L���X�g������
            if (pPlayer)
            {
                // �v���C���[�p�[�c���
                CModelParts PlayerParts = pPlayer->GetPlayerParts();

                // ����pPOS�ݒ�
                D3DXVECTOR3 HitPlayerPos = { pPlayer->GetPos()->x,
                    pPlayer->GetPos()->y + PlayerParts.GetPartsRadhiusu().y,
                    pPlayer->GetPos()->z };

                D3DXVECTOR3 Radhiusu = {m_size,m_size,m_size};

                // �������Ă��邩���f
                if (CManager::GetInstance()->GetCollision()->HitCircleCollision(m_pos, HitPlayerPos,
                    Radhiusu * 0.45f, PlayerParts.GetPartsRadhiusu() * 0.5f)) {
                    pPlayer->PlayerDamage(10);
                }
                break; // �v���C���[�����������烋�[�v�𔲂���
            }
        }
        // ���̃I�u�W�F�N�g�Ɉړ�
        pObject = pObject->GetNext();
    }
}

///////////////////////////////////////////////////////////////////////////////
//��
///////////////////////////////////////////////////////////////////////////////
CNova* CNova::Create(D3DXVECTOR3 pos,float maxsize,int life)
{
    CNova* pCNova = new CNova();
    pCNova->Init();
    pCNova->m_pos = pos;
    pCNova->m_fMaxSize = maxsize;
    pCNova->m_nLife = life;
    pCNova->SetType(CObject::TYPE::NOVA);
    return pCNova;
}
