//================================================================================================================================================================
//
//�v���C���[����[player3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "character.h"
#include "charge_gage.h"
#include "gage_back.h"
#include "gage_heat.h"
#include "modelparts.h"
#include "oeskill.h"
#include "gear.h"
#include "targetpointer.h"
#include "gage_player_life.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�v���C���[�N���X****************************************************************
class CPlayer3D :public CXcharacter
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CPlayer3D();
	~CPlayer3D()    override;
	HRESULT Init()  override;
	void Uninit()   override;
	void Update()   override;
	void Draw()     override;
	CModelParts GetPlayerParts() { return *m_PlayerParts[0];}
	void PlayerDamage(int damage);
	static CPlayer3D* Create();				//Object2D����

	//�`���[�W�i�K����
	typedef enum
	{
		FIRST = 1,
		SECOND,
		THIRD,
		FORTH,
		FIVE,
		FULLPOWER
	}POWERRANK;

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

	void Rotation();										             // ��]����
	bool MoveMent(D3DXVECTOR3& rot, D3DXVECTOR3 pos);                    // �ړ�����
	void Charge(D3DXVECTOR3& rot);                                       // ���ߏ���
	void ChargeAtk(D3DXVECTOR3 pos, D3DXVECTOR3& rot);                   // �U������
	void SearchRot(D3DXVECTOR3& rot, D3DXVECTOR3 pos);                   // �G�̕����Ɏ��@���������鏈��
	void Step(D3DXVECTOR3 rot);                                          // �X�e�b�v�������
	void DistanceSum(D3DXVECTOR3 pos, D3DXVECTOR3& rot);                 // �U������
	void OeSkill(D3DXVECTOR3 pos);                                       // �I�v�e�B�}�X�G�l���M�[�g�p����
	void CameraManagement(D3DXVECTOR3& pos, D3DXVECTOR3& rot);           // �J�������샂�[�h�Ǘ�����
	void AtkManagement(D3DXVECTOR3 &pos, D3DXVECTOR3& rot);              // �U�������S�ʂ̊Ǘ�
	void ChargeAtkManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot);         // �`���[�W�U���̊Ǘ�
	void RushAtk(D3DXVECTOR3 pos, D3DXVECTOR3& rot);                     // �A�ōU�����Ǘ�����
	void OverHeatManagement(D3DXVECTOR3 pos);                            // �I�[�o�[�q�[�g�������Ǘ�����
	void OeSkillManagement(D3DXVECTOR3 pos);                             // �I�v�e�B�}�X�G�l���M�[�����̊Ǘ�
	void MotionStateManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot);       // ���[�V�����Ǘ�����
	void OeSkill_CoolThruster(D3DXVECTOR3 pos);                          // �X���X�^�[��p�X�L��
	void OeSkill_Repair(D3DXVECTOR3 pos);                                // ���y�A�X�L������

	//�X�L���֘A�̃X�e�[�^�X���Z�b�g
	void OeSkillStatusrReset(int limittime){
		//�^�C�����~�b�g
		if (m_nOeSkillTime > limittime) {
			//�X�L���֘A�X�e�[�^�X������
			m_bUseOeSkill = false;
			m_bOeSkillBreak = true;
			m_Oeskill_Cool->SkillFlag(true);
			m_nOeSkillTime = NULL;
		}
	}

	//�X�L���g�p��̃N�[���^�C������
	void OeSkillBreakTime(int limittime) {
		//�^�C�����~�b�g
		if (m_nOeSkillBreakTime > limittime) {
			//�X�L���֘A�X�e�[�^�X������
			m_bOeSkillBreak = false;
			m_Oeskill_Cool->SkillFlag(false);
			m_nOeSkillBreakTime = NULL;
			m_bRecovery = false;
		}
	}

	//�X���X�^�[��p����
	void CoolThruster(float coolvalue) {
	    m_fHeatSum -= coolvalue;
	    LimitThruster();
	}

	//�X���X�^�[���M����
	void HeatThruster(float heatvalue) {
		m_fHeatSum += heatvalue;
		LimitThruster();
	}

	//�X���X�^�[�Ǘ��֐�
	void LimitThruster() {

		//����l�˔j
	   if (m_fHeatSum >= 100.f){
		   m_fHeatSum = 100.f;
	   }

	   //����l�˔j
	   else if (m_fHeatSum <= 0.f){
		   m_fHeatSum = 0.f;
	   }
	}

	Charge_Gage* m_ChargeGage;                                //�`���[�W�Q�[�W�|�C���^�[
	CGage_Heat * m_GageHeat;                                  //�`���[�W�Q�[�W�|�C���^�[
	CGage_Player_Life* m_PlayerLifeGage;                      //���C�t�Q�[�W�|�C���^�[
	CGage_Back* m_GageBack[MAX_GAGE_BACK];                    //�Q�[�W�̃o�b�N�w�i�|�C���^�[
	CSpeedgear* m_GearSpeed;                                  //���M�A�|�C���^�[
	CAtkgear*   m_GearAtk;                                    //���M�A�|�C���^�[
	COeSkill_Cool* m_Oeskill_Cool;							  //�X���X�^�[��p���u�̃|�C���^
	COeSkill_Jamming* m_Oeskill_Repair; 					  //�J�����W���~���O�̃|�C���^
	CTarget_Pointer* m_TargerPnt;                             //�^�[�Q�b�g�|�C���^�[�}�[�N�̃|�C���^�[

	float m_fChargeSum;                                       //���݂̗��ߏ󋵂̍ő�l
	D3DXVECTOR3 m_OldPos;                                     //�I�[���h�|�X
	char* m_FileModel[NUM];                                   //�t�@�C�������܂��B
	CModelParts* m_PlayerParts[NUM];                          //�p�[�c�|�C���^�[
	MotionSet m_Motion[NUM];                                  //���[�V����
	D3DXMATRIX m_mtxWorld;                                    //���[���h�ϊ��s��
	int m_nKeyCnt;                                            //���݂̃L�[��
	int m_nFrameCnt;										  //���[�V�����t���[���J�E���^�[
	D3DXVECTOR3 m_CameraRot;								  //�J�����̊p�x
	float m_fGav = -10.0f;									  //�d��
	bool m_bAtk;											  //�U���������f
	float m_fHeatSum;										  //�M�ʁi�I�[�o�[�q�[�g�Q�[�W�ϐ��j
	bool m_bFlowEnemMode;                                     //�ǐՃ��[�h�t���O
	D3DXVECTOR3 m_vVelocity;                                  //�X�e�b�v����̕������L�^����ϐ�

	int  m_nStepCnt;                                          //�X�e�b�v�W��
	bool m_bStepMode;                                         //�X�e�b�v���[�h
	bool m_bStepVec;                                          //�X�e�b�v������߂Ă邩
	D3DXVECTOR3 m_Step;                                       //�X�e�b�v���̕����ϐ�
	D3DXVECTOR3 m_move;                                       //�X�e�b�v���̕����ϐ�
	bool m_bOverheat;                                         //�I�[�o�[�q�[�g���Ă��邩

	int  m_nGap;
	int  m_nAtkSum;

	int  m_nAtkTime;
	bool m_bAtkPanchi;

	bool m_bUseOeSkill;                                    //�X�L�����g�p���
	int  m_nOeSkillTime;                                   //�X�L���p������
	static bool m_bOeSkillBreak;						   //�X�L���g�p��̃N�[���^�C���m�F
	int  m_nOeSkillBreakTime;                              //�X�L���g�p��̃N�[���^�C���J�E���g

	bool m_bRushAtk;									   //���b�V���U���̊m�F
	int  m_nRushCoolTime;								   //���b�V���U���̌��Ԏ�

	bool m_bRecovery;                                      //�񕜂��������f

	//�v���C���[�X�e�C�g
	typedef enum
	{
		NONE = 0,         //�ҋ@
		WALK,             //����
		CHARGE,           //�`���[�W
		STEP,             //�X�e�b�v���
		OVERHEAT,         //�I�[�o�[�q�b�g���
	}TYPE;

	TYPE m_MotionSet;

	POWERRANK m_PowerRank;

	void LoadMotion();                                        //���[�V����������
	void LoadParts();                                         //�p�[�c���ǂݍ���
	void Motion();											  //���[�V��������
	void SetMotion(TYPE g_Motions);							  //���[�V�����ύX����
};

#endif