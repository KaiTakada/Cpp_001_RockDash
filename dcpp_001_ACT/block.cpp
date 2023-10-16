//==================================================
//
// �u���b�N����(block.cpp)
// Author : Kai Takada
//
//==================================================
#include "block.h"
#include "manager.h"

//=======================
// �}�N����`
//=======================
#define PLAYER_EXCESSX (0.0f)						//�v���C���[�̃e�N�X�`���̕��̗]���ȕ�����

//=======================
// �o�C�i���t�@�C����
//=======================
const char *c_apFileBlock[CBlock::TYPE_MAX] =
{
	//"data\\MODEL\\BLOCK\\brick.x",		//�ʏ�u���b�N
	"data\\MODEL\\BLOCK\\BIGbrick.x",		//�ʏ�u���b�N
};

//=======================
// �ÓI�����o�ϐ��錾
//=======================
int CBlock::m_nNumAll = 0;											//���ݎg���Ă���u���b�N��

//=======================
// �R���X�g���N�^
//=======================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NORMAL;
}

//=======================
// �f�X�g���N�^
//=======================
CBlock::~CBlock()
{

}

//=======================
//�u���b�N�̏���������
//=======================
HRESULT CBlock::Init(void)
{
	m_type = TYPE_NORMAL;

	CObjectX::Init();
	
	m_posOld = GetPos();
	
	SetType(TYPE_BLOCK);

	return S_OK;
}

//=======================
//�u���b�N�̏���������
//=======================
HRESULT CBlock::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_NORMAL;

	CObjectX::Init(pos, rot);

	SetType(TYPE_BLOCK);

	return S_OK;
}

//=======================
//�u���b�N�̏I������
//=======================
void CBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//=======================
//�u���b�N�̍X�V����
//=======================
void CBlock::Update(void)
{
	m_posOld = GetPos();

	CollisionRect();

	CObjectX::Update();
}

//=======================
//�u���b�N�̕`�揈��
//=======================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//=======================
//�u���b�N�̐ݒ菈��
//=======================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CBlock *pBlock = nullptr;

	//�I�u�W�F�N�g����&������
	pBlock = new CBlock;

	if (pBlock != nullptr)
	{
		if (FAILED(pBlock->Init(pos, rot)))
		{
			return nullptr;
		}
		else
		{
			pBlock->m_posOld = pos;

			CXModel *pXmodel = CManager::GetInstance()->GetXModel();
			pBlock->SetIdxModel(pXmodel->Regist(c_apFileBlock[type], &vtxMin, &vtxMax));		//���f�����蓖��
		
			vtxMin = pXmodel->GetAddress(pBlock->GetIdxModel())->vtxMin;
			vtxMax = pXmodel->GetAddress(pBlock->GetIdxModel())->vtxMax;
			pBlock->SetVtx(vtxMin, vtxMax);
		}
	}
	else
	{
		return nullptr;
	}

	return pBlock;
}

//============================
//�u���b�N�̓����蔻��(����ŉ����߂�)
//============================
bool CBlock::CollisionRect(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 sizeMin, sizeMax;
	sizeMin = GetMinVtx();
	sizeMax = GetMaxVtx();

	D3DXVECTOR3 Objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ObjposOld = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 Objsize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Objmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����߂���

	bool bLand = false;			//���n�������ǂ���
	bool Collision = false;			//�����蔻�肪���������ǂ���

	for (int nCntPrt = 0; nCntPrt < PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				CObject::TYPE type = pObject->GetType();	//����̃I�u�W�F�N�g�̃^�C�v

				if (type == CObject::TYPE_PLAYER)
				{//�v���C���\��������
					Objpos = pObject->GetPos();
					ObjposOld = pObject->GetPosOld();
					Objsize = pObject->GetSize();
					Objmove = pObject->GetMove();

					//Objpos.y += 50.0f;
					//ObjposOld.y += 50.0f;

					if (pObject->GetJump() == false)
					{
						if (ObjposOld.x + Objsize.x <= pos.x + sizeMin.x
							&& Objpos.x + Objsize.x > pos.x + sizeMin.x
							&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
							&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMin.x) - (Objpos.x + Objsize.x) - 0.1f;
							Collision = true;
						}
						else if (ObjposOld.x - Objsize.x >= pos.x + sizeMax.x
							&& Objpos.x - Objsize.x <= pos.x + sizeMax.x
							&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
							&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMax.x) - (Objpos.x - Objsize.x) + 0.1f;
							Collision = true;
						}

						if (ObjposOld.z + Objsize.z <= pos.z + sizeMin.z
							&& Objpos.z + Objsize.z >= pos.z + sizeMin.z
							&& Objpos.x + Objsize.x >= pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x <= pos.x + sizeMax.x - 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N�k
							move.z = (pos.z + sizeMin.z) - (Objpos.z + Objsize.z) - 0.1f;
							Collision = true;
						}
						else if (ObjposOld.z - Objsize.z >= pos.z + sizeMax.z
							&& Objpos.z - Objsize.z <= pos.z + sizeMax.z
							&& Objpos.x + Objsize.x >= pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x <= pos.x + sizeMax.x - 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.z = (pos.z + sizeMax.z) - (Objpos.z - Objsize.z) + 0.1f;
							Collision = true;
						}

						if (ObjposOld.y - Objsize.y >= pos.y + sizeMax.y
							&& Objpos.y - Objsize.y <= pos.y + sizeMax.y
							&& Objpos.x + Objsize.x > pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x < pos.x + sizeMax.x + 0.1f
							&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
							&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							move.y = (pos.y + sizeMax.y) - (Objpos.y - Objsize.y) + 0.1f;
							pObject->SetJump(false);
							Collision = true;
							bLand = true;
						}
						else if (ObjposOld.y + Objsize.y <= pos.y + sizeMin.y
							&& Objpos.y + Objsize.y >= pos.y + sizeMin.y
							&& Objpos.x + Objsize.x > pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x < pos.x + sizeMax.x + 0.1f
							&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
							&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							move.y = (pos.y + sizeMin.y) - (Objpos.y + Objsize.y) - 0.1f;
							Collision = true;
						}
					}
					else
					{
						if (ObjposOld.x + Objsize.x <= pos.x + sizeMin.x
						&& Objpos.x + Objsize.x > pos.x + sizeMin.x
						&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
						&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMin.x) - (Objpos.x + Objsize.x) - 0.1f;
							Collision = true;
						}
						else if (ObjposOld.x - Objsize.x >= pos.x + sizeMax.x
							&& Objpos.x - Objsize.x <= pos.x + sizeMax.x
							&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
							&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N��
							move.x = (pos.x + sizeMax.x) - (Objpos.x - Objsize.x) + 0.1f;
							Collision = true;
						}

						if (ObjposOld.z + Objsize.z <= pos.z + sizeMin.z
							&& Objpos.z + Objsize.z >= pos.z + sizeMin.z
							&& Objpos.x + Objsize.x >= pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x <= pos.x + sizeMax.x - 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{//�u���b�N�k
							move.z = (pos.z + sizeMin.z) - (Objpos.z + Objsize.z) - 0.1f;
							Collision = true;
						}
						else if (ObjposOld.z - Objsize.z >= pos.z + sizeMax.z
							&& Objpos.z - Objsize.z <= pos.z + sizeMax.z
							&& Objpos.x + Objsize.x >= pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x <= pos.x + sizeMax.x - 0.1f
							&& ((Objpos.y + Objsize.y >= pos.y + sizeMin.y + 0.1f
								&& Objpos.y + Objsize.y <= pos.y + sizeMax.y - 0.1f)
								|| (Objpos.y - Objsize.y >= pos.y + sizeMin.y + 0.1f
									&& Objpos.y - Objsize.y <= pos.y + sizeMax.y - 0.1f)))
						{
							move.z = (pos.z + sizeMax.z) - (Objpos.z - Objsize.z) + 0.1f;
							Collision = true;
						}

						if (ObjposOld.y - Objsize.y >= pos.y + sizeMax.y
							&& Objpos.y - Objsize.y <= pos.y + sizeMax.y
							&& Objpos.x + Objsize.x > pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x < pos.x + sizeMax.x + 0.1f
							&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
							&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							//move.y = (pos.y + sizeMax.y) - (Objpos.y - Objsize.y) + 0.1f;
							pObject->SetJump(false);
							Collision = true;
							bLand = true;
						}
						else if (ObjposOld.y + Objsize.y <= pos.y + sizeMin.y
							&& Objpos.y + Objsize.y >= pos.y + sizeMin.y
							&& Objpos.x + Objsize.x > pos.x + sizeMin.x + 0.1f
							&& Objpos.x - Objsize.x < pos.x + sizeMax.x + 0.1f
							&& Objpos.z + Objsize.z > pos.z + sizeMin.z + 0.1f
							&& Objpos.z - Objsize.z < pos.z + sizeMax.z + 0.1f)
						{//�u���b�N��
							D3DXVECTOR3 Objmove = pObject->GetMove();
							pObject->SetMove(D3DXVECTOR3(Objmove.x, 0.0f, Objmove.z));

							//move.y = (pos.y + sizeMin.y) - (Objpos.y + Objsize.y) - 0.1f;
							Collision = true;
						}

					}
				}

				if (Collision)
				{
					pObject->SetPos(Objpos + move);
					break;
				}

				pObject = pObject->GetNext();
			}
			else
			{// (pObject == NULL) == End�܂ōs�������Ă��Ƃł��̗D��x�͏I��
				break;
			}
		}
	}

	return bLand;
}
