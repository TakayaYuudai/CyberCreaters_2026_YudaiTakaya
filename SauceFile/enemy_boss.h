//================================================================================================================================================================
//
//�{�X�G�l�~�[����[enemy_boss.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "character.h"
#include "modelparts.h"
#include "atk_time_effect.h"
#include "enemy_boss_hp_gage.h"
#include "gage_back.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�v���C���[�N���X****************************************************************
class CEnemy_Boss :public CXcharacter
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CEnemy_Boss();
	~CEnemy_Boss()  override;
	HRESULT Init()  override;
	void Uninit()   override;
	void Update()   override;
	void Draw()     override;
	CModelParts GetBossParts() { return *m_EnemBossParts[0];}
	static CEnemy_Boss* Create(bool t);				//Object2D����

  //-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	int  m_nAtkCnt;       //�U���̐����̃J�E���g
	int  m_nStayCnt;      //�C���^�[�o���J�E���g
	int  m_nMaxStayCnt;   //�ő�C���^�[�o������
	bool m_bAtk;          //���ݍU�����邩�ǂ����̔��f
	bool m_bTutorial;     //����Tutorial���ǂ���

	static const int NUM = 18;

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

	D3DXMATRIX m_mtxWorld;                                    //���[���h�ϊ��s��
	int m_nKeyCnt;                                            //���݂̃L�[��
	int m_nFrameCnt;										  //���[�V�����t���[���J�E���^�[

	char* m_FileModel[NUM];                                   //�t�@�C�������܂��B
	CModelParts* m_EnemBossParts[NUM];                        //�p�[�c�|�C���^�[
	MotionSet m_Motion[NUM];                                  //���[�V����
	CGage_Enemy_Hp* m_EnemyHp_Gage;                           //�̗̓Q�[�W�̃|�C���^�[
	CGage_Back* m_GageBack;                                   //�Q�[�W�w�i�|�C���^�[

	//�{�X�X�e�C�g
	typedef enum
	{
		STAY = NULL,        //�ҋ@
		TACKLE,             //�^�b�N��
		SNIPER,             //�e��
		NOVA,               //����
		STAN,               //�Ђ�ݏ��
		SKILL,              //�K�E
		MAX
	}STATE;

	STATE m_MotionSet;  //���[�V�����Ǘ�
	STATE m_AtkStay;    //���݂̎g�p���̋Z�̊Ǘ�

	void Tackle(D3DXVECTOR3 pos, D3DXVECTOR3& rot);
	void Nova(D3DXVECTOR3 pos , D3DXVECTOR3 rot);
	void Sniper(D3DXVECTOR3 pos);

	//void NockBack(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void LoadMotion();                                                                           //���[�V����������
	void LoadParts();                                                                            //�p�[�c���ǂݍ���
	void Motion();											                                     //���[�V��������
	void SetMotion(STATE g_Motions);							                                 //���[�V�����ύX����
	void DelParts();                                                                             //�p�[�c���폜
	
	 //�C���^�[�o�����Ԑݒ�
	void SetIntervalTime(int nIntervar) {
		m_nMaxStayCnt = nIntervar;
		m_bAtk = false;
		ShiftAtkState();
	}                                                                                           
	void ShiftAtkState(); // �{�X�̎��̍s�������߂�
};

#endif