#include"Header.h"
class Enemy :public Person //наследование поленй от класса Person
{
private:
	float stayX, stayY; //изначальные координаты
	vector<AttackLine>attackLines;
	AttackLine tmpLine;
	Clock clock; //время
	bool shoot;
	float attackSpeedTime; //время на атаку
	int range; //расстояние до персонажа
	int dx, dy;

public:
	Enemy(String filename, vector<Object>&levObj, float X, float Y) :Person(filename, X, Y) //передача параметров в конструктор родительского класа
	{
		shoot=false;
		clock.restart();
		obj = levObj;//инициализируем.получаем нужные объекты для взаимодействия врага с картой
		clock.restart();
		stayX = X;
		stayY = Y;
		SetStyleFromFile(filename); //загрузка стиля из файла
		initDrawingCharacterStyle(); //инициализация экипировки
	}

	void checkCollisionWithMap(float Dx, float Dy, FloatRect player,int &dmg)
	{
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
		{
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0) { addToY(-Dy); } //возвращаемся
					if (Dy < 0) { addToY(Dy*(-1)); }
					if (Dx > 0) { addToX(-Dx); }
					if (Dx < 0) { addToX(Dx*(-1)); }
				}
			}
			for (int j = 0; j < attackLines.size(); j++)
			{
				if (attackLines[j].getLine().getGlobalBounds().intersects(obj[i].rect))
				{
					if (obj[i].name == "solid")//если встретили препятствие
						attackLines.erase(attackLines.begin() + j);//удаляем
				}
				else if (attackLines[j].getLine().getGlobalBounds().intersects(player))
				{
					attackLines.erase(attackLines.begin() + j); //удаляем
					dmg = getDMG(); //наносим урон
				}
			
			}
		}
	}

	void update(FloatRect player, float time,int &dmg) //обновление данных 
	{
		range = sqrt((getX() - player.left)*(getX() - player.left) + (getY() - player.top)*(getY() - player.top)); //расчитываем расстояние до персонажа
		attackSpeedTime = clock.getElapsedTime().asMilliseconds();//обновляем данные по времени
		dx = 0; dy = 0;

		if (getAttackRange()+15< range && range < 75) //если персонаж близко, бежать за персонажем
		{
				if (getX() - player.left > 1)
					dx = -(0.095)*time;
				if (getX() - player.left < -1)
					dx = (0.095)*time;
				if (getY() - player.top > 1)
					dy = -(0.095)*time;
				if (getY() - player.top < -1)
					dy = (0.095)*time;
		}
		else if (getAttackRange()+15 >= range) //если хватает расстояния для удара
		{
			if (shoot == false) //удар
			{
				clock.restart();
				shoot = true;

				attackLines.push_back(tmpLine);
				attackLines[attackLines.size() - 1].create(getX(), getY(), getDMG(), getAttackRange(), Vector2f(player.left + 8, player.top + 8));
				attackSpeedTime /= 6;
			}
			else if (shoot == true && attackSpeedTime >= 450 - getAttackSpeed() * 3)
			{
				clock.restart();

				shoot = false;

			}
		}
		else //бежим обратно на изначальные координаты
		{
			dx = 0; dy = 0;

			if (getX() - stayX < 0)
				dx = (0.095)*time;
			if (getX() - stayX > 0)
				dx = -(0.095)*time;
			if (getY() - stayY < 0)
				dy = (0.095)*time;
			if (getY() - stayY > 0)
				dy = -(0.095)*time;

		}
		if (dy != 0 && dx != 0)
		{
			if (dx > 0)
				dx = (0.09)*time;
			else
				dx = -(0.09)*time;

			if (dy > 0)
				dy = (0.09)*time;
			else
				dy = -(0.09)*time;

		}
		addToY(dy);
		addToX(dx);
		checkCollisionWithMap(dx, dy,player,dmg); //столкновение с объектами карты и игроком 
		for (int i = 0; i < attackLines.size(); i++)
		{
			if (attackLines[i].getRange() <= 0)
				attackLines.erase(attackLines.begin() + i);
			else
				attackLines[i].update(time);
		}
		setSpritePos(); //обновленние координат спрайтов
	}
	void init() //инициализация
	{
		initDrawingCharacterStyle();
	}
	vector<RectangleShape> getLines()//получение прямоугольников
	{
		vector<RectangleShape>tmpL;
		for (int i = 0; i < attackLines.size(); i++)
			tmpL.push_back(attackLines[i].getLine());
		return tmpL;
	}
};