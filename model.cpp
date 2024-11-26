//============================================================
//
//���f��[model.cpp]
//Author:Rio Ohno
//
//============================================================

#include"model.h"

//�O���|�o���ϐ��錾
LPD3DXMESH g_pMeshModel = NULL;
LPD3DXBUFFER g_pBuffmatModel = NULL;
DWORD g_dwNumMatModel = 0;
LPDIRECT3DTEXTURE9 g_apTextureModel[MAX_MAT] = {};
D3DXVECTOR3 g_posModel;
D3DXVECTOR3 g_rotModel;
D3DXMATRIX g_mtxWorldModel;

//============================================================
// ���f���̏���������
//============================================================
void InitModel()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//�e�평����
	g_pMeshModel = NULL;
	g_pBuffmatModel = NULL;
	g_dwNumMatModel = 0;
	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//X�t�@�C���̓Ǎ�
	D3DXLoadMeshFromX("data\\MODEL\\TV.x",
						D3DXMESH_SYSTEMMEM, 
						pDevice,
						NULL,
						&g_pBuffmatModel,
						NULL,
						&g_dwNumMatModel,
						&g_pMeshModel);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffmatModel->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatModel; nCnt++)
	{
		//�e�N�X�`���|�C���^�̏�����
		g_apTextureModel[nCnt] = {};

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓Ǎ�
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&g_apTextureModel[nCnt]);

		}
	}
}

//============================================================
// ���f���̏I������
//============================================================
void UninitModel()
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffmatModel != NULL)
	{
		g_pBuffmatModel->Release();
		g_pBuffmatModel = NULL;
	}

	for (int nCnt = 0; nCnt < (int)g_dwNumMatModel; nCnt++)
	{
		if (g_apTextureModel[nCnt] != NULL)
		{
			g_apTextureModel[nCnt]->Release();
			g_apTextureModel[nCnt] = NULL;
		}
	}
}

//============================================================
// ���f���̍X�V����
//============================================================
void UpdateModel()
{

}

//============================================================
// ���f���̕`�揈��
//============================================================
void DrawModel()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffmatModel->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatModel; nCnt++)
	{

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureModel[nCnt]);

		//���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCnt);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}