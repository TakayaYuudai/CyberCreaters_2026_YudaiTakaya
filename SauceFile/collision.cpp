//================================================================================================================================================================
//
//当たり判定処理[collision.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "collision.h"
#include "manager.h"

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
Ccollision::Ccollision()
{
}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
Ccollision::~Ccollision()
{

}

//================================================================================================================================================================
//ボックス型の当たり判定（ぶつかり合い）
//================================================================================================================================================================
int Ccollision::HitBoxCollision(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos, D3DXVECTOR3 objectpos, D3DXVECTOR3 sizemain, D3DXVECTOR3 sizeobject)
{
	//判定処理
	if (
		//左の当たり判定
		pos.x + (sizemain.x * 0.5f) > (objectpos.x - (sizeobject.x * 0.5f))
		//右の当たり判定
		&& pos.x - (sizemain.x * 0.5f) < (objectpos.x + (sizeobject.x * 0.5f))
		//奥の当たり判定
		&& pos.z - (sizemain.z * 0.5f) < objectpos.z + (sizeobject.z * 0.5f)
		//手前の当たり判定
		&& pos.z + (sizemain.z * 0.5f) > objectpos.z - (sizeobject.z * 0.5f)
		)
	{
		//侵入が左から
		if (oldpos.x + (sizemain.x * 0.25f) <= objectpos.x - sizeobject.x * 0.5f)
		{
			return 1;
		}

		//侵入が右から
		else if (oldpos.x - (sizemain.x * 0.25f) >= (objectpos.x) + (sizeobject.x * 0.5f))
		{
			return 1;
		}

		//侵入が奥から
		else if (oldpos.z + (sizemain.z * 0.25f) >= (objectpos.z) + (sizeobject.z * 0.5f))
		{
			return 2;
		}

		//侵入が手前から
		else if (oldpos.z - (sizemain.z * 0.25f) <= (objectpos.z) - (sizeobject.z * 0.5f))
		{
			return 2;
		}
	}
	return  NULL;
}

//================================================================================================================================================================
//円形の当たり判定
//================================================================================================================================================================
bool Ccollision::HitCircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 objectpos, D3DXVECTOR3 sizemain, D3DXVECTOR3 sizeobject)
{
	// X軸の距離を計算
	float lengthX = pos.x - objectpos.x;

	// Y軸の距離を計算
	float lengthY = pos.y - objectpos.y;

	// Z軸の距離を計算
	float lengthZ = pos.z - objectpos.z;

	// 中心点間の距離を計算 (3次元空間での距離公式を使用)
	float CenterDistance = sqrtf((lengthX * lengthX) + (lengthZ * lengthZ) + (lengthY * lengthY));

	// それぞれのオブジェクトのサイズを基に、衝突範囲の半径を計算
	// サイズのX、Z、Yを考慮し、Y軸の影響は0.5倍で調整
	float radiuSum = (sizemain.x + sizeobject.x) + (sizemain.z + sizeobject.z) + (sizemain.y + sizeobject.y) * 0.5f;

	// オブジェクト間の距離が半径の合計以下であれば衝突と判定
	if (CenterDistance <= radiuSum) {
		// ヒット判定を返す
		return true;
	}

	// 衝突していない場合はfalseを返す
	return false;
}

