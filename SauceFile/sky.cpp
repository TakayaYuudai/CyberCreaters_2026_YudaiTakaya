//================================================================================================================================================================
//
//プレイヤー処理[player.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "manager.h"
#include "sky.h"

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================
#define MAX_SIZE (8500) //地面の半分のサイズ
#define HALFFIELDSIZE (MAX_SIZE * 0.5f) //地面の半分のサイズ
#define MAX_MESH_Z (50) //メッシュフィールドZ軸の最大頂点数
#define MAX_MESH_X (50) //メッシュフィールドX軸の最大長点数
#define MAX_INDEX  (MAX_MESH_X * MAX_MESH_Z * 2 + 4 * (MAX_MESH_Z - 1)) //最大インデックスの数
#define MAX_POS (MAX_MESH_Z * MAX_MESH_Z)    //最大頂点数
#define MAX_PLIMITIB (MAX_INDEX - 2)  //最大プリミティブ数

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CSky::CSky():CObject(0)
{
}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CSky::~CSky()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CSky::Init()
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    m_rot = {(float)NULL,(float)NULL,(float)NULL};

    // 頂点バッファの生成
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_POS,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &m_pVtxBuff,
        NULL))) {
        return E_FAIL;
    }
    // テクスチャの生成
    if (FAILED(D3DXCreateTextureFromFile(pDevice,
        "data\\TEXTURE\\back.png",
        &m_pTexture))) {
        return E_FAIL;
    }
    // インデックスバッファの生成
    if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDEX,
        D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &m_pidxBuffMeshField,
        NULL))) {
        return E_FAIL;
    }
    // インデックスバッファをロックしてデータを設定
    WORD* pidx = nullptr;
    if (SUCCEEDED(m_pidxBuffMeshField->Lock(0, 0, (void**)&pidx, 0))) {
        for (int iz = 0; iz < MAX_MESH_Z - 1; iz++) {
            for (int ix = 0; ix < MAX_MESH_X; ix++) {
                // 各行のインデックスを設定
                *pidx++ = ix + (iz * MAX_MESH_X);
                *pidx++ = ix + ((iz + 1) * MAX_MESH_X);
            }
            // ストリップ接続用のデグレードインデックス
            if (iz < MAX_MESH_Z - 2) {
                *pidx++ = ((iz + 1) * MAX_MESH_X) + (MAX_MESH_X - 1);
                *pidx++ = (iz + 1) * MAX_MESH_X;
            }
        }
        m_pidxBuffMeshField->Unlock();
    }
    // 頂点バッファをロックして頂点データを設定
    VERTEX_3D* pVtx = nullptr;
    if (SUCCEEDED(m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0))) {
        for (int iz = 0; iz < MAX_MESH_Z; iz++) {
            for (int ix = 0; ix < MAX_MESH_X; ix++) {
                // 横方向の角度 (0 ～ 2π)
                float theta = 2.0f * D3DX_PI * ((float)ix / (MAX_MESH_X - 1));
                // 縦方向の角度 (0 ～ π/2)
                float phi = D3DX_PI / 2.0f * ((float)iz / (MAX_MESH_Z - 1));
                // 半径
                float r = HALFFIELDSIZE;
                // デカルト座標へ変換（上半分のみ）
                float x = r * sinf(phi) * cosf(theta);
                float y = r * cosf(phi);
                float z = r * sinf(phi) * sinf(theta);
                // 頂点座標を設定
                pVtx[ix + (iz * MAX_MESH_X)].pos = D3DXVECTOR3(x, y, z);
                // 法線ベクトルを設定
                D3DXVECTOR3 normal = D3DXVECTOR3(x, y, z);
                D3DXVec3Normalize(&normal, &normal);
                pVtx[ix + (iz * MAX_MESH_X)].nor = normal;
                // テクスチャ座標を設定
                float u = (float)ix / (MAX_MESH_X - 1);
                float v = (float)iz / (MAX_MESH_Z - 1); // 上半分の球に合わせた v 値
                pVtx[ix + (iz * MAX_MESH_X)].tex = D3DXVECTOR2(u, v);
                // 頂点カラーを設定
                pVtx[ix + (iz * MAX_MESH_X)].col = D3DCOLOR_XRGB(255, 255, 255);
            }
        }
        m_pVtxBuff->Unlock();
    }
    return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CSky::Uninit()
{
	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//頂点バッファの破棄
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
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CSky::Update()
{
    m_rot.y += 0.001f;
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CSky::Draw()
{
    CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
    LPDIRECT3DDEVICE9 RendererDevice = pRenderer->GetDevice();
    D3DXMATRIX mtxRot, mtxTrans;
    float fDown = -500.f;

        // ワールドマトリックスの設定
        D3DXMatrixIdentity(&m_mtxWorldMeshfield);
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
        D3DXMatrixMultiply(&m_mtxWorldMeshfield, &m_mtxWorldMeshfield, &mtxRot);
        // 平行移動行列にオフセットを追加してドームの位置を下げる
        D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y + fDown, m_pos.z);
        D3DXMatrixMultiply(&m_mtxWorldMeshfield, &m_mtxWorldMeshfield, &mtxTrans);
        RendererDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshfield);
        // 頂点バッファとインデックスバッファを設定
        RendererDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
        RendererDevice->SetIndices(m_pidxBuffMeshField);
        RendererDevice->SetFVF(FVF_VERTEX_3D);
        // テクスチャの設定
        RendererDevice->SetTexture(0, m_pTexture);
        // ドームの描画
        RendererDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
            0,
            0,
            MAX_POS,
            0,
            (MAX_MESH_X * 2) * (MAX_MESH_Z - 1));
}

//================================================================================================================================================================
//生成
//================================================================================================================================================================
CSky* CSky::Create()
{
    CSky* pCSky = new CSky();
    pCSky->Init();
    pCSky->SetType(CObject::TYPE::NONE);
    return pCSky;
}