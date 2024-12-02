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
Player g_player;
static  Key_Info g_keyNeutrall[]=
{ //Key0
	{40,
	//パーツ0
	{{0.0f,0.2f,0.0f,0.06f, 0.0f, 0.0f},
	//パーツ1
	 {0.0f ,0.0f ,0.0f,-0.16f, 0.0f, 0.0f}}
	},
	 //Key1
	{40,
	{{0.0f, 1.2f, 0.0f,0.06f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f,-0.09f, 0.0f, 0.0f}}
	}
};

//============================================================
// プレイヤーの初期化処理
//============================================================
void InitPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//各種初期化
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.nNumModel = 0;
	g_player.nNumMotion = 0;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;
	g_player.nIndxShadow = SetShadow(g_player.pos,g_player.rot,D3DXVECTOR3(1.0f,0.5f,1.0f));
	g_player.bjump = false;
	g_player.bUse = true;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorldPlayer);

	//Xファイルの読込
	D3DXLoadMeshFromX("data\\MODEL\\cat\\koshi.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].dwNumMat,
		&g_player.aModel[0].pMesh);

	D3DXLoadMeshFromX("data\\MODEL\\cat\\mune.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMat,
		NULL,
		&g_player.aModel[1].dwNumMat,
		&g_player.aModel[1].pMesh);

	//D3DXLoadMeshFromX("data\\MODEL\\cat\\atama.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[2].pBuffMat,
	//	NULL,
	//	&g_player.aModel[2].dwNumMat,
	//	&g_player.aModel[2].pMesh);

	g_player.nNumModel = 2;												//パーツ数の設定

	//各パーツの階層構造設定
	g_player.aModel[0].nIndxModelpParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.aModel[1].nIndxModelpParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 9.5f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//g_player.aModel[2].nIndxModelpParent = 1;
	//g_player.aModel[2].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	//g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{

		int nNumVtx;//最大頂点数
		DWORD sizeFVF;//頂点フォーマットのサイズ
		BYTE* pVtxBUff;//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = g_player.aModel[nCntModel].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMesh->GetFVF());

		//頂点バッファのロック
		g_player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

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
		g_player.aModel[nCntModel].pMesh->UnlockVertexBuffer();

		//サイズの初期化
		g_player.size = g_player.vtxMax - g_player.vtxMin;

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCnt = 0; nCnt < (int)g_player.aModel[nCntModel].dwNumMat; nCnt++)
		{
			//テクスチャポインタの初期化
			g_player.aModel[nCntModel].apTextureModel[nCnt] = {};

			if (pMat[nCnt].pTextureFilename != NULL)
			{
				//テクスチャの読込
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCnt].pTextureFilename,
					&g_player.aModel[nCntModel].apTextureModel[nCnt]);

			}
		}
	}
}

//============================================================
// プレイヤーの終了処理
//============================================================
void UninitPlayer()
{
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{

		//メッシュの破棄
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}

		//テクスチャの破棄
		for (int nCnt1 = 0; nCnt1 < (int)g_player.aModel[nCntModel].dwNumMat; nCnt1++)
		{
			if (g_player.aModel[nCntModel].apTextureModel[nCnt1] != NULL)
			{
				g_player.aModel[nCntModel].apTextureModel[nCnt1]->Release();
				g_player.aModel[nCntModel].apTextureModel[nCnt1] = NULL;
			}
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
		g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 2.0f;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.move.z += cosf(pCamera->rot.y + D3DX_PI / 2.0f) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y - D3DX_PI / 2.0f;

	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y) * PLAYER_SPEED;
		g_player.move.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
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

		g_player.move.x += sinf(rot.y) * PLAYER_SPEED;
		g_player.move.z += cosf(rot.y) * PLAYER_SPEED;
		g_player.rotDest.y = pCamera->rot.y;
	}

	//ジャンプ
	if (g_player.bjump == false)
	{
		if (KeyboardTrigger(DIK_SPACE) == true)
		{
			g_player.move.y += 30.0f;
			g_player.bjump = true;
		}
	}

	g_player.move.y -= 0.8f;

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.15f;

	//位置の更新
	g_player.pos += g_player.move;

	//移動量の更新(減衰)
	g_player.move.x = (0.0f - g_player.move.x) * 0.1f;
	g_player.move.y = (0.0f - g_player.move.y) * 0.1f;
	g_player.move.z = (0.0f - g_player.move.z) * 0.1f;

	//床判定
	if (g_player.pos.y < 0)
	{
		g_player.pos.y = 0;
		g_player.bjump = false;
	}

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
	CollisionWall();

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, g_player.pos.z), g_player.rot, 5.0f);
	}

	//全モデル(パーツ)の更新
	//for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	//{
	//	//キー情報から位置と向きを算出
	//	int
	//}
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
	D3DXMatrixIdentity(&g_player.mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorldPlayer);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);


	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX  mtxRotModel, mtxTransModel;	//計算用マトリックス
		D3DXMATRIX mtxParent;				//親のマtリックス

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//パーツの親マトリックスの設定
		if (g_player.aModel[nCntModel].nIndxModelpParent != -1)//子の時
		{
			mtxParent = g_player.aModel[0].mtxWorld;
		}
		else//親の時
		{
			mtxParent = g_player.mtxWorldPlayer;
		}

		//算出したパーツのワールドマトリックスと親のマトリックスをかけ合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		//パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		for (int nCnt1 = 0; nCnt1 < (int)g_player.aModel[nCntModel].dwNumMat; nCnt1++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCnt1].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_player.aModel[nCntModel].apTextureModel[nCnt1]);

			//モデル(パーツ)の描画
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCnt1);
		}

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

void SetMotion(MOTIONTYPE type)
{
	switch (g_player.motionType)
	{
	case MOTIONTYPE_NEUTRAL:

		g_player.bLoopMotion = true;
		g_player.nNumKey = 2;
		

		break;

	case MOTIONTYPE_MOVE:
		break;

	case MOTIONTYPE_ACTION:
		break;

	case MOTIONTYPE_JUMP:
		break;

	}
}