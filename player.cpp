//============================================================
//
//プレイヤー[player.cpp]
//Author:Rio Ohno
//
//============================================================

#include"player.h"
#include "bullet.h"
#include "block.h"
#include "wall.h"

//グロ－バル変数宣言
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffmatPlayer = NULL;
DWORD g_dwNumMatPlayer = 0;
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_MAT_PLAYER] = {};
D3DXMATRIX g_mtxWorldPlayer;
Player g_player;

//============================================================
// プレイヤーの初期化処理
//============================================================
void InitPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//各種初期化
	g_pMeshPlayer = NULL;
	g_pBuffmatPlayer = NULL;
	g_dwNumMatPlayer = 0;
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nIndxShadow = SetShadow(g_player.pos,g_player.rot,D3DXVECTOR3(1.0f,0.5f,1.0f));

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//Xファイルの読込
	D3DXLoadMeshFromX("data\\MODEL\\TV.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffmatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	int nNumVtx;//最大頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBUff;//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//頂点バッファのロック
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

		//頂点座標を比較してモデルの最大最小を取得

		if (vtx.x > g_player.vtxMax.x)//x最大値
		{
			g_player.vtxMax.x = vtx.x;
		}
		else if (vtx.x < g_player.vtxMin.x)//x最小値
		{
			g_player.vtxMin.x = vtx.x;
		}

		if (vtx.y > g_player.vtxMax.y)//y最大値
		{
			g_player.vtxMax.y = vtx.y;
		}
		else if (vtx.y < g_player.vtxMin.y)//y最小値
		{
			g_player.vtxMin.y = vtx.y;
		}

		if (vtx.z > g_player.vtxMax.z)//z最大値
		{
			g_player.vtxMax.z = vtx.z;
		}
		else if (vtx.z < g_player.vtxMin.z)//z最小値
		{
			g_player.vtxMin.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBUff += sizeFVF;
	}

	//頂点バッファのアンロック
	g_pMeshPlayer->UnlockVertexBuffer();

	//サイズの初期化
	g_player.size = g_player.vtxMax - g_player.vtxMin;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffmatPlayer->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		//テクスチャポインタの初期化
		g_apTexturePlayer[nCnt] = {};

		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//テクスチャの読込
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&g_apTexturePlayer[nCnt]);

		}
	}
}

//============================================================
// プレイヤーの終了処理
//============================================================
void UninitPlayer()
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffmatPlayer != NULL)
	{
		g_pBuffmatPlayer->Release();
		g_pBuffmatPlayer = NULL;
	}

	//テクスチャの破棄
	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		if (g_apTexturePlayer[nCnt] != NULL)
		{
			g_apTexturePlayer[nCnt]->Release();
			g_apTexturePlayer[nCnt] = NULL;
		}
	}
}

//============================================================
// プレイヤーの更新処理
//============================================================
void UpdatePlayer()
{
	//カメラの情報取得
	Camera* pCamera = GetCamera();

	g_player.posOld = g_player.pos;

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_player.pos.x += sinf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.pos.z += cosf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2.0f;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_player.pos.x += sinf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.pos.z += cosf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2.0f;

	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{
		g_player.pos.x += sinf(pCamera->rot.y) * PLAYER_SPEED;
		g_player.pos.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//右回り左回り

		if (g_player.rot > 0)
		{
			rot.y = pCamera->rot.y + D3DX_PI;
		}
		else if (g_player.rot < 0)
		{
			rot.y = -(pCamera->rot.y + D3DX_PI);
		}

		g_player.pos.x += sinf(rot.y) * PLAYER_SPEED;
		g_player.pos.z += cosf(rot.y) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y;
	}

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.15f;

	//影の位置更新
	SetPositionShadow(g_player.nIndxShadow, g_player.pos);

	//目標の移動方向（角度）の補正
	if (g_player.rot.y > D3DX_PI)
	{	  
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}

	//当たり判定
	//CollisionBlock_X();
	//CollisionBlock_Z();
	//CollisionWall();

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetBullet(g_player.pos, g_player.rot, 5.0f);
	}
}

//============================================================
// プレイヤーの描画処理
//============================================================
void DrawPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffmatPlayer->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePlayer[nCnt]);

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCnt);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}

//============================================================
// プレイヤーの情報取得
//============================================================
Player* GetPlayer()
{
	return &g_player;
}