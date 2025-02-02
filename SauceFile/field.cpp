//================================================================================================================================================================
//
//フィールド処理[field.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "field.h"
#include "manager.h"

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CField::CField():CObject3D(2)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CField::~CField()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CField::Init()
{
	CObject3D::Init();

	SetSize(fSize, fSize);

	SetPos(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CField::Uninit()
{
	CObject3D::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CField::Update()
{
	CObject3D::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CField::Draw()
{
	CObject3D::Draw();
}

//================================================================================================================================================================
//フィールド生成
//================================================================================================================================================================
CField* CField::Create(std::string sPath)
{
	CField* pCField = new CField();
	pCField->Init();
	pCField->SetTexture(sPath);
	pCField->SetType(CObject::TYPE::FLOOR);
	return pCField;
}