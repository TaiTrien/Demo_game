#include "Mario.h"

void CMario::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	vy += MARIO_GRAVITY;
	if (y > 100) 
	{
		vy = 0; y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

void CMario::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) {
			if (state == MARIO_STATE_IDLE && isGrow == true && isWhite == false)
				ani = MARIO_ANI_IDLE_RIGHT;
			else if (state == MARIO_STATE_IDLE && isGrow == false)
				ani = MARIO_ANI_BABY_INDLE_RIGHT;
			else if (state == MARIO_STATE_IDLE && isGrow == true && isWhite == true)
				ani = MARIO_ANI_WHITE_IDLE_RIGHT;
		}
	
		else {
			if (state == MARIO_STATE_IDLE && isGrow == true && isWhite == false)
				ani = MARIO_ANI_IDLE_LEFT;
			else if (state == MARIO_STATE_IDLE && isGrow == false)
				ani = MARIO_ANI_BABY_INDLE_LEFT;
			else if (state == MARIO_STATE_IDLE && isGrow == true && isWhite == true)
				ani = MARIO_ANI_WHITE_IDLE_LEFT;
		} 		
		if (state == MARIO_STATE_SIT_DOWN && nx > 0) {
			if (isGrow == true) {
				if (isWhite == false)
					ani = MARIO_ANI_SIT_DOWN_RIGHT;
				else ani = MARIO_ANI_WHITE_SIT_DOWN_RIGHT;
			}
			else ani = MARIO_ANI_BABY_INDLE_RIGHT;
		}
		else if (state == MARIO_STATE_SIT_DOWN && nx<0){
			if (isGrow == true) {
				if (isWhite == false)
				ani = MARIO_ANI_SIT_DOWN_LEFT;
				else ani = MARIO_ANI_WHITE_SIT_DOWN_LEFT;
			}
			else ani = MARIO_ANI_BABY_INDLE_LEFT;
		}
		
	}
	else if (vx > 0) {
		if (isGrow == true) {
			if (isWhite == false)
			ani = MARIO_ANI_WALKING_RIGHT;
			else ani = MARIO_ANI_WHITE_WALKING_RIGHT;
		}
		else
			ani = MARIO_ANI_BABY_WALKING_RIGHT;
	}
	else if (vx < 0) {
		if (isGrow == true) {
			if (isWhite == false)
				ani = MARIO_ANI_WALKING_LEFT;
			else ani = MARIO_ANI_WHITE_WALKING_LEFT;
		}
		else
			ani = MARIO_ANI_BABY_WALKING_LEFT;
	}
	if (state == MARIO_STATE_JUMP) {
		if (isGrow == true) {
			if (nx > 0) {
				if (isWhite == false)
				ani = MARIO_ANI_IDLE_RIGHT;
				else ani = MARIO_ANI_WHITE_IDLE_RIGHT;
			}
			else {
				if (isWhite == false)
					ani = MARIO_ANI_IDLE_LEFT;
				else ani = MARIO_ANI_WHITE_IDLE_LEFT;
			}
		}
		else {
			if (nx > 0) ani = MARIO_ANI_BABY_INDLE_RIGHT;
			else ani = MARIO_ANI_BABY_INDLE_LEFT;
		}
	}
	animations[ani]->Render(x, y);
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP: 
		if (y==100)
			vy = -MARIO_JUMP_SPEED_Y;

	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_SIT_DOWN:
		vx = 0;
		break;
	}
}
boolean CMario::CheckISGrow() {
	return this->isGrow;
}
boolean CMario::CheckISWhite() {
	return this->isWhite;
}
void CMario::setGrow(boolean temp) {
	isGrow = temp;
}
void CMario::setWhite(boolean temp) {
	isWhite = temp;
}



