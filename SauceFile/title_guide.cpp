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
#include "title_guide.h"

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================
bool CTitle_Guide::m_bPushStart = false;
bool CTitle_Logo::m_bSortie = false;

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CTitle_Guide::CTitle_Guide():CObject2D(0)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CTitle_Guide::~CTitle_Guide()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CTitle_Guide::Init()
{
	CObject2D::Init();

	if (m_bPushStart){
		m_bPushStart = false;
	}

	m_size = { (float)NULL,(float)NULL };
	
	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CTitle_Guide::Uninit()
{
	CObject2D::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_Guide::Update()
{
	//パッド入力情報
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	if (pJoy->GetTrigger(CInputJoypad::JOYKEY_START) && !m_bPushStart){
		m_bPushStart = true;
	}

	CObject2D::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_Guide::Draw()
{
	CObject2D::Draw();
}

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CStart_Button::CStart_Button()
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CStart_Button::~CStart_Button()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CStart_Button::Init()
{
	CTitle_Guide::Init();

	m_size = { (float)NULL,(float)NULL };

	SetTexture("data\\TEXTURE\\title_guide_start.png");

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CStart_Button::Uninit()
{
	CTitle_Guide::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CStart_Button::Update(){

	const float fRatio = 1.5f;

	if (m_bPushStart && m_size.x > (float)NULL && m_size.y > (float)NULL){
		m_size.x -= 2.f * fRatio;
		m_size.y -= 0.5f* fRatio;
	}

	else if (m_size.x < (float)NULL || m_size.y < (float)NULL){
		m_size = {(float)NULL,(float)NULL };
	}

	if (m_size.x > (float)NULL || m_size.y > (float)NULL){
		SetSize(m_size.x, m_size.y);
	}

	CTitle_Guide::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CStart_Button::Draw()
{
	CTitle_Guide::Draw();
}

//================================================================================================================================================================
//ブロック生成
//================================================================================================================================================================
CStart_Button* CStart_Button::Create(D3DXVECTOR2 pos, float x, float y)
{
	CStart_Button* pCStart_Button = new CStart_Button();
	pCStart_Button->Init();
	pCStart_Button->SetSize(x, y);
	pCStart_Button->m_size = {x,y};
	pCStart_Button->SetPos(pos.x, pos.y);
	return pCStart_Button;
}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CTitle_Logo::Init(){

	CTitle_Guide::Init();

	SetTexture("data\\TEXTURE\\title.png");

	m_bSortie = false;

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CTitle_Logo::Uninit()
{
	CTitle_Guide::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_Logo::Update()
{
	const float fRatio = 1.5f;

	if (m_bPushStart){
		SetMove({-fSeed,0.f});
	}

	float fXpos = GetPos()->x;

	if (fXpos + m_size .x < (float)NULL){
		m_bSortie = true;
	}

	CTitle_Guide::Update();
}


//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_Logo::Draw()
{
	CTitle_Guide::Draw();
}

//================================================================================================================================================================
//ブロック生成
//================================================================================================================================================================
CTitle_Logo* CTitle_Logo::Create(D3DXVECTOR2 pos, float x, float y)
{
	CTitle_Logo* pCTitle_Logo = new CTitle_Logo();
	pCTitle_Logo->Init();
	pCTitle_Logo->SetSize(x, y);
	pCTitle_Logo->m_size = { x,y };
	pCTitle_Logo->SetPos(pos.x, pos.y);
	return pCTitle_Logo;
}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CTitle_LogoRight::Init() {

	CTitle_Guide::Init();

	SetTexture("data\\TEXTURE\\title_right.png");

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CTitle_LogoRight::Uninit()
{
	CTitle_Guide::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_LogoRight::Update()
{
	if (m_bPushStart) {
		SetMove({ fSeed,0.f });
	}

	CTitle_Guide::Update();
}


//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_LogoRight::Draw(){
	CTitle_Guide::Draw();
}

//================================================================================================================================================================
//ブロック生成
//================================================================================================================================================================
CTitle_LogoRight* CTitle_LogoRight::Create(D3DXVECTOR2 pos, float x, float y){

	CTitle_LogoRight* pCTitle_LogoRihgt = new CTitle_LogoRight();
	pCTitle_LogoRihgt->Init();
	pCTitle_LogoRihgt->SetSize(x, y);
	pCTitle_LogoRihgt->m_size = { x,y };
	pCTitle_LogoRihgt->SetPos(pos.x, pos.y);

	return pCTitle_LogoRihgt;
}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CTitle_Gear::Init(){

	CTitle_Guide::Init();

	SetTexture("data\\TEXTURE\\gear.png");

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CTitle_Gear::Uninit()
{
	CTitle_Guide::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_Gear::Update(){

	const float fRotSpeed = m_bPushStart? 0.1f : 0.01f;
	
	if (!m_RotVecCheck){
		SetRotAnim(fRotSpeed);
	}
	else {
		SetRotAnim(-fRotSpeed);
	}

	if (m_bPushStart){

		if (m_MoovVecChek) {
			SetMove({ fSeed,0.f });
		}
		else {
			SetMove({ -fSeed,0.f });
		}
	}

	// 赤設定
	if (m_bPushStart){
		PlusCollar(0, -2, -2);
	}

	CTitle_Guide::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CTitle_Gear::Draw()
{
	CTitle_Guide::Draw();
}

//================================================================================================================================================================
//ブロック生成
//================================================================================================================================================================
CTitle_Gear* CTitle_Gear::Create(D3DXVECTOR2 pos, float x, float y,bool r,bool m)
{
	CTitle_Gear* pCTitle_Gear = new CTitle_Gear();
	pCTitle_Gear->Init();
	pCTitle_Gear->SetSize(x, y);
	pCTitle_Gear->m_size = { x,y };
	pCTitle_Gear->SetPos(pos.x, pos.y);
	pCTitle_Gear->m_RotVecCheck = r;
	pCTitle_Gear->m_MoovVecChek = m;
	return pCTitle_Gear;
}

////================================================================================================================================================================
////初期設定
////================================================================================================================================================================
//HRESULT CBack_Select::Init()
//{
//	CTitle_Guide::Init();
//
//	SetTexture("data\\TEXTURE\\select_back.png");
//
//	m_bCheck = false;
//
//	return S_OK;
//}
//
////================================================================================================================================================================
////終了処理
////================================================================================================================================================================
//void CBack_Select::Uninit()
//{
//	CTitle_Guide::Uninit();
//}
//
////================================================================================================================================================================
////更新処理（全オブジェクト）
////================================================================================================================================================================
//void CBack_Select::Update()
//{
//	//パッド入力情報
//	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();
//
//	const float fScreenRatio = 0.35f;
//	const float fRatio = 4.f;
//
//	D3DXVECTOR2 size = { (float)NULL,(float)NULL };
//	
//	//　それぞれの方向数値を代入
//	if (m_size.x < SCREEN_WIDTH * fScreenRatio){
//		size.x += 2.f* fRatio;
//	}
//
//	if (m_size.y < SCREEN_HEIGHT * fScreenRatio){
//		size.y += 3.f* fRatio;
//	}
//
//	if (size.x == 0.f && size.y == 0.f && !m_bCheck){
//		CConfirmation::Create({ 640.f,250.f });
//	    CYes::Create({ 580.f,500.f });
//		m_bCheck = true;
//	}
//
//	//合計数値代入
//	m_size += size;
//
//	SetSize(m_size.x, m_size.y);
//
//	CTitle_Guide::Update();
//}
//
////================================================================================================================================================================
////描画処理（全オブジェクト）
////================================================================================================================================================================
//void CBack_Select::Draw()
//{
//	CTitle_Guide::Draw();
//}
//
////================================================================================================================================================================
////ブロック生成
////================================================================================================================================================================
//CBack_Select* CBack_Select::Create(D3DXVECTOR2 pos)
//{
//	CBack_Select* pCBack_Select = new CBack_Select();
//	pCBack_Select->Init();
//	pCBack_Select->SetPos(pos.x, pos.y);
//	return pCBack_Select;
//}
//
////================================================================================================================================================================
////初期設定
////================================================================================================================================================================
//HRESULT CConfirmation::Init(){
//
//	CTitle_Guide::Init();
//	SetTexture("data\\TEXTURE\\confirmation.png");
//	SetSize(400.f,100.f);
//	SetCollar(255, 255, 255, 0);
//	return S_OK;
//}
//
////================================================================================================================================================================
////終了処理
////================================================================================================================================================================
//void CConfirmation::Uninit()
//{
//	CTitle_Guide::Uninit();
//}
//
////================================================================================================================================================================
////更新処理（全オブジェクト）
////================================================================================================================================================================
//void CConfirmation::Update(){
//
//	//透明度
//	int nAlpha = GetAlpha();
//
//	if (nAlpha < 255){
//		PlusAlpha(5);
//	}
//
//	CTitle_Guide::Update();
//}
//
////================================================================================================================================================================
////描画処理（全オブジェクト）
////================================================================================================================================================================
//void CConfirmation::Draw()
//{
//	CTitle_Guide::Draw();
//}
//
////================================================================================================================================================================
////ブロック生成
////================================================================================================================================================================
//CConfirmation* CConfirmation::Create(D3DXVECTOR2 pos)
//{
//	CConfirmation* pCConfirmation = new CConfirmation();
//	pCConfirmation->Init();
//	pCConfirmation->SetPos(pos.x, pos.y);
//	return pCConfirmation;
//}
//
////================================================================================================================================================================
////初期設定
////================================================================================================================================================================
//HRESULT CYes::Init()
//{
//	CTitle_Guide::Init();
//	SetTexture("data\\TEXTURE\\yes.png");
//	SetSize(70.f,50.f);
//	SetCollar(255, 255, 255, 0);
//
//	return S_OK;
//}
//
////================================================================================================================================================================
////終了処理
////================================================================================================================================================================
//void CYes::Uninit()
//{
//	CTitle_Guide::Uninit();
//}
//
////================================================================================================================================================================
////更新処理（全オブジェクト）
////================================================================================================================================================================
//void CYes::Update()
//{
//	//パッド入力情報
//	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();
//
//	//透明度
//	int nAlpha = GetAlpha();
//
//	if (nAlpha < 255) {
//		PlusAlpha(5);
//	}
//
//	CTitle_Guide::Update();
//}
//
////================================================================================================================================================================
////描画処理（全オブジェクト）
////================================================================================================================================================================
//void CYes::Draw()
//{
//	CTitle_Guide::Draw();
//}
//
////================================================================================================================================================================
////ブロック生成
////================================================================================================================================================================
//CYes* CYes::Create(D3DXVECTOR2 pos)
//{
//	CYes* pCYes = new CYes();
//	pCYes->Init();
//	pCYes->SetPos(pos.x, pos.y);
//	return pCYes;
//}