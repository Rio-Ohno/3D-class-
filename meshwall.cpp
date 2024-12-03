//============================================================
//
//���b�V���̕�[MeshWall.cpp]
//Author:Rio Ohno
//
//============================================================

#include"meshwall.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;						//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;							//�e�N�X�`���p�|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshWall = NULL;						//�C���f�N�X�o�b�t�@�ւ̃|�C���^
MeshWall g_aMeshWall[MAX_MESHWALL];

//============================================================
// ���b�V���t�B�[���h�̏���������
//============================================================
void InitMeshWall()
{
	//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX_WALL * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDX_WALL * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshWall,
		NULL);

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		NULL,
		&g_pTextureMeshWall);

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		g_aMeshWall[nCnt].pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aMeshWall[nCnt].rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aMeshWall[nCnt].fHight = 100.0f;
		g_aMeshWall[nCnt].fWidth = 100.0f;
		g_aMeshWall[nCnt].bUse = false;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	int nDatax = MAX_X_WALL / 2;//���炷��
	int nDatay = MAX_X_WALL / 2;//���炷��
	int nCntx = 0;//�J�E���^�[
	int nCnty = 0;//�J�E���^�[

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//if (g_aMeshWall[nCnt].bUse == true)
		//{
			for (nCnty = 0; nCnty <= MAX_Y_WALL; nCnty++)
			{
				float posy = g_aMeshWall[nCnt].fHight * 2 / (MAX_Y_WALL) * (nDatay - nCnty);
				if (nDatay - nCnty == 0)//0�Ŋ������Ȃ�
				{
					posy = 0.0f;
				}

				for (nCntx = 0; nCntx <= MAX_X_WALL; nCntx++)
				{
					int nCntVertex = nCntx + nCnty * (MAX_X_WALL + 1);

					float posx = g_aMeshWall[nCnt].fWidth * 2 / (MAX_X_WALL) * (nCntx - nDatax);
					if (nCntx - nDatax == 0)//0�Ŋ������Ȃ�
					{
						posx = 0.0f;
					}

					//���_���W�̐ݒ�
					pVtx[nCntVertex].pos = D3DXVECTOR3(posx, posy, 0.0f);

					//�e���_�̖@���̐ݒ�
					pVtx[nCntVertex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

					//���_�J���[�̐ݒ�
					pVtx[nCntVertex].col = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0);

					//�e�N�X�`�����W�̐ݒ�
					//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
					//pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
					//pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
					//pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
					//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
					//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
					//pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
					//pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

				}

				//pVtx[0].pos.y = 20.0f;
			}
		//}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIndx;													//�C���f�b�N�X���ւ̃|�C���^
	g_pIndxBuffMeshWall->Lock(0, 0, (void**)&pIndx, 0);

	//�C���f�b�N�X�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//if (g_aMeshWall[nCnt].bUse == true)
		//{

			for (nCnty = 0; nCnty < MAX_Y_WALL; nCnty++)
			{
				for (nCntx = 0; nCntx <= MAX_X_WALL; nCntx++)
				{

					pIndx[0] = (MAX_X_WALL + 1) * (nCnty + 1) + nCntx;
					pIndx[1] = nCntx + (nCnty * (MAX_X_WALL + 1));

					pIndx += 2;
				}

				if (nCnty < MAX_Y_WALL - 1)
				{
					pIndx[0] = (nCntx - 1) + (nCnty * (MAX_X_WALL + 1));
					pIndx[1] = (nCntx - 1) + (nCnty * (MAX_X_WALL + 1)) + (MAX_X_WALL + 2) * (nCnty + 1);
					pIndx += 2;
				}
			}
		//}
	}

	//�C���f�b�N�X���A�����b�N
	g_pIndxBuffMeshWall->Unlock();
}

//============================================================
// �|���S���̏I������
//============================================================
void UninitMeshWall()
{
	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//�e�N�X�`���̉��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIndxBuffMeshWall != NULL)
	{
		g_pIndxBuffMeshWall->Release();
		g_pIndxBuffMeshWall = NULL;
	}
}

//============================================================
// �|���S���̍X�V����
//============================================================
void UpdateMeshWall()
{

}

//============================================================
// �|���S���̕`�揈��
//============================================================
void DrawMeshWall()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_aMeshWall[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshWall[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCnt].rot.y, g_aMeshWall[nCnt].rot.x, g_aMeshWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCnt].mtxWorld, &g_aMeshWall[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCnt].pos.x, g_aMeshWall[nCnt].pos.y, g_aMeshWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCnt].mtxWorld, &g_aMeshWall[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCnt].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIndxBuffMeshWall);

			//�e�N�X�`�����W�̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VERTEX_WALL, 0, MAX_POLY_WALL);//�^�C�v,?,�ǂ�pVtx����`�悷�邩,���_��,�ǂ̃C���f�b�N�X����`�悷�邩,�|���S����
		}
	}
}

//============================================================
// ��(���b�V��)�̐ݒ�
//============================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_aMeshWall[nCnt].bUse == false)
		{
			g_aMeshWall[nCnt].pos = pos;
			g_aMeshWall[nCnt].rot = rot;

			g_aMeshWall[nCnt].bUse = true;
			break;
		}
	}
}