#pragma once

#include <Windows.h>
#include <d3dx9.h>

class CGameObject
{
protected: 
	float x; 
	float y;

	LPDIRECT3DTEXTURE9 texture;			
public: 
	CGameObject() {};
	void SetPosition(float x, float y) { this->x = x, this->y = y; }

	CGameObject(LPCWSTR texturePath);
	virtual void Update(DWORD dt);
	void Render();
	~CGameObject();
};