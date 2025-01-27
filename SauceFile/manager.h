//================================================================================================================================================================
//
//�}�l�[�W���[����[manager.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//================================================================================================================================================================
//���C�u���������N
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
//�N���X��`
//================================================================================================================================================================

//********************************************�}�l�[�W���[�N���X****************************************************************
class CManager
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	CRenderer* GetRenderer() { return m_pRenderer; };       //�����_�[
	CLight* GetLight() { return m_pLight; };                //���C�g
	CCamera* GetCamera() { return m_pCamera; };             //�J����
	CInputKeyboard* GetKeyboard() { return m_pKeyboard; };  //�J����
	Ccollision* GetCollision() { return m_Collision; };     //�J����
	CInputJoypad* GetPad() { return m_joyPad; };            //�J����
	CScene* GetScene() { return m_pScene; };                //�V�[��
	void SetMode(CScene::MODE mode);                        //���݂̉��
	CFade* GetFade() { return m_pFade; };                   //�t�F�[�h1
	CFade2* GetFade2() { return m_pFade2; };                //�t�F�[�h2
	CSound* GetSound() { return m_pSound; };                //��֌W
	CFadeMiddleLeft* GetMiddleLeft() { return m_pMiddleLeft; }

	static CManager* GetInstance()
	{
		static CManager instance; //�ÓI�C���X�^���X
		return &instance;
	}

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	CRenderer* m_pRenderer;       //�����_���[
	CLight* m_pLight;             //���C�g���
	CCamera* m_pCamera;           //�r���[���
	CInputKeyboard* m_pKeyboard;  //�L�[�{�[�h
	Ccollision* m_Collision;      //�L�[�{�[�h
	CInputJoypad* m_joyPad;       //�L�[�{�[�h
	CScene* m_pScene;			  //��ʑJ�ڊ֌W
	CFade* m_pFade;		    	  //�t�F�[�h�֌W
	CFade2* m_pFade2;		   	  //�t�F�[�h�֌W
	CSound* m_pSound;             //�t�F�[�h�֌W
	CFadeMiddleLeft* m_pMiddleLeft;
};

#endif