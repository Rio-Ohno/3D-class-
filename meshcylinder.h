//============================================================
//
//インデックスバッファ[meshfield.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include"main.h"

//マクロ定義
#define MAX_X_CYLINDER (8)																		//x分割数
#define MAX_Z_CYLINDER (1)																		//z分割数
#define MAX_VERTEX ((MAX_X_CYLINDER+1)*(MAX_Z_CYLINDER+1))										//頂点数
#define MAX_INDX ((MAX_Z_CYLINDER * 2) * (MAX_X_CYLINDER + (MAX_Z_CYLINDER * 2) -1))			//インデックス数((x+1)*2*z+(z-1)*(縮退ポリゴン数=4Z))
#define MAX_POLY ((MAX_Z_CYLINDER*2)*(MAX_X_CYLINDER+(MAX_Z_CYLINDER-1)*2))						//ポリゴン数(x*z*2+(z-1)*(縮退ポリゴン=4Z))

//メッシュフィールド構造体
typedef struct
{
	D3DXVECTOR3 pos;																			//位置
	D3DXVECTOR3 rot;																			//向き
	D3DXMATRIX mtxWorld;																		//ワールドマトリックス
}MeshCylinder;

//プロトタイプ宣言
void InitMeshCylinder();																		//初期化
void UninitMeshCylinder();																		//終了処理
void UpdateMeshCylinder();																		//更新処理
void DrawMeshCylinder();																		//描画処理

#endif // !_MeshCylinder_H_
