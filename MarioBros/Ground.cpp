#include "Ground.h"
#include "BaseObject.h"
#include "Global.h"
#include "Animation.h"
#include "Sprite.h"

Ground::Ground() :BaseObject(){}
Ground::Ground(float _x, float _y, float width, float height, int ID, Sprite* sprite) : BaseObject(_x, _y, width, height)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(4, 4, 0.5, _sprite);
}

void Ground::Render()
{
		_sprite->Draw(_x, _y, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
		_sprite->Draw(_x, _y + 40, ZOOM, ZOOM, _ani->GetRect(1), 0.5);
}