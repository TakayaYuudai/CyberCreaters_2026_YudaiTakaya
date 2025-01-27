//================================================================================================================================================================
//
//�v���C���[HP�Q�[�W����[player_hp_gage.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "object2D.h"
#include "objectX.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�v���C���[�N���X****************************************************************
class C2dcharacter :public CObject2D
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	C2dcharacter(int nP);
	~C2dcharacter()       override;
	HRESULT Init()override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	void SetMove(D3DXVECTOR2 move) { m_move = move; };
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
private:
	D3DXVECTOR2 m_move;
	D3DXVECTOR3 m_rot;
};

class CXcharacter:public CObjectX
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CXcharacter(int nP);
	~CXcharacter() override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
	void SetMove(D3DXVECTOR3 move) { m_move = move;}
	void SetRot(D3DXVECTOR3 rot)   { m_rot = rot; }
	void SetLife(int nlife)        { m_nLife = nlife,m_nMaxLife = nlife;}

	//�_���[�W����
	void Damage(int minus) { m_nLife -= minus; 
	                     if (m_nLife <= NULL) Uninit();};
	//�񕜏���
	void RecoveryLife(int recoveryvalue) { m_nLife += recoveryvalue;
		                 if (m_nLife > m_nMaxLife) m_nLife = m_nMaxLife;}

	void SetUpMove(D3DXVECTOR3 move) { m_move += move; }

	//�v���C���[�X�e�C�g
	typedef enum
	{
		NONE = 0,         //�ҋ@
		ATK,              //ATTACK��
		DAMAGE            //�_���[�W���󂯂����
	}STATEMODE;

	//���C�t����Ԃ�
	int GetLife() {
		return m_nLife; };

	//���C�t�ő�l��Ԃ�
	int GetMaxLife() {
		return m_nMaxLife;}

	//�ړ��l��Ԃ�
	D3DXVECTOR3 GetMoveMent() { 
		return m_move; };

	//�X�e�C�g��Ԃ�
	STATEMODE GetState() {
		return m_StateMode; }

	//�X�e�C�g����
	void SetState(STATEMODE mode){
		m_StateMode = mode;}

private:
	STATEMODE m_StateMode;

	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	int m_nLife;
	int m_nMaxLife;
	int m_nInterval;

	//�X�e�[�W��������
	void LimitStage(D3DXVECTOR3& pos);
};

#endif