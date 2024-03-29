#include "Castle.h"
#include "BaseObject.h"
#include "GLobal.h"
#include "Animation.h"
#include "Sprite.h"

Castle::Castle() :BaseObject(){}
Castle::Castle(float _x, float _y, float width, float height,float vx, float vy, int ID, Sprite* sprite) : BaseObject(_x, _y, width, height, vx, vy)
{
	_sprite = sprite;
	_ID = ID;
	_ani = new Animation(1, 1, 0, _sprite);
	ResetRect();
}
void Castle::Render()
{
	if (_ID == 23)
		_sprite->Draw(_x, _y, 0, 600, ZOOM, ZOOM, _ani->GetRect(0), 1);	//Cửa sổ
}
void Castle::ResetRect()
{

}