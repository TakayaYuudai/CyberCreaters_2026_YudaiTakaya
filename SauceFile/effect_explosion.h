//================================================================================================================================================================
//
//3D弾処理[bullet3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _EFFECT_EXPLOSION_H_
#define _EFFECT_EXPLOSION_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "billboard.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************バレット3Dクラス****************************************************************
class CExplosion_Effect :public CBillboard
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CExplosion_Effect();
	~CExplosion_Effect()  override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	static CExplosion_Effect* Create(D3DXVECTOR3 pos);

private:
	int  m_nLife;
};

#endif