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

//�� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT �߽���ǥ�� �����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//Rectangle �Լ� �̿��ؼ� �簢�� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//Ellipse �Լ� �̿��ؼ� Ÿ�� �׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//Ellipse �Լ� �̿��ؼ� Ÿ�� �׸���
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//Rectangle �Լ� �����ε�
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//Ellipse �Լ� �����ε�
inline void Ellipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//inline int range(int fromNum, int toNum)
//{
//	return rand() % (toNum - fromNum + 1) + fromNum;
//}

//���������� �Ÿ� ���ϴ� �Լ�
inline float getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	// ���� ������ �Ÿ� ���ϴ� ����(��Ÿ��� ����)
	return sqrtf(x * x + y * y);
}


//���� ������ ���� ���ϴ� �Լ�
inline float getAngle(float startX, float startY, float endX, float endY)
{
#define PI 3.141592f
	float x = endX - startX;
	float y = endY - startY;

	//���� ������ �Ÿ� ���ϴ� ����
	float distance = sqrtf(x * x + y * y);
	//���������� ���� ���ϴ� ����
	float angle = acosf(x / distance);
	//����ó��
	//������ API acosf �� 0~180�� ������ ���Ȱ� (0.0f~ 3.14f)���Ͻ����ش�
	if (endY > startY)
	{
		angle = (PI * 2) - angle;
	}

	return angle;
}