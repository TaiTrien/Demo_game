#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_GRAVITY			0.1f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_SIT_DOWN		400
	

#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3
#define MARIO_ANI_SIT_DOWN_RIGHT	4
#define MARIO_ANI_SIT_DOWN_LEFT		5

#define MARIO_ANI_BABY_INDLE_LEFT	6
#define MARIO_ANI_BABY_INDLE_RIGHT	7
#define MARIO_ANI_BABY_WALKING_LEFT	8
#define MARIO_ANI_BABY_WALKING_RIGHT 9

#define MARIO_ANI_WHITE_IDLE_LEFT 10
#define MARIO_ANI_WHITE_IDLE_RIGHT 11
#define MARIO_ANI_WHITE_WALKING_LEFT 12
#define MARIO_ANI_WHITE_WALKING_RIGHT 13
#define MARIO_ANI_WHITE_SIT_DOWN_RIGHT 14
#define MARIO_ANI_WHITE_SIT_DOWN_LEFT 15

class CMario : public CGameObject
{
private:
	 boolean isGrow;
	 boolean isWhite;
public: 
	boolean CheckISGrow();
	boolean CheckISWhite();
	CMario() { isGrow = false; }
	void setWhite(boolean);
	void setGrow(boolean);
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};