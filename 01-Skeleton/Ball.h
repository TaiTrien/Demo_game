#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include "GameObject.h"
class Ball :public CGameObject
{
protected:
	float vxBall;
	float vyBall;
public:
	Ball(LPCWSTR texturePath) :CGameObject(texturePath) { vxBall = 0.1f; vyBall = 0.2f; };
	void Update(DWORD dt);
};
