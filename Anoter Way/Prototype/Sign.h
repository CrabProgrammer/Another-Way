#pragma once
#include"Header.h"
class Sign //класс надписи
{
private:
	string name; //название
	string text; //текст
public:
	Sign(string name, string text) //конструктор
	{
		this->name = name;
		this->text = text;
	}
	string getName()//аксессоры
	{
		return name;
	}
	string getText()
	{
		return text;
	}
};