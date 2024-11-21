//============================================================
//
//円柱[MeshCylinder.cpp]
//Author:Rio Ohno
//
//============================================================

#include"meshcylinder.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;						//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;							//テクスチャ用ポインタ
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshCylinder = NULL;						//インデクスバッファへのポインタ
MeshCylinder g_aMeshCylinder;

//============================================================
// メッシュフィールドの初期化処理
//============================================================
void InitMeshCylinder()
{
	//デバイスへのポインタと取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshCylinder,
		NULL);

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		NULL,
		&g_pTextureMeshCylinder);

	//for (int nCnt = 0; nCnt < MAX_INDX; nCnt++)
	//{
	g_aMeshCylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshCylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int radius = 50;														//半径
	//}

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntz = 0; nCntz <= MAX_Z_CYLINDER; nCntz++)
	{
		for (int nCntx = 0; nCntx <= MAX_X_CYLINDER; nCntx++)
		{
			const int index = nCntx + nCntz * (MAX_X_CYLINDER + 1);

			float fAngle = D3DX_PI * 2 / MAX_X_CYLINDER * nCntx;

			//頂点座標の設定
			pVtx[index].pos = D3DXVECTOR3(sinf(D3DXToRadian(fAngle))*radius, 0.0f, cosf(D3DXToRadian(fAngle))*radius);

			//各頂点の法線の設定
			pVtx[index].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//ベクトルの正規化
			D3DXVec3Normalize(&pVtx[index].nor, &pVtx[index].pos);
			
			//頂点カラーの設定
			pVtx[index].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

			//テクスチャ座標の設定
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
	}
//頂点バッファのアンロック
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスバッファをロック
	WORD* pIndx;													//インデックス情報へのポインタ
	g_pIndxBuffMeshCylinder->Lock(0, 0, (void**)&pIndx, 0);

	//インデックスの設定
	int nCntx = 0;
	int nCntz = 0;

	for (nCntz = 0; nCntz < MAX_Z_CYLINDER; nCntz++)
	{
		for (nCntx = 0; nCntx <= MAX_X_CYLINDER; nCntx++)
		{

			pIndx[0] = (MAX_X_CYLINDER + 1) * (nCntz + 1) + nCntx;
			pIndx[1] = nCntx + (nCntz * (MAX_X_CYLINDER + 1));

			pIndx += 2;
		}

		if (nCntz < MAX_Z_CYLINDER - 1)
		{
			pIndx[0] = (nCntx - 1) + (nCntz * (MAX_X_CYLINDER + 1));
			pIndx[1] = (nCntx - 1) + (nCntz * (MAX_X_CYLINDER + 1)) + (MAX_X_CYLINDER + 2) * (nCntz + 1);
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
	g_pIndxBuffMeshCylinder->Unlock();
}

//============================================================
// ポリゴンの終了処理
//============================================================
void UninitMeshCylinder()
{
	//頂点バッファの解放
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	//テクスチャの解放
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//インデックスバッファの解放
	if (g_pIndxBuffMeshCylinder != NULL)
	{
		g_pIndxBuffMeshCylinder->Release();
		g_pIndxBuffMeshCylinder = NULL;
	}
}

//============================================================
// ポリゴンの更新処理
//============================================================
void UpdateMeshCylinder()
{

}

//============================================================
// ポリゴンの描画処理
//============================================================
void DrawMeshCylinder()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//for (int nCnt = 0; nCnt < MAX_INDX; nCnt++)
	//{
		//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_aMeshCylinder.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshCylinder.rot.y, g_aMeshCylinder.rot.x, g_aMeshCylinder.rot.z);
	D3DXMatrixMultiply(&g_aMeshCylinder.mtxWorld, &g_aMeshCylinder.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_aMeshCylinder.pos.x, g_aMeshCylinder.pos.y, g_aMeshCylinder.pos.z);
	D3DXMatrixMultiply(&g_aMeshCylinder.mtxWorld, &g_aMeshCylinder.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_aMeshCylinder.mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデバイスのデータストリームに設定
	pDevice->SetIndices(g_pIndxBuffMeshCylinder);

	//テクスチャ座標の設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VERTEX, 0, MAX_POLY);//タイプ,?,どのpVtxから描画するか,頂点数,どのインデックスから描画するか,ポリゴン数
//}
}