#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "BaseObject.h"
#include <list>
using namespace std;

class Brick :public BaseObject
{
public:

	Brick();
	Brick(float _x, float _y, float width, float height,int vxObj, int vyObj,float vx, float vy, bool _isBright, int _ID, Sprite* _sprite);
	~Brick();
	void Render();
};