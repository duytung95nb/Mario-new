#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#include <d3dx9.h>

#include "game.h"
#include "sprite.h"
#include "BaseObject.h"
#include "Collision.h"

class CMarioSample: public CGame
{
public: 
	CMarioSample(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~CMarioSample();

	LPD3DXSPRITE _SpriteHandler;
	CSprite * _sprites[20];
	Collision* _col;


	int mario_x;			// position of kitty
	int mario_y;		

	float mario_vx;			// velocity of kitty
	float mario_vy;		

	float mario_vx_last;	// last vx of mario before stop ( to determine the direction of mario )

	DWORD last_time;		// this is to control the animate rate of kitty

	//LPDIRECT3DSURFACE9 Background;

	CSprite * mario_right;
	CSprite * mario_left;	

	CSprite * ground_middle;		
	CSprite * brick;
	CSprite * mountain;
	BaseObject* sample;
	BaseObject* sample2;
	BaseObject* box;

protected:
	LPDIRECT3DSURFACE9 _Background;

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	virtual void OnKeyDown(int KeyCode);

	void LoadMap();
	void CollisionHanding();
	void RenderBackground(int view_port_x, int view_port_y);
};
#endif