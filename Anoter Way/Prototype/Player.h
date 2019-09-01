#pragma once
#include "Header.h"

using namespace sf;

class Player :public Person //наследуем от класса Person
{
private:
	int currentLVL; // текущий уровень
	string tmp; //строка для возврата события
	vector<Equip>equipSets; //вектор экипировок
	vector<AttackLine>attackLines; //вектор линий атак
	AttackLine tmpLine; //временная линия
	Clock clock; //время для скорости атаки
	float attackSpeedTime; //время на атаку
	int currentSetID; //айди текущей экипировки
	bool shoot; //стрельба
	int dx, dy; //движение
	bool collision; //было ли столкновение

public:
	Player(std::string name, float X, float Y) : Person(name, X, Y){} //пустой конструктор
	void init(vector<Object>&levObj, float X, float Y); //инициализация персонажа
	string getCurrentEquipName() //получить текущее имя экипировки
	{
		return equipSets[currentSetID].getName();
	}
	void hpRegen() //регенерация здоровья 
	{
		setHP(getHP()+0.15f);
	}
	void setPosition(int x, int y) { setX(x); setY(y); } //установить координаты
	void control(float time, RenderWindow &window, vector<Enemy>&enemyVect); //управление
	string checkCollisionWithMap(vector<NPC>&npc, vector<Sign>&sign, vector<Enemy>&enemy); //пересечение с объектами карты
	void checkCollisionWithMap(float Dx, float Dy, float time, vector<Enemy>&enemyVect);//пересечение с непроходимыми объектами карты
	void update(float time, sf::RenderWindow &window, vector<Enemy>&enemyVect); //обновление данных
	vector<Equip> getEquipSets() //аксессоры
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
