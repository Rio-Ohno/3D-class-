//============================================================
//
//影[shadow.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _SHADOW_H_
#define _SHADOW_H_

#include"main.h"

//マクロ定義
#define MAX_SHADOW (1024)												//影の最大数
#define BASIS_SIZE (30.0f)												//サイズの基準

//影の構造体
typedef struct
{
	D3DXVECTOR3 pos;													//位置
	D3DXVECTOR3 rot;													//向き
	D3DXVECTOR3 scale;													//倍率(基準30)
	D3DXMATRIX mtxWorld;												//ワールドマトリックス
	bool bUse;															//使用しているかどうか
}Shadow;

//プロトタイプ宣言
void InitShadow();														//影の初期化
void UninitShadow();													//影の終了処理
void UpdateShadow();													//影の更新処理
void DrawShadow();														//影の描画処理
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);		//影の設定処理
void SetPositionShadow(int nIndxShadow, D3DXVECTOR3 pos);				//影の位置設定処理

#endif // !_Shadow_H_
#pragma once
