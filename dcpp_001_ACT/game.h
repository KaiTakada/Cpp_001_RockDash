//===============================================
//
// �Q�[��(game.h)
// Author: ���c ����
//
//===============================================
#ifndef _GAME_H_		//���̃}�N����`������ĂȂ�������
#define _GAME_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "main.h"
#include "manager.h"

//=========================
// �O���錾
//=========================
//class CRenderer;
class CPause;
class CGrowSelecter;
class CTimer;
class CEnemy_Boss;
class CMap;

//=========================
// ���(�V�[��)�N���X
//=========================
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V
	virtual void Draw();		//�`��
	static CGame *Create();		//����

	static CPlayer *GetPlayer() { return m_pPlayer; }							//�v���C���[�̎擾
	static CTimer *GetTimer() { return m_pTimer; }								//�^�C�}�[�̎擾

	static void NullPause() { m_pPause = nullptr; }								//�|�[�Y�|�C���^��null��

protected:

private:
	static CPlayer *m_pPlayer;					//�v���C���[
	static CPause *m_pPause;					//�|�[�Y
	static CTimer *m_pTimer;					//�^�C�}�[
	CMap *m_pMap;								//�}�b�v
	CField *m_pField;							//�n��
};

#endif