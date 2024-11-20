//============================================================
//
//ビルボード[billboard.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include"main.h"

//マクロ定義
#define MAX_BILLBOARD (256)											//ビルボードの最大数

//ビルボード構造体
typedef struct
{
	D3DXVECTOR3 pos;												//位置
	D3DXVECTOR3 rot;												//向き
	D3DXVECTOR3 dir;												//方向ベクトル(move?)
	D3DXMATRIX mtxWorld;											//ワールドマトリックス
	float radius;													//半径
	bool bUse;														//使用しているかどうか
}Billboard;

//プロトタイプ宣言
void InitBillboard();												//初期化処理
void UninitBillboard();												//終了処理
void UpdateBillboard();												//更新処理
void DrawBillboard();												//描画処理
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, float radius);	//設定処理

#endif // !_Billboard_H_
