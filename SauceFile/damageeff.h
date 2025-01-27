//================================================================================================================================================================
//
//プレイヤーHPゲージ処理[player_hp_gage.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _DAMAGE_EFF_H_
#define _DAMAGE_EFF_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object2D.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************プレイヤークラス****************************************************************
class CDamage_Eff :public CObject2D
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CDamage_Eff();
	~CDamage_Eff()     override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	static CDamage_Eff* Create(); //Object2D生成
private:
	int m_nLife;
};

#endif