//Framework ----------------------
#include "d3d9.h"
#include "d3dx9.h"
#include <tchar.h>
#include "time.h"
#include "Game.h"
#include "Graphic.h"
#include "Sprite.h"
#include "Animation.h"
#include "stdio.h"
//--------------------------------


#include <list>
using namespace std;
Game::Game(HWND _hWnd, HINSTANCE _hInstance)
{
	//Framework ----------------------
	hWnd=_hWnd;
	hInstance=_hInstance;
	g=new Graphic(hWnd);


	D3DXCreateFont(g->device,30,0,FW_BOLD,0,false,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,TEXT("Arial"),&fontArial);
	srand((unsigned)(time(NULL)));
}
void Game::GameRun()
{
	Update();
	Render();
}
void Game::ProcessInput()
{
}
void Game::Update()
{
	ProcessInput();
}
void Game::Render()
{
	//Framework ----------------------
	g->device->BeginScene();
	g->spriteDX->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	g->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); 
	//--------------------------------

	g->spriteDX->End();
	g->device->EndScene();
	g->device->Present(NULL,NULL,NULL,NULL);
	//--------------------------------
}

Game::~Game()
{
	delete g;
}
void Game::ChangeState(char _state)
{

	
}

void Game::ChangeStage(char _stage)
{
	
		
}
void Game::ChangeSubStage(char _stage)
{
	
}
void Game::SetIsBright(char _stage)
{
	
}
void Game::AddScore(int _score,float _x,float _y)
{

}

//-----K
void Game::Menu()
{	

}
void Game::AboutGame()
{

}
void Game::GameConfirm()
{
}
//------