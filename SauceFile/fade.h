//================================================================================================================================================================
//
//�v���C���[����[title.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _FADE_H_
#define _FADE_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "Pch.h"


//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************���t�gfade****************************************************************
class CFade
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CFade();
	~CFade();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR2 GetFadePos() { return m_pos; };

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_move;
	D3DXVECTOR2 m_endpos;
	float m_fWidth;
	float m_fHeight;
	float m_speed = 6.f;
};

//********************************************���C�gfade****************************************************************
class CFade2
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CFade2();
	~CFade2();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	D3DXVECTOR2 GetFadeDownPos() { return m_pos; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_move;
	D3DXVECTOR2 m_endpos;
	float m_fWidth;
	float m_fHeight;
	float m_speed = 6.f;
};

//********************************************���C�gfade****************************************************************
class CFadeMiddleLeft
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
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
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
	D3DXVECTOR2 m_pos;
	D3DXVECTOR3 m_rot;
	float m_fLengthPlayer;
	float m_fAnglePlayer;
	float m_fWidth;
	float m_fHeight;
};


#endif