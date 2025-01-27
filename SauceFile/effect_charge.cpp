//================================================================================================================================================================
//
//3D弾処理[bullet3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "effect_charge.h"
#include "billboard.h"
#include "manager.h"
#include "player_3d.h"

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================
#define	BLOCK_WIDE   (3.0f) //3D弾の横半径
#define	BLOCK_HEIGHT (3.0f) //3D弾の縦半径

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CCharge_Effect::CCharge_Effect() :CBillboard(0)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CCharge_Effect::~CCharge_Effect()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CCharge_Effect::Init()
{
    CBillboard::Init();

    SetSize(BLOCK_WIDE, BLOCK_WIDE);

    m_nLife = 60;

    SetCollar(255, 0, 0, 255);

    SetTexture("data\\TEXTURE\\effect000.jpg");

    return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CCharge_Effect::Uninit()
{
    CBillboard::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CCharge_Effect::Update()
{
    D3DXVECTOR3* pPos = CBillboard::GetPos();
    D3DXVECTOR3* pSize = CBillboard::GetSize();

    m_nLife--;

    if (m_nLife < 0) {
        Uninit();
    }

    pPos->x += m_move.x;
    pPos->y += m_move.y;
    pPos->z += m_move.z;

    CBillboard::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CCharge_Effect::Draw()
{
    CRenderer* pRenderer = nullptr;

    pRenderer = CManager::GetInstance()->GetRenderer();

    LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

    //αブレンディングを加算合成に設定
    RendererDivice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    RendererDivice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    RendererDivice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    CBillboard::Draw();

    //αブレンディンを元に戻そう
    RendererDivice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    RendererDivice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    RendererDivice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================================================================================================================================================================
// 3D弾生成
//================================================================================================================================================================
CCharge_Effect* CCharge_Effect::Create(D3DXVECTOR3 playerPos,int power)
{
    // エフェクトの新規生成
    CCharge_Effect* pCCharge_Effect = new CCharge_Effect();
    // 初期化
    pCCharge_Effect->Init();

    // ランダムで一定範囲内に生成位置を決定

    float spawnRange = 100.0f;  // 生成範囲（この値で調整）
    D3DXVECTOR3 randomOffset;
    randomOffset.x = (rand() % 200 - 100) / 100.0f * spawnRange;  // -spawnRange 〜 +spawnRange
    randomOffset.y = (rand() % 200 - 100) / 100.0f * spawnRange;  // 高さの範囲を調整
    randomOffset.z = (rand() % 200 - 100) / 100.0f * spawnRange;

    // エフェクトの位置を設定（プレイヤー位置にオフセットを加える）
    D3DXVECTOR3 effectPos = playerPos + randomOffset;
    pCCharge_Effect->SetPos(effectPos.x, effectPos.y, effectPos.z);

    // プレイヤーに向かう方向ベクトルを計算
    D3DXVECTOR3 directionToPlayer = playerPos - effectPos;

    //各種カラー変数
    int r = NULL , g = NULL, b = NULL;

    //躍動感のあるようにスピード調整
    float fspeedSplit = (float)NULL;

    //段階識別処理
    if (power == CPlayer3D::POWERRANK::FIRST)
    {
        b = 255;
        fspeedSplit = 1.f;
    }
    else if (power == CPlayer3D::POWERRANK::SECOND)
    {
        b = 255, g = 255;
        fspeedSplit = 1.25f;
    }
    else if (power == CPlayer3D::POWERRANK::THIRD)
    {
        g = 255;
        fspeedSplit = 1.5f;
    }
    else if (power == CPlayer3D::POWERRANK::FORTH)
    {
        g = 255, r = 255;
        fspeedSplit = 1.75f;
    }
    else if (power == CPlayer3D::POWERRANK::FIVE)
    {
        g = 50, r = 255;
        fspeedSplit = 2.f;
    }
    else if (power == CPlayer3D::POWERRANK::FULLPOWER)
    {
        r = 255;
        fspeedSplit = 2.5f;
    }

    //判別完了した各種色の数値を代入
    pCCharge_Effect->SetCollar(r,g,b,255);

    // 正規化（単位ベクトル化）
    D3DXVec3Normalize(&directionToPlayer, &directionToPlayer);

    // 移動方向を設定
    pCCharge_Effect->m_move = directionToPlayer * fspeedSplit;

    return pCCharge_Effect;
}