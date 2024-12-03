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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX_CYLINDER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDX_CYLINDER,
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

	//}

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;
	int radius = 150;														//半径
	int index = 0;

	//頂点バッファをロック
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntz = 0; nCntz <= MAX_Z_CYLINDER; nCntz++)
	{
		for (int nCntx = 0; nCntx <= MAX_X_CYLINDER; nCntx++)
		{
			//int index = nCntx + nCntz * (MAX_X_CYLINDER + 1);

			float fAngle = D3DX_PI * 2 / MAX_X_CYLINDER * nCntx;
			//radian=180/D3DX_PI

			//頂点座標の設定
			pVtx[index].pos = D3DXVECTOR3(sinf(fAngle) * radius, 100.0f * (MAX_Z_CYLINDER - nCntz), cosf(fAngle) * radius);

			//各頂点から原点へのベクトル
			D3DXVECTOR3 vec = pVtx[index].pos - g_aMeshCylinder.pos;

			//ベクトルの正規化,各頂点の法線の設定
			D3DXVec3Normalize(&pVtx[index].nor, &vec);
			
			//頂点カラーの設定
			pVtx[index].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);

			index++;
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
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VERTEX_CYLINDER, 0, MAX_POLY_CYLINDER);//タイプ,?,どのpVtxから描画するか,頂点数,どのインデックスから描画するか,ポリゴン数
//}
}