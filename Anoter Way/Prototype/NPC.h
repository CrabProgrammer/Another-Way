#pragma once
#include "Header.h"

class NPC :public Person
{
private:
	string name; //имя
	string text; //текст
public:
	NPC(std::string filename, string name, float X, float Y ) : Person(name, X, Y)
	{
		this->name = name;
		SetStyleFromFile(filename);// парсинг XML 
		initDrawingCharacterStyle(); //инициализация спрайтов по ID
	}
	void setText(string txt) { text=txt; } //аксессоры
	string getText() { return text; }
	string getName() { return name; }
	void init()//переинициализация спрайтов
	{
		initDrawingCharacterStyle();
	}
};
