//================================================================================================================================================================
//
//オブジェクト3D処理[object3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object.h"
#include <string>

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************3Dオブジェクト管理クラス****************************************************************
class CBillboard :public CObject
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CBillboard(int nPriority);		        //コンストラクタ
	~CBillboard() override;		//デストラクタ
	HRESULT Init()override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw()   override;		//描画処理

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

	//-----------------------------------------プライベート----------------------------------------------
private:
	void UpdatepVtx();
	void UpdateAnim();
	void UpdateCollar();

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャ
	D3DXVECTOR3 m_pos;						    //頂点座標
	D3DXVECTOR3 m_rot;						    //向き
	D3DXVECTOR3 m_size;                         //サイズ半径
	D3DXMATRIX m_mtxWorld;                      //ワールド変換行列
	float m_fWidth;                             //横半径
	float m_fHeight;                            //縦半径

	//アニメーション処理系統
	float m_fSplit;
	int m_nAnimationId;
	bool m_bRev;
	int m_nTime;
	int m_nextTime;

	//色関係の変数
	int m_nRed;
	int m_nGreen;
	int m_nBlue;
	int m_nAlpha;

	int  m_nLife;
	bool m_bDraw;
};

#endif