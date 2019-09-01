#pragma once
#include"Header.h"
class Equip
{
private:
	string name;// имя экипировки
	int ArmorSetID; //ID экипировки
	int protection; //защита
	int dmg; //урон
	float attackSpeed; //скорость атаки
	float attackRange; //дальность атаки
	int shieldID; //идентификаторы экипировки
	int weaponID;
	int helmetID;
	int armorID;
	int legsID;
	int shoesID;

public:
	void init() //инициализация значения в зависимости от их идентификатора
	{
		dmg = 0; //изначальные характеристики = 0
		attackRange = 0;
		attackSpeed = 0;
		protection = 0;
		ArmorSetID = armorID - 5 - 57 * (armorID / 57) + 12 * (armorID / 57);
		int tmp,protID=0;
		if (ArmorSetID > 60)
			tmp = ArmorSetID - 60;
		else
			tmp = ArmorSetID;
		protID = (tmp - 12 * int(tmp / 13)) % 4;
		if (protID % 4 == 0)
			protID = 4;
		protID = protID + 4 * int(tmp / 13);
		if (protID == 1)
			protection = 5;
		else if (protID == 2)
			protection = 8;
		else if (protID == 3)
			protection = 6;
		else if (protID == 4)
			protection = 15;
		else if (protID == 5)
			protection = 4;
		else if (protID == 6)
			protection = 14;
		else if (protID == 7)
			protection = 13;
		else if (protID == 8)
			protection = 12;
		else if (protID == 9)
			protection = 1;
		else if (protID == 10)
			protection = 16;
		else if (protID == 11)
			protection = 7;
		else if (protID == 12)
			protection = 7;
		else if (protID == 13)
			protection = 10;
		else if (protID == 14)
			protection = 6;
		else if (protID == 15)
			protection = 4;
		else if (protID == 16)
			protection = 16;
		else if (protID == 17)
			protection = 20;
		else if (protID == 18)
			protection = 19;
		else if (protID == 19)
			protection = 17;
		else if (protID == 20)
			protection = 18;
		protection *= 2;
		for (int i = 0; i < 5; i++)
		{
			if (dmg == 0)
			{
				
				if (weaponID == 42 + i || weaponID == 99 + i || weaponID == 156 + i || weaponID == 213 + i)
				{
					dmg = 15 + 3 * i;
					attackSpeed = 15;
					attackRange = 45;
				}
				if (weaponID == 47 + i || weaponID == 104 + i)
				{
					dmg = 15 + 5 * i;
					attackSpeed = 20 - 2 * i;
					attackRange = 5+i;
				}
				if (weaponID == 161 + i || weaponID == 218 + i)
				{
					dmg = 22 + 5 * i;
					attackSpeed = 22 - 2 * i;
					attackRange = 5 + i;
				}
				if (weaponID == 275 + i || weaponID == 332 + i)
				{
					dmg = 23 + 6 * i;
					attackSpeed = 18 - 2 * i;
					attackRange = 5 + i;
				}
				if (weaponID == 270 + i || weaponID == 327 + i)
				{
					dmg = 23 + 5 * i;
					attackSpeed = 22 - 2 * i;
					attackRange = 5 + i;
				}
				if (weaponID == 389 + i || weaponID == 446 + i)
				{
					dmg = 23 + 6 * i;
					attackSpeed = 22 - 2 * i;
					attackRange = 5 + i;
				}
				if (weaponID == 503 + i || weaponID == 560 + i)
				{
					dmg = 30 + 8 * i;
					attackSpeed = 22 - 2 * i;
					attackRange = 5 + i;
				}
				if (weaponID == 384 + i)
				{
					dmg = 11 + 12 * i;
					attackSpeed = 25 - 1 * i;
					attackRange = 6;
				}
				if (weaponID == 441 + i)
				{
					dmg = 11 + 8 * i;
					attackSpeed = 50;
					attackRange = 4;
				}
				if (weaponID == 498 + i)
				{
					dmg = 15 + 11 * i;
					attackSpeed = 25;
					attackRange = 6;
				}
				if (weaponID == 555 + i)
				{
					dmg = 18 + 12 * i;
					attackSpeed = 30;
					attackRange = 7;
				}
				if (weaponID == 52 + 57*i)
				{
					dmg = 13 + 7 * i;
					attackSpeed = 35;
					attackRange = 50;
				}
				if (weaponID == 53 + 57*i)
				{
					dmg = 18 + 7 * i;
					attackSpeed = 30;
					attackRange = 75;
				}
			}
			else
				break;
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (shieldID == 33 + j + i * 57 * 3 || shieldID == 37 + j + i * 57 * 3)
					protection += 5 + j * 5 + i * 5;
				if (shieldID == 90 + j + i * 57 * 3 || shieldID == 94 + j + i * 57 * 3)
					protection += 147 + i * 10;
				if (shieldID == 147 + j + i * 57 * 3 || shieldID == 151 + j + i * 57 * 3)
					protection += 15 + i * 15;
			}
		}
	}
	void SetEquipFromFile(string filename,string name) //парсинг xml документа
	{
		this->name = name;
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
		while (layerElement) //аналогично другим методам парсинга вытаскиваем все GID
		{
			Layer layer;
			tinyxml2::XMLElement *layerDataElement;
			layerDataElement = layerElement->FirstChildElement("data");
			tinyxml2::XMLElement *tileElement;
			tileElement = layerDataElement->FirstChildElement("tile");

			while (tileElement)
			{
				int tileGID = atoi(tileElement->Attribute("gid"));

				if (tileGID == 0) tileGID = 601;
				style[i] = tileGID - 1;

				tileElement = layerDataElement->NextSiblingElement("tile");
			}
			i++;
			layerElement = layerElement->NextSiblingElement("layer");
		}
		legsID=style[1]; //устанавливаем лишь экипировку
		shoesID=style[2];
		armorID=style[3];
		helmetID=style[6];
		shieldID=style[7];
		weaponID=style[8];
		init();
	}
	string getName() //аксессоры
	{
		return name;
	}	
	int getID()
	{
		return ArmorSetID;
	}
	int getDMG()
	{
		return dmg;
	}
	int getAttackSpeed()
	{
		return attackSpeed;
	}
	int getAttackRange()
	{
		return attackRange;
	}
	int getProtection()
	{
		return protection;
	}
	int getWeaponID()
	{
		return weaponID;
	}
	int getShieldID()
	{
		return shieldID;
	}
	int getHelmetID()
	{
		return helmetID;
	}
	int getArmorID()
	{
		return armorID;
	}
	int getlegsID()
	{
		return legsID;
	}
	int getShoesID()
	{
		return shoesID;
	}
	void setWeaponID(int id)
	{
		weaponID = id;
	}
	void setShieldID(int id)
	{
		shieldID = id;
	}
	void setHelmetID(int id)
	{
		helmetID = id;
	}
	void setArmorID(int id)
	{
		armorID = id;
	}
	void setLegsID(int id)
	{
		legsID = id;
	}
	void setShoesID(int id)
	{
		shoesID = id;
	}
	void setDMG(int damage)
	{
		dmg = damage;
	}
	void setProtection(int prot)
	{
		protection=prot;
	}
};

