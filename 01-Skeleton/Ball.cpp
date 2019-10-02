#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "Ball.h"

void Ball::Update(DWORD dt) {

	x += vxBall * dt;
	y += vyBall * dt;
	if (x > (320 - 25) || x < 0) vxBall = -vxBall;
	if (y > (240 - 45) || y < 0) vyBall = -vyBall;
}
