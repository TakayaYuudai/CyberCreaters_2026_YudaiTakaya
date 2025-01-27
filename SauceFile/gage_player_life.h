//================================================================================================================================================================
//
//プレイヤーヒートゲージ処理[gage_heat.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _GAGE_PLAYER_LIFE_H_
#define _GAGE_PLAYER_LIFE_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object2D.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************プレイヤークラス****************************************************************
class CGage_Player_Life :public CObject2D
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CGage_Player_Life();
	~CGage_Player_Life() override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	static CGage_Player_Life* Create(); //Object2D生成
};
#endif