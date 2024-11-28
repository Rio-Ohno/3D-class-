//============================================================
//
//壁[wall.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"
#include"camera.h"

//マクロ定義
#define MAX_WALL (10)																		//壁の最大数

//壁の構造体
typedef struct
{
	D3DXVECTOR3 pos;																		//位置
	D3DXVECTOR3 rot;																		//向き
	D3DXVECTOR3 vecWall;																	//vecLine
	D3DXVECTOR3 aPos[2];																	//頂点座標格納用([0]:始点)
	D3DXVECTOR3 fver;																		//判定
	D3DXMATRIX mtxWorldWall;																//ワールドマトリックス
	float fWidth;																			//幅
	float fHight;																			//高さ
	bool bUse;																				//使用しているかどうか
}Wall;

//プロトタイプ宣言
void InitWall();																			//壁の初期化処理
void UninitWall();																			//壁の終了処理
void UpdateWall();																			//壁の更新処理
void DrawWall();																			//壁の描画処理
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fWidth,float fHight, float a);			//壁の設定処理
void CollisionWall();																		//壁の当たり判定
Wall* GetWall();

#endif // !_Wall_H_