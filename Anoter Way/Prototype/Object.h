#pragma once
#include"Header.h"
struct Object
{
	string name;//�������� ���������� name ���� string
	Rect<float> rect;//��� Rect � �������� ����������
};
struct Layer//����
{
	vector<Sprite> tiles;//���������� � ������ �����
};
