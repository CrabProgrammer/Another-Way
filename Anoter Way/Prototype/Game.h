#pragma once
#include"Header.h"
class Game
{
private:
	Sprite cursor; //спрайт курсора
	Level level; //текущий уровень
	vector<NPC> vectNPC; //векторы обхъектов карты
	vector<Enemy> vectEnemy;
	vector<Sign> vectSign;
	Texture textureCursor; //текстура курсора
	vector<Equip> armorSet;// все экипировки доступные в игре
	Vector2i pixelPos; //координаты для преобразования координат мыши 
	Vector2f worldPos;
	Clock clock; //часы
	Time timeSinceLastUpdate; //время с прошлого обновления
	const Time timePerFrame = seconds(1.f / 55.f); //время на кадр

	const float speed= 27.f; //скорость движения
	MainMenu menu;//объекты игровых состояний
	Settings settings;
	Help help;
	Credits credits;
	Death death;
	End end;
	Music music; //музыка
	int enemyDmg; //вражеский урон
	vector<RectangleShape> lines, tmpLines;//вектора прямоугольников
	View view;//камера
	bool initNewGame; //инициализация новой игры
	string collisionEvent; //события
	int gameState; //игровое состояние
public:
	Game(); //конструктор
	void setPlayerCoordinateForView(float x, float y); //границы координат камеры
	void setDefaultWindowSettings(sf::RenderWindow &window); //установка стандартных параметров окна
	//загрука объектов уровней
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

	void createArmorSet(vector<Equip>&armorSet); // загрузка всех экипировок
	void giveItem(Player &player, string armorset); //выдать персонажу экипировку
	void checkEvent(string collisionEvent, RenderWindow &window, Player &player, GUI &gui); //проверка событий
};