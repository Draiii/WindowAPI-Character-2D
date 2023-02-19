#pragma once
#include "image.h"

//백버퍼 이미지를 이미지매니져에 담아두기
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	
	//백버퍼 이미지 얻기
	image* getBackBuffer() { return _backBuffer; }

	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};

