//============================================================
//
//�C���f�b�N�X�o�b�t�@[meshfield.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include"main.h"

//�}�N����`
#define MAX_X (2)																		//x������
#define MAX_Z (3)																		//z������
#define MAX_VERTEX ((MAX_X+1)*(MAX_Z+1))												//���_��
#define MAX_INDX ((MAX_Z * 2) * (MAX_X + (MAX_Z * 2) -1))								//�C���f�b�N�X��((x+1)*2*z+(z-1)*(�k�ރ|���S����=4Z))
#define MAX_POLY ((MAX_Z*2)*(MAX_X+(MAX_Z-1)*2))										//�|���S����(x*z*2+(z-1)*(�k�ރ|���S��=4Z))

//���b�V���t�B�[���h�\����
typedef struct
{
	D3DXVECTOR3 pos;																	//�ʒu
	D3DXVECTOR3 rot;																	//����
	D3DXMATRIX mtxWorld;																//���[���h�}�g���b�N�X
}MeshField;

//�v���g�^�C�v�錾
void InitMeshField();																	//������
void UninitMeshField();																	//�I������
void UpdateMeshField();																	//�X�V����
void DrawMeshField();																	//�`�揈��

#endif // !_MeshField_H_
