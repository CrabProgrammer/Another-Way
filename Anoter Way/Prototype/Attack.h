#pragma once
#include"Header.h"
class AttackLine //класс линии атаки
{
private:
	float x, y, speed, range,rotation; //координаты, угол,скорость и расстояние
	int damage; //урон
	int addRange; //расстояние
	Vector2f direction; //направление
	RectangleShape line; //прямоугольник
public:
	AttackLine() //инициализация
	{
		damage = 10;
		speed = 0.1f;
		line.setSize(sf::Vector2f(4, 1));
	}
	void update(float time) //обновление координат
	{
		int a=x, b=y;
		
		x += (cos(rotation / 180 * 3.14159265)*speed)*time;
		y += (sin(rotation / 180 * 3.14159265)*speed)*time;
		range -= sqrt((x - a)*(x - a) + (y - b)*(y - b)); //расстояние
		line.setPosition(x, y);
	}
	void create(float X, float Y,int dmg ,float range,Vector2f &mousePos) //создание линии атаки
	{
		x = X+8;
		y = Y+8;
		addRange = 15 * range;
		addRange /= range;
		damage = dmg;
		this->range = range + addRange;
		rotation = (atan2f(mousePos.y - y, mousePos.x - x) * 180 / 3.14159265); //угол полёта
		line.setRotation(rotation);
		line.setPosition(x, y);
	}	
	float getRange() //аксессоры
	{
		return range;
	}
	RectangleShape getLine()
	{
		return line;
	}
};