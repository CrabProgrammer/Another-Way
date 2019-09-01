#include "Header.h"
void Player::init(vector<Object>&levObj, float X, float Y)	//�����������
{
	setX(X); setY(Y); //��������� ����������
	setHP(100); //�������� � ������ ����
	attackLines.clear(); //������� ��������
	equipSets.clear();
	clock.restart(); //���������� �������
	shoot = false; //������� �� ���������
	obj = levObj;//��������������.�������� ��� ������� ��� �������������� ��������� � ������
	SetStyleFromFile("resources/Characters/PlayerStart.xml"); //�������� ������ ����������
	initDrawingCharacterStyle();// ����������� �������������
	currentLVL = 1; //������� ������� - 1
	equipSets.push_back(getEquip()); //���������� ���������� � ������
	currentSetID = 0;//������� ������������� ����������
}
void Player::control(float time, RenderWindow &window, vector<Enemy>&enemyVect)
{
	dx = 0; dy = 0;//��������
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))//�������� ������� ������
		dx = -(0.1f)*time;
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		dx = (0.1f)*time;
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		dy = -(0.1f)*time;
	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		dy = (0.1f)*time;
	if (dy != 0 && dx != 0) //���� �� ��������� - �������� �����������
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
	addToY(dy); //��������� ����������
	addToX(dx);
	checkCollisionWithMap(dx, dy, time, enemyVect);//�������� ������������ � ������
	attackSpeedTime = clock.getElapsedTime().asMilliseconds(); //���������� ������� ����������� � ���������� �����

	if (Mouse::isButtonPressed(Mouse::Left) && shoot == false) //���� ������ ������ ����� � �� �������
	{
		clock.restart();//���������� �������
		shoot = true; //�������
		
		attackLines.push_back(tmpLine); //���������� ����� �����
		attackLines[attackLines.size() - 1].create(getX(), getY(),getAttackSpeed(), getAttackRange(), Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))));// �������� ��������� ���������� �����
		attackSpeedTime /= 6; 
	}
	else if(Mouse::isButtonPressed(Mouse::Left)==false && shoot == true && attackSpeedTime >=450-getAttackSpeed()*3) //���������������� ������ ���������� �� �������� �����
	{
		clock.restart();
		shoot = false;
	}
}

void Player::checkCollisionWithMap(float Dx, float Dy, float time,vector<Enemy>&enemyVect)
{
	for (int i = 0; i < obj.size(); i++)//���������� �� ��������
	{
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			collision = false;
			if (obj[i].name == "solid")//���� ��������� �����������
				collision = true;
			else if (obj[i].name == "fguard") //�������� �� ������������ � �����������
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
			if(collision ==true) //������������ �� ���������� ����������
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
			if (obj[i].name == "fire") //���� ������ ����� - �������� �������� ������ ����
			{
				takeClearDamage(2);
			}	
		}
		for (int j = 0; j < attackLines.size(); j++) //���������� ����� �����
		{
			if (attackLines[j].getLine().getGlobalBounds().intersects(obj[i].rect))
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					attackLines.erase(attackLines.begin() + j); //�������
					continue;
				}
			for (int q = 0; q < enemyVect.size(); q++) 
				if (attackLines[j].getLine().getGlobalBounds().intersects(enemyVect[q].getRect())) //���� ������ �� �����
				{
					attackLines.erase(attackLines.begin() + j); //�������
					if(getDMG()>enemyVect[q].getProtection()/10) //�������� ����
						enemyVect[q].takeDamage(getDMG());
					if (enemyVect[q].getHP() < 0)//���� �������� ����� ������ 0
						enemyVect.erase(enemyVect.begin() + q); //������� �����
					break;
				}
		}
	}
}
string Player::checkCollisionWithMap(vector<NPC>&npc,vector<Sign>&sign, vector<Enemy>&enemy) //����������� � ��������� �����
{
	tmp = "";
	for (int i = 0; i<obj.size(); i++)// ���������� �� ��������
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � �������� � ���� ����, ���������� �������� � ����������� �� ��� ����
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
											// �������� �� �������
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


void Player::update(float time,RenderWindow &window, vector<Enemy>&enemyVect) //���������� ������ ���������
{
	setSpritePos(); //��������� ��������� ���������
	if(window.hasFocus()) //���� � ������
		control(time,window, enemyVect); //����������
	for (int i = 0; i < attackLines.size(); i++) 
	{
		if (attackLines[i].getRange() <= 0) //���� ��������� ������������ ����������
			attackLines.erase(attackLines.begin() + i);
		else
			attackLines[i].update(time);//���������� �����
	}
}
