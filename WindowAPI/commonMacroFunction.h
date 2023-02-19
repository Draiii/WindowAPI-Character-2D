#pragma once
//=============================================================
//	## commonMacroFunction ##
//=============================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT 중심좌표에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//Rectangle 함수 이용해서 사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//Ellipse 함수 이용해서 타원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//Ellipse 함수 이용해서 타원 그리기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//Rectangle 함수 오버로딩
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//Ellipse 함수 오버로딩
inline void Ellipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//inline int range(int fromNum, int toNum)
//{
//	return rand() % (toNum - fromNum + 1) + fromNum;
//}

//두점사이의 거리 구하는 함수
inline float getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	// 두점 사이의 거리 구하는 공식(피타고라스 정의)
	return sqrtf(x * x + y * y);
}


//두점 사이의 각도 구하는 함수
inline float getAngle(float startX, float startY, float endX, float endY)
{
#define PI 3.141592f
	float x = endX - startX;
	float y = endY - startY;

	//두점 사이의 거리 구하는 공식
	float distance = sqrtf(x * x + y * y);
	//두점사이의 각도 구하는 공식
	float angle = acosf(x / distance);
	//예외처리
	//윈도우 API acosf 는 0~180도 까지의 라디안값 (0.0f~ 3.14f)리턴시켜준다
	if (endY > startY)
	{
		angle = (PI * 2) - angle;
	}

	return angle;
}