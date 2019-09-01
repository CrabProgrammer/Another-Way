#pragma once
#include"Header.h"
class AttackLine //����� ����� �����
{
private:
	float x, y, speed, range,rotation; //����������, ����,�������� � ����������
	int damage; //����
	int addRange; //����������
	Vector2f direction; //�����������
	RectangleShape line; //�������������
public:
	AttackLine() //�������������
	{
		damage = 10;
		speed = 0.1f;
		line.setSize(sf::Vector2f(4, 1));
	}
	void update(float time) //���������� ���������
	{
		int a=x, b=y;
		
		x += (cos(rotation / 180 * 3.14159265)*speed)*time;
		y += (sin(rotation / 180 * 3.14159265)*speed)*time;
		range -= sqrt((x - a)*(x - a) + (y - b)*(y - b)); //����������
		line.setPosition(x, y);
	}
	void create(float X, float Y,int dmg ,float range,Vector2f &mousePos) //�������� ����� �����
	{
		x = X+8;
		y = Y+8;
		addRange = 15 * range;
		addRange /= range;
		damage = dmg;
		this->range = range + addRange;
		rotation = (atan2f(mousePos.y - y, mousePos.x - x) * 180 / 3.14159265); //���� �����
		line.setRotation(rotation);
		line.setPosition(x, y);
	}	
	float getRange() //���������
	{
		return range;
	}
	RectangleShape getLine()
	{
		return line;
	}
};