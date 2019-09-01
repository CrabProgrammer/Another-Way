#include"Header.h"
class Enemy :public Person //������������ ������ �� ������ Person
{
private:
	float stayX, stayY; //����������� ����������
	vector<AttackLine>attackLines;
	AttackLine tmpLine;
	Clock clock; //�����
	bool shoot;
	float attackSpeedTime; //����� �� �����
	int range; //���������� �� ���������
	int dx, dy;

public:
	Enemy(String filename, vector<Object>&levObj, float X, float Y) :Person(filename, X, Y) //�������� ���������� � ����������� ������������� �����
	{
		shoot=false;
		clock.restart();
		obj = levObj;//��������������.�������� ������ ������� ��� �������������� ����� � ������
		clock.restart();
		stayX = X;
		stayY = Y;
		SetStyleFromFile(filename); //�������� ����� �� �����
		initDrawingCharacterStyle(); //������������� ����������
	}

	void checkCollisionWithMap(float Dx, float Dy, FloatRect player,int &dmg)
	{
		for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		{
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					if (Dy > 0) { addToY(-Dy); } //������������
					if (Dy < 0) { addToY(Dy*(-1)); }
					if (Dx > 0) { addToX(-Dx); }
					if (Dx < 0) { addToX(Dx*(-1)); }
				}
			}
			for (int j = 0; j < attackLines.size(); j++)
			{
				if (attackLines[j].getLine().getGlobalBounds().intersects(obj[i].rect))
				{
					if (obj[i].name == "solid")//���� ��������� �����������
						attackLines.erase(attackLines.begin() + j);//�������
				}
				else if (attackLines[j].getLine().getGlobalBounds().intersects(player))
				{
					attackLines.erase(attackLines.begin() + j); //�������
					dmg = getDMG(); //������� ����
				}
			
			}
		}
	}

	void update(FloatRect player, float time,int &dmg) //���������� ������ 
	{
		range = sqrt((getX() - player.left)*(getX() - player.left) + (getY() - player.top)*(getY() - player.top)); //����������� ���������� �� ���������
		attackSpeedTime = clock.getElapsedTime().asMilliseconds();//��������� ������ �� �������
		dx = 0; dy = 0;

		if (getAttackRange()+15< range && range < 75) //���� �������� ������, ������ �� ����������
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
		else if (getAttackRange()+15 >= range) //���� ������� ���������� ��� �����
		{
			if (shoot == false) //����
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
		else //����� ������� �� ����������� ����������
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
		checkCollisionWithMap(dx, dy,player,dmg); //������������ � ��������� ����� � ������� 
		for (int i = 0; i < attackLines.size(); i++)
		{
			if (attackLines[i].getRange() <= 0)
				attackLines.erase(attackLines.begin() + i);
			else
				attackLines[i].update(time);
		}
		setSpritePos(); //����������� ��������� ��������
	}
	void init() //�������������
	{
		initDrawingCharacterStyle();
	}
	vector<RectangleShape> getLines()//��������� ���������������
	{
		vector<RectangleShape>tmpL;
		for (int i = 0; i < attackLines.size(); i++)
			tmpL.push_back(attackLines[i].getLine());
		return tmpL;
	}
};