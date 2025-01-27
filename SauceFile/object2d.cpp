//================================================================================================================================================================
//
//オブジェクト処理[object.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object2D.h"
#include "manager.h"

//================================================================================================================================================================
//コンストラクタ（自分自身の登録）
//================================================================================================================================================================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CObject2D::~CObject2D()
{

}

//================================================================================================================================================================
//初期設定
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

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
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
	pVtx[0].tex = D3DXVECTOR2(m_fSplitLeft, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fSplitRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_fSplitLeft, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fSplitRight, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CObject2D::Uninit()
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
	Deathflag();
}

//================================================================================================================================================================
//更新処理
//================================================================================================================================================================
void CObject2D::Update()
{
	if (m_pVtxBuff != nullptr)
	{
		//頂点更新処理
		UpdatepVtx();

		//座標更新処理
		UpdateUVtex();

		//Animation処理
		if (m_bRev)
		{
			UpdateAnim();
		}
	}
	//移動値代入
	m_pos += m_move;
}

//================================================================================================================================================================
//描画処理
//================================================================================================================================================================
void CObject2D::Draw()
{
	if (m_bDraw)
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
}

//================================================================================================================================================================
//Object2D座標設定
//================================================================================================================================================================
void CObject2D::SetPos(float x, float y)
{
	m_pos = D3DXVECTOR2(x, y);
}

//================================================================================================================================================================
//位置を返す
//================================================================================================================================================================
D3DXVECTOR2* CObject2D::GetPos()
{
	return &m_pos;
}

//================================================================================================================================================================
//位置を返す
//================================================================================================================================================================
D3DXVECTOR3* CObject2D::GetRot()
{
	return &m_rot;
}

//================================================================================================================================================================
//サイズを返す
//================================================================================================================================================================
D3DXVECTOR2* CObject2D::GetSize()
{
	m_size = D3DXVECTOR2(m_fWidth, m_fHeight);

	return &m_size;
}

//================================================================================================================================================================
//アニメーション設定
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
//アニメーションの更新
//================================================================================================================================================================
void CObject2D::UpdateAnim()
{
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	float fSplitSize = 1.0f / m_fSplit;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	{
		m_nextTime++;

		pVtx[0].tex = D3DXVECTOR2(fSplitSize * (float)(m_nAnimationId + 1.0f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(fSplitSize * (float)m_nAnimationId, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fSplitSize * (float)(m_nAnimationId + 1.0f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fSplitSize * (float)m_nAnimationId, 1.0f);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// アニメーション進行処理
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
//テクスチャの設定
//================================================================================================================================================================
void CObject2D::SetTexture(std::string sPath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//引数のファイルパスを参照してテクスチャ読み込み

	//c_str関数の補足?NULLで終わる文字配列へのポインタを返す(割と便利ですげぇ)
	D3DXCreateTextureFromFile(pDevice, sPath.c_str(), &m_pTexture);
}

//================================================================================================================================================================
//サイズ設定
//================================================================================================================================================================
void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_fHeight = fHeight*2.f;
	m_fWidth = fWidth* 2.f
		;
}

//================================================================================================================================================================
//UVtex座標設定
//================================================================================================================================================================
void CObject2D::SetUVtex(float fSplitLeft, float fSplitRight)
{
	m_fSplitLeft = fSplitLeft;
	m_fSplitRight = fSplitRight;
}

//================================================================================================================================================================
//UVtex座標更新処理
//================================================================================================================================================================
void CObject2D::UpdateUVtex()
{
	VERTEX_2D* pVtx; //頂点情報へのポインタ

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_fSplitLeft, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fSplitRight, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_fSplitLeft, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fSplitRight, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//pVtxの更新
//================================================================================================================================================================
void CObject2D::UpdatepVtx()
{
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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

	UpdateCollar();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
// 円形ゲージのアニメーション処理
//================================================================================================================================================================
void CObject2D::CircleGageAnim(float fGageStatus)
{
//	VERTEX_2D* pVtx;
//
//	// 頂点バッファをロック
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	// ゲージの最大セグメント数 (1周を何分割するか)
//	const int kMaxSegments = 36; // 1周を36分割 (10度刻み)
//
//	// 実際に描画するセグメント数 (fGageStatusに基づく)
//	int activeSegments = static_cast<int>(kMaxSegments * (fGageStatus * 0.01f));
//
//	// 半径
//	float fRadius = m_fWidth * 0.5f; // 幅を基準に設定 (適宜変更可能)
//
//	// 中心点の設定
//	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
//	pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f); // 中心点はテクスチャの中央
//
//	// セグメントごとの角度 (ラジアン)
//	float fSegmentAngle = D3DXToRadian(360.0f / kMaxSegments);
//
//	// 頂点の設定 (中心点 + セグメントごとの頂点)
//	for (int i = 0; i <= activeSegments; ++i)
//	{
//		// 現在の角度
//		float fAngle = fSegmentAngle * i;
//
//		// 円周上の頂点の座標を計算
//		float x = m_pos.x + cosf(fAngle) * fRadius;
//		float y = m_pos.y - sinf(fAngle) * fRadius; // Y軸は反転
//		pVtx[i + 1].pos = D3DXVECTOR3(x, y, 0.0f);
//
//		// テクスチャ座標を計算
//		float u = 0.5f + cosf(fAngle) * 0.5f;
//		float v = 0.5f - sinf(fAngle) * 0.5f; // テクスチャのY軸も反転
//		pVtx[i + 1].tex = D3DXVECTOR2(u, v);
//	}
//
//	// 三角形の構築 (中心点と各セグメントを結ぶ)
//	for (int i = 0; i < activeSegments; ++i)
//	{
//		// セグメントを構成する頂点インデックス
//		int index0 = 0;         // 中心点
//		int index1 = i + 1;     // 現在のセグメントの始点
//		int index2 = i + 2;     // 次のセグメントの終点
//
//		// 三角形を構成 (ここではインデックスを管理する想定で記述)
//		// 実際の描画でインデックスバッファが必要な場合は、別途設定してください。
//		// ex: pIndexBuffer[triIndex++] = {index0, index1, index2};
//	}
//
//	UpdateCollar();
//
//	// 頂点バッファをアンロックする
//	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//現在のポストアニメーション
//================================================================================================================================================================
void CObject2D::GageAnim(float fGageStatus)
{
	VERTEX_2D* pVtx;

	  // 頂点バッファをロック
	  m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	   
	//座標位置割合
	float fWidth = m_fWidth * 2 * 0.01 * fGageStatus;

	//各頂点設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y + m_fHeight, 0.0f);

	//現在のtex座標位置割合
	float TexWidth = 1.0 * 0.01 * fGageStatus;

	//最大値検出
	if (TexWidth > 1.f) {
		TexWidth = 1.f;
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexWidth, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(TexWidth, 1.0f);

	UpdateCollar();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//上から縦にアニメーションする
//================================================================================================================================================================
void CObject2D::UpdateCooldownGauge(float fGageStatus) {

	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//座標位置割合
	float fHeight = m_fHeight * 2 * 0.01 * fGageStatus;

	//各頂点設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, (m_pos.y + m_fHeight * 2.f)  - fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, (m_pos.y + m_fHeight * 2.f)  - fHeight, 0.0f);
														  
	//現在のtex座標位置割合
	float TexfHeight = 1.0 * 0.01 * fGageStatus;

	//最大値検出
	if (TexfHeight > 1.f){
		TexfHeight = 1.f;
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.f,0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f,0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f,TexfHeight);
	pVtx[3].tex = D3DXVECTOR2(1.f,TexfHeight);

	UpdateCollar();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//内側から外側へ
//================================================================================================================================================================
void CObject2D::InsideOutTex(float fGageStatus)
{
	VERTEX_2D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点の座標設定
	float fWidth = m_fWidth * 0.01f * fGageStatus;  // スケーリング
	float fHeight = m_fHeight * 0.01f * fGageStatus; // y座標もスケーリング

	// 位置を中央基準に修正
	float xOffset = fWidth / 2.0f;  // 幅の半分
	float yOffset = fHeight / 2.0f; // 高さの半分

	// スケーリング後の頂点位置を計算
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - xOffset, m_pos.y - yOffset, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + xOffset, m_pos.y - yOffset, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - xOffset, m_pos.y + yOffset, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + xOffset, m_pos.y + yOffset, 0.0f);

	// テクスチャ座標を内側から外側に広げるように計算
	float fTexCenter = 0.5f;  // テクスチャの中心
	float fTexRange = (fGageStatus / 100.0f) * 0.5f; // fGageStatus が 0～100 の範囲で 0～1 にスケール
	float fTexStart = fTexCenter - fTexRange;
	float fTexEnd = fTexCenter + fTexRange;

	// テクスチャ座標の設定
	float fTexVStart = fTexCenter - fTexRange; // y方向の開始位置
	float fTexVEnd = fTexCenter + fTexRange;   // y方向の終了位置

	pVtx[0].tex = D3DXVECTOR2(fTexStart, fTexVStart);
	pVtx[1].tex = D3DXVECTOR2(fTexEnd, fTexVStart);
	pVtx[2].tex = D3DXVECTOR2(fTexStart, fTexVEnd);
	pVtx[3].tex = D3DXVECTOR2(fTexEnd, fTexVEnd);

	UpdateCollar();

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//================================================================================================================================================================
//更新処理
//================================================================================================================================================================
void CObject2D::UpdateCollar()
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(m_nRed, m_nGreen, m_nBlue, m_nAlpha);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================================================================================================================================
//Object2D生成
//================================================================================================================================================================
CObject2D* CObject2D::Create(int nPriority)
{
	CObject2D* pCObject2D = new CObject2D(nPriority);
	pCObject2D->Init();
	return pCObject2D;
}