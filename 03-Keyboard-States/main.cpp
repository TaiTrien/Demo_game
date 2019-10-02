/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 90

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

CGame *game;
CMario *mario;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		if (mario->CheckISGrow() == true && mario->CheckISWhite() == false ) {
			mario->SetState(MARIO_STATE_IDLE);
			mario->setWhite(true);
		}
		else if (mario->CheckISGrow() == true && mario->CheckISWhite() == TRUE) {
			mario->SetState(MARIO_STATE_IDLE);
			mario->setGrow(false);
			mario->setWhite(false);
		}
		else {
			mario->SetState(MARIO_STATE_IDLE);
			mario->setGrow(true);
			mario->setWhite(false);
		}
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_RIGHT))
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_DOWN))
		mario->SetState(MARIO_STATE_SIT_DOWN);
	else mario->SetState(MARIO_STATE_IDLE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, L"textures\\mario.png",D3DCOLOR_XRGB(176, 224, 248));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);

	//mario mature 
	sprites->Add(10001, 246, 154, 260, 181, texMario);

	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 200, 181, texMario);

	sprites->Add(10012, 155, 154, 170, 181, texMario);
	sprites->Add(10013, 125, 154, 140, 181, texMario);

	sprites->Add(20011, 425, 195, 425 + 16, 195 + 26, texMario);
	sprites->Add(20012, 5, 195, 5 + 16, 195 + 26, texMario);
	//mario baby
	sprites->Add(30011, 247, 0, 247 + 12, 15, texMario);
	sprites->Add(30012, 275, 0, 275 + 16, 16, texMario);
	sprites->Add(30013, 306, 0, 306 + 15, 16, texMario);

	sprites->Add(30014, 187, 0, 187 + 12, 15, texMario);
	sprites->Add(30015, 155, 0, 155 + 16, 16, texMario);
	sprites->Add(30016, 125, 0, 125 + 15, 16, texMario);
	//mario white
	sprites->Add(40011, 246, 394, 246 + 14, 394 + 27, texMario);
	sprites->Add(40012, 275, 394, 275 + 16, 394 + 27, texMario);
	sprites->Add(40013, 305, 395, 305 + 16, 395 + 26, texMario);

	sprites->Add(40014, 186, 394, 186 + 14, 394 + 27, texMario);
	sprites->Add(40015, 155, 394, 155 + 16, 394 + 27, texMario);
	sprites->Add(40016, 125, 395, 125 + 16, 395 + 26, texMario);

	sprites->Add(40017, 425, 435, 425 + 16, 435 + 26, texMario);
	sprites->Add(40018, 5, 435, 5 + 16, 435 + 26, texMario);




	LPANIMATION ani;

	ani = new CAnimation(100);	
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);
	ani->Add(20011);
	animations->Add(502, ani);

	ani = new CAnimation(100);
	ani->Add(20012);
	animations->Add(503, ani);
	//ani baby

	ani = new CAnimation(100);
	ani->Add(30011);
	ani->Add(30012);
	ani->Add(30013);
	animations->Add(505, ani);

	ani = new CAnimation(100);
	ani->Add(30014);
	ani->Add(30015);
	ani->Add(30016);
	animations->Add(504, ani);

	ani = new CAnimation(100);
	ani->Add(30011);
	animations->Add(507, ani);

	ani = new CAnimation(100);
	ani->Add(30014);
	animations->Add(506, ani);
	// ani white
	ani = new CAnimation(100);
	ani->Add(40011);
	animations->Add(509, ani);

	ani = new CAnimation(100);
	ani->Add(40014);
	animations->Add(508, ani);

	ani = new CAnimation(100);
	ani->Add(40011);
	ani->Add(40012);
	ani->Add(40013);
	animations->Add(511, ani);

	ani = new CAnimation(100);
	ani->Add(40014);
	ani->Add(40015);
	ani->Add(40016);
	animations->Add(510, ani);

	ani = new CAnimation(100);
	ani->Add(40017);
	animations->Add(512, ani);

	ani = new CAnimation(100);
	ani->Add(40018);
	animations->Add(513, ani);

	mario = new CMario();
	CMario::AddAnimation(400);		// idle right
	CMario::AddAnimation(401);		// idle left
	CMario::AddAnimation(500);		// walk right
	CMario::AddAnimation(501);		// walk left
	CMario::AddAnimation(502);		// sit down right 
	CMario::AddAnimation(503);		// sit down left

	CMario::AddAnimation(506);		// baby idle right
	CMario::AddAnimation(507);		// baby idle left
	CMario::AddAnimation(504);		// baby walk right
	CMario::AddAnimation(505);		// baby walk left

	CMario::AddAnimation(508);		// white idle right
	CMario::AddAnimation(509);		// white idle left
	CMario::AddAnimation(510);		// white walk right
	CMario::AddAnimation(511);		// white walk left

	CMario::AddAnimation(512);		// white sit down left
	CMario::AddAnimation(513);		// white sit down right




	mario->SetPosition(0.0f, 100.0f);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		mario->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();

	return 0;
}