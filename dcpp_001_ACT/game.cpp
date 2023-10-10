//===============================================
//
// ゲーム(game.cpp)
// Author: 髙田 佳依
//
//===============================================

//=========================
// インクルードファイル
//=========================
#include "game.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "field.h"
#include "input.h"
#include "spawn.h"
#include "pause.h"
#include "fade.h"
#include "timer.h"
#include "growselecter.h"
#include "enemy_boss.h"
#include "result.h"

//=========================
// マクロ定義
//=========================

#if _DEBUG
#define START_TIME (10)		//スタート時秒数
#else
#define START_TIME (120)		//スタート時秒数
#endif

//=========================
// 静的メンバ変数
//=========================
CPlayer *CGame::m_pPlayer = nullptr;					//プレイヤー
CPause *CGame::m_pPause = nullptr;						//ポーズ
CTimer *CGame::m_pTimer = nullptr;						//タイマー

//============================
// コンストラクタ
//============================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pField = nullptr;
	m_pPause = nullptr;
	m_pTimer = nullptr;
	m_pResult = nullptr;

	m_bResult = false;
}

//============================
// デストラクタ
//============================
CGame::~CGame()
{

}

//============================
// 初期化
//============================
HRESULT CGame::Init()
{
	m_bResult = false;

	CScene::Init();

	//オブジェクトの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	////============ スポーン ============
	////NULLチェック
	//if (m_pSpawn != nullptr)
	//{
	//	m_pSpawn->Uninit();
	//	m_pSpawn = nullptr;
	//}

	//if (m_pSpawn == nullptr)
	//{
	//	m_pSpawn = CSpawn::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	//else
	//{
	//	return -1;
	//}
	
	if (m_pTimer != nullptr)
	{
		m_pTimer = nullptr;
	}

	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.45f, SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	m_pTimer->SetValue(START_TIME);

	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//============================
// 終了
//============================
void CGame::Uninit()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		m_pPause = nullptr;
	}

	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	if (m_pResult != nullptr)
	{
		m_pResult->Uninit();
		m_pResult = nullptr;
	}

	CScene::Uninit();

	CManager::GetSound()->Stop();
}

//============================
// 更新
//============================
void CGame::Update()
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamepad *pInputPad = CManager::GetInputGamepad();
	bool bPause = CManager::GetPause();

	CScene::Update();

	if (m_bResult == true)
	{//リザルト時はリザルトのみ更新
		if (bPause == true)
		{
			//リザルト表示
			if (m_pResult != nullptr)
			{
				m_pResult->Update();
			}
		}
		else
		{
			CManager::InvPause();
		}

		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_P) || pInputPad->GetPress(CInputGamepad::BUTTON_START, 0) == true)
	{//[ P ]キーでポーズ

		if (m_pPause == nullptr)
		{
			m_pPause = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		}
		else
		{
			m_pPause->Uninit();
			m_pPause = nullptr;
		}

		CManager::InvPause();
	}

	if (m_pPause != nullptr && bPause == true)
	{
		m_pPause->Update();
	}

	if (m_pTimer != nullptr)
	{//時間切れ
		if (m_pTimer->GetValue() <= 0)
		{
			m_pTimer->Uninit();
			m_pTimer = nullptr;
		}
	}

	if (CManager::GetResult() != CManager::RT_NONE && m_bResult == false)
	{//結果が確定したら

		//リザルト表示
		if (m_pResult != nullptr)
		{
			m_pResult->Uninit();
			m_pResult = nullptr;
		}

		m_pResult = CResult::Create();
		m_bResult = true;
	}

	int nNumCsr = 0;

	if (bPause == true)
	{
		nNumCsr = ShowCursor(true);
	}
	else
	{
		nNumCsr = ShowCursor(false);
	}
}

//============================
// 描画
//============================
void CGame::Draw()
{
	CScene::Draw();
}

//============================
// 生成
//============================
CGame * CGame::Create()
{
	CGame *pGame = nullptr;

	//オブジェクト生成&初期化
	pGame = new CGame;

	if (pGame != nullptr)
	{
		if (FAILED(pGame->Init()))
		{
			return nullptr;
		}
		else
		{
			//pGame->m_mode = CScene::MODE_GAME;
		}
	}
	else
	{
		return nullptr;
	}

	return pGame;
}
