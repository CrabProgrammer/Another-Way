#pragma once
//����������� ����������� ���������, ��������� SFML � tinyXML2
#include <string> 
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "tinyxml2.h"
//������������� ����������� ���
using namespace std;
using namespace sf;
static Font font;
//�������� ������������ ��� GameState � ������������ � ��
namespace GameState 
{
	static enum{ MainMenu,NewGame, Game,Help,Settings,Credits,Death,End, Exit };
}
//���������������� ����������� ������
#include "Object.h"
#include "Sign.h"
#include "Equip.h"
#include "Attack.h"
#include "Person.h"
#include "Enemy.h"
#include "NPC.h"
#include "Player.h"
#include "Level.h"
#include "ElementsOfGUI.h"
#include "Inventory.h"
#include "Menu.h"
#include "GUI.h"
#include "Settings.h"
#include "Game.h"
