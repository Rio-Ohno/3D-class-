//============================================================
//
//��[wall.cpp]
//Author:Rio Ohno
//
//============================================================

#include"wall.h"
#include"player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;									//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;										//�e�N�X�`���ւ̃|�C���^
Wall g_aWall[MAX_WALL];

//============================================================
// �ǂ̏���������
//============================================================
void InitWall()
{
	//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_aWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCnt].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

//============================================================
// �ǂ̏I������
//============================================================
void UninitWall()
{
	//���_�o�b�t�@�̉��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//============================================================
// �ǂ̍X�V����
//============================================================
void UpdateWall()
{

}

//============================================================
// �ǂ̕`�揈��
//============================================================
void DrawWall()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCnt].mtxWorldWall);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCnt].rot.y, g_aWall[nCnt].rot.x, g_aWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWorldWall, &g_aWall[nCnt].mtxWorldWall, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCnt].pos.x, g_aWall[nCnt].pos.y, g_aWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWorldWall, &g_aWall[nCnt].mtxWorldWall, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCnt].mtxWorldWall);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//�e�N�X�`�����W�̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//============================================================
//�ǂ̐ݒ菈��
//============================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHight, float a)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == false)
		{
			g_aWall[nCnt].pos = pos;
			g_aWall[nCnt].rot = rot;
			g_aWall[nCnt].fWidth = fWidth;
			g_aWall[nCnt].fHight = fHight;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = - g_aWall[nCnt].fWidth / 2;
			pVtx[0].pos.y = + g_aWall[nCnt].fHight / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = + g_aWall[nCnt].fWidth / 2;
			pVtx[1].pos.y = + g_aWall[nCnt].fHight / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = - g_aWall[nCnt].fWidth / 2;
			pVtx[2].pos.y = - g_aWall[nCnt].fHight / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = + g_aWall[nCnt].fWidth / 2;
			pVtx[3].pos.y = - g_aWall[nCnt].fHight / 2;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);

			g_aWall[nCnt].bUse = true;
			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

//============================================================
//�ǂ̓����蔻��
//============================================================
void CollisionWall()
{
	//�v���C���[�̏��擾
	Player* pPlayer = GetPlayer();

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;
	D3DXVECTOR3 vecWall[MAX_WALL], vecPlayer[MAX_WALL];														//aPos[0]���炻�ꂼ��ւ̃x�N�g���i�[�p

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == true)
		{
			D3DXVECTOR3 aPos[2];																			//���_���W�i�[�p([0]:�n�_)
			//float fver;																					//����

			//���_���W�i�[
			aPos[0] = g_aWall[nCnt].pos + pVtx[3].pos;
			aPos[1] = g_aWall[nCnt].pos + pVtx[4].pos;

			vecWall[nCnt] = aPos[1] - aPos[0];																//�ǂ̃x�N�g��
			vecPlayer[nCnt] = pPlayer->pos - aPos[0];														//aPos[0]����v���C���[�ւ̃x�N�g��

			g_aWall[nCnt].fver = (vecWall[nCnt].z * vecPlayer[nCnt].x) - (vecWall[nCnt].x * vecPlayer[nCnt].z);			//�O��

			if (g_aWall[nCnt].fver > 0)
			{
				pPlayer->pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffWall->Unlock();
}

Wall* GetWall()
{
	return &g_aWall[0];
}