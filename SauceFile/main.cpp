//================================================================================================================================================================
//
//���C������[main.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//�C���N���[�h�錾
//================================================================================================================================================================
#include "main.h"
#include "manager.h"

//================================================================================================================================================================
//���C�u�����̃����N
//================================================================================================================================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")    //�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�{
#pragma comment(lib,"xinput.lib")	//���͏����ɕK�{

//================================================================================================================================================================
//�}�N����`
//================================================================================================================================================================
#define CLASS_NAME "WindowClass"     //�N���X�̖��O
#define WINDOW_NAME "PowerOfGear"      //�E�C���h�E�̖��O�i�L���v�V�����ɕ\��

//================================================================================================================================================================
//�v���g�^�C�v�錾
//================================================================================================================================================================

//*******************************************�f�o�C�X�֌W****************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//================================================================================================================================================================
//�O���[�o���ϐ�
//================================================================================================================================================================

//================================================================================================================================================================
// ���C���֐�
//================================================================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
    DWORD dwCurrentTime;    // ���ݎ���
    DWORD dwExecLastTime;   // �Ō�ɏ�����������

    WNDCLASSEX wcex = {
        sizeof(WNDCLASSEX),                  // WNDCLASSEX�̃������T�C�Y
        CS_CLASSDC,                         // �E�C���h�E�̃X�^�C��
        WindowProc,                         // �E�C���h�E�v���V�[�W��
        0,                                  // �O�ɂ���
        0,                                  // �O�ɂ���
        hInstance,                          // �C���X�^���X�n���h��
        LoadIcon(NULL, IDI_APPLICATION),    // �^�X�N�o�[�̃A�C�R��
        LoadCursor(NULL, IDC_ARROW),        // �}�E�X�J�[�\���i�K�؂ȕW���J�[�\����I���j
        (HBRUSH)(COLOR_WINDOW + 1),         // �N���C�A���g�̈�̔w�i�F
        NULL,                               // ���j���[�o�[
        CLASS_NAME,                         // �E�C���h�E�N���X�̖��O
        LoadIcon(NULL, IDI_APPLICATION)     // �t�@�C���̃A�C�R��
    };

    HWND hWnd;  // �E�C���h�E�n���h��
    MSG msg;    // ���b�Z�[�W�\����
    RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };  // �E�C���h�E�̃N���C�A���g�̈�T�C�Y

    // �E�C���h�E�N���X�̓o�^
    if (!RegisterClassEx(&wcex)) {
        return -1; // �o�^���s���I��
    }

    // �N���C�A���g�̈���w��T�C�Y�ɒ���
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    // �E�C���h�E�𐶐�
    hWnd = CreateWindowEx(
        0,                               // �g���E�C���h�E�X�^�C��
        CLASS_NAME,                      // �E�C���h�E�N���X�̖��O
        WINDOW_NAME,                     // �E�C���h�E�̖��O
        WS_OVERLAPPEDWINDOW,             // �E�C���h�E�X�^�C��
        CW_USEDEFAULT,                   // �E�C���h�E�̍���X���W
        CW_USEDEFAULT,                   // �E�C���h�E�̍���Y���W
        rect.right - rect.left,          // �E�C���h�E��
        rect.bottom - rect.top,          // �E�C���h�E����
        NULL,                            // �e�E�C���h�E�n���h��
        NULL,                            // ���j���[�n���h��
        hInstance,                       // �C���X�^���X�n���h��
        NULL                             // �쐬�f�[�^
    );

    if (!hWnd) {
        return -1; // �E�C���h�E�쐬���s
    }

    // CManager�̃C���X�^���X�擾
    CManager* pManager = CManager::GetInstance();
    if (!pManager) {
        return -1; // �C���X�^���X�������s
    }

    // ����������
    if (FAILED(pManager->Init(hInstance, hWnd, TRUE))) {
        return -1; // ���������s
    }

    // ���ԕ���\��ݒ�
    timeBeginPeriod(1);
    dwCurrentTime = 0;
    dwExecLastTime = timeGetTime(); // ���ݎ������擾�i�ۑ��j

    // �E�C���h�E�̕\��
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // ���b�Z�[�W���[�v
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
        {
            if (msg.message == WM_QUIT) {
                break; // WM_QUIT����M�����烋�[�v�𔲂���
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // ���ԊǗ�
            dwCurrentTime = timeGetTime();
            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) // 60FPS����
            {
                dwExecLastTime = dwCurrentTime;

                // �X�V����
                pManager->Update();

                // �`�揈��
                pManager->Draw();
            }
        }
    }

    // �I������
    pManager->Uninit();

    // ���ԕ���\�����ɖ߂�
    timeEndPeriod(1);

    // �E�C���h�E�N���X�̓o�^������
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    return static_cast<int>(msg.wParam);
}


//================================================================================================================================================================
//�E�C���h�E�v���V�[�W��
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

		nID = MessageBox(hWnd, "�I�������Ⴄ��( ;��;)�H", "Are Yuo Ok?", MB_YESNO | MB_ICONWARNING);

		if (nID == IDYES)
		{
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;

	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //�L�[�������ꂽ���̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE: //esc�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�������₤��( ;��;)�H", "Are Yuo Ok?", MB_YESNO | MB_ICONWARNING);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������
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