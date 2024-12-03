//============================================================
//
//メッシュの壁[MeshWall.cpp]
//Author:Rio Ohno
//
//============================================================

#include"meshwall.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;						//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;							//テクスチャ用ポインタ
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshWall = NULL;						//インデクスバッファへのポインタ
MeshWall g_aMeshWall[MAX_MESHWALL];

//============================================================
// メッシュフィールドの初期化処理
//============================================================
void InitMeshWall()
{
	//デバイスへのポインタと取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX_WALL * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_INDX_WALL * MAX_MESHWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIndxBuffMeshWall,
		NULL);

	//テクスチャの読込
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

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	int nDatax = MAX_X_WALL / 2;//ずらす量
	int nDatay = MAX_X_WALL / 2;//ずらす量
	int nCntx = 0;//カウンター
	int nCnty = 0;//カウンター

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		//if (g_aMeshWall[nCnt].bUse == true)
		//{
			for (nCnty = 0; nCnty <= MAX_Y_WALL; nCnty++)
			{
				float posy = g_aMeshWall[nCnt].fHight * 2 / (MAX_Y_WALL) * (nDatay - nCnty);
				if (nDatay - nCnty == 0)//0で割ったなら
				{
					posy = 0.0f;
				}

				for (nCntx = 0; nCntx <= MAX_X_WALL; nCntx++)
				{
					int nCntVertex = nCntx + nCnty * (MAX_X_WALL + 1);

					float posx = g_aMeshWall[nCnt].fWidth * 2 / (MAX_X_WALL) * (nCntx - nDatax);
					if (nCntx - nDatax == 0)//0で割ったなら
					{
						posx = 0.0f;
					}

					//頂点座標の設定
					pVtx[nCntVertex].pos = D3DXVECTOR3(posx, posy, 0.0f);

					//各頂点の法線の設定
					pVtx[nCntVertex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

					//頂点カラーの設定
					pVtx[nCntVertex].col = D3DXCOLOR(0.5f, 0.8f, 0.8f, 1.0);

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

				//pVtx[0].pos.y = 20.0f;
			}
		//}
	}
	//頂点バッファのアンロック
	g_pVtxBuffMeshWall->Unlock();

	//インデックスバッファをロック
	WORD* pIndx;													//インデックス情報へのポインタ
	g_pIndxBuffMeshWall->Lock(0, 0, (void**)&pIndx, 0);

	//インデックスの設定
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

	//インデックスをアンロック
	g_pIndxBuffMeshWall->Unlock();
}

//============================================================
// ポリゴンの終了処理
//============================================================
void UninitMeshWall()
{
	//頂点バッファの解放
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//テクスチャの解放
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//インデックスバッファの解放
	if (g_pIndxBuffMeshWall != NULL)
	{
		g_pIndxBuffMeshWall->Release();
		g_pIndxBuffMeshWall = NULL;
	}
}

//============================================================
// ポリゴンの更新処理
//============================================================
void UpdateMeshWall()
{

}

//============================================================
// ポリゴンの描画処理
//============================================================
void DrawMeshWall()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MAX_MESHWALL; nCnt++)
	{
		if (g_aMeshWall[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aMeshWall[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCnt].rot.y, g_aMeshWall[nCnt].rot.x, g_aMeshWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCnt].mtxWorld, &g_aMeshWall[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCnt].pos.x, g_aMeshWall[nCnt].pos.y, g_aMeshWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCnt].mtxWorld, &g_aMeshWall[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデバイスのデータストリームに設定
			pDevice->SetIndices(g_pIndxBuffMeshWall);

			//テクスチャ座標の設定
			pDevice->SetTexture(0, g_pTextureMeshWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_VERTEX_WALL, 0, MAX_POLY_WALL);//タイプ,?,どのpVtxから描画するか,頂点数,どのインデックスから描画するか,ポリゴン数
		}
	}
}

//============================================================
// 壁(メッシュ)の設定
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