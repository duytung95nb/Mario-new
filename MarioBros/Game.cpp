//Framework ----------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h>
#include "Game.h"
#include "Graphic.h"
#include "Sprite.h"
#include "Animation.h"
#include <stdio.h>
#include "Global.h"
#include <conio.h>
#include <stdio.h>
#include "Castle.h"
#include "Mountain.h"
#include "Cloud.h"
#include "Grass.h"
#include "Ground.h"

//--------------------------------


#include <list>
using namespace std;
Game::Game(HWND hWnd, HINSTANCE hInstance)
{
	//Framework ----------------------
	_hWnd=hWnd;
	_hInstance=hInstance;
	_input = new Input(_hWnd, _hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);
	_g=new Graphic(_hWnd);
	_timeManager = new TimeManager();
	_audio = new Audio(_hWnd);
	_col = new Collision();
	//-----------------------------------

	//GAME STATE ---------------------
	_state = MS_MENU;
	_xMenu = 200;
	_yMenu = YMENU_MIN;
	//--------------------------------
	
	D3DXCreateFont(_g->device,30,0,FW_BOLD,0,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,TEXT("Arial"),&_fontArial);
	srand((unsigned)(time(NULL)));
	_bgMenu = _g->CreateSurface("Image\\imgbgMenu.png");
	for (int i = 0; i < 5; i++) _sprites[i] = NULL;
	LoadSprite();
	LoadAudio();
	mario_vx = 0;
	mario_vy = 0;
	//_camera = new Camera(0, 0, 800, 600);
	vx = 0;
	vy = 0;
	LoadMap();
	_mario = new Mario(0, 0, 136, 64, 0, 0, vx, vy, _sprites[S_BMARIO]);
	//LoadMapTemp();
	

}
void Game::LoadSprite()
{
	_sprites[S_SMARIO] = new Sprite(_g, "Image\\SmallMario.png");
	_sprites[S_BMARIO] = new Sprite(_g, "Image\\BigMario.png");
	_sprites[S_BASIC] = new Sprite(_g, "Image\\Basic.png");
	_sprites[S_MOUNTAIN] = new Sprite(_g,"Image\\imgMountain.png");
	_sprites[S_CLOUD] = new Sprite(_g, "Image\\imgCloud.bmp");
	_sprites[S_GRASS] = new Sprite(_g, "Image\\imgGrass.png");
	_marioMenu = new Sprite(_g, "Image\\imgSmallMario.png");
	
}
void Game::LoadAudio()
{
	_sound_1up = _audio->LoadSound("Sounds\\1up.wav");
	_sound_Beep = _audio->LoadSound("Sounds\\Beep.wav");
	_sound_BigJump = _audio->LoadSound("Sounds\\BigJump.wav");
	_sound_BowserDie = _audio->LoadSound("Sounds\\Bowser.wav");
	_sound_Break = _audio->LoadSound("Sounds\\Break.wav");
	_sound_Bump = _audio->LoadSound("Sounds\\Bump.wav");
	_sound_Coin = _audio->LoadSound("Sounds\\Coin.wav");
	_sound_Die = _audio->LoadSound("Sounds\\Die.wav");
	_sound_EnemyFire = _audio->LoadSound("Sounds\\EnemyFire.wav");
	_sound_FireBall = _audio->LoadSound("Sounds\\FireBall.wav");
	_sound_Flagpole = _audio->LoadSound("Sounds\\Flagpole.wav");
	_sound_GameOver = _audio->LoadSound("Sounds\\GameOver.wav");
	_sound_Item = _audio->LoadSound("Sounds\\Item.wav");
	_sound_Jump = _audio->LoadSound("Sounds\\Jump.wav");
	_sound_Kick = _audio->LoadSound("Sounds\\Kick.wav");
	_sound_Pause = _audio->LoadSound("Sounds\\Pause.wav");
	_sound_Powerup = _audio->LoadSound("Sounds\\Powerup.wav");
	_sound_Skid = _audio->LoadSound("Sounds\\Skid.wav");
	_sound_Squish = _audio->LoadSound("Sounds\\Squish.wav");
	_sound_Thwomp = _audio->LoadSound("Sounds\\Thwomp.wav");
	_sound_Vine = _audio->LoadSound("Sounds\\Vine.wav");
	_sound_Warp = _audio->LoadSound("Sounds\\Warp.wav");
}

typedef struct SRC {
	int id;
	int srcX;
	int srcY;
};
list<SRC> getlistSRC(string filepath){
	list<SRC> list;
	FILE *f = fopen(filepath.c_str(), "rt");
	while (!feof(f)){
		SRC t;
		fscanf(f, "%d", &t.id);
		fscanf(f, "%d", &t.srcX);
		fscanf(f, "%d", &t.srcY);
		list.push_back(t);
	}
	fclose(f);

	return list;
}
void Game::LoadMap()
{
	int srcX;
	int srcY;
	list<SRC> l = getlistSRC("MAP1.txt");
	int i = 0;
	for each(const SRC &t in l){
		srcX = t.srcX;
		srcY = t.srcY;

		switch (t.id)
		{
			case 28: case 29:
				_staticObjs[i] = new Mountain(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0,vx,vy, t.id, _sprites[S_MOUNTAIN]);
				i++;
				break;
			case 25: case 26: case 27:
				_staticObjs[i] = new Cloud(PIXEL * (t.srcX), PIXEL * (t.srcY), 40, 40, vx, vy, t.id, _sprites[S_CLOUD]);
				i++;
			case 11: case 12: case 13:
				_staticObjs[i] = new Grass(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0, vx, vy, t.id, _sprites[S_GRASS]);
				i++;
				break;
			case 22:
				_staticObjs[i] = new Ground(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0, vx, vy, t.id, _sprites[S_BASIC]);
				i++;
				break;
			/*case 23:
				_staticObjs[i] = new Castle(PIXEL * (t.srcX), PIXEL * (t.srcY), 0, 0, vx, vy, t.id, _sprites[S_CLOUD]);
				i++;
				break;*/
			case 17: case 18: case 19:
				_staticObjs[i] = new Brick(PIXEL * (t.srcX), PIXEL * (t.srcY), 40, 40,0,0, vx, vy, true, t.id, _sprites[S_BASIC]);
				i++;
				break;
			default:
				_staticObjs[i] = new Brick(PIXEL * (t.srcX), PIXEL * (t.srcY), 40, 40,0,0, vx, vy, true, 0, _sprites[S_BASIC]);
				i++;
				break;
		}
	}
	_countI = i;

	getchar();
}
void Game::LoadMapTemp()
{
	for (int i = 0; i < 2; i++)
	_staticObjs[i] = new Brick(PIXEL * 10*10, PIXEL*100, 50, 50,0,0 ,vx, vy, true, 0, _sprites[S_BASIC]);
	_mario = new Mario(PIXEL * 15* 10, _staticObjs[0]->_y, 136, 64,0,0, vx, vy, _sprites[S_BMARIO]);
}
void Game::GameRun()
{
	_timeManager->LimitFPS(60);
	_TPF = _timeManager->TPF;
	_input->GetMouse();
	_input->GetKey();
	/*DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 100 / 60;
	DWORD now = GetTickCount();

	_DeltaTime = now - frame_start;
	if (_DeltaTime >= tick_per_frame)
	{
		frame_start = now;
		Update(_DeltaTime);
		Render();
	}*/
	
	Update();
	Render();
}
void Game::ProcessInput()
{
	switch (_state)
	{
	case MS_MENU:
		if (_input->KeyDown(DIK_Q))
			PostQuitMessage(0);
		else if (_input->KeyPress(DIK_DOWN))
		{
			_yMenu += YMENU;
			if (_yMenu > YMENU_MAX)
				_yMenu = YMENU_MIN;
		}
		else if (_input->KeyPress(DIK_UP))
		{
			_yMenu -= YMENU;
			if (_yMenu < YMENU_MIN)
				_yMenu = YMENU_MAX;
		}
		else if (_input->KeyPress(DIK_RETURN))
		{
			if (_yMenu = YMENU_MIN)
				_state = MS_PLAYING;
		}
		_audio->PlaySound(_sound_GameOver);
		break;
		
	case MS_PLAYING:
		if (_input->KeyDown(DIK_Q))
			PostQuitMessage(0);
		break;
	}
}
void Game::Update()
{
	float normalx;
	float normaly;
	BaseObject* _obj;
	list<BaseObject*>::iterator i;
	ProcessInput();
	_mario->Update(_staticObjs, _dynamicObjs, _input, _TPF);
	//float collisiontime = _col->SweptAABB(mario, _staticObjs[0],OUT normalx,OUT normaly);
	//_mario->_x += mario->_vxObj * collisiontime;
	//mario->_y += mario->_vyObj * collisiontime;
	/*mario->_x += mario_vx * collisiontime;
	mario->_y += mario_vy * collisiontime;
	if (collisiontime < 1.0f)
	{
		mario->_x = 100;
		MessageBox(_hWnd, "Da va cgamm,", "dfg", MB_OK);
	}*/
	//mario->_y += mario->_vy * collisiontime;
	/*float remainingtime = 1.0f - collisiontime;
	mario->_vx *= remainingtime;
	mario->_vx *= remainingtime;
	if (abs(normalx) > 0.0001f)
		mario->_vx = -mario->_vx;
	if (abs(normalx) > 0.0001f)
		mario->_vy = -mario->_vy;*/
	//mario = _col->GetSweptBroadphaseBox(_staticObjs[0]);
	/*if (_col->AABBCheck(mario, _staticObjs[0]))
	{
		float normalx, normaly;
		float collisiontime = _col->SweptAABB(mario, _staticObjs[0], OUT normalx, OUT normaly);
		mario->_x += mario_vx * collisiontime;
		mario->_y += mario_vy * collisiontime;

		if (collisiontime < 1.0f)
		{

		}
	}*/
}
void Game::Render()
{
	_g->device->BeginScene();
	_g->spriteDX->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	_g->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); 
	switch (_state)
	{
		case MS_MENU:
			_g->device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0, 0); 
			GameMenu();
			break;
		case MS_PLAYING:
			_g->device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(107, 140, 255), 1.0, 0);
			GamePlay();
			break;
	}
	_g->spriteDX->End();
	_g->device->EndScene();
	_g->device->Present(NULL,NULL,NULL,NULL);
}

//Choose menu
void Game::GameMenu()
{
	_g->device->StretchRect(_bgMenu, NULL, _g->backBuffer, NULL, D3DTEXF_NONE);
	_recMenu.top = 16;
	_recMenu.left = 102;
	_recMenu.right = 120;
	_recMenu.bottom = 32;
	_marioMenu->Draw(_xMenu, _yMenu,ZOOM,ZOOM, 2, 2, _recMenu, 1);
}
void Game::GamePlay()
{

	for (int i = 0; i < _countI; i++)
		_staticObjs[i]->Render();
	/*for (int i = 0; i < 2; i++)
		_staticObjs[i]->Render();*/
	_mario->Render();
}
Game::~Game()
{
	delete _g;
	delete _audio;
	delete _input;
	delete _timeManager;
}


