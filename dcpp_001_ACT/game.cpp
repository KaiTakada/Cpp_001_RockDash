//===============================================
//
// �Q�[��(game.cpp)
// Author: ���c ����
//
//===============================================

//=========================
// �C���N���[�h�t�@�C��
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

//=========================
// �}�N����`
//=========================

#if _DEBUG
#define START_TIME (10)		//�X�^�[�g���b��
#else
#define START_TIME (120)		//�X�^�[�g���b��
#endif

//=========================
// �ÓI�����o�ϐ�
//=========================
CPlayer *CGame::m_pPlayer = nullptr;					//�v���C���[
CPause *CGame::m_pPause = nullptr;						//�|�[�Y
CTimer *CGame::m_pTimer = nullptr;						//�^�C�}�[

//============================
// �R���X�g���N�^
//============================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pField = nullptr;
	m_pPause = nullptr;
	m_pTimer = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CGame::~CGame()
{

}

//============================
// ������
//============================
HRESULT CGame::Init()
{
	CScene::Init();

	//�I�u�W�F�N�g�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	////============ �X�|�[�� ============
	////NULL�`�F�b�N
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
// �I��
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

	CScene::Uninit();

	CManager::GetSound()->Stop();
}

//============================
// �X�V
//============================
void CGame::Update()
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputGamepad *pInputPad = CManager::GetInputGamepad();
	bool bPause = CManager::GetPause();

	CScene::Update();

	if (pInputKeyboard->GetTrigger(DIK_P) || pInputPad->GetPress(CInputGamepad::BUTTON_START, 0) == true)
	{//[ P ]�L�[�Ń|�[�Y

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
	{//���Ԑ؂�
		if (m_pTimer->GetValue() <= 0)
		{
			m_pTimer->Uninit();
			m_pTimer = nullptr;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_F))
	{
		CManager::SetResult(CManager::RT_WIN);
	}

	CFade *pFade = CScene::GetFade();

	if (CManager::GetResult() != CManager::RT_NONE)
	{//���ʂ��m�肵����
		
		pFade->SetState(CScene::MODE_RESULT);
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
// �`��
//============================
void CGame::Draw()
{
	CScene::Draw();
}

//============================
// ����
//============================
CGame * CGame::Create()
{
	CGame *pGame = nullptr;

	//�I�u�W�F�N�g����&������
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
