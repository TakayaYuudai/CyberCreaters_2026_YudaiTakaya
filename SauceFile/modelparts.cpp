//================================================================================================================================================================
//
//�v���C���[����[player3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "modelparts.h"
#include "manager.h"

////================================================================================================================================================================
////�}�N����`
////================================================================================================================================================================

////================================================================================================================================================================
////�O���[�o���ϐ�
////================================================================================================================================================================

//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CModelParts::CModelParts()
{

}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CModelParts::~CModelParts()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CModelParts::Init()
{
	m_pParent = nullptr;

	for (int i = 0; i < 10; i++)
	{
		m_pTexObjectX[i] = nullptr;
	}

	//�p�[�c�T�C�Y��񏉊���
	m_vtxMaxPartsSize = {0.f,0.f,0.f};
	m_vtxMinPartsSize = {0.f,0.f,0.f};
	m_vtxSumPartsSize = {0.f,0.f,0.f};

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CModelParts::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat!= nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	for (int i = 0; i < (int)m_dwNumMat; i++)
	{
		if (m_pTexObjectX[i]!= nullptr)
		{
			m_pTexObjectX[i]->Release();
			m_pTexObjectX[i] = nullptr;
		}
	}
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CModelParts::Draw()
{
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���f���ɍ��킹���e�̏���--------------------------------------------------------------------------

	//�e�s��
	D3DXMATRIX mtxShadow;
	//���ʏ��
	D3DXPLANE plane;
	//���C�g�t����
	D3DXVECTOR4 vecLight;
	//���ʏ�̂P�_�Ɩ@��
	D3DXVECTOR3 pos, nor;

	//���C�g�̋t�����x�N�g���ݒ�
	vecLight = D3DXVECTOR4(200.0f, 200.0f, 200.f, 0.f);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	nor = D3DXVECTOR3(0.f, 1.f, 0.f);

	//�e�s��̏�����
	D3DXMatrixIdentity(&mtxShadow);
	//�@���ƕ��ʏ�̂P�_���畽�ʏ��𐶐�
	D3DXPlaneFromPointNormal(&plane, &pos, &nor);
	//���C�g�ƕ��ʏ�񂩂�e�s����쐬
	D3DXMatrixShadow(&mtxShadow, &vecLight, &plane);


	D3DXMATRIX mtxParent;

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetWorldMatrix();
	}
	else
	{
		RendererDivice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	RendererDivice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	RendererDivice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		RendererDivice->SetMaterial(&pMat[nCntMat].MatD3D);
		//�e�N�X�`���̐ݒ�
		RendererDivice->SetTexture(0, NULL);
		//���f���i�p�[�c�j�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	RendererDivice->SetMaterial(&matDef);
}

//================================================================================================================================================================
//���f���̍ő�l�ƍŏ������߂�
//================================================================================================================================================================
void CModelParts::ModelSizeSum()
{
	int nNumVtx;    //���_��
	DWORD sizeFVF;  //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^

	//���_�����擾���܂�
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//�ő�l�����߂邽�߂̕ϐ�
		D3DXVECTOR3 vtx;

		vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X�ő咸�_���W�̔�r
		if (vtx.x > m_vtxMaxPartsSize.x)
		{
			//���_�����擾
			m_vtxMaxPartsSize.x = vtx.x;
		}

		//X�ŏ����_���W�̔�r
		else if (vtx.x < m_vtxMinPartsSize.x)
		{
			//���_�����擾
			m_vtxMinPartsSize.x = vtx.x;
		}

		//Y�ő咸�_���W�̔�r
		if (vtx.y > m_vtxMaxPartsSize.y)
		{
			//���_�����擾
			m_vtxMaxPartsSize.y = vtx.y;
		}

		//Z�ŏ����_���W�̔�r
		else if (vtx.y < m_vtxMinPartsSize.y)
		{
			//���_�����擾
			m_vtxMinPartsSize.y = vtx.y;
		}

		//Z�ő咸�_���W�̔�r
		if (vtx.z > m_vtxMaxPartsSize.z)
		{
			//���_�����擾
			m_vtxMaxPartsSize.z = vtx.z;
		}

		//Z�ŏ����_���W�̔�r
		else if (vtx.z < m_vtxMinPartsSize.z)
		{
			//���_�����擾
			m_vtxMinPartsSize.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂悤
		pVtxBuff += sizeFVF;
	}

	//�I�u�W�F�N�g�̃T�C�Y�̌v�Z�����܂�
	m_vtxSumPartsSize = m_vtxMaxPartsSize - m_vtxMinPartsSize;

	//���_�o�b�t�@�̃A�����b�N
	m_pMesh->UnlockVertexBuffer();
}

//================================================================================================================================================================
//�v���C���[����
//================================================================================================================================================================
CModelParts* CModelParts::Create(D3DXVECTOR3 pos,const char* apFileName)
{
	CModelParts* pCModelParts = new CModelParts();
	pCModelParts->m_pos = pos;
	pCModelParts->m_rot = { (float)NULL,(float)NULL, (float)NULL };
	pCModelParts->LoadParts(apFileName);
	pCModelParts->Init();
	pCModelParts->m_nId = -1;
	return pCModelParts;
}

//================================================================================================================================================================
//�e�q�ݒ�
//================================================================================================================================================================
void CModelParts::SetParent(CModelParts* pParent)
{
	//if (!(pParent->m_nId == -1))
	{
		m_pParent = pParent;
	}
}

//================================================================================================================================================================
//���f����������
//================================================================================================================================================================
void CModelParts::LoadParts(const char* apFileName)
{
	CRenderer* pRenderer = nullptr;
	pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	D3DXLoadMeshFromX(apFileName,
		D3DXMESH_SYSTEMMEM,
		RendererDivice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh
	);

	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int i = 0; i < (int)m_dwNumMat; i++)
	{
		if (pMat[i].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(RendererDivice,
				pMat[i].pTextureFilename,
				&m_pTexObjectX[i]);
		}
	}
}