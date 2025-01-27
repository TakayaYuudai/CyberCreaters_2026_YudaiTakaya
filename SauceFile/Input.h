//================================================================================================================================================================
//
//入力受け付け処理[Input.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "main.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================
 
//********************************************入力基底クラス****************************************************************
class CInput
{
public:
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;//端末ごとに
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static const int NUM_KEY_MAX = 256; //テクスチャの分割数
};


class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;//端末ごとに
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
private:
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
	BYTE m_aKeyState[NUM_KEY_MAX]; //キーボードのプレス情報
};

//ジョイパッド入力
class CInputJoypad : public CInput
{
public:

	//定数
	static const int SPEED_KEY = 14;
	static const int JOYPAD_DEADZONE = 1;

	//キーの種類
	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_LB,
		JOYKEY_RB,
		JOYKEY_LT,
		JOYKEY_RT,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	//スティックの番号
	typedef enum
	{
		STICKTYPE_LEFT = 0, // 左スティック
		STICKTYPE_RIGHT,	// 右スティック
		STICKTYPE_MAX
	}STICKTYPE;

	//スティックの方向
	typedef enum
	{
		STICKANGLE_UP = 0, // 上
		STICKANGLE_DOWN,   // 下
		STICKANGLE_LEFT,   // 左
		STICKANGLE_RIGHT,  // 右
		STICKANGLE_MAX,
	}STICKANGLE;

	//スティックの入力情報
	typedef struct
	{
		float afTplDiameter[STICKTYPE_MAX];                      // スティックの倒し具合
		float afAngle[STICKTYPE_MAX];                            // スティックの角度
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // スティックの方向プレス情報
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向トリガー情報
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // スティックの方向リピート情報
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向リリース情報
	}STICKINPUT;

	//基本の処理
	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(void);
	void Uninit() override;
	void Update() override;
	void UpdateStick(XINPUT_STATE* xinput); //スティックの更新処理

	//キーの入力状態を返す関数
	bool GetPress(JOYKEY key);		//プレス状態取得
	bool GetTrigger(JOYKEY key);	//トリガー状態を取得
	bool GetRepeate(JOYKEY key);	//リピート状態を取得
	D3DXVECTOR2 GetLInputState(); //コントローラーの入力情報の取得
	D3DXVECTOR2 GetRInputState(); //コントローラーの入力情報の取得
	STICKINPUT GetStick();			//スティックの情報を取得
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

	D3DXVECTOR2 GetLTrigger() { return m_LTrigger; };
	D3DXVECTOR2 GetRTrigger() { return m_RTrigger; };

private:
	//メンバ関数
	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos); //2点の角度を求める関数

	//メンバ変数
	BYTE m_aKeyState[NUM_KEY_MAX];						//キーの状態
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//キーの状態(トリガー)
	int m_KeyPressCount;							//キーを押してる時間のカウント
	int m_JoyKeyPressCount;							//キーを押してる時間のカウント
	WORD m_joykeyState;								//ジョイパッドのプレス情報
	WORD m_joykeyStateTrigger;						//ジョイパッドのトリガー情報
	WORD m_joykeyStateRelease;						//ジョイパッドのリリース情報
	WORD m_joykeyStateRepeat;						//ジョイパッドのリピート情報
	int m_Time;										//時間を計る
	WORD m_Strength;								// 振動の強さ (0 ～ 65535)
	D3DXVECTOR3 m_joykeyStickPos;					// スティックの傾き
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX];	//スティックの入力情報
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
	STICKINPUT m_stick;								//スティックの入力情報

	D3DXVECTOR2 m_LInput;							// 入力情報
	D3DXVECTOR2 m_RInput;							// 入力情報

	D3DXVECTOR2 m_LTrigger;
	D3DXVECTOR2 m_RTrigger;

	XINPUT_STATE m_joykeyCurrentTime;				// コントローラーの現在の時間
	XINPUT_STATE m_joykeyExecLastTime;				// コントローラーの最後に真を返した時間
	XINPUT_STATE m_joykeyInput;						// コントローラーの入力情報
	XINPUT_VIBRATION m_joykeyMoter;					// コントローラーのモーター
	WORD m_Button;									//ボタンの判定
	WORD m_OldButton;								//古いボタンの判定
};

#endif