//================================================================================================================================================================
//
//�J��������[camera.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "main.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�J�����I�u�W�F�N�g�Ǘ��N���X****************************************************************
class CCamera
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera(); //�J�����ݒ�
	void SetShake(int shakeLate, float shakesum);

	// �J�����̌�������
	void SetRot(D3DXVECTOR3 rot) {
		m_rot = rot;}

    // �J�����̌�����Ԃ�
    D3DXVECTOR3 GetRot() {
        return m_rot;}

    // ���b�N�I����Ԃ̒ǐՏ���
	void FollowCameraTargetEnem(D3DXVECTOR3 playerPos, D3DXVECTOR3 enemyPos, D3DXVECTOR3 rot);

	// �m�[�}����Ԃ̒ǐՏ���
	void FollowCameraTargetPlayer(D3DXVECTOR3 playerPos, D3DXVECTOR3 rot);

	// �Z�ɑ΂��鉉�o�p�J��������
	void DirectionCamera(D3DXVECTOR3 targetpos, D3DXVECTOR3 rot, float distance);

	//���o���Ԑݒ�
	void SetDirectionTime(int directiontime) {
	
		if (!m_bDirectionMode){
			m_bDirectionMode = true;
			m_nDirectionMaxTime = directiontime;
		}
	}

    // �Ώۂ̑��x��ݒ�
    bool SetBack(bool back) {
		m_bBack = back;}

	// �J�����̍ő剓����
	void SetCameraCloseDistance(float distance) {
		m_fCloseDistance = distance;}

	// �J������������
	void PlusDistance(float value) {
		m_fCloseDistance += value;}

	// �J���������߂Â���
	void MinusDistance(float value) {
		m_fCloseDistance -= value;}

	//���o���̔����Ԃ�
	bool GetPlayStay() { return m_bDirectionMode; }

	//������Ԃ�
	float GetCameraDistance() {return m_fCloseDistance;}

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	D3DXVECTOR3 m_posV;			  //���_
	D3DXVECTOR3 m_posR;			  //�����_
	D3DXVECTOR3 m_vecU;           //�����
	D3DXMATRIX  m_mtxProjection;  //�v���W�F�N�V�����s��
	D3DXMATRIX  m_mtxView;        //�r���[�s��
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;

	int m_nShakeLate;            //�h�炷�t���[�����[�g
	int m_nDirectionTime;        //���o���Ԍv��
	int m_nDirectionMaxTime;     //���o�ő厞��
	float m_fShakeSum;           //�h�炷��
	float m_bBack;               //�Ώۂ̈ړ����x
	float m_bFlight;             //Flight���Ă��邩�ǂ���
	float m_fCloseDistance;      //�ő�̗����鋗��
	bool  m_bDirectionMode;      //���o�����ǂ����̔��f

	//���o�I���錾
	void EndDirectionTime() {
		m_nDirectionTime++;
		if (m_nDirectionTime >= m_nDirectionMaxTime) {
			m_bDirectionMode = false;
			m_nDirectionMaxTime = NULL;
			m_nDirectionTime = NULL;
		}
	}
};

#endif