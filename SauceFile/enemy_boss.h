//================================================================================================================================================================
//
//ボスエネミー処理[enemy_boss.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "character.h"
#include "modelparts.h"
#include "atk_time_effect.h"
#include "enemy_boss_hp_gage.h"
#include "gage_back.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************プレイヤークラス****************************************************************
class CEnemy_Boss :public CXcharacter
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CEnemy_Boss();
	~CEnemy_Boss()  override;
	HRESULT Init()  override;
	void Uninit()   override;
	void Update()   override;
	void Draw()     override;
	CModelParts GetBossParts() { return *m_EnemBossParts[0];}
	static CEnemy_Boss* Create(bool t);				//Object2D生成

  //-----------------------------------------プライベート----------------------------------------------
private:
	int  m_nAtkCnt;       //攻撃体勢時のカウント
	int  m_nStayCnt;      //インターバルカウント
	int  m_nMaxStayCnt;   //最大インターバル時間
	bool m_bAtk;          //現在攻撃するかどうかの判断
	bool m_bTutorial;     //現在Tutorialかどうか

	static const int NUM = 18;

	//キーの構造体
	typedef struct {
		D3DXVECTOR3 Motion_pos;
		D3DXVECTOR3 Motion_rot;
	}Key;

	//キーセット構造体
	typedef struct {
		int FrameRate;
		Key Key[NUM];
	}KeySet;

	//モーションの構造体
	typedef struct {
		int LoopCheck;
		int NumKey;
		KeySet KeySet[NUM];
	}MotionSet;

	D3DXMATRIX m_mtxWorld;                                    //ワールド変換行列
	int m_nKeyCnt;                                            //現在のキー数
	int m_nFrameCnt;										  //モーションフレームカウンター

	char* m_FileModel[NUM];                                   //ファイル名やります。
	CModelParts* m_EnemBossParts[NUM];                        //パーツポインター
	MotionSet m_Motion[NUM];                                  //モーション
	CGage_Enemy_Hp* m_EnemyHp_Gage;                           //体力ゲージのポインター
	CGage_Back* m_GageBack;                                   //ゲージ背景ポインター

	//ボスステイト
	typedef enum
	{
		STAY = NULL,        //待機
		TACKLE,             //タックル
		SNIPER,             //銃撃
		NOVA,               //爆発
		STAN,               //ひるみ状態
		SKILL,              //必殺
		MAX
	}STATE;

	STATE m_MotionSet;  //モーション管理
	STATE m_AtkStay;    //現在の使用中の技の管理

	void Tackle(D3DXVECTOR3 pos, D3DXVECTOR3& rot);
	void Nova(D3DXVECTOR3 pos , D3DXVECTOR3 rot);
	void Sniper(D3DXVECTOR3 pos);

	//void NockBack(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void LoadMotion();                                                                           //モーション初期化
	void LoadParts();                                                                            //パーツ情報読み込み
	void Motion();											                                     //モーション処理
	void SetMotion(STATE g_Motions);							                                 //モーション変更処理
	void DelParts();                                                                             //パーツ情報削除
	
	 //インターバル時間設定
	void SetIntervalTime(int nIntervar) {
		m_nMaxStayCnt = nIntervar;
		m_bAtk = false;
		ShiftAtkState();
	}                                                                                           
	void ShiftAtkState(); // ボスの次の行動を決める
};

#endif