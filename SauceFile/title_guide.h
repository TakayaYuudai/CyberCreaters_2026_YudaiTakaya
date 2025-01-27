//================================================================================================================================================================
//
//�v���C���[HP�Q�[�W����[player_hp_gage.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _START_BUTTON_H_
#define _START_BUTTON_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "object2D.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�^�C�g���Ǘ��N���X****************************************************************
class CTitle_Guide :public CObject2D
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
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

//********************************************Start�{�^��guide****************************************************************
class CStart_Button :public CTitle_Guide
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CStart_Button();
	~CStart_Button()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CStart_Button* Create(D3DXVECTOR2 pos, float x, float y); //Object2D����
};

//********************************************Start�{�^��guide****************************************************************
class CTitle_Logo :public CTitle_Guide
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CTitle_Logo() {};
	~CTitle_Logo()override {};
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_Logo* Create(D3DXVECTOR2 pos, float x, float y); //Object2D����
	static bool GetSortie() { return m_bSortie; }
private:
	static bool m_bSortie;
};

//********************************************Start�{�^��guide****************************************************************
class CTitle_LogoRight :public CTitle_Guide
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CTitle_LogoRight() {};
	~CTitle_LogoRight()override {};
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_LogoRight* Create(D3DXVECTOR2 pos, float x, float y); //Object2D����
};

//********************************************Start�{�^��guide****************************************************************
class CTitle_Gear :public CTitle_Guide
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CTitle_Gear() {};
	~CTitle_Gear()override {};
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CTitle_Gear* Create(D3DXVECTOR2 pos, float x, float y,bool r , bool m); //Object2D����
private:
	bool m_RotVecCheck;
	bool m_MoovVecChek;
};

////*******************************************�m�F�w�i****************************************************************
//class CConfirmation :public CTitle_Guide
//{
//	//-----------------------------------------�p�u���b�N----------------------------------------------
//public:
//	CConfirmation() {};
//	~CConfirmation()override {};
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CConfirmation* Create(D3DXVECTOR2 pos); //Object2D����
//};
//
////*******************************************�m�F�w�i****************************************************************
//class CBack_Select:public CTitle_Guide
//{
//	//-----------------------------------------�p�u���b�N----------------------------------------------
//public:
//	CBack_Select() {};
//	~CBack_Select()override {};
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CBack_Select* Create(D3DXVECTOR2 pos); //Object2D����
//private:
//	bool m_bCheck;
//};
//
////*******************************************�Q�[���i�s�iYES�j****************************************************************
//class CYes :public CTitle_Guide
//{
//	//-----------------------------------------�p�u���b�N----------------------------------------------
//public:
//	CYes() {};
//	~CYes()override {};
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//	static CYes* Create(D3DXVECTOR2 pos); //Object2D����
//};

#endif