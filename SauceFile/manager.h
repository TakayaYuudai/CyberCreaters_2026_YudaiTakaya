//================================================================================================================================================================
//
//マネージャー処理[manager.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "renderer.h"
#include "light.h"
#include "camera.h"
#include "Input.h"
#include "collision.h"
#include "scene.h"
#include "fade.h"
#include "sky.h"
#include "sound.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************マネージャークラス****************************************************************
class CManager
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	CRenderer* GetRenderer() { return m_pRenderer; };       //レンダー
	CLight* GetLight() { return m_pLight; };                //ライト
	CCamera* GetCamera() { return m_pCamera; };             //カメラ
	CInputKeyboard* GetKeyboard() { return m_pKeyboard; };  //カメラ
	Ccollision* GetCollision() { return m_Collision; };     //カメラ
	CInputJoypad* GetPad() { return m_joyPad; };            //カメラ
	CScene* GetScene() { return m_pScene; };                //シーン
	void SetMode(CScene::MODE mode);                        //現在の画面
	CFade* GetFade() { return m_pFade; };                   //フェード1
	CFade2* GetFade2() { return m_pFade2; };                //フェード2
	CSound* GetSound() { return m_pSound; };                //空関係
	CFadeMiddleLeft* GetMiddleLeft() { return m_pMiddleLeft; }

	static CManager* GetInstance()
	{
		static CManager instance; //静的インスタンス
		return &instance;
	}

	//-----------------------------------------プライベート----------------------------------------------
private:
	CRenderer* m_pRenderer;       //レンダラー
	CLight* m_pLight;             //ライト情報
	CCamera* m_pCamera;           //ビュー情報
	CInputKeyboard* m_pKeyboard;  //キーボード
	Ccollision* m_Collision;      //キーボード
	CInputJoypad* m_joyPad;       //キーボード
	CScene* m_pScene;			  //画面遷移関係
	CFade* m_pFade;		    	  //フェード関係
	CFade2* m_pFade2;		   	  //フェード関係
	CSound* m_pSound;             //フェード関係
	CFadeMiddleLeft* m_pMiddleLeft;
};

#endif