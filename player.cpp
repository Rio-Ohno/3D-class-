//============================================================
//
//�v���C���[[player.cpp]
//Author:Rio Ohno
//
//============================================================

#include"player.h"
#include "bullet.h"
#include "block.h"
#include "wall.h"

//�O���|�o���ϐ��錾
Player g_player;
static  Key_Info g_keyNeutrall[]=
{ //Key0
	{40,
	//�p�[�c0
	{{0.0f,0.2f,0.0f,0.06f, 0.0f, 0.0f},
	//�p�[�c1
	 {0.0f ,0.0f ,0.0f,-0.16f, 0.0f, 0.0f}}
	},
	 //Key1
	{40,
	{{0.0f, 1.2f, 0.0f,0.06f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f,-0.09f, 0.0f, 0.0f}}
	}
};

//============================================================
// �v���C���[�̏���������
//============================================================
void InitPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�e�평����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.nNumModel = 0;
	g_player.nNumMotion = 0;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;
	g_player.nIndxShadow = SetShadow(g_player.pos,g_player.rot,D3DXVECTOR3(1.0f,0.5f,1.0f));
	g_player.bjump = false;
	g_player.bUse = true;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorldPlayer);

	//X�t�@�C���̓Ǎ�
	D3DXLoadMeshFromX("data\\MODEL\\cat\\koshi.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].dwNumMat,
		&g_player.aModel[0].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\cat\\mune.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,
		NULL,
		&g_player.aModel[1].dwNumMat,
		&g_player.aModel[1].pMesh);

	//D3DXLoadMeshFromX("data\\MODEL\\cat\\atama.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[2].pBuffMat,
	//	NULL,
	//	&g_player.aModel[2].dwNumMat,
	//	&g_player.aModel[2].pMesh);

	g_player.nNumModel = 2;												//�p�[�c���̐ݒ�

	//�e�p�[�c�̊K�w�\���ݒ�
	g_player.aModel[0].nIndxModelpParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[1].nIndxModelpParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 9.5f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//g_player.aModel[2].nIndxModelpParent = 1;
	//g_player.aModel[2].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	//g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{

		int nNumVtx;//�ő咸�_��
		DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBUff;//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = g_player.aModel[nCntModel].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

		for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

			//���_���W���r���ă��f���̍ő�ŏ����擾

			if (vtx.x > g_player.vtxMax.x)//x�ő�l
			{
				g_player.vtxMax.x = vtx.x;
			}
			else if (vtx.x < g_player.vtxMin.x)//x�ŏ��l
			{
				g_player.vtxMin.x = vtx.x;
			}

			if (vtx.y > g_player.vtxMax.y)//y�ő�l
			{
				g_player.vtxMax.y = vtx.y;
			}
			else if (vtx.y < g_player.vtxMin.y)//y�ŏ��l
			{
				g_player.vtxMin.y = vtx.y;
			}

			if (vtx.z > g_player.vtxMax.z)//z�ő�l
			{
				g_player.vtxMax.z = vtx.z;
			}
			else if (vtx.z < g_player.vtxMin.z)//z�ŏ��l
			{
				g_player.vtxMin.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBUff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_player.aModel[nCntModel].pMesh->UnlockVertexBuffer();

		//�T�C�Y�̏�����
		g_player.size = g_player.vtxMax - g_player.vtxMin;

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCnt = 0; nCnt < (int)g_player.aModel[nCntModel].dwNumMat; nCnt++)
		{
			//�e�N�X�`���|�C���^�̏�����
			g_player.aModel[nCntModel].apTextureModel[nCnt] = {};

			if (pMat[nCnt].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓Ǎ�
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCnt].pTextureFilename,
					&g_player.aModel[nCntModel].apTextureModel[nCnt]);

			}
		}
	}
}

//============================================================
// �v���C���[�̏I������
//============================================================
void UninitPlayer()
{
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{

		//���b�V���̔j��
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}

		//�e�N�X�`���̔j��
		for (int nCnt1 = 0; nCnt1 < (int)g_player.aModel[nCntModel].dwNumMat; nCnt1++)
		{
			if (g_player.aModel[nCntModel].apTextureModel[nCnt1] != NULL)
			{
				g_player.aModel[nCntModel].apTextureModel[nCnt1]->Release();
				g_player.aModel[nCntModel].apTextureModel[nCnt1] = NULL;
			}
		}
	}
}

//============================================================
// �v���C���[�̍X�V����
//============================================================
void UpdatePlayer()
{
	//�J�����̏��擾
	Camera* pCamera = GetCamera();

	g_player.posOld = g_player.pos;

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2.0f;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.move.z += cosf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2.0f;

	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPEED;
		g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�E��荶���

		if (g_player.rot > 0)
		{
			rot.y = pCamera->rot.y + D3DX_PI;
		}
		else if (g_player.rot < 0)
		{
			rot.y = -(pCamera->rot.y + D3DX_PI);
		}

		g_player.move.x += sinf(rot.y) * PLAYER_SPEED;
		g_player.move.z += cosf(rot.y) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y;
	}

	//�W�����v
	if (g_player.bjump == false)
	{
		if (KeyboardTrigger(DIK_SPACE) == true)
		{
			g_player.move.y += 30.0f;
			g_player.bjump = true;
		}
	}

	g_player.move.y -= 0.8f;

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.15f;

	//�ʒu�̍X�V
	g_player.pos += g_player.move;

	//�ړ��ʂ̍X�V(����)
	g_player.move.x = (0.0f - g_player.move.x) * 0.1f;
	g_player.move.y = (0.0f - g_player.move.y) * 0.1f;
	g_player.move.z = (0.0f - g_player.move.z) * 0.1f;

	//������
	if (g_player.pos.y < 0)
	{
		g_player.pos.y = 0;
		g_player.bjump = false;
	}

	//�e�̈ʒu�X�V
	SetPositionShadow(g_player.nIndxShadow, g_player.pos);

	//�ڕW�̈ړ������i�p�x�j�̕␳
	if (g_player.rot.y > D3DX_PI)
	{	  
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}

	//�����蔻��
	//CollisionBlock_X();
	//CollisionBlock_Z();
	CollisionWall();

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, g_player.pos.z), g_player.rot, 5.0f);
	}

	//�S���f��(�p�[�c)�̍X�V
	//for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	//{
	//	//�L�[��񂩂�ʒu�ƌ������Z�o
	//	int
	//}
}

//============================================================
// �v���C���[�̕`�揈��
//============================================================
void DrawPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorldPlayer);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);


	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX  mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;				//�e�̃}t���b�N�X

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�p�[�c�̐e�}�g���b�N�X�̐ݒ�
		if (g_player.aModel[nCntModel].nIndxModelpParent != -1)//�q�̎�
		{
			mtxParent = g_player.aModel[0].mtxWorld;
		}
		else//�e�̎�
		{
			mtxParent = g_player.mtxWorldPlayer;
		}

		//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		for (int nCnt1 = 0; nCnt1 < (int)g_player.aModel[nCntModel].dwNumMat; nCnt1++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCnt1].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_player.aModel[nCntModel].apTextureModel[nCnt1]);

			//���f��(�p�[�c)�̕`��
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCnt1);
		}

	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}

//============================================================
// �v���C���[�̏��擾
//============================================================
Player* GetPlayer()
{
	return &g_player;
}

void SetMotion(MOTIONTYPE type)
{
	switch (g_player.motionType)
	{
	case MOTIONTYPE_NEUTRAL:

		g_player.bLoopMotion = true;
		g_player.nNumKey = 2;
		

		break;

	case MOTIONTYPE_MOVE:
		break;

	case MOTIONTYPE_ACTION:
		break;

	case MOTIONTYPE_JUMP:
		break;

	}
}