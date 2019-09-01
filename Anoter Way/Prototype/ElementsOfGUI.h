#pragma once
#include"Header.h"
class Button //����� ������
{
private:
	Texture buttonTexture, buttonPressedTexture; //�������� ���� ��������� ������
	Sprite buttonSprite, buttonPressedSprite;//������� ���� ��������� ������
	Text buttonText; //����� �� ������
	bool isPressed; //������ ��
	Vector2f pos; //���������� ������
	FloatRect rect; //���������� ������������� �������
public:
	void init(string Text, int x, int y,bool wide) //�������������
	{
		if (wide == false) //���� ������ �� �������
		{
			buttonTexture.loadFromFile("resources/img/buttonSquare_brown.png"); //��������� �����������
			buttonPressedTexture.loadFromFile("resources/img/buttonSquare_brown_pressed.png");
			rect.height = 45; //������ �� ������ � ������
			rect.width = 45;
		}
		else //� ��������� ������ ��������� ����������� ������� ������
		{
			buttonTexture.loadFromFile("resources/img/buttonLong_brown.png");
			buttonPressedTexture.loadFromFile("resources/img/buttonLong_brown_pressed.png");
			rect.height = 45;
			rect.width = 190;
		}
		rect.top = y; //������������� ����������
		rect.left = x;
		//������ �������� ��������, � �� ����������
		buttonSprite.setTexture(buttonTexture); 
		buttonPressedSprite.setTexture(buttonPressedTexture);
		buttonSprite.setPosition(x, y);
		buttonPressedSprite.setPosition(x, y+4);
		//������������� �����, �����, ������ ,���� � �������. ������������� ����������
		buttonText.setFont(font); 
		buttonText.setString(Text);
		buttonText.setCharacterSize(18);
		buttonText.setFillColor(Color::White);
		buttonText.setOutlineThickness(1);
		buttonText.setPosition(x + 7, y + buttonTexture.getSize().y/2 - buttonText.getCharacterSize() / 2);
		pos = buttonText.getPosition();

		isPressed = false;
	}
	void draw(RenderWindow &window) //����������� ������
	{
		if (isPressed == true) //���� ������
		{
			window.draw(buttonPressedSprite);
			buttonText.setPosition(pos.x, pos.y + 4);//����� ��������� ���� ������ � �������
		}
		else //���� ���, ������ ��������� ������
		{
			window.draw(buttonSprite);
			buttonText.setPosition(pos.x, pos.y);
		}
		window.draw(buttonText);	//������ �����
	}
	bool checkClick(RenderWindow &window) //�������� �� �������
	{

		if ((Mouse::getPosition(window).x > rect.left &&Mouse::getPosition(window).y > rect.top
			&& Mouse::getPosition(window).x < rect.left + rect.width
			&& Mouse::getPosition(window).y < rect.top + rect.height) && Mouse::isButtonPressed(Mouse::Left))
		{ //���� ���������� ���� �������� � ������������ ������ � ������ ����� ������ ����
			isPressed = true;//������ ������
		}
		else
		{
			if (isPressed == true) //���� ������ �� ������ ��������, ����������� ������
			{
				isPressed = false;
				return true; 
			}
		}
		return false; //���������� ����
	}
};
class Arrow //����� �������
{
private: 
	Texture arrowTexture;
	Sprite arrowSprite;
	bool isPressed;
	Vector2f pos;
	FloatRect rect;
public:
	Arrow() //����������� �������������� ������
	{
		arrowSprite.scale(2.f, 2.f);
	}
	void init(string filename, int x, int y) //�������������. �������� ����������� � ��������� ���������
	{
		arrowTexture.loadFromFile(filename);
		arrowSprite.setTexture(arrowTexture);
		arrowSprite.setPosition(x, y);
		rect.height = 45;
		rect.width = 45;
		rect.top = y;
		rect.left = x;
		isPressed = false;
	}
	void draw(RenderWindow &window)
	{
		window.draw(arrowSprite); //��������� �������
	}
	bool checkClick(RenderWindow &window) //�������� �� ������� ���������� ������� ������
	{
		if ((Mouse::getPosition(window).x > rect.left &&Mouse::getPosition(window).y > rect.top
			&& Mouse::getPosition(window).x < rect.left + rect.width
			&& Mouse::getPosition(window).y < rect.top + rect.height) && Mouse::isButtonPressed(Mouse::Left))
		{
			isPressed = true;
		}
		else
		{
			if (isPressed == true)
			{
				isPressed = false;
				return true;
			}
			else
				isPressed = false;
		}
		return false;
	}
};
class Label //����� �������
{
private:
	Text text; 
public:
	void init(string output, int size, int x, int y) //������������� ������
	{
		text.setString(output);
		text.setFont(font);
		text.setPosition(x, y);
		text.setCharacterSize(size);
		text.setOutlineThickness(1);
	}
	void draw(RenderWindow &window) 
	{
		window.draw(text); //��������� ������
	}
	void draw(RenderWindow &window,int stat) //��������� ������ � ����������� ������������� ����������
	{
		Text tmp(text);
		tmp.setString(to_string(stat));
		tmp.move(80, 0);
		window.draw(text);
		window.draw(tmp);
	}
};

class StatBar //����� ����� ��������������
{
private:
	RectangleShape rect;
	RectangleShape rectBack;
	Vector2f pos;
	Vector2f size;
	int maxW;
	int max, current;
public:
	void init( int X, int Y, int W, int H,Color c)
	{ 
		max = 100; //������������� ������������ � ������� ���������� ��������
		current = 100;
		pos.x= X; //������������� ���������� � �������
		pos.y = Y;
		maxW = W; //������������ ������
		size.y = H;
		size.x = W;
		rect.setPosition(X, Y);
		rect.setFillColor(c); //������������� ����
		rectBack.setPosition(X, Y);
		rectBack.setSize(size);
		rectBack.setOutlineThickness(2);
		rectBack.setOutlineColor(Color::Black);
	}
	void draw(int stat,RenderWindow &window)
	{
		current = stat;
		size.x = (current*maxW) / max; //����������� ������ ��������������
		rect.setSize(size);
		window.draw(rectBack);
		window.draw(rect);
	}
};
class Panel //������ ������������ �� ������
{
public:
	Texture texture;
	Sprite sprite;
	Text text;
	void init(RenderWindow &window) //�������������
	{
		text.setFont(font);// ������������� �����
		text.setCharacterSize(25);// ������ ������
		text.setOutlineThickness(1); //������ �������
		texture.loadFromFile("resources/img/panel.png"); //�������� �����������
		sprite.setTexture(texture); //��������
		sprite.setPosition(window.getSize().x/2-200, window.getSize().y/2 - 200);//�������� ������
		sprite.setScale(4.f, 4.f); //������������ � 4 ����
		text.setPosition(sprite.getPosition().x+150, sprite.getPosition().y + 30);//����� � �������� ����� ������
	}
	void draw(RenderWindow &window)
	{
		window.draw(sprite);
		window.draw(text);
	}
	Vector2f getPos()
	{
		return sprite.getPosition();
	}
};

class TextPanel //����� ��������� ������
{
private:
	Texture texture;
	Sprite sprite;
	Text text;
public:
	void init(RenderWindow &window)
	{
		text.setFont(font);
		text.setCharacterSize(24); //������������� ������ ������
		text.setOutlineThickness(1); //�������
		text.setPosition(60, window.getSize().y - 110); //���������� ������ � ������� ����� ���� ������
		texture.loadFromFile("resources/img/textPanel.png"); //��������� �����������
		sprite.setTexture(texture);
		sprite.setPosition(30, window.getSize().y-130);
		sprite.setScale((window.getSize().x-90.0f)/93.0f, 1.2f); //������������ �� ������ ������
	}
	void draw(RenderWindow &window,string txt )
	{
		text.setString(txt); //������������� �����
		window.draw(sprite);
		window.draw(text);
	}
};