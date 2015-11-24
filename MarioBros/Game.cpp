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
#include "Map.h"

//--------------------------------


#include <list>
using namespace std;
Game::Game(HWND _hWnd, HINSTANCE _hInstance)
{
	//Framework ----------------------
	hWnd=_hWnd;
	hInstance=_hInstance;
	_input = new Input(hWnd, hInstance, SCREEN_WIDTH, SCREEN_HEIGHT);
	g=new Graphic(hWnd);
	_timeManager = new TimeManager();
	
	
	D3DXCreateFont(g->device,30,0,FW_BOLD,0,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,TEXT("Arial"),&fontArial);
	srand((unsigned)(time(NULL)));

	for (int i = 0; i < 5; i++) _sprites[i] = NULL;
	_sprites[S_SMARIO] = new Sprite(g, "Image\\SmallMario.png");
	_sprites[S_BMARIO] = new Sprite(g, "Image\\BigMario.png");
	_sprites[S_PIPE] = new Sprite(g, "Image\\Pipe.bmp");
	_sprites[S_BACKGROUND] = new Sprite(g,"Image\\imgWorld111.png");
	_camera = new Camera(0, 0, 800, 600);
	Map::Map("map1.txt", true, this);
	a = new Pipe(100, 100, 1000, 1000, 1010, _sprites[S_PIPE]);
	b = new BackGround(0, 0, 0, 0,2000, _sprites[S_BACKGROUND]);
}
void Game::GameRun()
{
	_timeManager->LimitFPS(60);
	TPF = _timeManager->TPF;
	_input->GetMouse();
	_input->GetKey();
	Update();
	Render();
}
void Game::ProcessInput()
{
}
void Game::Update()
{
	BaseObject* _obj;
	list<BaseObject>::iterator i;
	ProcessInput();


	// cleart object old
	_staticObjs.clear();
	_dynamicObjs.clear();
	
	//staticList->insert(staticList->end(), staticObj.begin(), staticObj.end());
	//dynamicList->insert(dynamicList->end(), dynamicObj.begin(), dynamicObj.end());
}
void Game::Render()
{
	//Framework ----------------------
	g->device->BeginScene();
	g->spriteDX->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	g->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); 
	//--------------------------
	a->Render();
	b->Render();
	g->spriteDX->End();
	g->device->EndScene();
	g->device->Present(NULL,NULL,NULL,NULL);
	//--------------------------------
}

Game::~Game()
{
	delete g;
	delete _input;
	delete _timeManager;
}


