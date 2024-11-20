//============================================================
//
//壁[wall.cpp]
//Author:Rio Ohno
//
//============================================================

#include"wall.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;					//テクスチャへのポインタ
Wall g_aWall[MAX_WALL];

//============================================================
// 壁の初期化処理
//============================================================
void InitWall()
{
	//デバイスへのポインタと取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_aWall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCnt].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}

//============================================================
// 壁の終了処理
//============================================================
void UninitWall()
{
	//頂点バッファの解放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//============================================================
// 壁の更新処理
//============================================================
void UpdateWall()
{

}

//============================================================
// 壁の描画処理
//============================================================
void DrawWall()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCnt].mtxWorldWall);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCnt].rot.y, g_aWall[nCnt].rot.x, g_aWall[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWorldWall, &g_aWall[nCnt].mtxWorldWall, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCnt].pos.x, g_aWall[nCnt].pos.y, g_aWall[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCnt].mtxWorldWall, &g_aWall[nCnt].mtxWorldWall, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCnt].mtxWorldWall);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//テクスチャ座標の設定
			pDevice->SetTexture(0, g_pTextureWall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//============================================================
//壁の設定処理
//============================================================
void SetWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot, float fx, float fy,float fz,float a)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_aWall[nCnt].bUse == false)
		{
			g_aWall[nCnt].pos = pos;
			g_aWall[nCnt].rot = rot;

			//頂点座標の設定
			pVtx[0].pos.x = g_aWall[nCnt].pos.x - fx;
			pVtx[0].pos.y = g_aWall[nCnt].pos.y + fy;
			pVtx[0].pos.z = g_aWall[nCnt].pos.z + fz;

			pVtx[1].pos.x = g_aWall[nCnt].pos.x + fx;
			pVtx[1].pos.y = g_aWall[nCnt].pos.y + fy;
			pVtx[1].pos.z = g_aWall[nCnt].pos.z + fz;

			pVtx[2].pos.x = g_aWall[nCnt].pos.x - fx;
			pVtx[2].pos.y = g_aWall[nCnt].pos.y - fy;
			pVtx[2].pos.z = g_aWall[nCnt].pos.z - fz;

			pVtx[3].pos.x = g_aWall[nCnt].pos.x + fx;
			pVtx[3].pos.y = g_aWall[nCnt].pos.y - fy;
			pVtx[3].pos.z = g_aWall[nCnt].pos.z - fz;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, a);

			g_aWall[nCnt].bUse = true;
			break;
		}

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffWall->Unlock();
}