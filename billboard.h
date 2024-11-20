//============================================================
//
//�r���{�[�h[billboard.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include"main.h"

//�}�N����`
#define MAX_BILLBOARD (256)											//�r���{�[�h�̍ő吔

//�r���{�[�h�\����
typedef struct
{
	D3DXVECTOR3 pos;												//�ʒu
	D3DXVECTOR3 rot;												//����
	D3DXVECTOR3 dir;												//�����x�N�g��(move?)
	D3DXMATRIX mtxWorld;											//���[���h�}�g���b�N�X
	float radius;													//���a
	bool bUse;														//�g�p���Ă��邩�ǂ���
}Billboard;

//�v���g�^�C�v�錾
void InitBillboard();												//����������
void UninitBillboard();												//�I������
void UpdateBillboard();												//�X�V����
void DrawBillboard();												//�`�揈��
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, float radius);	//�ݒ菈��

#endif // !_Billboard_H_
