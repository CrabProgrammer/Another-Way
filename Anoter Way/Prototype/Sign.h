#pragma once
#include"Header.h"
class Sign //����� �������
{
private:
	string name; //��������
	string text; //�����
public:
	Sign(string name, string text) //�����������
	{
		this->name = name;
		this->text = text;
	}
	string getName()//���������
	{
		return name;
	}
	string getText()
	{
		return text;
	}
};