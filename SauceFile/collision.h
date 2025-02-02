//================================================================================================================================================================
//
//当たり判定処理[collision.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "main.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************当たり判定管理クラス****************************************************************
class Ccollision
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	Ccollision();
	~Ccollision();

	//ボックス型の当たり判定（ぶつかりあい）
	int HitBoxCollision(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos,D3DXVECTOR3 objectpos, 
		D3DXVECTOR3 sizemain, D3DXVECTOR3 sizeobject);

	//円形での当たり判定
	bool HitCircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 objectpos, 
		D3DXVECTOR3 sizemain, D3DXVECTOR3 sizeobject);

	//カプセルでの当たり判定
	bool HitCapsuleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 objectpos,
		D3DXVECTOR3 sizemain, D3DXVECTOR3 sizeobject);

	//-----------------------------------------プライベート----------------------------------------------
private:
};

#endif