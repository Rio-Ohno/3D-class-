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
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffmatPlayer = NULL;
DWORD g_dwNumMatPlayer = 0;
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_MAT_PLAYER] = {};
D3DXMATRIX g_mtxWorldPlayer;
Player g_player;

//============================================================
// �v���C���[�̏���������
//============================================================
void InitPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�e�평����
	g_pMeshPlayer = NULL;
	g_pBuffmatPlayer = NULL;
	g_dwNumMatPlayer = 0;
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nIndxShadow = SetShadow(g_player.pos,g_player.rot,D3DXVECTOR3(1.0f,0.5f,1.0f));

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//X�t�@�C���̓Ǎ�
	D3DXLoadMeshFromX("data\\MODEL\\TV.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffmatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	int nNumVtx;//�ő咸�_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBUff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

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
	g_pMeshPlayer->UnlockVertexBuffer();

	//�T�C�Y�̏�����
	g_player.size = g_player.vtxMax - g_player.vtxMin;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffmatPlayer->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		//�e�N�X�`���|�C���^�̏�����
		g_apTexturePlayer[nCnt] = {};

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓Ǎ�
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&g_apTexturePlayer[nCnt]);

		}
	}
}

//============================================================
// �v���C���[�̏I������
//============================================================
void UninitPlayer()
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffmatPlayer != NULL)
	{
		g_pBuffmatPlayer->Release();
		g_pBuffmatPlayer = NULL;
	}

	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		if (g_apTexturePlayer[nCnt] != NULL)
		{
			g_apTexturePlayer[nCnt]->Release();
			g_apTexturePlayer[nCnt] = NULL;
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
		g_player.pos.x += sinf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.pos.z += cosf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2.0f;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_player.pos.x += sinf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.pos.z += cosf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2.0f;

	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{
		g_player.pos.x += sinf(pCamera->rot.y) * PLAYER_SPEED;
		g_player.pos.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
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

		g_player.pos.x += sinf(rot.y) * PLAYER_SPEED;
		g_player.pos.z += cosf(rot.y) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y;
	}

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.15f;

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
	//CollisionWall();

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetBullet(g_player.pos, g_player.rot, 5.0f);
	}
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
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffmatPlayer->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePlayer[nCnt]);

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCnt);
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