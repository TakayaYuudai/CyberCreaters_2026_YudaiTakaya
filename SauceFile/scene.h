//================================================================================================================================================================
//
//��ʑJ�ڏ���[scene.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "Pch.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�V�[���Ǘ��N���X****************************************************************
class CScene
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	//��ʂ̎�ފǗ�
	typedef enum
	{
		MODE_TITLE = 0,        //�^�C�g��
		MODE_TUTORIAL,		   //�`���[�g���A��
		MODE_GAME,			   //�Q�[��
		MODE_RESULT,		   //���U���g
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
	void FadeTrigger();//��ʃt�F�[�h�����s����

	void FadeFlag(bool Flag);

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	MODE m_Mode;
	static bool m_bPushFade;		 //�t�F�[�h���[�h���ǂ���
	int m_nFadeCnt;			         //�t�F�[�h�����܂ł̎���
	int m_nFadeMaxTime = 300;
	static bool m_bWinResult;        //�������s�k�����f
};

//********************************************�^�C�g���Ǘ��N���X****************************************************************
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

//********************************************�X�g�[���[�N���X****************************************************************
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

//********************************************�Q�[���Ǘ��N���X****************************************************************
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

//********************************************���U���g�Ǘ��N���X****************************************************************
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
	void WinResult();		//���������ꍇ�̃��U���g
	void LoseResult();		//�s�k�����ꍇ�̃��U���g
};

#endif