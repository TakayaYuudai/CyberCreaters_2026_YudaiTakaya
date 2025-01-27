//================================================================================================================================================================
//
//カメラ処理[camera.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "main.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************カメラオブジェクト管理クラス****************************************************************
class CCamera
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	CCamera();
	~CCamera();
	HRESULT Init();
	void Uninit();
	void Update();
	void SetCamera(); //カメラ設定
	void SetShake(int shakeLate, float shakesum);

	// カメラの向きを代入
	void SetRot(D3DXVECTOR3 rot) {
		m_rot = rot;}

    // カメラの向きを返す
    D3DXVECTOR3 GetRot() {
        return m_rot;}

    // ロックオン状態の追跡処理
	void FollowCameraTargetEnem(D3DXVECTOR3 playerPos, D3DXVECTOR3 enemyPos, D3DXVECTOR3 rot);

	// ノーマル状態の追跡処理
	void FollowCameraTargetPlayer(D3DXVECTOR3 playerPos, D3DXVECTOR3 rot);

	// 技に対する演出用カメラ処理
	void DirectionCamera(D3DXVECTOR3 targetpos, D3DXVECTOR3 rot, float distance);

	//演出時間設定
	void SetDirectionTime(int directiontime) {
	
		if (!m_bDirectionMode){
			m_bDirectionMode = true;
			m_nDirectionMaxTime = directiontime;
		}
	}

    // 対象の速度を設定
    bool SetBack(bool back) {
		m_bBack = back;}

	// カメラの最大遠距離
	void SetCameraCloseDistance(float distance) {
		m_fCloseDistance = distance;}

	// カメラ距離離す
	void PlusDistance(float value) {
		m_fCloseDistance += value;}

	// カメラ距離近づける
	void MinusDistance(float value) {
		m_fCloseDistance -= value;}

	//演出中の判定を返す
	bool GetPlayStay() { return m_bDirectionMode; }

	//距離を返す
	float GetCameraDistance() {return m_fCloseDistance;}

	//-----------------------------------------プライベート----------------------------------------------
private:
	D3DXVECTOR3 m_posV;			  //視点
	D3DXVECTOR3 m_posR;			  //注視点
	D3DXVECTOR3 m_vecU;           //上方向
	D3DXMATRIX  m_mtxProjection;  //プロジェクション行列
	D3DXMATRIX  m_mtxView;        //ビュー行列
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;

	int m_nShakeLate;            //揺らすフレームレート
	int m_nDirectionTime;        //演出時間計測
	int m_nDirectionMaxTime;     //演出最大時間
	float m_fShakeSum;           //揺らす量
	float m_bBack;               //対象の移動速度
	float m_bFlight;             //Flightしているかどうか
	float m_fCloseDistance;      //最大の離れらる距離
	bool  m_bDirectionMode;      //演出中かどうかの判断

	//演出終わり宣言
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