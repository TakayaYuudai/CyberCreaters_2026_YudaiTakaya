//================================================================================================================================================================
//
//プレイヤー処理[player3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _TITLE_PLAYER3D_H_
#define _TITLE_PLAYER3D_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "character.h"
#include "modelparts.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************プレイヤークラス****************************************************************
class CPlayer_Title :public CXcharacter
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CPlayer_Title();
	~CPlayer_Title()    override;
	HRESULT Init()  override;
	void Uninit()   override;
	void Update()   override;
	void Draw()     override;
	static CPlayer_Title* Create();				//Object2D生成

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

	CModelParts* m_PlayerParts[NUM];                          //パーツポインター

	//プレイヤーステイト
	typedef enum
	{
		NONE = 0,         //待機
		WALK,             //歩く
		CHARGE,           //チャージ
		STEP,             //ステップ回避
		OVERHEAT,         //オーバーヒット状態
	}TYPE;

	D3DXMATRIX m_mtxWorld;                                    //ワールド変換行列
	MotionSet m_Motion[NUM];                                  //モーション
	int m_nKeyCnt;                                            //現在のキー数
	int m_nFrameCnt;										  //モーションフレームカウンター
	TYPE m_MotionSet;
	char* m_FileModel[NUM];                                   //ファイル名やります。
	D3DXVECTOR3 m_CameraRot;
	D3DXVECTOR3 m_CameraPos;
	void LoadMotion();                                        //モーション初期化
	void LoadParts();                                         //パーツ情報読み込み
	void Motion();											  //モーション処理
	void SetMotion(TYPE g_Motions);							  //モーション変更処理
};

#endif