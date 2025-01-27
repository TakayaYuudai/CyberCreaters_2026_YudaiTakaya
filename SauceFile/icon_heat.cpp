//================================================================================================================================================================
//
//プレイヤーHPゲージ処理[player_hp_gage.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "icon_heat.h"
#include "icon_circle.h"
#include "manager.h"

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================
#define	BLOCK_WIDE   (17.5f) //ブロックの横半径

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CIcon_Heat::CIcon_Heat() :CObject2D(0)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CIcon_Heat::~CIcon_Heat()
{
}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CIcon_Heat::Init()
{
	CObject2D::Init();
	SetSize(BLOCK_WIDE, BLOCK_WIDE);
	SetTexture("data\\TEXTURE\\icon_heat.png");

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CIcon_Heat::Uninit()
{
	CObject2D::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CIcon_Heat::Update()
{
	CObject2D::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CIcon_Heat::Draw()
{
	CObject2D::Draw();
}

//================================================================================================================================================================
//ブロック生成
//================================================================================================================================================================
CIcon_Heat* CIcon_Heat::Create(D3DXVECTOR2 pos)
{
	CIcon_Heat* pCIcon_Heat = new CIcon_Heat();
	pCIcon_Heat->Init();
	pCIcon_Heat->SetPos(pos.x, pos.y);
	CIcon_Circle::Create(pos, 23.f, 23.f);
	return pCIcon_Heat;
}