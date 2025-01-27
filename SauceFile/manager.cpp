//================================================================================================================================================================
//
//マネージャー処理[manager.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//インクルード宣言
//================================================================================================================================================================
#include "manager.h"
#include "object.h"
#include <time.h>

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CManager::CManager()
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CManager::~CManager()
{

}

//================================================================================================================================================================
//初期化関数
//================================================================================================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの生成
	m_pRenderer = new CRenderer();

	m_pRenderer->Init(hInstance, hWnd, bWindow);

	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard();

		//キーボードの初期化処理
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	if (m_joyPad == nullptr)
	{
		m_joyPad = new CInputJoypad();

		//キーボードの初期化処理
		if (FAILED(m_joyPad->Init()))
		{
			return E_FAIL;
		}
	}

	//カメラ生成
	m_pCamera = new CCamera();
	m_pCamera->Init();

	//ライト生成
	m_pLight = new CLight();
	m_pLight->Init();

	//ライト生成
	m_pFade = new CFade();
	m_pFade->Init();

	m_pFade2 = new CFade2();
	m_pFade2->Init();

	//ライト生成
	m_Collision = new Ccollision();

	m_pSound = new CSound();
	m_pSound->InitSound(hWnd);

	m_pMiddleLeft = new CFadeMiddleLeft();
	m_pMiddleLeft->Init();

	CManager::SetMode(CScene::MODE_TITLE);

	//シード値の変更
	srand((int)time(NULL));

	return S_OK;
}

//================================================================================================================================================================
//終了関数
//================================================================================================================================================================
void CManager::Uninit()
{
	CObject::ReleaseAll();

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}


	if (m_joyPad != nullptr)
	{
		m_joyPad->Uninit();
		delete m_joyPad;
		m_joyPad = nullptr;
	}


	if (m_Collision!= nullptr)
	{
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}


	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	if (m_pFade2 != nullptr)
	{
		m_pFade2->Uninit();
		delete m_pFade2;
		m_pFade2 = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pMiddleLeft != nullptr)
	{
		m_pMiddleLeft->Uninit();
		delete m_pMiddleLeft;
		m_pMiddleLeft = nullptr;
	}
}

//================================================================================================================================================================
//更新関数
//================================================================================================================================================================
void CManager::Update()
{
	m_pRenderer->Update();
	m_pKeyboard->Update();
	m_joyPad->Update();
	m_pCamera->Update();
	m_pScene->Update();
	m_pFade->Update();
	m_pFade2->Update();
	m_pMiddleLeft->Update();
}

//================================================================================================================================================================
//更新関数
//================================================================================================================================================================
void CManager::Draw()
{
	m_pRenderer->Draw();
	m_pScene->Draw();
	m_pFade->Draw();
	m_pFade2->Draw();
	m_pMiddleLeft->Draw();
}

//================================================================================================================================================================
//画面遷移生成処理
//================================================================================================================================================================
void CManager::SetMode(CScene::MODE mode)
{
	//終了処理
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	//引数で渡された種類の画面を生成
	m_pScene = CScene::Create(mode);
}
