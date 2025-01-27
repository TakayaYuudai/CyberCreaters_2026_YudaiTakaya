//================================================================================================================================================================
//
//プレイヤー処理[player3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "character.h"
#include "charge_gage.h"
#include "gage_back.h"
#include "gage_heat.h"
#include "modelparts.h"
#include "oeskill.h"
#include "gear.h"
#include "targetpointer.h"
#include "gage_player_life.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************プレイヤークラス****************************************************************
class CPlayer3D :public CXcharacter
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CPlayer3D();
	~CPlayer3D()    override;
	HRESULT Init()  override;
	void Uninit()   override;
	void Update()   override;
	void Draw()     override;
	CModelParts GetPlayerParts() { return *m_PlayerParts[0];}
	void PlayerDamage(int damage);
	static CPlayer3D* Create();				//Object2D生成

	//チャージ段階識別
	typedef enum
	{
		FIRST = 1,
		SECOND,
		THIRD,
		FORTH,
		FIVE,
		FULLPOWER
	}POWERRANK;

	//-----------------------------------------プライベート----------------------------------------------
private:
	static const int NUM = 19;
	static const int MAX_MOTION = 5;
	static const int MAX_GAGE_BACK = 3;

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

	void Rotation();										             // 回転処理
	bool MoveMent(D3DXVECTOR3& rot, D3DXVECTOR3 pos);                    // 移動処理
	void Charge(D3DXVECTOR3& rot);                                       // ため処理
	void ChargeAtk(D3DXVECTOR3 pos, D3DXVECTOR3& rot);                   // 攻撃処理
	void SearchRot(D3DXVECTOR3& rot, D3DXVECTOR3 pos);                   // 敵の方向に自機を向かせる処理
	void Step(D3DXVECTOR3 rot);                                          // ステップ回避処理
	void DistanceSum(D3DXVECTOR3 pos, D3DXVECTOR3& rot);                 // 攻撃処理
	void OeSkill(D3DXVECTOR3 pos);                                       // オプティマスエネルギー使用処理
	void CameraManagement(D3DXVECTOR3& pos, D3DXVECTOR3& rot);           // カメラ視野モード管理処理
	void AtkManagement(D3DXVECTOR3 &pos, D3DXVECTOR3& rot);              // 攻撃処理全般の管理
	void ChargeAtkManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot);         // チャージ攻撃の管理
	void RushAtk(D3DXVECTOR3 pos, D3DXVECTOR3& rot);                     // 連打攻撃を管理する
	void OverHeatManagement(D3DXVECTOR3 pos);                            // オーバーヒート処理を管理する
	void OeSkillManagement(D3DXVECTOR3 pos);                             // オプティマスエネルギー処理の管理
	void MotionStateManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot);       // モーション管理処理
	void OeSkill_CoolThruster(D3DXVECTOR3 pos);                          // スラスター冷却スキル
	void OeSkill_Repair(D3DXVECTOR3 pos);                                // リペアスキル処理

	//スキル関連のステータスリセット
	void OeSkillStatusrReset(int limittime){
		//タイムリミット
		if (m_nOeSkillTime > limittime) {
			//スキル関連ステータス初期化
			m_bUseOeSkill = false;
			m_bOeSkillBreak = true;
			m_Oeskill_Cool->SkillFlag(true);
			m_nOeSkillTime = NULL;
		}
	}

	//スキル使用後のクールタイム処理
	void OeSkillBreakTime(int limittime) {
		//タイムリミット
		if (m_nOeSkillBreakTime > limittime) {
			//スキル関連ステータス初期化
			m_bOeSkillBreak = false;
			m_Oeskill_Cool->SkillFlag(false);
			m_nOeSkillBreakTime = NULL;
			m_bRecovery = false;
		}
	}

	//スラスター冷却処理
	void CoolThruster(float coolvalue) {
	    m_fHeatSum -= coolvalue;
	    LimitThruster();
	}

	//スラスター増熱処理
	void HeatThruster(float heatvalue) {
		m_fHeatSum += heatvalue;
		LimitThruster();
	}

	//スラスター管理関数
	void LimitThruster() {

		//上限値突破
	   if (m_fHeatSum >= 100.f){
		   m_fHeatSum = 100.f;
	   }

	   //上限値突破
	   else if (m_fHeatSum <= 0.f){
		   m_fHeatSum = 0.f;
	   }
	}

	Charge_Gage* m_ChargeGage;                                //チャージゲージポインター
	CGage_Heat * m_GageHeat;                                  //チャージゲージポインター
	CGage_Player_Life* m_PlayerLifeGage;                      //ライフゲージポインター
	CGage_Back* m_GageBack[MAX_GAGE_BACK];                    //ゲージのバック背景ポインター
	CSpeedgear* m_GearSpeed;                                  //速ギアポインター
	CAtkgear*   m_GearAtk;                                    //殴ギアポインター
	COeSkill_Cool* m_Oeskill_Cool;							  //スラスター冷却装置のポインタ
	COeSkill_Jamming* m_Oeskill_Repair; 					  //カメラジャミングのポインタ
	CTarget_Pointer* m_TargerPnt;                             //ターゲットポインターマークのポインター

	float m_fChargeSum;                                       //現在の溜め状況の最大値
	D3DXVECTOR3 m_OldPos;                                     //オールドポス
	char* m_FileModel[NUM];                                   //ファイル名やります。
	CModelParts* m_PlayerParts[NUM];                          //パーツポインター
	MotionSet m_Motion[NUM];                                  //モーション
	D3DXMATRIX m_mtxWorld;                                    //ワールド変換行列
	int m_nKeyCnt;                                            //現在のキー数
	int m_nFrameCnt;										  //モーションフレームカウンター
	D3DXVECTOR3 m_CameraRot;								  //カメラの角度
	float m_fGav = -10.0f;									  //重力
	bool m_bAtk;											  //攻撃中か判断
	float m_fHeatSum;										  //熱量（オーバーヒートゲージ変数）
	bool m_bFlowEnemMode;                                     //追跡モードフラグ
	D3DXVECTOR3 m_vVelocity;                                  //ステップ回避の方向を記録する変数

	int  m_nStepCnt;                                          //ステップ係数
	bool m_bStepMode;                                         //ステップモード
	bool m_bStepVec;                                          //ステップ方向定めてるか
	D3DXVECTOR3 m_Step;                                       //ステップ時の方向変数
	D3DXVECTOR3 m_move;                                       //ステップ時の方向変数
	bool m_bOverheat;                                         //オーバーヒートしているか

	int  m_nGap;
	int  m_nAtkSum;

	int  m_nAtkTime;
	bool m_bAtkPanchi;

	bool m_bUseOeSkill;                                    //スキルを使用状態
	int  m_nOeSkillTime;                                   //スキル継続時間
	static bool m_bOeSkillBreak;						   //スキル使用後のクールタイム確認
	int  m_nOeSkillBreakTime;                              //スキル使用後のクールタイムカウント

	bool m_bRushAtk;									   //ラッシュ攻撃の確認
	int  m_nRushCoolTime;								   //ラッシュ攻撃の隙間時

	bool m_bRecovery;                                      //回復したか判断

	//プレイヤーステイト
	typedef enum
	{
		NONE = 0,         //待機
		WALK,             //歩く
		CHARGE,           //チャージ
		STEP,             //ステップ回避
		OVERHEAT,         //オーバーヒット状態
	}TYPE;

	TYPE m_MotionSet;

	POWERRANK m_PowerRank;

	void LoadMotion();                                        //モーション初期化
	void LoadParts();                                         //パーツ情報読み込み
	void Motion();											  //モーション処理
	void SetMotion(TYPE g_Motions);							  //モーション変更処理
};

#endif