//============================================================
//
//ビルボード[Billboard.cpp]
//Author:Rio Ohno
//
//============================================================

#include"billboard.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;					//テクスチャへのポインタ
Billboard g_aBillboard[MAX_BILLBOARD];							//ビルボード構造体

//============================================================
// ビルボードの初期化処理
//============================================================
void InitBillboard()
{
	//デバイスへのポインタと取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		NULL,
		&g_pTextureBillboard);

	//頂点バッファの生成
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

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();
}

//============================================================
// ビルボードの終了処理
//============================================================
void UninitBillboard()
{
	//頂点バッファの解放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
}

//============================================================
// ビルボードの更新処理
//============================================================
void UpdateBillboard()
{

}

//============================================================
// ビルボードの描画処理
//============================================================
void DrawBillboard()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_aBillboard[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBillboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;//ビューマトリックス

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aBillboard[nCnt].mtxWorld._11 = mtxView._11;
			g_aBillboard[nCnt].mtxWorld._12 = mtxView._21;
			g_aBillboard[nCnt].mtxWorld._13 = mtxView._31;
			g_aBillboard[nCnt].mtxWorld._21 = mtxView._12;
			g_aBillboard[nCnt].mtxWorld._22 = mtxView._22;
			g_aBillboard[nCnt].mtxWorld._23 = mtxView._32;
			g_aBillboard[nCnt].mtxWorld._31 = mtxView._13;
			g_aBillboard[nCnt].mtxWorld._32 = mtxView._23;
			g_aBillboard[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCnt].pos.x, g_aBillboard[nCnt].pos.y, g_aBillboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aBillboard[nCnt].mtxWorld, &g_aBillboard[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ座標の設定
			pDevice->SetTexture(0, g_pTextureBillboard);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================
// ビルボードの設定処理
//============================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir,float radius)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_aBillboard[nCnt].bUse == false)
		{
			g_aBillboard[nCnt].pos = pos;
			g_aBillboard[nCnt].dir = dir;
			g_aBillboard[nCnt].radius = radius;

			//頂点座標の設定
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
	//頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();
}
