//============================================================
//
//弾[bullet.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//マクロ定義
#define MAX_BULLET (256)											//弾の最大数
#define BULLET_SPEED (1.0f)											//弾のスピード
#define BULLET_LIFE (180)											//弾のライフ

//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;												//位置
	D3DXVECTOR3 rot;												//向き
	D3DXVECTOR3 dir;												//方向ベクトル(move?)
	D3DXMATRIX mtxWorld;											//ワールドマトリックス
	int nIndexShadow;												//影のインデックス
	float radius;													//半径
	int nLife;														//寿命
	bool bUse;														//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet();													//初期化処理
void UninitBullet();												//終了処理
void UpdateBullet();												//更新処理
void DrawBullet();													//描画処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, float radius);		//設定処理
Bullet* GetBullet();												//情報渡す

#endif // !_Bullet_H_
