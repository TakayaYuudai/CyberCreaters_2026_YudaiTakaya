//================================================================================================================================================================
//
//�I�u�W�F�N�g2D����[object2D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "object.h"
#include <string>

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************2D�I�u�W�F�N�g�Ǘ��N���X****************************************************************
class CObject2D :public CObject
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	CObject2D(int nPriority);		        //�R���X�g���N�^
	~CObject2D() override;		//�f�X�g���N�^
	HRESULT Init() override;	//�����ݒ�
	void Uninit() override;		//�I������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��
	void SetAnimation(float fSplit, int nTime);
	void SetPos(float x, float y);
	void SetTexture(std::string sPath);
	void SetSize(float fWidth, float fHeight);
	void GageAnim(float fGageStatus);
	void SetUVtex(float fSplit, float fSplitRight);
	void SetCollar(int r, int g, int b, int a) { m_nRed = r, m_nGreen = g, m_nBlue = b, m_nAlpha = a; };
	void SetMove(D3DXVECTOR2 move) { m_move = move; }
	void CircleGageAnim(float fGageStatus);
	void UpdateCollar();
	void SetDraw(bool draw) { m_bDraw = draw; };
	void InsideOutTex(float fGageStatus);
	void UpdateCooldownGauge(float fGageStatus);

	void SetRot(float y) {
		m_rot.z = y;
	}

	void SetRotAnim(float y) {
		m_rot.z += y;
	}

	int GetAlpha() {
		return m_nAlpha;
	}

	void PlusAlpha(int a) {
		m_nAlpha += a;
		if (m_nAlpha > 255)m_nAlpha = 255;
	}

	int GetMaxColor() { return 255;}

	void PlusCollar(int r, int g, int b) {
		m_nRed += r, m_nGreen += g, m_nBlue += b;

		if (m_nRed > 255) { m_nRed = 255; }
		if (m_nRed < 0) { m_nRed = 0; }
		if (m_nGreen > 255) { m_nGreen = 255; }
		if (m_nGreen < 0) { m_nGreen = 0; }
		if (m_nBlue > 255) { m_nBlue = 255;}
		if (m_nBlue < 0) { m_nBlue = 0; }
	}

	D3DXVECTOR2* GetPos();
	D3DXVECTOR3* GetRot();
	D3DXVECTOR2* GetSize();

	static CObject2D* Create(int nPriority);

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	void UpdateAnim();
	void UpdatepVtx();
	void UpdateUVtex();

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`��
	D3DXVECTOR2 m_pos;						    //���_���W
	D3DXVECTOR3 m_rot;						    //����
	D3DXVECTOR2 m_move;
	D3DXVECTOR2 m_size;
	float m_fLengthPlayer;				        //�Ίp���̒���
	float m_fAnglePlayer;
	float m_fWidth;
	float m_fHeight;

	float m_fSplit;
	int m_nAnimationId;
	bool m_bRev;
	int m_nTime;
	int m_nextTime;

	float m_fSplitRight;
	float m_fSplitLeft;

	bool m_bGage;

	int m_nRed;
	int m_nGreen;
	int m_nBlue;
	int m_nAlpha;

	bool m_bDraw;
};

#endif