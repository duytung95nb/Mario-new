 #include "BaseObject.h"




BaseObject::BaseObject()
{
	_sprite = NULL;
	_ani = NULL;
	ResetRect();
}

BaseObject::BaseObject(float xWorld, float yWorld, float width, float height, float vx, float vy)
{
	_x = xWorld;
	_y = yWorld;
	_width = width;
	_height = height;
	_vx = vx;
	_vy = vy;
	_sprite = NULL;
	_direction = 0; ///1 left to  ,2 right to
	_ani = NULL;
	ResetRect();
	b1.h = _height;
	b1.w = _width;
	b1.vx = _vx;
	b1.vy = _vy;
	b1.x = _x;
	b1.y = _y;
}

BaseObject::~BaseObject()
{
	if (_ani != NULL)
		delete _ani;
}
void BaseObject::ResetRect()
{
	_rect.left = _x;
	_rect.top = _y;
	_rect.right = _rect.left + _width;
	_rect.bottom = _rect.top + _height;
}