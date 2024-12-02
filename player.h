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
#include"model.h"

//マクロ定義.......................................................
#define MAX_KEY (10)					//キーの最大数
#define MAX_MAT_PLAYER (512)			//マトリックスの最大数
#define MAX_MOTION (4)					//モーションの最大数
#define MAX_PARTS (2)					//パーツの最大数
#define PLAYER_SPEED (1.5f)				//プレイヤーのスピード

//モーションの種類............................................
typedef enum
{
	MOTIONTYPE_NEUTRAL=0,				//ニュートラル
	MOTIONTYPE_MOVE,					//移動
	MOTIONTYPE_ACTION,					//アクション
	MOTIONTYPE_JUMP,					//ジャンプ
	MOTIONTYPE_MAX
}MOTIONTYPE;

//キーの構造体................................................
typedef struct
{
	float fPosX;						//位置X
	float fPosY;						//位置Y
	float fPosZ;						//位置Z
	float fRotX;						//向きX
	float fRotY;						//向きY
	float fRotZ;						//向きZ
}Key;

//キー情報の構造体............................................
typedef struct
{
	int nFrame;							//再生フレーム
	Key aKEY[MAX_PARTS];				//各パーツのキー要素
}Key_Info;

//モーション情報の構造体......................................
typedef struct
{
	bool bLoop;							//ループするかどうか
	int nNumKey;						//キーの総数
	Key_Info aKeyInfo[MAX_KEY];			//キー情報
}Motion_Info;

//プレイヤー構造体....................................................
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 posOld;					//前回の位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 rotDest;				//目標の向き
	D3DXVECTOR3 vtxMin;					//モデルの最小値
	D3DXVECTOR3 vtxMax;					//モデルの最大値
	D3DXVECTOR3 size;					//サイズ(大きさ)
	D3DXVECTOR3 move;					//移動量
	D3DXMATRIX mtxWorldPlayer;			//プレイヤーのワールドマトリックス
	Model aModel[MAX_PARTS];			//モデル(パーツ)
	Motion_Info aMotionInfo[MAX_MOTION];//モーション情報
	MOTIONTYPE motionType;				//モーションの種類
	int nNumModel;						//モデル(パーツ)の総数
	int nNumMotion;						//モーションの最大数
	int nNumKey;						//キーの最大数
	int nKey;							//現在のキーNO.
	int nCounterMotion;					//モーションカウンター
	int nIndxShadow;					//影のインデックス格納用
	bool bLoopMotion;					//ループするかどうか
	bool bjump;							//ジャンプ
	bool bUse;							//使用しているかどうか
}Player;

//============================================================
//プロトタイプ宣言
//============================================================
void InitPlayer();						//プレイヤーの初期化処理
void UninitPlayer();					//プレイヤーの終了処理
void UpdatePlayer();					//プレイヤーの更新処理
void DrawPlayer();						//プレイヤーの描画処理
void SetMotion(MOTIONTYPE type);		//プレイヤーのモーション設定
Player* GetPlayer();					//プレイヤーの情報取得

#endif // !_MODEL_H_
