//============================================================
//
//プレイヤー[player.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"

//マクロ定義
#define MAX_MAT_PLAYER (512)			//マトリックスの最大数
#define PLAYER_SPEED (0.5f)				//プレイヤーのスピード

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 posOld;					//前回の位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 rotDest;				//目標の向き
	D3DXVECTOR3 vtxMin;					//モデルの最小値
	D3DXVECTOR3 vtxMax;					//モデルの最大値
	D3DXVECTOR3 size;					//サイズ(大きさ)
	int nIndxShadow;					//影のインデックス格納用
}Player;

//プロトタイプ宣言
void InitPlayer();//プレイヤーの初期化処理
void UninitPlayer();//プレイヤーの終了処理
void UpdatePlayer();//プレイヤーの更新処理
void DrawPlayer();//プレイヤーの描画処理
Player* GetPlayer();

#endif // !_MODEL_H_
