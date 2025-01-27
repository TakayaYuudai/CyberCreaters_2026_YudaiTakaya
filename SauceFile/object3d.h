//================================================================================================================================================================
//
//オブジェクト3D処理[object3D.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "object.h"
#include <string>

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************3Dオブジェクト管理クラス****************************************************************
class CObject3D :public CObject
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CObject3D(int nPriority);		        //コンストラクタ
	~CObject3D() override;		//デストラクタ
	HRESULT Init() override;	//初期設定
	void Uninit() override;		//終了処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

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

	//-----------------------------------------プライベート----------------------------------------------
private:
	void UpdatepVtx();
	void UpdateGageVtx();
	void UpdateAnim();

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

	bool m_bGage; //ゲージ型に伸ばした物

	bool m_bDraw; //移すべきかどうか
};

#endif