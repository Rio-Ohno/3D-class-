//============================================================
//
//カメラ[camera.cpp]
//Author:Rio Ohno
//
//============================================================

#include"camera.h"

//グローバル変数
Camera g_camera;					//カメラ情報

//============================================================
// カメラの初期化処理
//============================================================
void InitCamera()
{
	//各種初期化
	g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.bAssent = false;

	//視点から注視点の距離計算
	float fDisX = g_camera.posR.x - g_camera.posV.x;
	float fDisY = g_camera.posR.y - g_camera.posV.y;
	float fDisZ = g_camera.posR.z - g_camera.posV.z;

	//対角線の長さを算出する
	g_camera.fDistance = sqrtf(fDisX * fDisX + fDisZ * fDisZ + fDisY * fDisY);
}

//============================================================
// カメラの終了処理
//============================================================
void UninitCamera()
{

}

//============================================================
//カメラの更新処理
//============================================================
void UpdateCamera()
{
	//リセット================================================================================
	if (KeyboardTrigger(DIK_R) == true)
	{
		InitCamera();
	}

	//追従のオンオフ
	if (KeyboardTrigger(DIK_F) == true)
	{
		g_camera.bAssent = g_camera.bAssent ? false : true;
	}

	if (g_camera.bAssent == false)
	{
		g_camera.type = CAMERATYPE_NOMAL;
	}
	else if (g_camera.bAssent = true)
	{
		g_camera.type = CAMERATYPE_ASSENT;
	}


	if (g_camera.type == CAMERATYPE_NOMAL)
	{
		//注視点の旋回============================================================================
		if (GetKeyboardPress(DIK_A) == true)//Aボタン
		{
			g_camera.rot.y -= 0.01f;

			//目標の移動方向（角度）の補正
			if (g_camera.rot.y < -D3DX_PI)
			{
				g_camera.rot.y += D3DX_PI * 2.0f;
			}

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
		}
		else if (GetKeyboardPress(DIK_D) == true)//Dボタン
		{
			g_camera.rot.y += 0.01f;

			//目標の移動方向（角度）の補正
			if (g_camera.rot.y > D3DX_PI)
			{
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
		}

		//カメラの移動============================================================================
		if (GetKeyboardPress(DIK_I) == true)
		{
			g_camera.posV.x += sinf(g_camera.rot.y) * 1.0f;
			g_camera.posV.z += cosf(g_camera.rot.y) * 1.0f;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
		}
		else if (GetKeyboardPress(DIK_K) == true)
		{
			g_camera.posV.x -= sinf(g_camera.rot.y) * 1.0f;
			g_camera.posV.z -= cosf(g_camera.rot.y) * 1.0f;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

		}
		else if (GetKeyboardPress(DIK_J) == true)
		{

			g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI / 2.0f) * 1.0f;
			g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI / 2.0f) * 1.0f;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

		}
		else if (GetKeyboardPress(DIK_L) == true)
		{

			g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI / 2.0f) * 1.0f;
			g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI / 2.0f) * 1.0f;

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;

		}
		//else if (GetKeyboardPress(DIK_T) == true)
		//{
		//	g_camera.posV.y += 0.05f;
		//	g_camera.posR.y = g_camera.posV.y;
		//}
		//else if (GetKeyboardPress(DIK_G) == true)
		//{
		//	g_camera.posV.y -= 0.05f;
		//	g_camera.posR.y = g_camera.posV.y;
		//}
	}
	//追従====================================================================================
	else if (g_camera.type == CAMERATYPE_ASSENT)
	{
		Player* pPlayer = GetPlayer();

		//対角線の角度を算出する

		//目的の値
		g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * PLAYER_SPEED;
		g_camera.posRDest.y = pPlayer->pos.y;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * PLAYER_SPEED;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posVDest.y = pPlayer->pos.y;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fDistance;

		//
		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.05;
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.05;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.05;

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.05;
		//g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.05;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.05;

	}

	//視点の旋回============================================================================
	if (GetKeyboardPress(DIK_E) == true)//Hボタン
	{
		g_camera.rot.y -= 0.01f;

		//目標の移動方向（角度）の補正
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;

	}
	else if (GetKeyboardPress(DIK_Q) == true)//Fボタン
	{
		g_camera.rot.y += 0.01f;

		//目標の移動方向（角度）の補正
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fDistance;

	}
	else if (GetKeyboardPress(DIK_Y) == true)
	{
		g_camera.rot.x -= 0.01f;

		//角度の正規化
		if (g_camera.rot.x < -D3DX_PI)
		{
			g_camera.rot.x += D3DX_PI * 2.0f;
		}

		g_camera.posV.y = g_camera.posR.y - sinf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.x) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_H) == true)
	{
		g_camera.rot.x += 0.01f;

		//角度の正規化
		if (g_camera.rot.x > D3DX_PI)
		{
			g_camera.rot.x -= D3DX_PI * 2.0f;
		}

		g_camera.posV.y = g_camera.posR.y - sinf(g_camera.rot.x) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.x) * g_camera.fDistance;
	}
}

//============================================================
// カメラの設定処理
//============================================================
void SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタ

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f),
														(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
														10.0f,
														1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//============================================================
// カメラの情報取得
//============================================================
Camera*GetCamera()
{
	return &g_camera;
}