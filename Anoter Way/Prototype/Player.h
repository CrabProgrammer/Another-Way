#pragma once
#include "Header.h"

using namespace sf;

class Player :public Person //��������� �� ������ Person
{
private:
	int currentLVL; // ������� �������
	string tmp; //������ ��� �������� �������
	vector<Equip>equipSets; //������ ����������
	vector<AttackLine>attackLines; //������ ����� ����
	AttackLine tmpLine; //��������� �����
	Clock clock; //����� ��� �������� �����
	float attackSpeedTime; //����� �� �����
	int currentSetID; //���� ������� ����������
	bool shoot; //��������
	int dx, dy; //��������
	bool collision; //���� �� ������������

public:
	Player(std::string name, float X, float Y) : Person(name, X, Y){} //������ �����������
	void init(vector<Object>&levObj, float X, float Y); //������������� ���������
	string getCurrentEquipName() //�������� ������� ��� ����������
	{
		return equipSets[currentSetID].getName();
	}
	void hpRegen() //����������� �������� 
	{
		setHP(getHP()+0.15f);
	}
	void setPosition(int x, int y) { setX(x); setY(y); } //���������� ����������
	void control(float time, RenderWindow &window, vector<Enemy>&enemyVect); //����������
	string checkCollisionWithMap(vector<NPC>&npc, vector<Sign>&sign, vector<Enemy>&enemy); //����������� � ��������� �����
	void checkCollisionWithMap(float Dx, float Dy, float time, vector<Enemy>&enemyVect);//����������� � ������������� ��������� �����
	void update(float time, sf::RenderWindow &window, vector<Enemy>&enemyVect); //���������� ������
	vector<Equip> getEquipSets() //���������
	{
		return equipSets;
	}
	void addEquipSet(Equip tmp)
	{
		equipSets.push_back(tmp);
	}
	Equip getCurrentEquip()
	{
		return getEquip();
	}
	void setEquip(int id)
	{
		setNewEquip(equipSets[id]);
		initDrawingCharacterStyle();
		currentSetID = id;
	}
	vector<RectangleShape> getLines()
	{
		vector<RectangleShape>tmpL;
		for (int i = 0; i < attackLines.size(); i++)
			tmpL.push_back(attackLines[i].getLine());
		return tmpL;
	}
	int getCurrentSetID()	{		return currentSetID;	}	

	Vector2f getPosition()  {		return Vector2f(getX(), getY()); }
	void setObj(vector<Object>&vectObj) {		obj = vectObj; 	}
	void setLVL(int lvl)	{		currentLVL = lvl;	}
};
