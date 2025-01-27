//================================================================================================================================================================
//
//�I�u�W�F�N�g3D����[object3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "object.h"
#include <string>

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************3D�I�u�W�F�N�g�Ǘ��N���X****************************************************************
class CObject3D :public CObject
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CObject3D(int nPriority);		        //�R���X�g���N�^
	~CObject3D() override;		//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

	void SetPos(float x, float y, float z);
	void SetTexture(std::string sPath);
	void SetSize(float fWidth, float fHeight);
	void SetGageSize(float fWidth, float fHeight);
	void SetAnimation(float fSplit, int nTime);
	void DrawSet(bool DrawSet);
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	D3DXVECTOR3* GetPos();
	D3DXVECTOR3* GetRot();
	D3DXVECTOR3* GetSize();

	static CObject3D* Create(int nPriority);

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	void UpdatepVtx();
	void UpdateGageVtx();
	void UpdateAnim();

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
	D3DXVECTOR3 m_pos;						    //���_���W
	D3DXVECTOR3 m_rot;						    //����
	D3DXVECTOR3 m_size;                         //�T�C�Y���a
	D3DXMATRIX m_mtxWorld;                      //���[���h�ϊ��s��
	float m_fWidth;                             //�����a
	float m_fHeight;                            //�c���a

	//�A�j���[�V���������n��
	float m_fSplit;
	int m_nAnimationId;
	bool m_bRev;
	int m_nTime;
	int m_nextTime;

	bool m_bGage; //�Q�[�W�^�ɐL�΂�����

	bool m_bDraw; //�ڂ��ׂ����ǂ���
};

#endif