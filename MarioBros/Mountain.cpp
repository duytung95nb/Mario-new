#include "Mountain.h"
#include "Global.h"


Mountain::Mountain() :BaseObject(){}

Mountain::Mountain(float _x, float _y, float width, float height, float vx, float vy, int ID, Sprite* sprite) : BaseObject(_x, _y, width, height,vx,vy)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(1, 2, 0.5, _sprite);
}

void Mountain::Render()
{
	switch (_ID)
	{
		case 28:
			_sprite->Draw(_x, _y,_vx,_vy, ZOOM, ZOOM, _ani->GetRect(0), 0.5);
			_sprite->Draw(_x, _y + TILE_SIZE + 2, _vx, _vy, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
			break;
		case(29) :
			_sprite->Draw(_x, _y, _vx, _vy, ZOOM, ZOOM, _ani->GetRect(0), 0.5);
		break;
	}
}

Mountain::~Mountain(){};