#include "Brick.h"
#include "Global.h"


Brick::Brick() :BaseObject()
{
}
Brick::Brick(float _x, float _y, float _cameraX, float _cameraY, int ID, CSprite* sprite) : BaseObject(_x, _y, _cameraX, _cameraY)
{
	_sprite = sprite;
	_ID = ID;
	_vx = 5;
	_vy = 5;
	_width = _sprite->_Width;
	_height = _sprite->_Height;
}
void Brick::Update()
{
	_x += 10;
}
void Brick::Render()
{
	//_sprite->setIndex(3);
	_sprite->Render(_x, _y, Camera::_cameraX, Camera::_cameraY, BRICK_DEEP);
}
