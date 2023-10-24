//===============================================
//
// �X�R�A(score.cpp)
// Author ���c ����
//
//===============================================
#ifndef _TIMER_H_		//���̃}�N����`������ĂȂ�������
#define _TIMER_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

//=========================
// �C���N���[�h�t�@�C��
//=========================
#include "manager.h"
#include "object.h"

//=========================
// �}�N����`
//=========================
#define MAX_TIME_SCORE (3)	//�X�R�A����

//=========================
// �O���錾
//=========================
class CNumber;
class CScore;
class CObject2D;

//=========================
// �I�u�W�F�N�g2D�w�i�N���X
//=========================
class CTimer : public CObject
{
public:
	struct STime
	{
		int nMinute;		//��
		int nSecond;		//�b
		int nMilliSecond;		//�R���}�b
		
		STime &operator+=(const STime &time);
	};

	CTimer();		//�R���X�g���N�^
	~CTimer();		//�f�X�g���N�^

	HRESULT Init(void);							//������(�f�t�H)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//������(�I�o��)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);		//������(�I�o��)
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��

	static CTimer *Create(void);		//����
	static CTimer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);		//����

	void SetValue(int nValue);		//�X�R�A�l�ݒ�
	void CntValue(int nValue);		//�X�R�A�l���Z
	int GetValue() { return m_nValue; }		//�X�R�A�l�擾

	void SetTime(STime time);		//�X�R�A�l�ݒ�
	void CntTime(STime time);		//�X�R�A�l���Z
	STime GetTime() { return m_time; }		//�X�R�A�l�擾

	//���������֐��Ŏd���Ȃ��ɍ�����B��ŏ�������
	void SetPos(const D3DXVECTOR3 pos);			//�ʒu�ݒ�
	void SetRot(const D3DXVECTOR3 rot);			//�����ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }		//�ʒu�擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//�����擾

protected:

private:
	CScore *m_apScore[MAX_TIME_SCORE];		//�X�R�A���
	CObject2D *m_apColon[MAX_TIME_SCORE - 1];		//�X�R�A���
	STime m_time;		//���Ԍ^�f�[�^
	int m_nValue;		//�X�R�A�̒l
	int m_nSecond;		//1�b���萔�l
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
};

#endif