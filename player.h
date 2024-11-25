//============================================================
//
//�v���C���[[player.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"

//�}�N����`
#define MAX_MAT_PLAYER (512)			//�}�g���b�N�X�̍ő吔
#define PLAYER_SPEED (0.5f)				//�v���C���[�̃X�s�[�h

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 posOld;					//�O��̈ʒu
	D3DXVECTOR3 rot;					//����
	D3DXVECTOR3 rotDest;				//�ڕW�̌���
	D3DXVECTOR3 vtxMin;					//���f���̍ŏ��l
	D3DXVECTOR3 vtxMax;					//���f���̍ő�l
	D3DXVECTOR3 size;					//�T�C�Y(�傫��)
	int nIndxShadow;					//�e�̃C���f�b�N�X�i�[�p
}Player;

//�v���g�^�C�v�錾
void InitPlayer();//�v���C���[�̏���������
void UninitPlayer();//�v���C���[�̏I������
void UpdatePlayer();//�v���C���[�̍X�V����
void DrawPlayer();//�v���C���[�̕`�揈��
Player* GetPlayer();

#endif // !_MODEL_H_
