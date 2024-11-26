//============================================================
//
//モデル[model.cpp]
//Author:Rio Ohno
//
//============================================================

#include"model.h"

//グロ－バル変数宣言
LPD3DXMESH g_pMeshModel = NULL;
LPD3DXBUFFER g_pBuffmatModel = NULL;
DWORD g_dwNumMatModel = 0;
LPDIRECT3DTEXTURE9 g_apTextureModel[MAX_MAT] = {};
D3DXVECTOR3 g_posModel;
D3DXVECTOR3 g_rotModel;
D3DXMATRIX g_mtxWorldModel;

//============================================================
// モデルの初期化処理
//============================================================
void InitModel()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//各種初期化
	g_pMeshModel = NULL;
	g_pBuffmatModel = NULL;
	g_dwNumMatModel = 0;
	g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//Xファイルの読込
	D3DXLoadMeshFromX("data\\MODEL\\TV.x",
						D3DXMESH_SYSTEMMEM, 
						pDevice,
						NULL,
						&g_pBuffmatModel,
						NULL,
						&g_dwNumMatModel,
						&g_pMeshModel);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffmatModel->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatModel; nCnt++)
	{
		//テクスチャポインタの初期化
		g_apTextureModel[nCnt] = {};

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//テクスチャの読込
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&g_apTextureModel[nCnt]);

		}
	}
}

//============================================================
// モデルの終了処理
//============================================================
void UninitModel()
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
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
// モデルの更新処理
//============================================================
void UpdateModel()
{

}

//============================================================
// モデルの描画処理
//============================================================
void DrawModel()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffmatModel->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatModel; nCnt++)
	{

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureModel[nCnt]);

		//モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCnt);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}