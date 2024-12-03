//============================================================
//
//インデックスバッファ[meshfield.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include"main.h"

//マクロ定義
#define MAX_X_FIELD (6)																	//x分割数
#define MAX_Z_FIELD (6)																	//z分割数
#define MAX_VERTEX_FIELD ((MAX_X_FIELD+1)*(MAX_Z_FIELD+1))								//頂点数
#define MAX_INDX_FIELD ((MAX_Z_FIELD * 2) * (MAX_X_FIELD + (MAX_Z_FIELD * 2) -1))		//インデックス数((x+1)*2*z+(z-1)*(縮退ポリゴンの頂点数=4Z))
#define MAX_POLY_FIELD ((MAX_Z_FIELD * 2) * (MAX_X_FIELD + (MAX_Z_FIELD - 1) * 2))		//ポリゴン数(x*z*2+(z-1)*(縮退ポリゴン=4Z))

//メッシュフィールド構造体
typedef struct
{
	D3DXVECTOR3 pos;																	//位置
	D3DXVECTOR3 rot;																	//向き
	float  fHight;																		//高さ
	float  fWidth;																		//幅
	D3DXMATRIX mtxWorld;																//ワールドマトリックス
}MeshField;

//プロトタイプ宣言
void InitMeshField();																	//初期化
void UninitMeshField();																	//終了処理
void UpdateMeshField();																	//更新処理
void DrawMeshField();																	//描画処理

#endif // !_MeshField_H_
