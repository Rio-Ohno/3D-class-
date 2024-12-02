//============================================================
//
//インデックスバッファ[meshwall.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include"main.h"

//マクロ定義
#define MAX_X_WALL (2)																	//x分割数
#define MAX_Y_WALL (1)																	//z分割数
#define MAX_VERTEX_WALL ((MAX_X_WALL+1)*(MAX_Y_WALL+1))									//頂点数
#define MAX_INDX_WALL ((MAX_Y_WALL * 2) * (MAX_X_WALL + (MAX_Y_WALL * 2) -1))			//インデックス数((x+1)*2*z+(z-1)*(縮退ポリゴン数=4Z))
#define MAX_POLY_WALL ((MAX_Y_WALL*2)*(MAX_X_WALL+(MAX_Y_WALL-1)*2))					//ポリゴン数(x*z*2+(z-1)*(縮退ポリゴン=4Z))
#define MAX_MESHWALL (4)																	//壁の最大数

//メッシュフィールド構造体
typedef struct
{
	D3DXVECTOR3 pos;																	//位置
	D3DXVECTOR3 rot;																	//向き
	float  fHight;																		//高さ
	float  fWidth;																		//幅
	D3DXMATRIX mtxWorld;																//ワールドマトリックス
	bool bUse;																			//使用しているかどうか
}MeshWall;

//プロトタイプ宣言
void InitMeshWall();																	//初期化
void UninitMeshWall();																	//終了処理
void UpdateMeshWall();																	//更新処理
void DrawMeshWall();																	//描画処理
void SetMeshWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot);										//設定処理

#endif // !_MeshWall_H_

