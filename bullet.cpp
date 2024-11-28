//============================================================
//
//弾[Bullet.cpp]
//Author:Rio Ohno
//
//============================================================

#include"bullet.h"
#include "shadow.h"
#include "explosion.h"
#include"wall.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;										//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;												//テクスチャへのポインタ
Bullet g_aBullet[MAX_BULLET];															//ビルボード構造体

//============================================================
// 弾の初期化処理
//============================================================
void InitBullet()
{
	//デバイスへのポインタと取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読込
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_aBullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCnt].nIndexShadow = 0;
		g_aBullet[nCnt].nLife = BULLET_LIFE;
		g_aBullet[nCnt].radius = 20.0f;
		g_aBullet[nCnt].bUse = false;
	}

	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
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
	g_pVtxBuffBullet->Unlock();
}

//============================================================
// 弾の終了処理
//============================================================
void UninitBullet()
{
	//頂点バッファの解放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//============================================================
// 弾の更新処理
//============================================================
void UpdateBullet()
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{
			//前回の位置を保存
			g_aBullet[nCnt].posOld = g_aBullet[nCnt].pos;

			float rot = g_aBullet[nCnt].dir.y + D3DX_PI;

			//移動量更新
			g_aBullet[nCnt].move.x = sinf(rot) * BULLET_SPEED;
			g_aBullet[nCnt].move.y = g_aBullet[nCnt].pos.y;
			g_aBullet[nCnt].move.z = cosf(rot) * BULLET_SPEED;

			//寿命が尽きたら消す
			g_aBullet[nCnt].nLife--;
			if (g_aBullet[nCnt].nLife <= 0)
			{
				g_aBullet[nCnt].bUse = false;
				SetExplosion(g_aBullet[nCnt].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), g_aBullet[nCnt].rot, g_aBullet[nCnt].radius);
			}

			//目標の移動方向（角度）の補正
			if (rot > D3DX_PI)
			{
				rot -= D3DX_PI * 2.0f;
			}
			else if (g_aBullet[nCnt].dir.y + D3DX_PI < -D3DX_PI)
			{
				rot += D3DX_PI * 2.0f;
			}

			CollisionBullet();

			//位置の更新
			g_aBullet[nCnt].pos += g_aBullet[nCnt].move;

			//影の位置更新
			SetPositionShadow(g_aBullet[nCnt].nIndexShadow, g_aBullet[nCnt].pos);

			//頂点座標の設定
			pVtx[0].pos.x = g_aBullet[nCnt].pos.x - g_aBullet[nCnt].radius;
			pVtx[0].pos.y = g_aBullet[nCnt].pos.y + g_aBullet[nCnt].radius;
			pVtx[0].pos.z = g_aBullet[nCnt].pos.z;

			pVtx[1].pos.x = g_aBullet[nCnt].pos.x + g_aBullet[nCnt].radius;
			pVtx[1].pos.y = g_aBullet[nCnt].pos.y + g_aBullet[nCnt].radius;
			pVtx[1].pos.z = g_aBullet[nCnt].pos.z;

			pVtx[2].pos.x = g_aBullet[nCnt].pos.x - g_aBullet[nCnt].radius;
			pVtx[2].pos.y = g_aBullet[nCnt].pos.y - g_aBullet[nCnt].radius;
			pVtx[2].pos.z = g_aBullet[nCnt].pos.z;

			pVtx[3].pos.x = g_aBullet[nCnt].pos.x + g_aBullet[nCnt].radius;
			pVtx[3].pos.y = g_aBullet[nCnt].pos.y - g_aBullet[nCnt].radius;
			pVtx[3].pos.z = g_aBullet[nCnt].pos.z;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

//============================================================
// 弾の描画処理
//============================================================
void DrawBullet()
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

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCnt].mtxWorld);

			D3DXMATRIX mtxView;//ビューマトリックス

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aBullet[nCnt].mtxWorld._11 = mtxView._11;
			g_aBullet[nCnt].mtxWorld._12 = mtxView._21;
			g_aBullet[nCnt].mtxWorld._13 = mtxView._31;
			g_aBullet[nCnt].mtxWorld._21 = mtxView._12;
			g_aBullet[nCnt].mtxWorld._22 = mtxView._22;
			g_aBullet[nCnt].mtxWorld._23 = mtxView._32;
			g_aBullet[nCnt].mtxWorld._31 = mtxView._13;
			g_aBullet[nCnt].mtxWorld._32 = mtxView._23;
			g_aBullet[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCnt].pos.x, g_aBullet[nCnt].pos.y, g_aBullet[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCnt].mtxWorld, &g_aBullet[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャ座標の設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================================================
// 弾の設定処理
//============================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, float radius)
{
	//頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == false)
		{
			g_aBullet[nCnt].pos = pos;													//位置の設定
			g_aBullet[nCnt].dir = dir;													//方向ベクトルの設定
			g_aBullet[nCnt].radius = radius;											//半径の設定
			g_aBullet[nCnt].nLife = BULLET_LIFE;

			pVtx[0].pos.x = g_aBullet[nCnt].pos.x - g_aBullet[nCnt].radius;
			pVtx[0].pos.y = g_aBullet[nCnt].pos.y + g_aBullet[nCnt].radius;
			pVtx[0].pos.z = g_aBullet[nCnt].pos.z;

			pVtx[1].pos.x = g_aBullet[nCnt].pos.x + g_aBullet[nCnt].radius;
			pVtx[1].pos.y = g_aBullet[nCnt].pos.y + g_aBullet[nCnt].radius;
			pVtx[1].pos.z = g_aBullet[nCnt].pos.z;

			pVtx[2].pos.x = g_aBullet[nCnt].pos.x - g_aBullet[nCnt].radius;
			pVtx[2].pos.y = g_aBullet[nCnt].pos.y - g_aBullet[nCnt].radius;
			pVtx[2].pos.z = g_aBullet[nCnt].pos.z;

			pVtx[3].pos.x = g_aBullet[nCnt].pos.x + g_aBullet[nCnt].radius;
			pVtx[3].pos.y = g_aBullet[nCnt].pos.y - g_aBullet[nCnt].radius;
			pVtx[3].pos.z = g_aBullet[nCnt].pos.z;

			//影のインデックスの設定
			g_aBullet[nCnt].nIndexShadow = SetShadow(g_aBullet[nCnt].pos, g_aBullet[nCnt].rot,D3DXVECTOR3(0.25f,0.5f,0.25f));
			g_aBullet[nCnt].bUse = true;												//使用している状態にする
			break;
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffBullet->Unlock();
}

//============================================================
// 弾の情報取得
//============================================================
Bullet* GetBullet()
{
	return &g_aBullet[0];
}

//============================================================
// 弾の当たり判定
//============================================================
bool CollisionBullet()		
{

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{	
			//++++++++++++++++
			//壁との当たり判定
			//++++++++++++++++
			
			//壁の情報取得
			Wall* pWall = GetWall();

			D3DXVECTOR3 vecLine = pWall->vecWall;//vecLine格納
			D3DXVECTOR3 vecMove = g_aBullet[nCnt].move - pWall->aPos[0];

			//計算結果格納用
			D3DXVECTOR3 vecNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//外積
			D3DXVec3Cross(&vecNor, &pWall->vecWall, &vecMove);

			if (vecNor.y < 0)
			{
				SetExplosion(g_aBullet[nCnt].posOld, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), g_aBullet[nCnt].rot, g_aBullet[nCnt].radius * 0.9f);
				vecNor *= -1;

				//内積
				float fvec = (vecMove.x*vecNor.z);
			}
		}
	}
	return g_aBullet[0].ver;
}