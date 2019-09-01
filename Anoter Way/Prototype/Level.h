#pragma once
#include "Header.h"

class Level
{
private:
	int width, height, tileWidth, tileHeight; //размеры карты и тайлов
	int firstTileID;//ID первого тайла
	Texture tilesetImage; //текстура
	vector<Object> objects; //вектор объектов карты
	vector<Layer> layers;//вектор слоёв
public:
	bool LoadFromFile(string filename); //парсинг карты уровня
	Object GetObject(string name); //возвращает объект с таким названием
	vector<Object> GetObjects(string name); //возвращает все объекты с таким названием
	vector<Object> GetAllObjects(); //возвращает все объекты
	void Draw(RenderWindow &window,Player &player,vector<Enemy>&enemy); //рисование карты , персонажа и врагов
};

