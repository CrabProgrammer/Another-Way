#pragma once
#include "Header.h"

class NPC :public Person
{
private:
	string name; //���
	string text; //�����
public:
	NPC(std::string filename, string name, float X, float Y ) : Person(name, X, Y)
	{
		this->name = name;
		SetStyleFromFile(filename);// ������� XML 
		initDrawingCharacterStyle(); //������������� �������� �� ID
	}
	void setText(string txt) { text=txt; } //���������
	string getText() { return text; }
	string getName() { return name; }
	void init()//����������������� ��������
	{
		initDrawingCharacterStyle();
	}
};
