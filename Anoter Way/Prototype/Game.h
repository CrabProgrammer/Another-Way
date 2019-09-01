#pragma once
#include"Header.h"
class Game
{
private:
	Sprite cursor; //������ �������
	Level level; //������� �������
	vector<NPC> vectNPC; //������� ��������� �����
	vector<Enemy> vectEnemy;
	vector<Sign> vectSign;
	Texture textureCursor; //�������� �������
	vector<Equip> armorSet;// ��� ���������� ��������� � ����
	Vector2i pixelPos; //���������� ��� �������������� ��������� ���� 
	Vector2f worldPos;
	Clock clock; //����
	Time timeSinceLastUpdate; //����� � �������� ����������
	const Time timePerFrame = seconds(1.f / 55.f); //����� �� ����

	const float speed= 27.f; //�������� ��������
	MainMenu menu;//������� ������� ���������
	Settings settings;
	Help help;
	Credits credits;
	Death death;
	End end;
	Music music; //������
	int enemyDmg; //��������� ����
	vector<RectangleShape> lines, tmpLines;//������� ���������������
	View view;//������
	bool initNewGame; //������������� ����� ����
	string collisionEvent; //�������
	int gameState; //������� ���������
public:
	Game(); //�����������
	void setPlayerCoordinateForView(float x, float y); //������� ��������� ������
	void setDefaultWindowSettings(sf::RenderWindow &window); //��������� ����������� ���������� ����
	//������� �������� �������
	void create_LVL1(); 
	void create_LVL2();
	void create_LVL3();
	void create_LVL4();
	void create_LVL5();

	void create_Castle1();
	void create_Castle2();
	void create_Prison();

	void create_Desert1();
	void create_Desert2();

	void create_Cave();
	void create_Church();
	void create_House1();
	void create_House2();
	void create_House3();
	void create_House4();

	void createArmorSet(vector<Equip>&armorSet); // �������� ���� ����������
	void giveItem(Player &player, string armorset); //������ ��������� ����������
	void checkEvent(string collisionEvent, RenderWindow &window, Player &player, GUI &gui); //�������� �������
};