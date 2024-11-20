//============================================================
//
//カメラ[camera.h]
//Author:Rio Ohno
//
//=============================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"
#include"input.h"
#include"player.h"

//カメラのタイプ
typedef enum
{
	CAMERATYPE_NOMAL = 0,
	CAMERATYPE_ASSENT,
	CAMERATYPE_MAX
}CAMERATYPE;

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 vecU;
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXVECTOR3 rot;
	CAMERATYPE type;
	float fDistance;
	bool bAssent;
}Camera;

//プロトタイプ宣言
void InitCamera();
void UninitCamera();
void UpdateCamera();
void SetCamera();
Camera* GetCamera();

#endif // !_CAMERA_H_

