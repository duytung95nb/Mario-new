#pragma once

#include "d3d9.h"
#include "d3dx9.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#include "Graphic.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>
using namespace std;

class Game
{
private:

	//Framework ----------------------
	Graphic		*g;
	float		TPF;					//Time per frame
	HWND		hWnd;
	HINSTANCE	hInstance;
	LPD3DXFONT	fontArial;
	void ProcessInput();
	void Update();
	void Render();
	//--------------------------------

	//Framework ----------------------
public:
	Game(HWND _hWnd, HINSTANCE _hInstance);
	~Game();
	void GameRun();





	IDirect3DSurface9* menu;	//Background state menu
	//IDirect3DSurface9* itemMenu;//Hiện phần new game, load game...
	IDirect3DSurface9* gameOver; //Background state gameOver
	IDirect3DSurface9* gameWin; //Background state gameWver
	IDirect3DSurface9* about;   //Background state about game
	IDirect3DSurface9* gameConfirm;//Background state game confirm: khi đang chơi mà player nhấn phím ESC thì sẽ hiện
	                               //ra thông báo để hỏi xem player có thực sự muốn thoát hay không?
	RECT menurect;//k
	int posymenu;//k
	int posymenuC;
	void Menu();//k
	void AboutGame();//k
	void GameConfirm();
	//-----------

	void ChangeState(char _state);
	void ChangeStage(char _stage);
	void ChangeSubStage(char _stage);
	void SetIsBright(char _stage);
	void AddScore(int _score,float _x,float _y);			
};
