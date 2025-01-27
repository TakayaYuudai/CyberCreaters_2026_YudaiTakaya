//================================================================================================================================================================
//
//モデルパーツだよ[modelparts.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "renderer.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************マネージャークラス****************************************************************
class CModelParts
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CModelParts();
	~CModelParts();
	HRESULT Init();
	void Uninit();
	void Draw();
	static CModelParts* Create(D3DXVECTOR3 pos, const char* apFileName);

	void LoadParts(const char * apFileName);

	D3DXVECTOR3& GetPos() { return m_pos;};

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
	
	D3DXVECTOR3& GetRot() { return m_rot; };
	
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };

	void SetDeffalt() { m_DefPos = m_pos; 
	                    m_DefRot = m_rot; };

	D3DXVECTOR3 GetPartsRadhiusu() { return m_vtxSumPartsSize;};

	void SetId(int Id) { m_nId = Id; };

	void SetParent(CModelParts* pParent);

	void ModelSizeSum();

	D3DXVECTOR3 GetDefPos() { return m_DefPos; };
	D3DXVECTOR3 GetDefRot() { return m_DefRot; };
	D3DXMATRIX& GetWorldMatrix() { return m_mtxWorld;};

	//-----------------------------------------プライベート----------------------------------------------
private:
	LPDIRECT3DTEXTURE9 m_pTexObjectX[10];
	LPD3DXMESH m_pMesh;
	LPD3DXBUFFER m_pBuffMat;
	DWORD m_dwNumMat;
	D3DXVECTOR3 m_vtxMinModel, m_vtxMaxModel;

	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_DefPos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_DefRot;
	D3DXVECTOR3 m_vtxMaxPartsSize;
	D3DXVECTOR3 m_vtxMinPartsSize;
	D3DXVECTOR3 m_vtxSumPartsSize;

	int m_nId;
	CModelParts* m_pParent;
};

#endif