//============================================================
//
//�u���b�N[block.cpp]
//Author:Rio Ohno
//
//============================================================

#include"block.h"

//�O���|�o���ϐ��錾
LPD3DXMESH g_pMeshBlock = NULL;
LPD3DXBUFFER g_pBuffmatBlock = NULL;
DWORD g_dwNumMatBlock = 0;
LPDIRECT3DTEXTURE9 g_apTextureBlock[MAX_MAT_BLOCK] = {};
D3DXVECTOR3 g_posBlock;
D3DXVECTOR3 g_rotBlock;
D3DXVECTOR3 g_vtxMinBlock;//���f���̍ŏ��l
D3DXVECTOR3 g_vtxMaxBlock;//���f���̍ő�l
D3DXMATRIX g_mtxWorldBlock;

//============================================================
// ���f���̏���������
//============================================================
void InitBlock()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�e�평����
	g_pMeshBlock = NULL;
	g_pBuffmatBlock = NULL;
	g_dwNumMatBlock = 0;
	g_posBlock = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
	g_rotBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBlock);

	//X�t�@�C���̓Ǎ�
	D3DXLoadMeshFromX("data\\MODEL\\box000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffmatBlock,
		NULL,
		&g_dwNumMatBlock,
		&g_pMeshBlock);

	int nNumVtx;//�ő咸�_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBUff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = g_pMeshBlock->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshBlock->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

		//���_���W���r���ă��f���̍ő�ŏ����擾

		if (vtx.x > g_vtxMaxBlock.x)//x�ő�l
		{
			g_vtxMaxBlock.x = vtx.x;
		}
		else if (vtx.x < g_vtxMinBlock.x)//x�ŏ��l
		{
			g_vtxMinBlock.x = vtx.x;
		}

		if (vtx.y > g_vtxMaxBlock.y)//y�ő�l
		{
			g_vtxMaxBlock.y = vtx.y;
		}
		else if (vtx.y < g_vtxMinBlock.y)//y�ŏ��l
		{
			g_vtxMinBlock.y = vtx.y;
		}

		if (vtx.z > g_vtxMaxBlock.z)//z�ő�l
		{
			g_vtxMaxBlock.z = vtx.z;
		}
		else if (vtx.z < g_vtxMinBlock.z)//z�ŏ��l
		{
			g_vtxMinBlock.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBUff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pMeshBlock->UnlockVertexBuffer();
		
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffmatBlock->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatBlock; nCnt++)
	{
		//�e�N�X�`���|�C���^�̏�����
		g_apTextureBlock[nCnt] = {};

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓Ǎ�
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&g_apTextureBlock[nCnt]);

		}
	}
}

//============================================================
// ���f���̏I������
//============================================================
void UninitBlock()
{
	//���b�V���̔j��
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffmatBlock != NULL)
	{
		g_pBuffmatBlock->Release();
		g_pBuffmatBlock = NULL;
	}

	for (int nCnt = 0; nCnt < (int)g_dwNumMatBlock; nCnt++)
	{
		if (g_apTextureBlock[nCnt] != NULL)
		{
			g_apTextureBlock[nCnt]->Release();
			g_apTextureBlock[nCnt] = NULL;
		}
	}
}

//============================================================
// ���f���̍X�V����
//============================================================
void UpdateBlock()
{

}

//============================================================
// ���f���̕`�揈��
//============================================================
void DrawBlock()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBlock);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotBlock.y, g_rotBlock.x, g_rotBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBlock.x, g_posBlock.y, g_posBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlock);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffmatBlock->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatBlock; nCnt++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBlock[nCnt]);

		//���f��(�p�[�c)�̕`��
		g_pMeshBlock->DrawSubset(nCnt);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}

void CollisionBlock_X()
{
	Player* pPlayer = GetPlayer();

	//���E�̓����蔻��
	if ((pPlayer->pos.z - (pPlayer->size.z / 2)) < (g_posBlock.z + g_vtxMaxBlock.z) &&
		(pPlayer->pos.z + (pPlayer->size.z / 2)) > (g_posBlock.z + g_vtxMinBlock.z))
	{
		if ((pPlayer->posOld.x + (pPlayer->size.x / 2)) <= (g_posBlock.x + g_vtxMinBlock.x) &&
			(pPlayer->pos.x + (pPlayer->size.x / 2)) > (g_posBlock.x + g_vtxMinBlock.x))
		{
			pPlayer->pos.x = (g_posBlock.x + g_vtxMinBlock.x) - pPlayer->size.x / 2;
		}
		else if ((pPlayer->posOld.x - (pPlayer->size.x / 2)) >= (g_posBlock.x + g_vtxMaxBlock.x) &&
			(pPlayer->pos.x - (pPlayer->size.x / 2)) < (g_posBlock.x + g_vtxMaxBlock.x))
		{
			pPlayer->pos.x = (g_posBlock.x + g_vtxMaxBlock.x) + pPlayer->size.x / 2;
		}
	}
}

void CollisionBlock_Z()
{
	Player* pPlayer = GetPlayer();

	//�O��̓����蔻��
	if ((pPlayer->pos.x - (pPlayer->size.x / 2)) < (g_posBlock.x + g_vtxMaxBlock.x) &&
		(pPlayer->pos.x + (pPlayer->size.x / 2)) > (g_posBlock.x + g_vtxMinBlock.x))
	{
		if ((pPlayer->posOld.z + (pPlayer->size.z / 2)) <= (g_posBlock.z + g_vtxMinBlock.z) &&
			(pPlayer->pos.z + (pPlayer->size.z / 2)) > (g_posBlock.z + g_vtxMinBlock.z))
		{
			pPlayer->pos.z = (g_posBlock.z + g_vtxMinBlock.z) - pPlayer->size.z / 2;
		}
		else if ((pPlayer->posOld.z - (pPlayer->size.z / 2)) >= (g_posBlock.z + g_vtxMaxBlock.z) &&
			(pPlayer->pos.z - (pPlayer->size.z / 2)) < (g_posBlock.z + g_vtxMaxBlock.z))
		{
			pPlayer->pos.z = (g_posBlock.z + g_vtxMaxBlock.z) + pPlayer->size.z / 2;
		}
	}
}