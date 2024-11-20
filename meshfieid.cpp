//============================================================
//
//メッシュフィールド[MeshField.cpp]
//Author:Rio Ohno
//
//============================================================

#include"meshfield.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;						//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;							//テクスチャ用ポインタ
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshField = NULL;						//インデクスバッファへのポインタ
MeshField g_aMeshField;

//============================================================
// メッシュフィールドの初期化処理
//============================================================
void InitMeshField()
{
	//デバイスへのポインタと取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshField,
		NULL);

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		NULL,
		&g_pTextureMeshField);

	//for (int nCnt = 0; nCnt < MAX_INDX; nCnt++)
	//{
		g_aMeshField.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//}

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_POLY; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
		pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
		pVtx[8].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	}
	//頂点バッファのアンロック
	g_pVtxBuffMeshField->Unlock();

	//インデックスバッファをロック
	WORD* pIndx;													//インデックス情報へのポインタ
	g_pIndxBuffMeshField->Lock(0, 0, (void**)&pIndx, 0);

	//インデックスの設定
	int nCntx = 0;
	int nCntz = 0;

	for (nCntz = 0; nCntz < MAX_Z; nCntz++)
	{
		for (nCntx = 0; nCntx <= MAX_X; nCntx++)
		{

			pIndx[0] = (MAX_X + nCntx + 1) * (nCntz + 1);
			pIndx[1] = nCntx * (nCntz * (MAX_X+1));

			pIndx += 2;
		}

		if (nCntz < MAX_Z - 1)
		{
			pIndx[0] = nCntx * (nCntz * (MAX_X + 1));
			pIndx[1] = nCntx * (nCntz * (MAX_X + 1)) + (MAX_X + 2) * (nCntz + 1);
			pIndx += 2;
		}
	}

	//pIndx[0] = 3;
	//pIndx[1] = 0;

	//pIndx[2] = 4;
	//pIndx[3] = 1;

	//pIndx[4] = 5;
	//pIndx[5] = 2;

	//pIndx[6] = 2;
	//pIndx[7] = 6;

	//pIndx[8] = 6;
	//pIndx[9] = 3;

	//pIndx[10] = 7;
	//pIndx[11] = 4;

	//pIndx[12] = 8;
	//pIndx[13] = 5;

	//インデックスをアンロック
	g_pIndxBuffMeshField->Unlock();
}

//============================================================
// ポリゴンの終了処理
//============================================================
void UninitMeshField()
{
	//頂点バッファの解放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//テクスチャの解放
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//インデックスバッファの解放
	if (g_pIndxBuffMeshField != NULL)
	{
		g_pIndxBuffMeshField->Release();
		g_pIndxBuffMeshField = NULL;
	}
}

//============================================================
// ポリゴンの更新処理
//============================================================
void UpdateMeshField()
{

}

//============================================================
// ポリゴンの描画処理
//============================================================
void DrawMeshField()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//for (int nCnt = 0; nCnt < MAX_INDX; nCnt++)
	//{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aMeshField.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField.rot.y, g_aMeshField.rot.x, g_aMeshField.rot.z);
		D3DXMatrixMultiply(&g_aMeshField.mtxWorld, &g_aMeshField.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aMeshField.pos.x, g_aMeshField.pos.y, g_aMeshField.pos.z);
		D3DXMatrixMultiply(&g_aMeshField.mtxWorld, &g_aMeshField.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField.mtxWorld);

		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

		//インデックスバッファをデバイスのデータストリームに設定
		pDevice->SetIndices(g_pIndxBuffMeshField);

		//テクスチャ座標の設定
		pDevice->SetTexture(0, g_pTextureMeshField);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0,MAX_VERTEX,0,MAX_POLY);//タイプ,?,どのpVtxから描画するか,頂点数,どのインデックスから描画するか,ポリゴン数
	//}
}