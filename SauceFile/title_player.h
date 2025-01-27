//================================================================================================================================================================
//
//�v���C���[����[player3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _TITLE_PLAYER3D_H_
#define _TITLE_PLAYER3D_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "character.h"
#include "modelparts.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�v���C���[�N���X****************************************************************
class CPlayer_Title :public CXcharacter
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CPlayer_Title();
	~CPlayer_Title()    override;
	HRESULT Init()  override;
	void Uninit()   override;
	void Update()   override;
	void Draw()     override;
	static CPlayer_Title* Create();				//Object2D����

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	static const int NUM = 19;
	static const int MAX_MOTION = 5;
	static const int MAX_GAGE_BACK = 3;

	//�L�[�̍\����
	typedef struct {
		D3DXVECTOR3 Motion_pos;
		D3DXVECTOR3 Motion_rot;
	}Key;

	//�L�[�Z�b�g�\����
	typedef struct {
		int FrameRate;
		Key Key[NUM];
	}KeySet;

	//���[�V�����̍\����
	typedef struct {
		int LoopCheck;
		int NumKey;
		KeySet KeySet[NUM];
	}MotionSet;

	CModelParts* m_PlayerParts[NUM];                          //�p�[�c�|�C���^�[

	//�v���C���[�X�e�C�g
	typedef enum
	{
		NONE = 0,         //�ҋ@
		WALK,             //����
		CHARGE,           //�`���[�W
		STEP,             //�X�e�b�v���
		OVERHEAT,         //�I�[�o�[�q�b�g���
	}TYPE;

	D3DXMATRIX m_mtxWorld;                                    //���[���h�ϊ��s��
	MotionSet m_Motion[NUM];                                  //���[�V����
	int m_nKeyCnt;                                            //���݂̃L�[��
	int m_nFrameCnt;										  //���[�V�����t���[���J�E���^�[
	TYPE m_MotionSet;
	char* m_FileModel[NUM];                                   //�t�@�C�������܂��B
	D3DXVECTOR3 m_CameraRot;
	D3DXVECTOR3 m_CameraPos;
	void LoadMotion();                                        //���[�V����������
	void LoadParts();                                         //�p�[�c���ǂݍ���
	void Motion();											  //���[�V��������
	void SetMotion(TYPE g_Motions);							  //���[�V�����ύX����
};

#endif