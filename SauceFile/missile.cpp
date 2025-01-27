//================================================================================================================================================================
//
//通常エネミー処理[normal_enemy.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "manager.h"
#include "player_3d.h"
#include "nova.h"
#include "effect_backpack.h"
#include "missile.h"

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CMissile::CMissile() :CObjectX(0){
}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CMissile::~CMissile(){
}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CMissile::Init(){
	CObjectX::Init();
	ModelFilePath("data\\MODEL\\enemy_weapon\\missile.x");
	m_Move = { 0.f,0.f,0.f };
    m_fSpeed = (float)NULL;
    m_nUpTime = 120;
    m_bFirst = false;
	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CMissile::Uninit(){
	CObjectX::Uninit();
}

//================================================================================================================================================================
//更新処理
//================================================================================================================================================================
void CMissile::Update(){
    // ミサイルの現在の座標と回転角度を取得
    D3DXVECTOR3* pPos = CObjectX::GetPos();
    D3DXVECTOR3* pRot = CObjectX::GetRot();

    // 着弾処理（地面に到達した場合）
    if (pPos->y <= 10.f){
        CNova::Create(*pPos, 300.f, 120); // 着弾エフェクトを生成
        Uninit();                         // ミサイルを削除
        return;                           // 処理を終了
    }

    // プレイヤーヒット処理(）
    if (HitPlayer(*pPos)) {
        CNova::Create(*pPos, 150.f, 60); // 着弾エフェクトを生成
        Uninit();                         // ミサイルを削除
        return;                           // 処理を終了
    }

    HitPlayer(*pPos);

    // 上昇時間が残っている場合
    if (m_nUpTime > NULL){
        //　ミサイル上昇処理
        UpMissile(*pPos,*pRot);
    }

    // 上昇演出終了後
    else {
      //　目的に向かう
        TergetMove(*pPos, *pRot);
    }

    // ミサイルの位置を更新
    pPos->x += m_Move.x;
    pPos->y += m_Move.y;
    pPos->z += m_Move.z;
    
    // 親クラスの更新処理を呼び出し
    CObjectX::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CMissile::Draw(){
	CObjectX::Draw();
}

//================================================================================================================================================================
// ミサイル上昇処理
//================================================================================================================================================================
void CMissile::UpMissile(D3DXVECTOR3 pos, D3DXVECTOR3& rot){

    D3DXVECTOR3 pPos = pos;

    --m_nUpTime;

    // 敵の回転角度を基準に斜め上方向を計算
    const float moveSpeed = 10.0f;  // 移動速度

    // 角度補完変数
    const float radian = 36.f;
    const float f = 0.2f;

    // 上昇角度（tiltAngle）を自由に設定
    const float tiltAngle = 90.0f * (D3DX_PI / 180.0f);  // 上昇角度を度数法からラジアンに変換（90）

    // 左斜め上の移動方向を計算
    float leftMoveX = sinf(rot.y - D3DX_PI / radian) * moveSpeed * f;   // X方向の移動（左右）
    float leftMoveY = sinf(tiltAngle) * moveSpeed;                    // Y方向（上昇）の角度を調整
    float leftMoveZ = cosf(rot.y - D3DX_PI / radian) * moveSpeed * f;   // Z方向の移動（前後）

    // 右斜め上の移動方向を計算
    float rightMoveX = sinf(rot.y + D3DX_PI / radian) * moveSpeed * f;  // X方向の移動（左右）
    float rightMoveY = sinf(tiltAngle) * moveSpeed;                       // Y方向（上昇）の角度を調整
    float rightMoveZ = cosf(rot.y + D3DX_PI / radian) * moveSpeed * f;  // Z方向の移動（前後）

    // 移動値を左右どちらかに設定（ランダムで選択する例）
    if (m_bFirst) {
        m_Move.x = leftMoveX;
        m_Move.y = leftMoveY;
        m_Move.z = leftMoveZ;

        rot.x = D3DX_PI * 0.65f;
        rot.y = D3DX_PI * 0.5f;

        if (m_nUpTime > 60) {
            CManager::GetInstance()->GetCamera()->SetDirectionTime(60);
            CManager::GetInstance()->GetCamera()->DirectionCamera(pPos,rot, 1000.f);
        }
    }

    else {
        m_Move.x = rightMoveX;
        m_Move.y = rightMoveY;
        m_Move.z = rightMoveZ;

        rot.x = D3DX_PI * 0.65f;
        rot.y = -D3DX_PI * 0.5f;

        if (m_nUpTime <= 60) {
            CManager::GetInstance()->GetCamera()->SetDirectionTime(60);
            CManager::GetInstance()->GetCamera()->DirectionCamera(pPos, rot, 1000.f);
        }
    }

    //エフェクト関係
    D3DXVECTOR3 Pos = { pPos.x, pPos.y - 50.f,pPos.z };  // 出す場所
    CBack_Effect::Create(Pos,rot);                       // 生成
}

//================================================================================================================================================================
// 目的に合わせて追跡
//================================================================================================================================================================
void CMissile::TergetMove(D3DXVECTOR3 pos, D3DXVECTOR3& rot) {

    // プレイヤーのポジションを格納するローカル変数
    D3DXVECTOR3 playerPos(0.0f, 0.0f, 0.0f);

    //ミサイルエフェクト生成位置（Y）
    const float EffCreateY = -50.f;

    // オブジェクトリストを走査
    CObject* pObject = CObject::GetTop();

    while (pObject != nullptr) {

        // プレイヤータイプのオブジェクトを探す
        if (pObject->GetType() == CObject::TYPE::PLAYER) {

            CPlayer3D* pPlayer = dynamic_cast<CPlayer3D*>(pObject);

            if (pPlayer) {
                // プレイヤーとの距離の差分を計算
                float dx = pPlayer->GetPos()->x - pos.x; // x座標の差
                float dz = pPlayer->GetPos()->z - pos.z; // z座標の差
                float dy = pPlayer->GetPos()->y - pos.y; // y座標の差

                // プレイヤーとの距離を計算（3D空間）
                float distance = sqrtf(dx * dx + dz * dz + dy * dy);

                // プレイヤー方向への角度を計算
                float targetAngleY = atan2f(dx, dz);       // y軸（水平）回転
                float targetAngleX = asinf(dy / distance); // x軸（上下）回転

                // ピッチ（上下角度）にさらに下向きのオフセットを追加
                const float pitchOffset = 0.2f * (D3DX_PI / 180.f); // 下向き15°を追加
                targetAngleX -= pitchOffset;

                // 回転制限（ピッチ角度の範囲を制限）
                const float fMinPitch = -45.f * (D3DX_PI / 180.f); // -45°をラジアンに変換
                const float fMaxPitch = 30.f * (D3DX_PI / 180.f);  // +30°をラジアンに変換

                // fAngleX（ピッチ）の制限
                if (targetAngleX < fMinPitch) {
                    targetAngleX = fMinPitch;
                }
                else if (targetAngleX > fMaxPitch) {
                    targetAngleX = fMaxPitch;
                }

                // 現在の回転方向をターゲット方向に補間してスムーズに回転
                const float rotationSpeed = 0.85f; // 回転速度
                rot.y += (targetAngleY - rot.y + D3DX_PI) * rotationSpeed;
                rot.x += (targetAngleX - rot.x) * rotationSpeed;
                rot.z = 0.0f; // z軸の回転はゼロに固定

                // ミサイルの移動ベクトルを計算
                float mx = sinf(rot.y + D3DX_PI) * m_fSpeed; // x方向の移動
                float my = sinf(rot.x) * m_fSpeed;           // y方向の移動
                float mz = cosf(rot.y + D3DX_PI) * m_fSpeed; // z方向の移動

                // m_Moveを設定
                m_Move = { mx, my, mz };

                break; // プレイヤーが見つかったらループを抜ける
            }
        }
        // 次のオブジェクトへ
        pObject = pObject->GetNext();
    }

    //演出中かどうか
    if (CManager::GetInstance()->GetCamera()->GetPlayStay()) {
        //強制ストップ
        m_Move = { (float)NULL,(float)NULL, (float)NULL };
    }

    //　演出ではない場合
    if (!CManager::GetInstance()->GetCamera()->GetPlayStay()) {
        D3DXVECTOR3 Pos = { pos.x,pos.y+EffCreateY,pos.z };
        CBack_Effect::Create(Pos,rot);
    }
}

//================================================================================================================================================================
//　プレイヤーとの衝突判定
//================================================================================================================================================================
bool CMissile::HitPlayer(D3DXVECTOR3 pos) {

    // オブジェクトリストを走査
    CObject* pObject = CObject::GetTop();

    D3DXVECTOR3 Size = {20.f,20.f,20.f};

    while (pObject != nullptr) {

        // プレイヤータイプのオブジェクトを探す
        if (pObject->GetType() == CObject::TYPE::PLAYER) {

            CPlayer3D* pPlayer = dynamic_cast<CPlayer3D*>(pObject);

            // キャストダウン成功時
            if (pPlayer) {
                 // プレイヤーに衝突判定
                 CModelParts PlayerParts = pPlayer->GetPlayerParts();

                 D3DXVECTOR3 HitPlayerPos = { pPlayer->GetPos()->x,
                                              pPlayer->GetPos()->y + PlayerParts.GetPartsRadhiusu().y,
                                              pPlayer->GetPos()->z 
                                            };
                 //　ヒット判定
                 if (CManager::GetInstance()->GetCollision()->HitCircleCollision(
                     pos, HitPlayerPos, Size, PlayerParts.GetPartsRadhiusu()))
                 {
                     D3DXVECTOR3 knockbackDir = D3DXVECTOR3(pPlayer->GetPos()->x - pos.x,
                         pPlayer->GetPos()->y - pos.y,
                         pPlayer->GetPos()->z - pos.z);

                     D3DXVec3Normalize(&knockbackDir, &knockbackDir);
                 
                     float knockbackSpeed = 30.f;
                     D3DXVECTOR3 knockbackForce = knockbackDir * knockbackSpeed;
                 
                     pPlayer->SetMove(knockbackForce);
                     pPlayer->PlayerDamage(10);

                     return true;
                 }
            }
        }
        // 次のオブジェクトへ
        pObject = pObject->GetNext();
    }
    return false;
}

//================================================================================================================================================================
//生成
//================================================================================================================================================================
CMissile* CMissile::Create(D3DXVECTOR3 pos,float s,bool bFirst){
	CMissile* pCMissile = new CMissile();
	pCMissile->Init();
	pCMissile->SetType(TYPE::MISSILE);
	pCMissile->SetPos(pos.x, pos.y, pos.z);
    pCMissile->m_fSpeed = s;
    pCMissile->m_bFirst = bFirst;
	return pCMissile;
}