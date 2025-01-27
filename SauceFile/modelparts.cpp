//================================================================================================================================================================
//
//プレイヤー処理[player3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "modelparts.h"
#include "manager.h"

////================================================================================================================================================================
////マクロ定義
////================================================================================================================================================================

////================================================================================================================================================================
////グローバル変数
////================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CModelParts::CModelParts()
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CModelParts::~CModelParts()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CModelParts::Init()
{
	m_pParent = nullptr;

	for (int i = 0; i < 10; i++)
	{
		m_pTexObjectX[i] = nullptr;
	}

	//パーツサイズ情報初期化
	m_vtxMaxPartsSize = {0.f,0.f,0.f};
	m_vtxMinPartsSize = {0.f,0.f,0.f};
	m_vtxSumPartsSize = {0.f,0.f,0.f};

	return S_OK;
}

//================================================================================================================================================================
//終了処理
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
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CModelParts::Draw()
{
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;
	//マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	CRenderer* pRenderer = nullptr;
	pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//モデルに合わせた影の処理--------------------------------------------------------------------------

	//影行列
	D3DXMATRIX mtxShadow;
	//平面情報
	D3DXPLANE plane;
	//ライト逆方向
	D3DXVECTOR4 vecLight;
	//平面上の１点と法線
	D3DXVECTOR3 pos, nor;

	//ライトの逆方向ベクトル設定
	vecLight = D3DXVECTOR4(200.0f, 200.0f, 200.f, 0.f);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	nor = D3DXVECTOR3(0.f, 1.f, 0.f);

	//影行列の初期化
	D3DXMatrixIdentity(&mtxShadow);
	//法線と平面上の１点から平面情報を生成
	D3DXPlaneFromPointNormal(&plane, &pos, &nor);
	//ライトと平面情報から影行列を作成
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

	//ワールドマトリックスの設定
	RendererDivice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	RendererDivice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		RendererDivice->SetMaterial(&pMat[nCntMat].MatD3D);
		//テクスチャの設定
		RendererDivice->SetTexture(0, NULL);
		//モデル（パーツ）の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	RendererDivice->SetMaterial(&matDef);
}

//================================================================================================================================================================
//モデルの最大値と最小を求める
//================================================================================================================================================================
void CModelParts::ModelSizeSum()
{
	int nNumVtx;    //頂点数
	DWORD sizeFVF;  //頂点フォーマットのサイズ
	BYTE* pVtxBuff; //頂点バッファへのポインタ

	//頂点数を取得します
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//最大値を求めるための変数
		D3DXVECTOR3 vtx;

		vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X最大頂点座標の比較
		if (vtx.x > m_vtxMaxPartsSize.x)
		{
			//頂点情報を取得
			m_vtxMaxPartsSize.x = vtx.x;
		}

		//X最小頂点座標の比較
		else if (vtx.x < m_vtxMinPartsSize.x)
		{
			//頂点情報を取得
			m_vtxMinPartsSize.x = vtx.x;
		}

		//Y最大頂点座標の比較
		if (vtx.y > m_vtxMaxPartsSize.y)
		{
			//頂点情報を取得
			m_vtxMaxPartsSize.y = vtx.y;
		}

		//Z最小頂点座標の比較
		else if (vtx.y < m_vtxMinPartsSize.y)
		{
			//頂点情報を取得
			m_vtxMinPartsSize.y = vtx.y;
		}

		//Z最大頂点座標の比較
		if (vtx.z > m_vtxMaxPartsSize.z)
		{
			//頂点情報を取得
			m_vtxMaxPartsSize.z = vtx.z;
		}

		//Z最小頂点座標の比較
		else if (vtx.z < m_vtxMinPartsSize.z)
		{
			//頂点情報を取得
			m_vtxMinPartsSize.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進めよう
		pVtxBuff += sizeFVF;
	}

	//オブジェクトのサイズの計算をします
	m_vtxSumPartsSize = m_vtxMaxPartsSize - m_vtxMinPartsSize;

	//頂点バッファのアンロック
	m_pMesh->UnlockVertexBuffer();
}

//================================================================================================================================================================
//プレイヤー生成
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
//親子設定
//================================================================================================================================================================
void CModelParts::SetParent(CModelParts* pParent)
{
	//if (!(pParent->m_nId == -1))
	{
		m_pParent = pParent;
	}
}

//================================================================================================================================================================
//モデル生成処理
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