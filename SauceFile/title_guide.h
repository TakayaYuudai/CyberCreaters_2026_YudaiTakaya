//================================================================================================================================================================
//
//プレイヤーHPゲージ処理[player_hp_gage.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _START_BUTTON_H_
#define _START_BUTTON_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object2D.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************タイトル管理クラス****************************************************************
class CTitle_Guide :public CObject2D
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CTitle_Guide();
	~CTitle_Guide() override;
	HRESULT Init()  override;
	void Uninit()   override;
	void Update()   override;
	void Draw()     override;
	static bool GetStart() { return m_bPushStart; }

protected:
	static bool m_bPushStart;
	D3DXVECTOR2 m_size;
	float fSeed = 4.f;
};

//********************************************Startボタンguide****************************************************************
class CStart_Button :public CTitle_Guide
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CStart_Button();
	~CStart_Button()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CStart_Button* Create(D3DXVECTOR2 pos, float x, float y); //Object2D生成
};

//********************************************Startボタンguide****************************************************************
class CTitle_Logo :public CTitle_Guide
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CTitle_Logo() {};
	~CTitle_Logo()override {};
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_Logo* Create(D3DXVECTOR2 pos, float x, float y); //Object2D生成
	static bool GetSortie() { return m_bSortie; }
private:
	static bool m_bSortie;
};

//********************************************Startボタンguide****************************************************************
class CTitle_LogoRight :public CTitle_Guide
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CTitle_LogoRight() {};
	~CTitle_LogoRight()override {};
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_LogoRight* Create(D3DXVECTOR2 pos, float x, float y); //Object2D生成
};

//********************************************Startボタンguide****************************************************************
class CTitle_Gear :public CTitle_Guide
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CTitle_Gear() {};
	~CTitle_Gear()override {};
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_Gear* Create(D3DXVECTOR2 pos, float x, float y,bool r , bool m); //Object2D生成
private:
	bool m_RotVecCheck;
	bool m_MoovVecChek;
};

////*******************************************確認背景****************************************************************
//class CConfirmation :public CTitle_Guide
//{
//	//-----------------------------------------パブリック----------------------------------------------
//public:
//	CConfirmation() {};
//	~CConfirmation()override {};
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CConfirmation* Create(D3DXVECTOR2 pos); //Object2D生成
//};
//
////*******************************************確認背景****************************************************************
//class CBack_Select:public CTitle_Guide
//{
//	//-----------------------------------------パブリック----------------------------------------------
//public:
//	CBack_Select() {};
//	~CBack_Select()override {};
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CBack_Select* Create(D3DXVECTOR2 pos); //Object2D生成
//private:
//	bool m_bCheck;
//};
//
////*******************************************ゲーム進行（YES）****************************************************************
//class CYes :public CTitle_Guide
//{
//	//-----------------------------------------パブリック----------------------------------------------
//public:
//	CYes() {};
//	~CYes()override {};
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CYes* Create(D3DXVECTOR2 pos); //Object2D生成
//};

#endif