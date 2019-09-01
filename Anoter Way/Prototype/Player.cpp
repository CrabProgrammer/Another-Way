#include "Header.h"
void Player::init(vector<Object>&levObj, float X, float Y)	//инициалиция
{
	setX(X); setY(Y); //стартовые координаты
	setHP(100); //здоровье в начале игры
	attackLines.clear(); //очистка векторов
	equipSets.clear();
	clock.restart(); //перезапуск времени
	shoot = false; //выстрел не произошел
	obj = levObj;//инициализируем.получаем все объекты для взаимодействия персонажа с картой
	SetStyleFromFile("resources/Characters/PlayerStart.xml"); //загрузка первой экипировки
	initDrawingCharacterStyle();// выставление характеристик
	currentLVL = 1; //текущий уровень - 1
	equipSets.push_back(getEquip()); //добавление экипировки в вектор
	currentSetID = 0;//текущий идентификатор экипировки
}
void Player::control(float time, RenderWindow &window, vector<Enemy>&enemyVect)
{
	dx = 0; dy = 0;//движение
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))//проверка нажатий кнопок
		dx = -(0.1f)*time;
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		dx = (0.1f)*time;
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		dy = -(0.1f)*time;
	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		dy = (0.1f)*time;
	if (dy != 0 && dx != 0) //если по диагонали - скорость уменьшается
	{
		if (dx > 0)
			dx = (0.093f)*time;
		else
			dx = -(0.093f)*time;
		if (dy > 0)
			dy = (0.093f)*time;
		else
			dy = -(0.093f)*time;
	}
	addToY(dy); //обновляем координаты
	addToX(dx);
	checkCollisionWithMap(dx, dy, time, enemyVect);//проверка столкновений с картой
	attackSpeedTime = clock.getElapsedTime().asMilliseconds(); //обновление времени пройденного с предидущей атаки

	if (Mouse::isButtonPressed(Mouse::Left) && shoot == false) //если нажата кнопка атаки и не атакует
	{
		clock.restart();//перезапуск таймера
		shoot = true; //атакует
		
		attackLines.push_back(tmpLine); //добавление линии атаки
		attackLines[attackLines.size() - 1].create(getX(), getY(),getAttackSpeed(), getAttackRange(), Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))));// создание последней добавленой линии
		attackSpeedTime /= 6; 
	}
	else if(Mouse::isButtonPressed(Mouse::Left)==false && shoot == true && attackSpeedTime >=450-getAttackSpeed()*3) //сбалансированный таймер основанный на скорости атаки
	{
		clock.restart();
		shoot = false;
	}
}

void Player::checkCollisionWithMap(float Dx, float Dy, float time,vector<Enemy>&enemyVect)
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
	{
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			collision = false;
			if (obj[i].name == "solid")//если встретили препятствие
				collision = true;
			else if (obj[i].name == "fguard") //проверка на столкновение с персонажами
			{
				if (equipSets[currentSetID].getName() != "Ranger")
					collision = true;
				else 
					collision = false;
			}
			else if (obj[i].name == "bandit")
			{
				if (equipSets[currentSetID].getName() != "Bandit")
					collision = true;
				else
					collision = false;
			}
			else if (obj[i].name == "eguard")
			{
				if (equipSets[currentSetID].getName() != "Magus")
					collision = true;
				else
					collision = false;
			}
			else if (obj[i].name == "dfguard")
			{
				if (equipSets[currentSetID].getName() != "Dfguard")
					collision = true;
				else
					collision = false;
			}
			else if (obj[i].name == "dguard")
			{
				if (equipSets[currentSetID].getName() != "Dguard")
					collision = true;
				else
					collision = false;
			}
			else if (obj[i].name == "cguard1"|| obj[i].name == "cguard2")
			{
				if (equipSets[currentSetID].getName() != "Cguard")
					collision = true;
				else
					collision = false;
			}
			else if (obj[i].name == "pguard1"|| obj[i].name == "pguard2")
			{
				if (equipSets[currentSetID].getName() != "Jester")
					collision = true;
				else
					collision = false;
			}
			else if (obj[i].name == "kguard")
			{
				if (equipSets[currentSetID].getName() != "Kguard")
					collision = true;
				else
					collision = false;
			}
			if(collision ==true) //возвращаемся на предидущие координаты
			{
				if ((obj[i].rect.left<getRect().left + getRect().width || obj[i].rect.left + obj[i].rect.width>getRect().left) && getRect().intersects(obj[i].rect))
				{
					addToX(-Dx);
				}
				if ((obj[i].rect.top<getRect().top + getRect().height || obj[i].rect.top + obj[i].rect.height>getRect().top) && getRect().intersects(obj[i].rect))
				{
					addToY(-Dy);
				}
			}
			if (obj[i].name == "fire") //если объект огонь - персонаж получает чистый урон
			{
				takeClearDamage(2);
			}	
		}
		for (int j = 0; j < attackLines.size(); j++) //перебираем линии атаки
		{
			if (attackLines[j].getLine().getGlobalBounds().intersects(obj[i].rect))
				if (obj[i].name == "solid")//если встретили препятствие
				{
					attackLines.erase(attackLines.begin() + j); //удаляем
					continue;
				}
			for (int q = 0; q < enemyVect.size(); q++) 
				if (attackLines[j].getLine().getGlobalBounds().intersects(enemyVect[q].getRect())) //если попала во врага
				{
					attackLines.erase(attackLines.begin() + j); //удаляем
					if(getDMG()>enemyVect[q].getProtection()/10) //наносить урон
						enemyVect[q].takeDamage(getDMG());
					if (enemyVect[q].getHP() < 0)//если здоровье врага меньше 0
						enemyVect.erase(enemyVect.begin() + q); //удаляем врага
					break;
				}
		}
	}
}
string Player::checkCollisionWithMap(vector<NPC>&npc,vector<Sign>&sign, vector<Enemy>&enemy) //пересечение с объектами карты
{
	tmp = "";
	for (int i = 0; i<obj.size(); i++)// проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом и если было, возвращаем значение в зависимости от его типа
		{
			for (int j = 0; j < npc.size(); j++)
			{
				if (obj[i].name == npc[j].getName())
					tmp = "NPC"+npc[j].getName();
			}
			for (int j = 0; j < sign.size(); j++)
			{
				if (obj[i].name == sign[j].getName())
					tmp = "Sign" + sign[j].getName();
			}
											// ПЕРЕХОДЫ ПО УРОВНЯМ
			if (currentLVL == 1 && obj[i].name == "lvl2") 
			{
				currentLVL = 2;
				tmp = "lvl2-1";
				break;
			}
			else if (currentLVL == 2 )
			{
				if (obj[i].name == "lvl1")
				{
					currentLVL = 1;
					tmp = "lvl1";
					break;
				}
				else if (obj[i].name == "cave1")
				{
					currentLVL = 3;
					tmp = "cave1";
					break;
				}
				else if (obj[i].name == "house1")
				{
					currentLVL = 4;
					tmp = "house1";
					break;
				}
				else if (obj[i].name == "lvl3")
				{
					currentLVL = 5;
					tmp = "lvl3-1";
					break;
				}
			}
			else if (currentLVL == 3) //cave
			{
				if (obj[i].name == "lvl2")
				{
					currentLVL = 2;
					tmp = "lvl2-2";
					break;
				}
			}
			else if (currentLVL == 4) //house1
			{
				if (obj[i].name == "lvl2")
				{
					currentLVL = 2;
					tmp = "lvl2-3";
					break;
				}
			}
			else if (currentLVL == 5) //lvl 3
			{
				if (obj[i].name == "lvl2")
				{
					currentLVL = 2;
					tmp = "lvl2-4";
					break;
				}
				if (obj[i].name == "lvl4")
				{
					currentLVL = 7;
					tmp = "lvl4-1";
					break;
				}
				else if (obj[i].name == "house2")
				{
					currentLVL = 6;
					tmp = "house2";
					break;
				}
			}
			else if (currentLVL == 6) //house2
			{
				if (obj[i].name == "lvl3")
				{
					currentLVL = 5;
					tmp = "lvl3-3";
					break;
				}
			}
			else if (currentLVL == 7) //lvl 4
			{
				if (obj[i].name == "lvl3")
				{
					currentLVL = 5;
					tmp = "lvl3-2";
					break;
				}
				if (obj[i].name == "church")
				{
					currentLVL = 8;
					tmp = "church";
					break;
				}
				if (obj[i].name == "desert1")
				{
					currentLVL = 9;//desert1
					tmp = "desert1-1";
					break;
				}
				if (obj[i].name == "lvl5")
				{
					currentLVL = 13; //lvl5
					tmp = "lvl5-1";
					break;
				}
			}
			else if (currentLVL == 8) //church
			{
				if (obj[i].name == "lvl4")
				{
					currentLVL = 7;
					tmp = "lvl4-2";
					break;
				}
			}
			else if (currentLVL == 9) //desert1
			{	
				if (obj[i].name == "lvl4")
				{
					currentLVL = 7;
					tmp = "lvl4-3";
					break;
				}
				if (obj[i].name == "house3")
				{
					currentLVL = 10;
					tmp = "house3";
					break;
				}
				if (obj[i].name == "desert2")
				{
					currentLVL = 11;
					tmp = "desert2-1";
					break;
				}
								
			}
			else if (currentLVL == 10) //house3
			{
				if (obj[i].name == "desert1")
				{
					currentLVL = 9;
					tmp = "desert1-2";
					break;
				}
			}
			else if (currentLVL == 11) //desert2
			{
				if (obj[i].name == "desert1")
				{
					currentLVL = 9;
					tmp = "desert1-3";
					break;
				}
				if (obj[i].name == "house4")
				{
					currentLVL = 12;
					tmp = "house4";
					break;
				}
			}
			else if (currentLVL == 12) //house4
			{
				if (obj[i].name == "desert2")
				{
					currentLVL = 11;
					tmp = "desert2-2";
					break;
				}
			}
			else if (currentLVL == 13) //lvl5
			{
				if (obj[i].name == "lvl4")
				{
					currentLVL = 7; //lvl4
					tmp = "lvl4-4";
					break;
				}
				if (obj[i].name == "castle1")
				{
					currentLVL = 14; 
					tmp = "castle1-1";
					break;
				}
			}
			else if (currentLVL == 14) //castle1
			{
				if (obj[i].name == "lvl5")
				{
					currentLVL = 13; //lvl5
					tmp = "lvl5-2";
					break;
				}
				if (obj[i].name == "castle2")
				{
					currentLVL = 15;
					tmp = "castle2";
					break;
				}
			}
			else if (currentLVL == 15) //castle2
			{
				if (obj[i].name == "prison"||(obj[i].name == "king"&&enemy.size()==0))
				{
					currentLVL = 16; 
					tmp = "prison";
					break;
				}
				if (obj[i].name == "castle1")
				{
					currentLVL = 14;
					tmp = "castle1-2";
					break;
				}
			}
			else if (currentLVL == 16) //prison
			{
				if (obj[i].name == "end")
				{
					tmp = "end";
					break;
				}
			}
		}
	return tmp;
}


void Player::update(float time,RenderWindow &window, vector<Enemy>&enemyVect) //обновление данных персонажа
{
	setSpritePos(); //установка координат персонажа
	if(window.hasFocus()) //если в фокусе
		control(time,window, enemyVect); //управление
	for (int i = 0; i < attackLines.size(); i++) 
	{
		if (attackLines[i].getRange() <= 0) //если пролетело максимальное расстояние
			attackLines.erase(attackLines.begin() + i);
		else
			attackLines[i].update(time);//обновление линий
	}
}
