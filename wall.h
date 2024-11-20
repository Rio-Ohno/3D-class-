//============================================================
//
//��[wall.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"
#include"camera.h"

//�}�N����`
#define MAX_WALL (10)																		//�ǂ̍ő吔

//�ǂ̍\����
typedef struct
{
	D3DXVECTOR3 pos;																		//�ʒu
	D3DXVECTOR3 rot;																		//����
	D3DXMATRIX mtxWorldWall;																//���[���h�}�g���b�N�X
	bool bUse;																				//�g�p���Ă��邩�ǂ���
}Wall;

//�v���g�^�C�v�錾
void InitWall();																			//�ǂ̏���������
void UninitWall();																			//�ǂ̏I������
void UpdateWall();																			//�ǂ̍X�V����
void DrawWall();																			//�ǂ̕`�揈��
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fx,float fy, float fz, float a);		//�ǂ̐ݒ菈��

#endif // !_Wall_H_