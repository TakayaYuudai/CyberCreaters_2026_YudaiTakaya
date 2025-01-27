//================================================================================================================================================================
//
//プレイヤー処理[title.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _FADE_H_
#define _FADE_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "Pch.h"


//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************レフトfade****************************************************************
class CFade
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CFade();
	~CFade();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR2 GetFadePos() { return m_pos; };

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_move;
	D3DXVECTOR2 m_endpos;
	float m_fWidth;
	float m_fHeight;
	float m_speed = 6.f;
};

//********************************************ライトfade****************************************************************
class CFade2
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CFade2();
	~CFade2();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR2 GetFadeDownPos() { return m_pos; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_move;
	D3DXVECTOR2 m_endpos;
	float m_fWidth;
	float m_fHeight;
	float m_speed = 6.f;
};

//********************************************ライトfade****************************************************************
class CFadeMiddleLeft
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CFadeMiddleLeft() {};
	~CFadeMiddleLeft() {};
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void SetRot(float r) { m_rot.z = r; }
	void SetRotAnim(float r) { m_rot.z += r; }
	D3DXVECTOR3 GetRot() { return m_rot; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
	D3DXVECTOR2 m_pos;
	D3DXVECTOR3 m_rot;
	float m_fLengthPlayer;
	float m_fAnglePlayer;
	float m_fWidth;
	float m_fHeight;
};


#endif