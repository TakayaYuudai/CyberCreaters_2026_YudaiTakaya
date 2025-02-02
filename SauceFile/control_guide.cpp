//================================================================================================================================================================
//
//プレイヤーHPゲージ処理[player_hp_gage.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "manager.h"
#include "control_guide.h"

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CControl_Guide::CControl_Guide() :CObject2D(0)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CControl_Guide::~CControl_Guide()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CControl_Guide::Init()
{
	CObject2D::Init();

	m_bPushStart = true;

	m_size = { (float)NULL,(float)NULL };

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CControl_Guide::Uninit()
{
	CObject2D::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CControl_Guide::Update()
{
	//パッド入力情報
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	if (pJoy->GetTrigger(CInputJoypad::JOYKEY_Y)) {
		m_bPushStart = !m_bPushStart;
	}

	CObject2D::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CControl_Guide::Draw()
{
	CObject2D::Draw();
}

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CControl_GuideTex::CControl_GuideTex()
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CControl_GuideTex::~CControl_GuideTex()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CControl_GuideTex::Init()
{
	CControl_Guide::Init();

	m_size = { (float)NULL,(float)NULL };

	SetTexture("data\\TEXTURE\\control.png");

	SetSize((float)NULL, (float)NULL);

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CControl_GuideTex::Uninit()
{
	CControl_Guide::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CControl_GuideTex::Update() {

	const float fRatio = 5.f;
	const D3DXVECTOR2 MaxSize = {400.f,360.f};
	bool bPush = GetStart();

	if (bPush) {

		if (m_size.x < MaxSize.x){
			m_size.x += 2.f * fRatio;
		}
		if (m_size.y < MaxSize.y){
			m_size.y += 1.5f * fRatio;
		}
	}

	if (!bPush) {

		if (m_size.x > 0.f) {
			m_size.x -= 2.f * fRatio;
		}
		if (m_size.y > 0.f) {
			m_size.y -= 1.5f * fRatio;
		}
	}

	SetSize(m_size.x, m_size.y);

	CControl_Guide::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CControl_GuideTex::Draw()
{
	CControl_Guide::Draw();
}

//================================================================================================================================================================
//ブロック生成
//================================================================================================================================================================
CControl_GuideTex* CControl_GuideTex::Create(D3DXVECTOR2 pos)
{
	CControl_GuideTex* pCControl_GuideTex = new CControl_GuideTex();
	pCControl_GuideTex->Init();
	pCControl_GuideTex->SetPos(pos.x, pos.y);
	return pCControl_GuideTex;
}

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CButton_Guide::CButton_Guide()
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CButton_Guide::~CButton_Guide()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CButton_Guide::Init()
{
	CControl_Guide::Init();

	SetTexture("data\\TEXTURE\\button_guide.png");

	SetSize(200.f,50.f);

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CButton_Guide::Uninit()
{
	CControl_Guide::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CButton_Guide::Update() {

	CControl_Guide::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CButton_Guide::Draw()
{
	CControl_Guide::Draw();
}

//================================================================================================================================================================
//ブロック生成
//================================================================================================================================================================
CButton_Guide* CButton_Guide::Create(D3DXVECTOR2 pos)
{
	CButton_Guide* pCButton_Guide = new CButton_Guide();
	pCButton_Guide->Init();
	pCButton_Guide->SetPos(pos.x, pos.y);
	return pCButton_Guide;
}