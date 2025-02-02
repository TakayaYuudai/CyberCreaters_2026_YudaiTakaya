//================================================================================================================================================================
//
//フィールド処理[field.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object3D.h"
#include <string>

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************フィールド管理クラス****************************************************************
class CField :public CObject3D
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CField();
	~CField()    override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	static CField* Create(std::string sPath); //Object2D生成

  //-----------------------------------------プライベート----------------------------------------------
private:
	D3DXVECTOR3 m_move;
	float fSize = 3000.f;
};

#endif