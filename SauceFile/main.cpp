//================================================================================================================================================================
//
//メイン処理[main.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//インクルード宣言
//================================================================================================================================================================
#include "main.h"
#include "manager.h"

//================================================================================================================================================================
//ライブラリのリンク
//================================================================================================================================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")    //システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必須
#pragma comment(lib,"xinput.lib")	//入力処理に必須

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================
#define CLASS_NAME "WindowClass"     //クラスの名前
#define WINDOW_NAME "PowerOfGear"      //ウインドウの名前（キャプションに表示

//================================================================================================================================================================
//プロトタイプ宣言
//================================================================================================================================================================

//*******************************************デバイス関係****************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
// メイン関数
//================================================================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
    DWORD dwCurrentTime;    // 現在時刻
    DWORD dwExecLastTime;   // 最後に処理した時刻

    WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX),                  // WNDCLASSEXのメモリサイズ
        CS_CLASSDC,                         // ウインドウのスタイル
        WindowProc,                         // ウインドウプロシージャ
        0,                                  // ０にする
        0,                                  // ０にする
        hInstance,                          // インスタンスハンドル
        LoadIcon(NULL, IDI_APPLICATION),    // タスクバーのアイコン
        LoadCursor(NULL, IDC_ARROW),        // マウスカーソル（適切な標準カーソルを選択）
        (HBRUSH)(COLOR_WINDOW + 1),         // クライアント領域の背景色
        NULL,                               // メニューバー
        CLASS_NAME,                         // ウインドウクラスの名前
        LoadIcon(NULL, IDI_APPLICATION)     // ファイルのアイコン
    };

    HWND hWnd;  // ウインドウハンドル
    MSG msg;    // メッセージ構造体
    RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };  // ウインドウのクライアント領域サイズ

    // ウインドウクラスの登録
    if (!RegisterClassEx(&wcex)) {
        return -1; // 登録失敗時終了
    }

    // クライアント領域を指定サイズに調整
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    // ウインドウを生成
    hWnd = CreateWindowEx(
        0,                               // 拡張ウインドウスタイル
        CLASS_NAME,                      // ウインドウクラスの名前
        WINDOW_NAME,                     // ウインドウの名前
        WS_OVERLAPPEDWINDOW,             // ウインドウスタイル
        CW_USEDEFAULT,                   // ウインドウの左上X座標
        CW_USEDEFAULT,                   // ウインドウの左上Y座標
        rect.right - rect.left,          // ウインドウ幅
        rect.bottom - rect.top,          // ウインドウ高さ
        NULL,                            // 親ウインドウハンドル
        NULL,                            // メニューハンドル
        hInstance,                       // インスタンスハンドル
        NULL                             // 作成データ
    );

    if (!hWnd) {
        return -1; // ウインドウ作成失敗
    }

    // CManagerのインスタンス取得
    CManager* pManager = CManager::GetInstance();
    if (!pManager) {
        return -1; // インスタンス生成失敗
    }

    // 初期化処理
    if (FAILED(pManager->Init(hInstance, hWnd, TRUE))) {
        return -1; // 初期化失敗
    }

    // 時間分解能を設定
    timeBeginPeriod(1);
    dwCurrentTime = 0;
    dwExecLastTime = timeGetTime(); // 現在時刻を取得（保存）

    // ウインドウの表示
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // メッセージループ
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
        {
            if (msg.message == WM_QUIT) {
                break; // WM_QUITを受信したらループを抜ける
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 時間管理
            dwCurrentTime = timeGetTime();
            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) // 60FPS相当
            {
                dwExecLastTime = dwCurrentTime;

                // 更新処理
                pManager->Update();

                // 描画処理
                pManager->Draw();
            }
        }
    }

    // 終了処理
    pManager->Uninit();

    // 時間分解能を元に戻す
    timeEndPeriod(1);

    // ウインドウクラスの登録を解除
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    return static_cast<int>(msg.wParam);
}


//================================================================================================================================================================
//ウインドウプロシージャ
//================================================================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	static POINT pos = { 100, 100 };
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	int  nID;
	static HWND hWndEditOutput;

	switch (uMsg)
	{
	case WM_CLOSE:

		nID = MessageBox(hWnd, "終了しちゃうの( ;∀;)？", "Are Yuo Ok?", MB_YESNO | MB_ICONWARNING);

		if (nID == IDYES)
		{
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //0を返さないと終了してしまう
		}
		break;

	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //キーが押された時のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE: //escキーが押された
			nID = MessageBox(hWnd, "終了しちやうの( ;∀;)？", "Are Yuo Ok?", MB_YESNO | MB_ICONWARNING);
			if (nID == IDYES)
			{
				//ウィンドウを破棄する
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}