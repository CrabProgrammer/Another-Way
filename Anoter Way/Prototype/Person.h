#pragma once
#include"Header.h"

struct Character //структура внешности персонажа
{
	int body;
	int beard;
	int hair;
};

class Person //родительский класс персонажей
{
private:
	int w, h;
	Equip equip; //текущая экипировка
	Texture texture;
	Character character; //внешность
	string name;
	float health;
	float x, y;
	vector<Sprite> sprites; //спрайты внешнего вида
public:
	vector<Object> obj;
	Person(std::string Name, float X, float Y) //инициализирующий конструктор
	{		
		x = X; y = Y;
		w = 16; h = 16;
		health = 100;
		texture.loadFromFile("resources/Characters/Characters.png"); //загрузка текстуры
		name = Name;
	}
	void drawSprites(RenderWindow &window) //отрисовка спрайтов
	{
		for (int i = 0; i<9; i++)
			window.draw(sprites[i]);
	}
	vector <Sprite> getSprite() { return sprites; } //аксесоры
	void setSpritePos()
	{
		for (int i = 0; i<sprites.size(); i++)
			sprites[i].setPosition(x, y);
	}
	Equip getEquip()
	{
		return equip;
	}
	void takeDamage(int damage)
	{
		health -= damage - getProtection() / 10;
	}
	void takeClearDamage(int damage)
	{
		health -= damage;
	}
	FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}
	int getDMG() { return equip.getDMG(); }
	int getAttackSpeed() { return equip.getAttackSpeed(); }
	int getAttackRange() { return equip.getAttackRange(); }
	int getProtection() { return equip.getProtection(); }
	void setHP(float hp) { health = hp; }
	float getHP() { return health; }
	float getX() { return x; }
	float getY() { return y; }
	void setX(float X) { x = X; }
	void setY(float Y) { y = Y; }
	void addToX(float X) { x += X; }
	void addToY(float Y) { y += Y; }
	void initDrawingCharacterStyle() //инициализация спрайтов в зависимости от ID
	{
		Sprite tmp;
		sprites.clear();
		tmp.setTexture(texture);
		tmp.setPosition(x, y);

		tmp.setTextureRect(IntRect(character.body * 16 - int(character.body / 57) * 16 * 57, int((character.body / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(equip.getlegsID() * 16 - int(equip.getlegsID() / 57) * 16 * 57, int((equip.getlegsID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(equip.getShoesID() * 16 - int(equip.getShoesID() / 57) * 16 * 57, int((equip.getShoesID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(equip.getArmorID() * 16 - int(equip.getArmorID() / 57) * 16 * 57, int((equip.getArmorID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(character.beard * 16 - int(character.beard / 57) * 16 * 57, int((character.beard / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(character.hair * 16 - int(character.hair / 57) * 16 * 57, int((character.hair / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(equip.getHelmetID() * 16 - int(equip.getHelmetID() / 57) * 16 * 57, int((equip.getHelmetID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(equip.getWeaponID() * 16 - int(equip.getWeaponID() / 57) * 16 * 57, int((equip.getWeaponID() / 57) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(equip.getShieldID() * 16 - int(equip.getShieldID() / 57) * 16 * 57, int((equip.getShieldID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
	}
	void SetStyleFromFile(string filename) // устанавливаем стиль из файла
	{
		sf::Texture tilesetImage;
		int style[9];
		tinyxml2::XMLDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument
														  // загружаем XML-карту
		levelFile.LoadFile(filename.c_str());
		tinyxml2::XMLElement *map;
		map = levelFile.FirstChildElement("map");
		tinyxml2::XMLElement *layerElement;
		layerElement = map->FirstChildElement("layer");
		int i = 0;
		while (layerElement)
		{
			Layer layer;
			//  контейнер <data> 
			tinyxml2::XMLElement *layerDataElement;
			layerDataElement = layerElement->FirstChildElement("data");
			//  контейнер <tile> - описание тайлов каждого слоя
			tinyxml2::XMLElement *tileElement;
			tileElement = layerDataElement->FirstChildElement("tile");

			while (tileElement)
			{
				int tileGID = atoi(tileElement->Attribute("gid"));

				if (tileGID == 0) tileGID = 601;
				style[i] = tileGID - 1; //устанавливаем айди

				tileElement = layerDataElement->NextSiblingElement("tile");
			}

			i++;

			layerElement = layerElement->NextSiblingElement("layer");
		}
		//присваиваем ID
		character.body = style[0];
		equip.setLegsID(style[1]);
		equip.setShoesID(style[2]);
		equip.setArmorID(style[3]);
		character.beard = style[4];
		character.hair = style[5];
		equip.setHelmetID(style[6]);
		equip.setShieldID(style[7]);
		equip.setWeaponID(style[8]);
		equip.init();

	}
	string getName() //аксессоры
	{
		return name;
	}
	void setNewEquip(Equip &NewEquip)
	{
		equip = NewEquip;
	}
	void setDMG(int damage)
	{
		equip.setDMG(damage);
	}
	void setProtection(int prot)
	{
		equip.setProtection(prot);
	}
};
