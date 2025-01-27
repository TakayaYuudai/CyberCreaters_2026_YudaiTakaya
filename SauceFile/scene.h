//================================================================================================================================================================
//
//画面遷移処理[scene.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "Pch.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************シーン管理クラス****************************************************************
class CScene
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	//画面の種類管理
	typedef enum
	{
		MODE_TITLE = 0,        //タイトル
		MODE_TUTORIAL,		   //チュートリアル
		MODE_GAME,			   //ゲーム
		MODE_RESULT,		   //リザルト
		MODE_MAX,
	}MODE;

	CScene();
	virtual ~CScene();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	int GetFadeTime() { return m_nFadeCnt; };
	bool GatFadeMode();
	static bool GetDidWinResult() { return m_bWinResult; }
	static CScene* Create(MODE mode);
	int GetFadeMaxTime() { return m_nFadeMaxTime; };
	MODE GetMode() { return m_Mode; };
	void SetLodeResult(bool flag) { m_bWinResult = flag; }
	void FadeTrigger();//画面フェードを実行する

	void FadeFlag(bool Flag);

	//-----------------------------------------プライベート----------------------------------------------
private:
	MODE m_Mode;
	static bool m_bPushFade;		 //フェードモードかどうか
	int m_nFadeCnt;			         //フェード完了までの時間
	int m_nFadeMaxTime = 300;
	static bool m_bWinResult;        //勝利か敗北か判断
};

//********************************************タイトル管理クラス****************************************************************
class CTitle :public CScene
{

public:
	CTitle();
	~CTitle()      override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
};

//********************************************ストーリークラス****************************************************************
class CTutorial :public CScene
{
public:
	CTutorial();
	~CTutorial()      override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
};

//********************************************ゲーム管理クラス****************************************************************
class CGame :public CScene
{
public:
	CGame();
	~CGame()       override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
};

//********************************************リザルト管理クラス****************************************************************
class CResult :public CScene
{
public:
	CResult();
	~CResult()     override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
private:
	void WinResult();		//勝利した場合のリザルト
	void LoseResult();		//敗北した場合のリザルト
};

#endif