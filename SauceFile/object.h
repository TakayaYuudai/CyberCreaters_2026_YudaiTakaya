//================================================================================================================================================================
//
//オブジェクト処理[object.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "Pch.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************オブジェクトクラス****************************************************************
class CObject
{
	//-----------------------------------------パブリック----------------------------------------------
public:

	//オブジェクトタイプ識別処理
	typedef enum
	{
		NONE = 0,         //無
		PLAYER,           //プレイヤー
		BOSS,             //ボス敵
		FLOOR,            //床
		MISSILE,          //ミサイルウェポン
		NOVA,             //爆発攻撃
		MAXOBJ
	}TYPE;

	CObject(int nPriority);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static  void ReleaseAll(); //全オブジェクト解放
	static  void UpdateAll();  //全オブジェクト更新
	static  void DrawAll();    //全オブジェクト描画

	static CObject* GetObject(int nID);
	TYPE GetType();                 //タイプ取得
	void SetType(TYPE ntype);       //タイプ設定

	// Death フラグの取得と設定
	void Deathflag(){
		m_bDeath = true;
	}

	CObject* GetTop() {
		return m_pTop;
	}

	CObject* GetNext() {
		return m_pNext;
	}

	//-----------------------------------------プロテクテッド----------------------------------------------
protected:
	void Release(); //自分自身の解放

  //-----------------------------------------プライベート----------------------------------------------
private:

	int m_nPriority;
	static CObject* m_pTop;
	static CObject* m_pCur;

	CObject * m_pPrev;
	CObject * m_pNext;

	bool m_bDeath;

	TYPE m_type;                            //オブジェクトタイプ
	static int m_nNumAll;                   //オブジェクト総数
	int m_nID;                              //自分自身のID
};

#endif