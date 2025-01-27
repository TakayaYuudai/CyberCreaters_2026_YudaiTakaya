//================================================================================================================================================================
//
//プレイヤーHPゲージ処理[player_hp_gage.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object2D.h"
#include "objectX.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************プレイヤークラス****************************************************************
class C2dcharacter :public CObject2D
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	C2dcharacter(int nP);
	~C2dcharacter()       override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	void SetMove(D3DXVECTOR2 move) { m_move = move; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
private:
	D3DXVECTOR2 m_move;
	D3DXVECTOR3 m_rot;
};

class CXcharacter:public CObjectX
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CXcharacter(int nP);
	~CXcharacter() override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
	void SetMove(D3DXVECTOR3 move) { m_move = move;}
	void SetRot(D3DXVECTOR3 rot)   { m_rot = rot; }
	void SetLife(int nlife)        { m_nLife = nlife,m_nMaxLife = nlife;}

	//ダメージ処理
	void Damage(int minus) { m_nLife -= minus; 
	                     if (m_nLife <= NULL) Uninit();};
	//回復処理
	void RecoveryLife(int recoveryvalue) { m_nLife += recoveryvalue;
		                 if (m_nLife > m_nMaxLife) m_nLife = m_nMaxLife;}

	void SetUpMove(D3DXVECTOR3 move) { m_move += move; }

	//プレイヤーステイト
	typedef enum
	{
		NONE = 0,         //待機
		ATK,              //ATTACK中
		DAMAGE            //ダメージを受けた状態
	}STATEMODE;

	//ライフ情報を返す
	int GetLife() {
		return m_nLife; };

	//ライフ最大値を返す
	int GetMaxLife() {
		return m_nMaxLife;}

	//移動値を返す
	D3DXVECTOR3 GetMoveMent() { 
		return m_move; };

	//ステイトを返す
	STATEMODE GetState() {
		return m_StateMode; }

	//ステイトを代入
	void SetState(STATEMODE mode){
		m_StateMode = mode;}

private:
	STATEMODE m_StateMode;

	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	int m_nLife;
	int m_nMaxLife;
	int m_nInterval;

	//ステージ制限処理
	void LimitStage(D3DXVECTOR3& pos);
};

#endif