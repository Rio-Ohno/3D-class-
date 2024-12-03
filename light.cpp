//============================================================
//
//ライト[light.cpp]
//Author:Rio Ohno
//
//============================================================

#include"light.h"

//グローバル変数
D3DLIGHT9 g_light[MAX_LIGHT];//ライト情報

//============================================================
// ライトの初期化処理
//============================================================
void InitLight()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir[MAX_LIGHT];//ライトの方向ベクトル

	//ライトをクリア
	ZeroMemory(&g_light, sizeof(g_light));

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの種類を設定
		g_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;//平行光源

		//ライトの拡散光を設定
		g_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//ライトの方向を設定
	vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.2f);
	vecDir[1] = D3DXVECTOR3(-0.2f, -0.8f, -0.4f);
	vecDir[2] = D3DXVECTOR3(0.0f, -0.8f, 0.2f);

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//正視化する
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		g_light[nCnt].Direction = vecDir[nCnt];

		//ライトを設定する
		pDevice->SetLight(nCnt, &g_light[nCnt]);
	}

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//============================================================
// ライトの終了処理
//============================================================
void UninitLight()
{

}

//============================================================
// ライトの更新処理
//============================================================
void UpdateLight()
{

}
