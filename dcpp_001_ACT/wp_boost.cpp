//==================================================
//
// �u�[�X�^�[(wp_boost.cpp) �p���FCWeapon
// Author : Kai Takada
//
//==================================================
#include "wp_boost.h"
#include "weapon.h"
#include "Xmodel.h"
#include "manager.h"
#include "bullet.h"

#include "sound.h"
//#include "particle.h"

//=======================
// �}�N����`
//=======================
#define READ_SIZE (128)		//�Ǎ��|�C���^�T�C�Y

//=======================
// �ÓI�����o�ϐ��錾
//=======================

//=======================
// �R���X�g���N�^
//=======================
CBoost::CBoost(int nPriority) : CWeapon(nPriority)
{

}

//=======================
// �f�X�g���N�^
//=======================
CBoost::~CBoost()
{

}

//=======================
// ����������
//=======================
HRESULT CBoost::Init(void)
{
	CWeapon::Init();
	
	SetType(TYPE_WEAPON);

	return S_OK;
}

//=======================
// ����������
//=======================
HRESULT CBoost::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CWeapon::Init(pos, rot, CWeapon::WPNTYPE_BOOST);

	SetType(TYPE_WEAPON);

	return S_OK;
}

//=======================
// �I������
//=======================
void CBoost::Uninit(void)
{
	CWeapon::Uninit();
}

//=======================
// �X�V����
//=======================
void CBoost::Update(void)
{
	CWeapon::Update();
}

//=======================
// �`�揈��
//=======================
void CBoost::Draw(void)
{
	CWeapon::Draw();
}

//=======================
// ��������
//=======================
CBoost *CBoost::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	CBoost *pWeapon = nullptr;

	//�I�u�W�F�N�g����&������
	pWeapon = new CBoost;

	if (pWeapon != nullptr)
	{
		if (FAILED(pWeapon->Init(pos, rot)))
		{
			return nullptr;
		}
		else
		{
			//���f���̊��蓖�Ă͐e�ňꊇ�ōs��
		}
	}
	else
	{
		return nullptr;
	}

	return pWeapon;
}
