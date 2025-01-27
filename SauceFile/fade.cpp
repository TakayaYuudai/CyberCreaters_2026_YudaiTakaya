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
#include "fade.h"
#include "scene.h"

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================
#define	PLEYER_WIDE   (1280.f * 0.5f)                //プレイヤーの横半径
#define	PLEYER_HEIGHT (SCREEN_HEIGHT * (0.5f * 0.5f))      //プレイヤーの縦半径

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CFade::CFade()
{
}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CFade::~CFade()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CFade::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
		"data\\TEXTURE\\fade.jpg",
		&m_pTexture);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = D3DXVECTOR2(PLEYER_WIDE,0.f - PLEYER_HEIGHT - 100.f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_endpos = D3DXVECTOR2(0.0f, 0.0f);
	m_fWidth = PLEYER_WIDE;
	m_fHeight = PLEYER_HEIGHT + 10.f;

	//頂点座標の指定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CFade::Uninit()
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
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CFade::Update()
{
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bFadeMode = CManager::GetInstance()->GetScene()->GatFadeMode();

	switch (bFadeMode)
	{
		//フェード移行モード
	case false:
	
		//端まで到達してない時加速
		m_move.y = -m_speed;

		if (m_pos.y <= (float)NULL - m_fHeight- 100.f) {
			m_move.y = 0.f;
			CManager::GetInstance()->GetMiddleLeft()->SetRot(0.f);
		}

		break;

		//フェードスタンバイモード
	default:

		//端まで到達してない時加速
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

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CFade::Draw()
{
	CRenderer* pRenderer = nullptr;

	pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//頂点バッファをデータストリームへ設定
	RendererDivice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	RendererDivice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	RendererDivice->SetTexture(0, m_pTexture);

	//ポリゴン描画
	RendererDivice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類
}


//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CFade2::CFade2()
{
}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CFade2::~CFade2()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CFade2::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
		"data\\TEXTURE\\fade.jpg",
		&m_pTexture);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = D3DXVECTOR2(PLEYER_WIDE, SCREEN_HEIGHT + PLEYER_HEIGHT + 100.f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_endpos = D3DXVECTOR2(0.0f, 0.0f);
	m_fWidth = PLEYER_WIDE;
	m_fHeight = PLEYER_HEIGHT + 10.f;

	//頂点座標の指定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CFade2::Uninit()
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
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CFade2::Update()
{
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bFadeMode = CManager::GetInstance()->GetScene()->GatFadeMode();

	switch (bFadeMode)
	{
		//フェード移行モード
	case false:

		//端まで到達してない時加速
		m_move.y = m_speed;

		if (m_pos.y >= SCREEN_HEIGHT + m_fHeight +100.f) {
			m_move.y = 0.f;
		}

		break;

		//フェードスタンバイモード
	default:

		//端まで到達してない時加速
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

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CFade2::Draw()
{
	CRenderer* pRenderer = nullptr;

	pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//頂点バッファをデータストリームへ設定
	RendererDivice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	RendererDivice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	RendererDivice->SetTexture(0, m_pTexture);

	//ポリゴン描画
	RendererDivice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類
}


//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CFadeMiddleLeft::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
		"data\\TEXTURE\\fade_middle.png",
		&m_pTexture);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_fWidth = 100.f;
	m_fHeight = 200.f;
	m_pos = CManager::GetInstance()->GetFade()->GetFadePos();
	m_rot = { 0.f,0.f,0.f };

	//対角線の長さを算出する
	m_fLengthPlayer = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / (float)2;
	//対角線の角度を算出する
	m_fAnglePlayer = atan2f(m_fWidth, m_fHeight);

	//頂点座標の指定
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

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f,0.f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CFadeMiddleLeft::Uninit()
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
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CFadeMiddleLeft::Update()
{
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bFadeMode = CManager::GetInstance()->GetScene()->GatFadeMode();

	m_pos.x = CManager::GetInstance()->GetFade()->GetFadePos().x;
	m_pos.y = CManager::GetInstance()->GetFade()->GetFadePos().y + SCREEN_HEIGHT * 0.25f;

	//頂点座標の指定
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

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CFadeMiddleLeft::Draw()
{
	CRenderer* pRenderer = nullptr;

	pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//頂点バッファをデータストリームへ設定
	RendererDivice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	RendererDivice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	RendererDivice->SetTexture(0, m_pTexture);

	//ポリゴン描画
	RendererDivice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//プリミティブの種類
}