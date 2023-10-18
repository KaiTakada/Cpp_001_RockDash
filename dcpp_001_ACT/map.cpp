//===============================================
//
// �}�b�v(map.cpp)
// Author:Kai Takada
//
//===============================================

//============================
// �C���N���[�h�t�@�C��
//============================
#include "manager.h"	//�匳
#include "game.h"
#include "map.h"
#include "input.h"
#include "block.h"

//=======================
//�}�N����`
//=======================

//=======================
// �t�@�C���p�X
//=======================
const char *c_apFilenameMap[CMap::MAP_MAX] =
{
	"data\\SET\\MAP\\save.txt",
	"data\\SET\\MAP\\load.txt",
};

//=======================
// �ÓI�����o�ϐ�
//=======================

//============================
// �R���X�g���N�^
//============================
CMap::CMap(int nPriority) : CObject(nPriority)
{
	m_pBlock = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CMap::~CMap()
{

}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CMap::Init()
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	m_pBlock->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//====================================
// ������(�ʒu�I�o��)
//====================================
HRESULT CMap::Init(const D3DXVECTOR3 pos)
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	m_pBlock->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//============================
// �I��
//============================
void CMap::Uninit(void)
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	Release();
}

//============================
// �X�V
//============================
void CMap::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CBlock *pBlock;
	D3DXVECTOR3 pos;
	
	if (m_pBlock != nullptr)
	{
		pos = m_pBlock->GetPos();
	}

	//�J�[�\���̈ړ�
	if (pInputKeyboard->GetTrigger(DIK_W))
	{//��
		pos.y += 10.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_S))
	{//��
		pos.y -= 10.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_A))
	{//��
		pos.x -= 10.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_D))
	{//��
		pos.x += 10.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN))
	{//�u���b�N�ݒu
		pBlock = CBlock::Create(pos);
		pBlock->SetSize(m_pBlock->GetSize());
	}
}

//============================
// �`��
//============================
void CMap::Draw(void)
{

}

//============================
// �|�[�Y�̐���
//============================
CMap * CMap::Create(D3DXVECTOR3 pos)
{
	CMap *pMap = nullptr;

	//�I�u�W�F�N�g����&������
	pMap = new CMap;

	if (pMap != nullptr)
	{
		if (FAILED(pMap->Init(pos)))
		{
			return nullptr;
		}
		else
		{

		}
	}
	else
	{
		return nullptr;
	}

	return pMap;
}
