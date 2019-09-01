#pragma once
#include "Header.h"

class Level
{
private:
	int width, height, tileWidth, tileHeight; //������� ����� � ������
	int firstTileID;//ID ������� �����
	Texture tilesetImage; //��������
	vector<Object> objects; //������ �������� �����
	vector<Layer> layers;//������ ����
public:
	bool LoadFromFile(string filename); //������� ����� ������
	Object GetObject(string name); //���������� ������ � ����� ���������
	vector<Object> GetObjects(string name); //���������� ��� ������� � ����� ���������
	vector<Object> GetAllObjects(); //���������� ��� �������
	void Draw(RenderWindow &window,Player &player,vector<Enemy>&enemy); //��������� ����� , ��������� � ������
};

