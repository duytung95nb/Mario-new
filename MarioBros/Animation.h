#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"

class Sprite;
class Animation
{
private:
	float	waitNextImage;				//Chờ chuyển hình
	int		numImageInRow;				//Số hình trên một hàng
	int		numImageInColumn;			//Số hình trên một cột

public:
	int		widthOfFrame;				//Chiều rộng
	int		heightOfFrame;				//Chiều cao

	int		index;						//Chỉ số hình
	float	timePerImage;				//Thời gian chuyển hình
	RECT	rect;						//Hình chữ nhật trong hình

	Animation();
	Animation(int _numImageInRow, int _numImageInColumn, float _timePerImage, Sprite* sprite);
	Animation(int _numImageInRow, int _numImageInColumn, float _timePerImage, int iWidth, int iHeight);
	~Animation();
	void Update(int indexFirstImage, int indexLastImage, float TPF);
	void SetIndex(int _index);
	RECT GetRect(int imageIndex);
};

#endif