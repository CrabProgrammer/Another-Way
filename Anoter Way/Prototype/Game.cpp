#include"Header.h"
void Game::setPlayerCoordinateForView(float x, float y) //установка границ для камеры
{
	float tempX = x; float tempY = y;
	if (x < view.getSize().x / 2) tempX = view.getSize().x / 2;
	if (x >16 * 50 - view.getSize().x / 2) tempX = 16 * 50 - view.getSize().x / 2;
	if (y < view.getSize().y / 2) tempY = view.getSize().y / 2;
	if (y >16 * 50 - view.getSize().y / 2) tempY = 16 * 50 - view.getSize().y / 2;
	view.setCenter(tempX, tempY);
}
Game::Game()
{
	RenderWindow window(VideoMode(800, 600), "Another Way", Style::Close);//создаём окно
	view.reset(FloatRect(0, 0, 800, 600)); //размеры камеры
	view.zoom(0.3f); //приближаем камеру
	
	gameState = GameState::MainMenu; //начальное игровое состояние

	Player player("Player", 0, 0); //создание игрока
	createArmorSet(armorSet); //создание всех экипировок

	initNewGame = false; //новая игра не инициализирована

	music.openFromFile("resources/Overworld.ogg"); //загрузка музыки
	music.setLoop(true); //зацикливание 
	music.stop(); //остановка

	setDefaultWindowSettings(window); //устанавливаем стандартные настройки окна
	GUI gui(window); //создаём графический интерфейс пользователя
	menu.init(window);//инициализируем окна
	settings.init(window);
	credits.init(window);
	help.init(window);
	death.init(window);
	end.init(window);

	timeSinceLastUpdate = Time::Zero; //обнуляем время с последнего обновления
	while (window.isOpen()) //пока окно открыто
	{
		Event event; //событие
		while (window.pollEvent(event)) //пока окно принимает события
		{
			if (event.type == sf::Event::Closed) //если событие закрытия окна
				window.close();// закрыть окно
		}
		switch (gameState) //переключение игровых состояний
		{
		case GameState::MainMenu: 
			cursor.setScale(1, 1); //масштабируем курсор
			window.setView(window.getDefaultView());  //устанавливаем стандартную камеру
			menu.draw(window, cursor, gameState); //рисуем меню
			if (music.getStatus() == SoundSource::Status::Playing) //если музыка играет
				music.stop(); //останавливаем
			break;
		case GameState::Settings: //отображение окна настроек
			settings.draw(window, cursor, gameState, gui, menu, help, credits, death, end, music);
			break;
		case GameState::Help: //отображние окна помощи
			help.draw(window, cursor, gameState);
			break;
		case GameState::Credits: //отображение окна "о разработчике"
			credits.draw(window, cursor, gameState);
			break;
		case GameState::Death: //отображение окна смерти
			window.setView(window.getDefaultView());
			cursor.setScale(1, 1);
			death.draw(window, cursor, gameState);
			break;
		case GameState::End: //отображение окна конца игры
			window.setView(window.getDefaultView());
			cursor.setScale(1, 1);
			end.draw(window, cursor, gameState);
			break;
		case GameState::NewGame: //инициализация новой игры, если таковая требуетмя
			if (initNewGame == false)
			{
				level.LoadFromFile("resources/Maps/Level1.xml");//загрузили в него карту, внутри класса с помощью методов он ее обработает.
				create_LVL1();
				player.init(level.GetAllObjects(), level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
				initNewGame = true;
			}
			gameState = GameState::Game;
			break;
		case GameState::Game:// игра
			if (music.getStatus() == SoundSource::Status::Stopped)
			{
				music.play(); //запуск музыки
				clock.restart(); //перезапуск часов
				cursor.setScale(0.3f, 0.3f); //масштабируем курсор
			}
			window.clear(Color::Black); //очищаем экран

			if (player.getHP() < 100) //если здоровье меньше 100
				player.hpRegen(); //регенерация
			if (player.getHP() <= 0) //если здоровье меньше либо равно 0
			{
				initNewGame = false; //сбро инициализации
				gameState = GameState::Death; //экран поражения
				continue;
			}

			timeSinceLastUpdate += clock.restart(); //время с последнего обновления
			if (timeSinceLastUpdate > timePerFrame) //если время на кадр пройдено
			{
				window.setView(view); //устанавливаем камеру

				timeSinceLastUpdate -= timePerFrame; //отнимаем время на кадр
				player.update(speed, window, vectEnemy); //обновляем данные персонажа
				lines.clear(); //очищаем вектор линий
				for (int i = 0; i < vectEnemy.size(); i++) //перебираем врагов
				{
					enemyDmg = 0; 
					vectEnemy[i].update(player.getRect(), speed, enemyDmg);
					if (enemyDmg > player.getProtection() / 10)
						player.takeDamage(enemyDmg); //наносится урон если пробивает защиту
					tmpLines = vectEnemy[i].getLines(); //добавление линий к общему вектору
					lines.reserve(lines.size() + tmpLines.size());
					lines.insert(lines.end(), tmpLines.begin(), tmpLines.end());
				}
			}
			level.Draw(window, player, vectEnemy); //отрисовка карты вместе с персонажем и врагами
			setPlayerCoordinateForView(player.getX() + 8, player.getY() + 8); //границы камеры

			worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //координаты курсора на карте уровня
			cursor.setPosition(worldPos);

			for (int i = 0; i < vectNPC.size(); i++) //отрисовка всех NPC
				vectNPC[i].drawSprites(window);
			tmpLines = player.getLines(); 
			lines.reserve(lines.size() + tmpLines.size());
			lines.insert(lines.end(), tmpLines.begin(), tmpLines.end());
			for (int i = 0; i < lines.size(); i++)
				window.draw(lines[i]); //отрисовка всех линий

			collisionEvent = player.checkCollisionWithMap(vectNPC, vectSign, vectEnemy); //проверка событий столкновений с объектом
			checkEvent(collisionEvent,window,player,gui); //обработчик событий
			
			gui.drawGUI(window, player, gameState); //отрисовка графического интерфейса
			window.draw(cursor); //отрисовка курсора
			window.display(); //отображение содержимого окна
			break;
		}
	}
}

void Game::setDefaultWindowSettings(sf::RenderWindow &window) //стандартные настройки окна
{
	font.loadFromFile("font.otf"); //загрузка шрифта

	window.setMouseCursorVisible(false); //видимость курсора
	window.setVerticalSyncEnabled(true); //включение вертикальной синхронизации
	textureCursor.loadFromFile("resources/img/cursor.png"); //загрузка курсора
	cursor.setTexture(textureCursor);
	cursor.setScale(0.3f, 0.3f);//масштабирование спрайта курсора

	Image icon;
	icon.loadFromFile("resources/img/Icon.png"); 
	window.setIcon(16, 16, icon.getPixelsPtr()); //устанавливаем иконку окна
}

void Game::createArmorSet(vector<Equip>&armorSet) //создание(загрузка) всех экипировок
{
	Equip tmp;
	tmp.SetEquipFromFile("resources/Characters/Weapon.xml", "Weapon");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Ranger.xml", "Ranger");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Bandit.xml", "Bandit");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Blacksmith.xml", "Blacksmith");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Magus.xml", "Magus");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Thief.xml", "Thief");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Miner.xml", "Miner");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Jester.xml", "Jester");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Dfguard.xml", "Dfguard");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Dguard.xml", "Dguard");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Priest.xml", "Priest");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Kguard.xml", "Kguard");
	armorSet.push_back(tmp);
	tmp.SetEquipFromFile("resources/Characters/Cguard.xml","Cguard");
	armorSet.push_back(tmp);

}

void Game::giveItem(Player &player,string armorset) //выдача экипировки
{
	bool give = true; 
	int setID;
	for (int i = 0; i < armorSet.size(); i++) //перебираем все экипировки
	{
		if (armorSet[i].getName() == armorset)
		{
			setID = i;
			for (int j = 0; j < player.getEquipSets().size(); j++)//перебираем экипировки персонажа
			{
				if (player.getEquipSets()[j].getID() == armorSet[i].getID()) //если такая экипировка уже найдена
				{
					give = false; //не добавлять
					break;
				}
			}
			break;
		}
	}
	if (give == true) //если такой экипировки не было, добавить экипировку
		player.addEquipSet(armorSet[setID]);
}