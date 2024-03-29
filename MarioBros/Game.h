#ifndef _GAME_H
#define _GAME_H

#include <d3d9.h>
#include <d3dx9.h>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#include "Graphic.h"
#include "Sprite.h"
#include "Animation.h"
#include "Input.h"
#include "TimeManager.h"
#include "Camera.h"
#include <list>
#include <string>
#include <iostream>
#include "Brick.h"
#include "BaseObject.h"
#include "Audio.h"
#include "Mario.h"
#include "Box.h"
#include "Collision.h"

using namespace std;
class Game
{
private:
	Graphic	*	_g;
	Audio   *   _audio;
	float		_TPF;					//Time per frame
	HWND		_hWnd;
	HINSTANCE	_hInstance;
	LPD3DXFONT	_fontArial;
	Input* _input;
	TimeManager*	_timeManager;
	void ProcessInput();
	void Update();
	void Render();
	int _count;
	Collision* _col;
	DWORD _DeltaTime;
public:
	int n;
	int m;
	int _state;
	Sprite* _sprites[20];
	Game(HWND hWnd, HINSTANCE hInstance);
	~Game();
	void GameRun();
	
	int vx;
	int vy;

	Camera* _camera;
	BaseObject  *_staticObjs[1000];
	BaseObject	*_dynamicObjs[1000];
	BaseObject* _mario;
	Sprite* _marioMenu;
	float mario_vx;
	float mario_vy;

	IDirect3DSurface9* _bgMenu;	//Background state menu
	//IDirect3DSurface9* itemMenu;//Hiện phần new game, load game...
	RECT _recMenu; //xét va chạm để vào màn chơi
	int _xMenu;//k
	int _yMenu;
	int _yarrMenu[2];
	

	//Load Resource-----------
	CSound *_sound_1up, *_sound_Beep, *_sound_BigJump, *_sound_BowserDie, *_sound_Break, *_sound_Bump, *_sound_Coin;
	CSound *_sound_Die, *_sound_EnemyFire, *_sound_FireBall, *_sound_Flagpole, *_sound_GameOver, *_sound_Item, *_sound_Warp;
	CSound	*_sound_Jump, *_sound_Kick, *_sound_Pause, *_sound_Powerup, *_sound_Skid, *_sound_Squish, *_sound_Thwomp, *_sound_Vine;

	void LoadMapTemp();
	void LoadMap();
	void LoadSprite();
	void LoadAudio();
	//------------------------

	void GameMenu();
	void GamePlay();

	int _countI = 0;
};

#endif