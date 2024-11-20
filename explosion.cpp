//============================================================
//
//爆発処理[explosion.cpp]
//Author:Rio Ohno
//
//============================================================

#include "explosion.h"

//マクロ定義
#define MAX_EXPLOSION (128)                                   //弾の最大数
#define EXPLOSION_WIDTH (50)                                  //ポリゴンの幅
#define EXPLOSION_HEIGHT (50)                                 //ポリゴンの高さ

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;                                          //位置
	D3DXVECTOR3 rot;                                          //向き
	D3DXCOLOR col;                                            //色
	D3DXMATRIX mtxWorld;									  //ワールドマトリックス
	bool bUse;                                                //使用しているかどう
	int nCounterAnim;                                         //アニメーションカウンター
	int nPatternAnim;                                         //アニメーションパターン
	float radius;											  //半径
}EXPLOSION;


//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;				  //テクスチャ用ポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;           //頂点バッファへのポインタ
EXPLOSION g_aExplosion[MAX_EXPLOSION];                        //弾の情報

//=============================================================================================================
//初期化処理
//=============================================================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion = NULL;

	//デバイスに取得
	pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Explosion000.png",
		&g_pTextureExplosion);


	//爆発の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;                      //使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_3D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;//頂点データのポインタを4つ分進める

	}
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================================================
//弾の終了処理
//=============================================================================================================
void UninitExplosion()
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================================================
//弾の更新処理
//=============================================================================================================
void UpdateExplosion()
{
	int nCntExplosion = 0;

	VERTEX_3D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//弾が使用されているとき

			g_aExplosion[nCntExplosion].nCounterAnim++;
			if ((g_aExplosion[nCntExplosion].nCounterAnim % 8) == 0)
			{
				g_aExplosion[nCntExplosion].nCounterAnim = 0;

				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 7)//総パターン数を超えた
				{
					g_aExplosion[nCntExplosion].bUse = false;//使用していない状態にする
				}

				//テクスチャ座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================================================
//弾の描画処理
//=============================================================================================================
void DrawExplosion()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトの無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_aExplosion[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCnt].mtxWorld);

			D3DXMATRIX mtxView;//ビューマトリックス

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aExplosion[nCnt].mtxWorld._11 = mtxView._11;
			g_aExplosion[nCnt].mtxWorld._12 = mtxView._21;
			g_aExplosion[nCnt].mtxWorld._13 = mtxView._31;
			g_aExplosion[nCnt].mtxWorld._21 = mtxView._12;
			g_aExplosion[nCnt].mtxWorld._22 = mtxView._22;
			g_aExplosion[nCnt].mtxWorld._23 = mtxView._32;
			g_aExplosion[nCnt].mtxWorld._31 = mtxView._13;
			g_aExplosion[nCnt].mtxWorld._32 = mtxView._23;
			g_aExplosion[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCnt].pos.x, g_aExplosion[nCnt].pos.y, g_aExplosion[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCnt].mtxWorld, &g_aExplosion[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ座標の設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================================================
//爆発の設定処理
//=============================================================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 rot, float radius)
{
	VERTEX_3D* pVtx;
	int nCntExplosion;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//弾が使用されていないとき
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].radius = radius;

			//頂点座標の設定
			pVtx[0].pos.x = g_aExplosion[nCntExplosion].pos.x - g_aExplosion[nCntExplosion].radius;
			pVtx[0].pos.y = g_aExplosion[nCntExplosion].pos.y + g_aExplosion[nCntExplosion].radius;
			pVtx[0].pos.z = g_aExplosion[nCntExplosion].pos.z;

			pVtx[1].pos.x = g_aExplosion[nCntExplosion].pos.x + g_aExplosion[nCntExplosion].radius;
			pVtx[1].pos.y = g_aExplosion[nCntExplosion].pos.y + g_aExplosion[nCntExplosion].radius;
			pVtx[1].pos.z = g_aExplosion[nCntExplosion].pos.z;

			pVtx[2].pos.x = g_aExplosion[nCntExplosion].pos.x - g_aExplosion[nCntExplosion].radius;
			pVtx[2].pos.y = g_aExplosion[nCntExplosion].pos.y - g_aExplosion[nCntExplosion].radius;
			pVtx[2].pos.z = g_aExplosion[nCntExplosion].pos.z;

			pVtx[3].pos.x = g_aExplosion[nCntExplosion].pos.x + g_aExplosion[nCntExplosion].radius;
			pVtx[3].pos.y = g_aExplosion[nCntExplosion].pos.y - g_aExplosion[nCntExplosion].radius;
			pVtx[3].pos.z = g_aExplosion[nCntExplosion].pos.z;

			g_aExplosion[nCntExplosion].bUse = true;//使用してる状態にする
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}
