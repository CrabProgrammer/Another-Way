#pragma once
#include"Header.h"
struct Object
{
	string name;//объ€вили переменную name типа string
	Rect<float> rect;//тип Rect с нецелыми значени€ми
};
struct Layer//слои
{
	vector<Sprite> tiles;//закидываем в вектор тайлы
};
