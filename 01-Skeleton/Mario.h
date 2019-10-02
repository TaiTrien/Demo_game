#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include "GameObject.h"

class Mario : public CGameObject
{
protected:
	float vxMario;
	float vyMario;
public:
	Mario(LPCWSTR texturePath) :CGameObject(texturePath) { vxMario = 0.1f; };
	void Update(DWORD dt);
	void Render();
};