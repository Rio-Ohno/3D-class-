//============================================================
//
//�r���{�[�h[Billboard.cpp]
//Author:Rio Ohno
//
//============================================================

#include"billboard.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;					//�e�N�X�`���ւ̃|�C���^
Billboard g_aBillboard[MAX_BILLBOARD];							//�r���{�[�h�\����

//============================================================
// �r���{�[�h�̏���������
//============================================================
void InitBillboard()
{
	//�f�o�C�X�ւ̃|�C���^�Ǝ擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile(pDevice,
		NULL,
		&g_pTextureBillboard);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_aBillboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCnt].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCnt].radius = 20.0f;
		g_aBillboard[nCnt].bUse = false;
	}

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

//============================================================
// �r���{�[�h�̏I������
//============================================================
void UninitBillboard()
{
	//���_�o�b�t�@�̉��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//============================================================
// �r���{�[�h�̍X�V����
//============================================================
void UpdateBillboard()
{

}

//============================================================
// �r���{�[�h�̕`�揈��
//============================================================
void DrawBillboard()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_aBillboard[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBillboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;//�r���[�}�g���b�N�X

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			g_aBillboard[nCnt].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCnt].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCnt].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCnt].mtxWorld._21 = mtxView._12;
			g_aBillboard[nCnt].mtxWorld._22 = mtxView._22;
			g_aBillboard[nCnt].mtxWorld._23 = mtxView._32;
			g_aBillboard[nCnt].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCnt].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCnt].pos.x, g_aBillboard[nCnt].pos.y, g_aBillboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCnt].mtxWorld, &g_aBillboard[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCnt].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`�����W�̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillboard);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================
// �r���{�[�h�̐ݒ菈��
//============================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir,float radius)
{
	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_aBillboard[nCnt].bUse == false)
		{
			g_aBillboard[nCnt].pos = pos;
			g_aBillboard[nCnt].dir = dir;
			g_aBillboard[nCnt].radius = radius;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aBillboard[nCnt].pos.x - g_aBillboard[nCnt].radius;
			pVtx[0].pos.y = g_aBillboard[nCnt].pos.y + g_aBillboard[nCnt].radius;
			pVtx[0].pos.z = g_aBillboard[nCnt].pos.z;

			pVtx[1].pos.x = g_aBillboard[nCnt].pos.x + g_aBillboard[nCnt].radius;
			pVtx[1].pos.y = g_aBillboard[nCnt].pos.y + g_aBillboard[nCnt].radius;
			pVtx[1].pos.z = g_aBillboard[nCnt].pos.z;

			pVtx[2].pos.x = g_aBillboard[nCnt].pos.x - g_aBillboard[nCnt].radius;
			pVtx[2].pos.y = g_aBillboard[nCnt].pos.y - g_aBillboard[nCnt].radius;
			pVtx[2].pos.z = g_aBillboard[nCnt].pos.z;

			pVtx[3].pos.x = g_aBillboard[nCnt].pos.x + g_aBillboard[nCnt].radius;
			pVtx[3].pos.y = g_aBillboard[nCnt].pos.y - g_aBillboard[nCnt].radius;
			pVtx[3].pos.z = g_aBillboard[nCnt].pos.z;

			g_aBillboard[nCnt].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();
}
