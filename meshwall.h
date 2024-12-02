//============================================================
//
//�C���f�b�N�X�o�b�t�@[meshwall.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include"main.h"

//�}�N����`
#define MAX_X_WALL (2)																	//x������
#define MAX_Y_WALL (1)																	//z������
#define MAX_VERTEX_WALL ((MAX_X_WALL+1)*(MAX_Y_WALL+1))									//���_��
#define MAX_INDX_WALL ((MAX_Y_WALL * 2) * (MAX_X_WALL + (MAX_Y_WALL * 2) -1))			//�C���f�b�N�X��((x+1)*2*z+(z-1)*(�k�ރ|���S����=4Z))
#define MAX_POLY_WALL ((MAX_Y_WALL*2)*(MAX_X_WALL+(MAX_Y_WALL-1)*2))					//�|���S����(x*z*2+(z-1)*(�k�ރ|���S��=4Z))
#define MAX_MESHWALL (4)																	//�ǂ̍ő吔

//���b�V���t�B�[���h�\����
typedef struct
{
	D3DXVECTOR3 pos;																	//�ʒu
	D3DXVECTOR3 rot;																	//����
	float  fHight;																		//����
	float  fWidth;																		//��
	D3DXMATRIX mtxWorld;																//���[���h�}�g���b�N�X
	bool bUse;																			//�g�p���Ă��邩�ǂ���
}MeshWall;

//�v���g�^�C�v�錾
void InitMeshWall();																	//������
void UninitMeshWall();																	//�I������
void UpdateMeshWall();																	//�X�V����
void DrawMeshWall();																	//�`�揈��
void SetMeshWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot);										//�ݒ菈��

#endif // !_MeshWall_H_

