//============================================================
//
//ブロック[block.h]
//Author:Rio Ohno
//
//============================================================

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
#include"player.h"

//マクロ定義
#define MAX_MAT_BLOCK (512)

//プロトタイプ宣言
void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();
void CollisionBlock_X();
void CollisionBlock_Z();

#endif // !_MODEL_H_

#pragma once
