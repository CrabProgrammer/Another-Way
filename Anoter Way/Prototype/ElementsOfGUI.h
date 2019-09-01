#pragma once
#include"Header.h"
class Button //класс кнопки
{
private:
	Texture buttonTexture, buttonPressedTexture; //текстуры двух состояний кнопок
	Sprite buttonSprite, buttonPressedSprite;//спрайты двух состояний кнопок
	Text buttonText; //текст на кнопке
	bool isPressed; //нажата ли
	Vector2f pos; //координаты кнопки
	FloatRect rect; //координаты прямоугольной области
public:
	void init(string Text, int x, int y,bool wide) //инициализация
	{
		if (wide == false) //если кнопка не широкая
		{
			buttonTexture.loadFromFile("resources/img/buttonSquare_brown.png"); //загружаем изображения
			buttonPressedTexture.loadFromFile("resources/img/buttonSquare_brown_pressed.png");
			rect.height = 45; //размер по ширине и высоте
			rect.width = 45;
		}
		else //в противном случае загружаем изображения широких кнопок
		{
			buttonTexture.loadFromFile("resources/img/buttonLong_brown.png");
			buttonPressedTexture.loadFromFile("resources/img/buttonLong_brown_pressed.png");
			rect.height = 45;
			rect.width = 190;
		}
		rect.top = y; //устанавливаем координаты
		rect.left = x;
		//задаем текстуры спрайтам, и их координаты
		buttonSprite.setTexture(buttonTexture); 
		buttonPressedSprite.setTexture(buttonPressedTexture);
		buttonSprite.setPosition(x, y);
		buttonPressedSprite.setPosition(x, y+4);
		//устанавливаем шрифт, текст, размер ,цвет и обводку. Устанавливаем координаты
		buttonText.setFont(font); 
		buttonText.setString(Text);
		buttonText.setCharacterSize(18);
		buttonText.setFillColor(Color::White);
		buttonText.setOutlineThickness(1);
		buttonText.setPosition(x + 7, y + buttonTexture.getSize().y/2 - buttonText.getCharacterSize() / 2);
		pos = buttonText.getPosition();

		isPressed = false;
	}
	void draw(RenderWindow &window) //отображение кнопки
	{
		if (isPressed == true) //если нажата
		{
			window.draw(buttonPressedSprite);
			buttonText.setPosition(pos.x, pos.y + 4);//текст смещается ниже вместе с кнопкой
		}
		else //если нет, рисуем ненажатую кнопку
		{
			window.draw(buttonSprite);
			buttonText.setPosition(pos.x, pos.y);
		}
		window.draw(buttonText);	//рисуем текст
	}
	bool checkClick(RenderWindow &window) //проверка на нажатие
	{

		if ((Mouse::getPosition(window).x > rect.left &&Mouse::getPosition(window).y > rect.top
			&& Mouse::getPosition(window).x < rect.left + rect.width
			&& Mouse::getPosition(window).y < rect.top + rect.height) && Mouse::isButtonPressed(Mouse::Left))
		{ //если координаты мыши совпадут с координатами кнопки и нажата левая кнопка мыши
			isPressed = true;//кнопка нажата
		}
		else
		{
			if (isPressed == true) //если нажата но кнопка отпущена, возваращаем правду
			{
				isPressed = false;
				return true; 
			}
		}
		return false; //возвращаем ложь
	}
};
class Arrow //класс стрелок
{
private: 
	Texture arrowTexture;
	Sprite arrowSprite;
	bool isPressed;
	Vector2f pos;
	FloatRect rect;
public:
	Arrow() //конструктор масштабирующий спрайт
	{
		arrowSprite.scale(2.f, 2.f);
	}
	void init(string filename, int x, int y) //инициализация. Загрузка изображения и установка координат
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
		window.draw(arrowSprite); //отрисовка стрелки
	}
	bool checkClick(RenderWindow &window) //проверка на нажатие идентичное нажатию кнопки
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
class Label //класс надпись
{
private:
	Text text; 
public:
	void init(string output, int size, int x, int y) //инициализация текста
	{
		text.setString(output);
		text.setFont(font);
		text.setPosition(x, y);
		text.setCharacterSize(size);
		text.setOutlineThickness(1);
	}
	void draw(RenderWindow &window) 
	{
		window.draw(text); //отрисовка текста
	}
	void draw(RenderWindow &window,int stat) //отрисовка текста с принимаемым целочисленным параметром
	{
		Text tmp(text);
		tmp.setString(to_string(stat));
		tmp.move(80, 0);
		window.draw(text);
		window.draw(tmp);
	}
};

class StatBar //класс шкалы характеристики
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
		max = 100; //устанавливаем максимальное и текущее процентные значения
		current = 100;
		pos.x= X; //устанавливаем координаты и размеры
		pos.y = Y;
		maxW = W; //максимальная ширина
		size.y = H;
		size.x = W;
		rect.setPosition(X, Y);
		rect.setFillColor(c); //устанавливаем цвет
		rectBack.setPosition(X, Y);
		rectBack.setSize(size);
		rectBack.setOutlineThickness(2);
		rectBack.setOutlineColor(Color::Black);
	}
	void draw(int stat,RenderWindow &window)
	{
		current = stat;
		size.x = (current*maxW) / max; //высчитываем размер прямоугольника
		rect.setSize(size);
		window.draw(rectBack);
		window.draw(rect);
	}
};
class Panel //панель отображаемая на экране
{
public:
	Texture texture;
	Sprite sprite;
	Text text;
	void init(RenderWindow &window) //инициализация
	{
		text.setFont(font);// устанавливаем шрифт
		text.setCharacterSize(25);// размер шрифта
		text.setOutlineThickness(1); //ширина обводки
		texture.loadFromFile("resources/img/panel.png"); //загрузка изображения
		sprite.setTexture(texture); //текстура
		sprite.setPosition(window.getSize().x/2-200, window.getSize().y/2 - 200);//середина экрана
		sprite.setScale(4.f, 4.f); //масштабируем в 4 раза
		text.setPosition(sprite.getPosition().x+150, sprite.getPosition().y + 30);//текст в середине верха панели
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

class TextPanel //класс текстовой панели
{
private:
	Texture texture;
	Sprite sprite;
	Text text;
public:
	void init(RenderWindow &window)
	{
		text.setFont(font);
		text.setCharacterSize(24); //устанавливаем размер шрифта
		text.setOutlineThickness(1); //обводку
		text.setPosition(60, window.getSize().y - 110); //координаты текста в верхнем левом углу панели
		texture.loadFromFile("resources/img/textPanel.png"); //загружаем изображение
		sprite.setTexture(texture);
		sprite.setPosition(30, window.getSize().y-130);
		sprite.setScale((window.getSize().x-90.0f)/93.0f, 1.2f); //масштабируем по ширине экрана
	}
	void draw(RenderWindow &window,string txt )
	{
		text.setString(txt); //устанавливаем текст
		window.draw(sprite);
		window.draw(text);
	}
};