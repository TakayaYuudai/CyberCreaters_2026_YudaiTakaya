//================================================================================================================================================================
//
//�I�u�W�F�N�g3D����[object3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "object.h"
#include <string>

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************3D�I�u�W�F�N�g�Ǘ��N���X****************************************************************
class CBillboard :public CObject
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CBillboard(int nPriority);		        //�R���X�g���N�^
	~CBillboard() override;		//�f�X�g���N�^
	HRESULT Init()override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw()   override;		//�`�揈��

	void SetPos(float x, float y, float z);
	void SetTexture(std::string sPath);
	void SetSize(float fWidth, float fHeight);
	void SetAnimation(float fSplit, int nTime);
	void GageAnim(static float fGageStatus);
	void SetLife(int nLife) { m_nLife = nLife;}

	void DamageLife(int nDamage) {m_nLife -= nDamage;
	if (m_nLife <= 0) {Uninit();}}

	void SetCollar(int r, int g, int b, int a) {
		m_nRed = r, m_nGreen = g, m_nBlue = b, m_nAlpha = a;}

	void SetDraw(bool d) {
		m_bDraw = d;}

	bool GetDraw() {
		return m_bDraw;}

	D3DXVECTOR3* GetPos();
	D3DXVECTOR3* GetSize();

	static CBillboard* Create(int nPriority);

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	void UpdatepVtx();
	void UpdateAnim();
	void UpdateCollar();

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

	//�F�֌W�̕ϐ�
	int m_nRed;
	int m_nGreen;
	int m_nBlue;
	int m_nAlpha;

	int  m_nLife;
	bool m_bDraw;
};

#endif