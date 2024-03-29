#include "sprite.h"
#include "trace.h"
#include "Global.h"
#include <d3dx9.h>

CSprite::CSprite(LPD3DXSPRITE SpriteHandler, char* FilePath, int Width, int Height, int Count, int SpritePerRow) 
{
	D3DXIMAGE_INFO info; 
	HRESULT result; 
	
	_Image = NULL;
	_SpriteHandler = SpriteHandler;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(FilePath,&info);
	if (result!=D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'",FilePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv; 
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		//D3DCOLOR_XRGB(0,63,63),
		D3DCOLOR_XRGB(255, 0, 255),
		&info,
		NULL,
		&_Image);

	if (result!=D3D_OK) 
	{
		trace(L"[ERROR] Failed to create texture from file '%s'",FilePath);
		return;
	}
}
void CSprite::Render(int X, int Y,int vpx,int vpy, int zoomX, int zoomY, RECT rSrc, float deep)
{
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = 1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, deep);
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, zoomX, zoomY, 1);
	_SpriteHandler->SetTransform(&mt1);

	_SpriteHandler->Draw(
		_Image,
		&rSrc,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}
void CSprite::Render(int X, int Y, int vpx, int vpy, float deep)
{
	RECT srect;
	srect.left = (_Index % _SpritePerRow)*(_Width)+1;
	srect.top = (_Index / _SpritePerRow)*(_Height)+1;
	srect.right = srect.left + _Width ;
	srect.bottom = srect.top + _Height +1;

	D3DXVECTOR3 position((float)X,(float)Y,0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = 1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos,&position,&mt);
	
	D3DXVECTOR3 p(vp_pos.x,vp_pos.y,deep);
	D3DXVECTOR3 center((float)_Width/2,(float)_Height/2,0);
	
	D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, ZOOM, ZOOM, 1);
	_SpriteHandler->SetTransform(&mt1);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		&center,
		&p, 
		D3DCOLOR_XRGB(255,255,255)
	);
}
void CSprite::setIndex(int index)
{
	_Index = index;
}

void CSprite::Next() 
{
	_Index = (_Index + _Count -1) % _Count;
}
void CSprite::Next(int _start, int _end)
{
	_Index++;
	if (_Index > _end)
		_Index = _start;
}
//void CSprite::A(int start, int end)
//{
//
//}
//void CSprite::Reset(int start)
//{
//	_Index = start;
//}

void CSprite::Reset()
{
	_Index = 0;
}

CSprite::~CSprite()
{
	_Image->Release();
}