//============================================================
//
//ブロック[block.cpp]
//Author:Rio Ohno
//
//============================================================

#include"block.h"

//グロ－バル変数宣言
LPD3DXMESH g_pMeshBlock = NULL;
LPD3DXBUFFER g_pBuffmatBlock = NULL;
DWORD g_dwNumMatBlock = 0;
LPDIRECT3DTEXTURE9 g_apTextureBlock[MAX_MAT_BLOCK] = {};
D3DXVECTOR3 g_posBlock;
D3DXVECTOR3 g_rotBlock;
D3DXVECTOR3 g_vtxMinBlock;//モデルの最小値
D3DXVECTOR3 g_vtxMaxBlock;//モデルの最大値
D3DXMATRIX g_mtxWorldBlock;

//============================================================
// モデルの初期化処理
//============================================================
void InitBlock()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//各種初期化
	g_pMeshBlock = NULL;
	g_pBuffmatBlock = NULL;
	g_dwNumMatBlock = 0;
	g_posBlock = D3DXVECTOR3(20.0f, 0.0f, 0.0f);
	g_rotBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBlock);

	//Xファイルの読込
	D3DXLoadMeshFromX("data\\MODEL\\box000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffmatBlock,
		NULL,
		&g_dwNumMatBlock,
		&g_pMeshBlock);

	int nNumVtx;//最大頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBUff;//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = g_pMeshBlock->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshBlock->GetFVF());

	//頂点バッファのロック
	g_pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

		//頂点座標を比較してモデルの最大最小を取得

		if (vtx.x > g_vtxMaxBlock.x)//x最大値
		{
			g_vtxMaxBlock.x = vtx.x;
		}
		else if (vtx.x < g_vtxMinBlock.x)//x最小値
		{
			g_vtxMinBlock.x = vtx.x;
		}

		if (vtx.y > g_vtxMaxBlock.y)//y最大値
		{
			g_vtxMaxBlock.y = vtx.y;
		}
		else if (vtx.y < g_vtxMinBlock.y)//y最小値
		{
			g_vtxMinBlock.y = vtx.y;
		}

		if (vtx.z > g_vtxMaxBlock.z)//z最大値
		{
			g_vtxMaxBlock.z = vtx.z;
		}
		else if (vtx.z < g_vtxMinBlock.z)//z最小値
		{
			g_vtxMinBlock.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBUff += sizeFVF;
	}

	//頂点バッファのアンロック
	g_pMeshBlock->UnlockVertexBuffer();
		
	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffmatBlock->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatBlock; nCnt++)
	{
		//テクスチャポインタの初期化
		g_apTextureBlock[nCnt] = {};

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//テクスチャの読込
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&g_apTextureBlock[nCnt]);

		}
	}
}

//============================================================
// モデルの終了処理
//============================================================
void UninitBlock()
{
	//メッシュの破棄
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}

	//マテリアルの破棄
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
// モデルの更新処理
//============================================================
void UpdateBlock()
{

}

//============================================================
// モデルの描画処理
//============================================================
void DrawBlock()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBlock);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotBlock.y, g_rotBlock.x, g_rotBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBlock.x, g_posBlock.y, g_posBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlock);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffmatBlock->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatBlock; nCnt++)
	{
		//マテリアルの設定
		pDevice->SetTexture(0, g_apTextureBlock[nCnt]);

		//モデル(パーツ)の描画
		g_pMeshBlock->DrawSubset(nCnt);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}

void CollisionBlock_X()
{
	Player* pPlayer = GetPlayer();

	//左右の当たり判定
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

	//前後の当たり判定
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