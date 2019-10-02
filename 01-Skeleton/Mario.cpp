#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "Mario.h"

void Mario::Update(DWORD dt) {
	
	x += vxMario * dt;
	if (x > (320 - 25) || x < 0) vxMario = -vxMario;
}
