//================================================================================================================================================================
//
//カメラ処理[camera.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "camera.h"
#include "manager.h"
#include <cmath>  // abs関数のために必要

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CCamera::CCamera()
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CCamera::~CCamera()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 200.f, -300); //視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  //上方向ベクトル
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fCloseDistance = 400.f;
	m_nShakeLate = 0;
	m_fShakeSum = 0.0f;
	m_nDirectionTime = NULL;
	m_nDirectionMaxTime = NULL;
	m_bDirectionMode = false;
	m_bBack = false;

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CCamera::Uninit()
{
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CCamera::Update(){

	if (m_bDirectionMode){
		EndDirectionTime();
	}
}

//================================================================================================================================================================
//相対距離カメラ
//================================================================================================================================================================
void CCamera::FollowCameraTargetEnem(D3DXVECTOR3 playerPos, D3DXVECTOR3 enemyPos, D3DXVECTOR3 rot) {

	if (!m_bDirectionMode){
		// プレイヤーと敵の位置からカメラの向きを計算
		float x = enemyPos.x - playerPos.x;  // 横の差分
		float z = enemyPos.z - playerPos.z;  // 縦の差分
		float y = enemyPos.y - playerPos.y;  // 上下の差分

		float angleToEnemy = atan2f(x, z);   // 敵への角度

		// プレイヤーの向きに基づいてカメラを調整
		const float cameraHeight = 170.0f;   // 高さのオフセット

		// プレイヤーの向きに基づいてカメラ位置を計算
		const float cameraAngle = rot.y + D3DX_PI;  // プレイヤーの回転からカメラ方向を計算

		// 目標位置を計算
		D3DXVECTOR3 targetPos;

		//目標位置設定
		targetPos.x = playerPos.x - (m_fCloseDistance * sinf(cameraAngle));
		targetPos.z = playerPos.z - (m_fCloseDistance * cosf(cameraAngle));

		//カメラ何処まで移すか割合を求める
		float midpointY;
		//カメラの注視点を中間に
		midpointY = (playerPos.y + enemyPos.y) * 0.5f;

		targetPos.y = midpointY; // 中間高さを目標位置に反映

		//スムージング係数
		float smoothingFactor = 0.075f;

		// カメラ位置を補間してスムーズに動かす
		m_posV.x += (targetPos.x - m_posV.x) * smoothingFactor;
		m_posV.z += (targetPos.z - m_posV.z) * smoothingFactor;

		// プレイヤーとの最小距離を保つための制限
		float minDistance = 350.0f;
		float currentDistance = sqrtf((m_posV.x - playerPos.x) * (m_posV.x - playerPos.x) +
			(m_posV.z - playerPos.z) * (m_posV.z - playerPos.z));

		//カメラの最小位置に補完する
		if (currentDistance < minDistance) {
			float scale = minDistance / currentDistance;
			m_posV.x = playerPos.x + (m_posV.x - playerPos.x) * scale;
			m_posV.z = playerPos.z + (m_posV.z - playerPos.z) * scale;
		}

		//現在のカメラの方向を保存
		float fAngle = atan2f(x, z);
		D3DXVECTOR3 AngleY = GetRot();
		AngleY.y = fAngle + D3DX_PI;

		//位置設定
		CManager::GetInstance()->GetCamera()->SetRot(AngleY);

		// 最終的なカメラ高さ調整
		m_posV.y = playerPos.y;

		// 注視点の位置を設定（プレイヤーの位置）
		m_posR.x = playerPos.x;
		m_posR.y = playerPos.y;
		m_posR.z = playerPos.z;
	}
}

//================================================================================================================================================================
//対象の後ろを追い続ける設定
//================================================================================================================================================================
void CCamera::FollowCameraTargetPlayer(D3DXVECTOR3 playerPos, D3DXVECTOR3 rot) {

	if (!m_bDirectionMode){

		// プレイヤーの後ろに位置するためのオフセットを定義
		float height;   // プレイヤーの高さからのオフセット

		if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_TITLE) {
			height = 250.f;
		}
		else {
			height = 170.f;
		}

		height = 170.f;

		// プレイヤーの向いている方向からカメラの位置を計算
		float fAngle = rot.y + D3DX_PI; // プレイヤーの向きに基づく角度計算

		// 目標位置を計算
		D3DXVECTOR3 targetPos;
		targetPos.x = playerPos.x - (m_fCloseDistance * sinf(fAngle));
		targetPos.y = playerPos.y + height; // プレイヤーの上方に配置
		targetPos.z = playerPos.z - (m_fCloseDistance * cosf(fAngle));

		// カメラの位置を補間してスムーズに動かす
		float smoothingFactor = 0.085f; // スムージングの係数（0.0f～1.0f）

		// 全体割合を徐々に駆けていく
		m_posV.x += (targetPos.x - m_posV.x) * smoothingFactor;
		m_posV.z += (targetPos.z - m_posV.z) * smoothingFactor;

		// カメラの位置を調整（最大制限と最小制限を加える）
		float maxY = 1200.f; // 最大高さ
		float minY = 100.f;  // 最小高さ

		// プレイヤーの速度に応じてカメラの位置を調整
		float newY = m_posV.y + (targetPos.y - m_posV.y);

		//軸をずらした際に違和感をなくす
		m_posV.y = newY - rot.x;

		// プレイヤーとの距離制限を適用
		float minDistance = 350.f; // プレイヤーとの最小距離
		float currentDistance = sqrt((m_posV.x - playerPos.x) * (m_posV.x - playerPos.x) +
			(m_posV.z - playerPos.z) * (m_posV.z - playerPos.z));

		//一定以上カメラを近づけさせない処理
		if (currentDistance < minDistance) {
			// カメラをプレイヤーから一定の距離だけ離す
			float scale = minDistance / currentDistance;
			m_posV.x = playerPos.x + (m_posV.x - playerPos.x) * scale;
			m_posV.z = playerPos.z + (m_posV.z - playerPos.z) * scale;
		}

		// 見る位置をプレイヤーに設定（y軸の回転を固定）
		m_posR.x = playerPos.x;
		m_posR.y = playerPos.y + rot.x; // プレイヤーのy位置をそのまま使用
		m_posR.z = playerPos.z;
	}
}

//================================================================================================================================================================
//敵の行動に合わせた演出設定
//================================================================================================================================================================
void CCamera::DirectionCamera(D3DXVECTOR3 tergetpos, D3DXVECTOR3 rot,float distance){

	if (m_bDirectionMode){

	        // プレイヤーの後ろに位置するためのオフセットを定義
	        float height = 170.f;   // プレイヤーの高さからのオフセット
	        
	        // プレイヤーの向いている方向からカメラの位置を計算
	        float fAngle = rot.y; // プレイヤーの向きに基づく角度計算
	        
	        // 目標位置を計算
	        D3DXVECTOR3 targetPos;
	        targetPos.x = tergetpos.x - (m_fCloseDistance * sinf(fAngle));
	        targetPos.y = tergetpos.y + height; // プレイヤーの上方に配置
	        targetPos.z = tergetpos.z - (m_fCloseDistance * cosf(fAngle));
	        
	        // カメラの位置を補間してスムーズに動かす
	        float smoothingFactor = 0.085f; // スムージングの係数（0.0f～1.0f）
	        
	        // 全体割合を徐々に駆けていく
	        m_posV.x += (targetPos.x - m_posV.x) * smoothingFactor;
	        m_posV.z += (targetPos.z - m_posV.z) * smoothingFactor;
	        
	        // カメラの位置を調整（最大制限と最小制限を加える）
	        float maxY = 1200.f; // 最大高さ
	        float minY = 100.f;  // 最小高さ
	        
	        // プレイヤーの速度に応じてカメラの位置を調整
	        float newY = m_posV.y + (targetPos.y - m_posV.y);
	        
	        //軸をずらした際に違和感をなくす
	        m_posV.y = newY - rot.x;
	        
	        // プレイヤーとの距離制限を適用
	        float minDistance = distance; // プレイヤーとの最小距離
	        float currentDistance = sqrt((m_posV.x - tergetpos.x) * (m_posV.x - tergetpos.x) +
	        	(m_posV.z - tergetpos.z) * (m_posV.z - tergetpos.z));
	        
	        //一定以上カメラを近づけさせない処理
	        if (currentDistance < minDistance) {
				// カメラをプレイヤーから一定の距離だけ離す
				float scale = minDistance / currentDistance;
	        	m_posV.x = tergetpos.x + (m_posV.x - tergetpos.x) * scale;
	        	m_posV.z = tergetpos.z + (m_posV.z - tergetpos.z) * scale;
	        }
	        
	        // 見る位置をプレイヤーに設定（y軸の回転を固定）
	        m_posR.x = tergetpos.x;
	        m_posR.y = tergetpos.y + rot.x; // プレイヤーのy位置をそのまま使用
	        m_posR.z = tergetpos.z;
	}
}

//================================================================================================================================================================
//カメラの設定
//================================================================================================================================================================
void CCamera::SetCamera(){

	CRenderer* pRenderer = nullptr;
	pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 100.0f, 8000.0f);

	//プロジェクションマトリックスの設定
	RendererDivice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posv = m_posV;
	D3DXVECTOR3 posr = m_posR;

	//揺れ処理
	if (m_nShakeLate > 0){

		--m_nShakeLate;

		//振動値代入
		adjust.x += m_fShakeSum;
		adjust.z += m_fShakeSum;

		//シェイク方向設定
		adjust.x = (float)(rand() % 50) * m_fShakeSum;
		adjust.z = (float)(rand() % 50) * m_fShakeSum;

		//疑似カメラに代入
		posv += adjust;
		posr += adjust;
	}

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &posv, &posr, &m_vecU);
	//ビューマトリックスの設定
	RendererDivice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//================================================================================================================================================================
//カメラ振動設定
//================================================================================================================================================================
void CCamera::SetShake(int shakeLate, float shakesum){
	m_nShakeLate = shakeLate;
	m_fShakeSum = shakesum;
}

