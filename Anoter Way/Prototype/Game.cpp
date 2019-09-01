#include"Header.h"
void Game::setPlayerCoordinateForView(float x, float y) //��������� ������ ��� ������
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
	RenderWindow window(VideoMode(800, 600), "Another Way", Style::Close);//������ ����
	view.reset(FloatRect(0, 0, 800, 600)); //������� ������
	view.zoom(0.3f); //���������� ������
	
	gameState = GameState::MainMenu; //��������� ������� ���������

	Player player("Player", 0, 0); //�������� ������
	createArmorSet(armorSet); //�������� ���� ����������

	initNewGame = false; //����� ���� �� ����������������

	music.openFromFile("resources/Overworld.ogg"); //�������� ������
	music.setLoop(true); //������������ 
	music.stop(); //���������

	setDefaultWindowSettings(window); //������������� ����������� ��������� ����
	GUI gui(window); //������ ����������� ��������� ������������
	menu.init(window);//�������������� ����
	settings.init(window);
	credits.init(window);
	help.init(window);
	death.init(window);
	end.init(window);

	timeSinceLastUpdate = Time::Zero; //�������� ����� � ���������� ����������
	while (window.isOpen()) //���� ���� �������
	{
		Event event; //�������
		while (window.pollEvent(event)) //���� ���� ��������� �������
		{
			if (event.type == sf::Event::Closed) //���� ������� �������� ����
				window.close();// ������� ����
		}
		switch (gameState) //������������ ������� ���������
		{
		case GameState::MainMenu: 
			cursor.setScale(1, 1); //������������ ������
			window.setView(window.getDefaultView());  //������������� ����������� ������
			menu.draw(window, cursor, gameState); //������ ����
			if (music.getStatus() == SoundSource::Status::Playing) //���� ������ ������
				music.stop(); //�������������
			break;
		case GameState::Settings: //����������� ���� ��������
			settings.draw(window, cursor, gameState, gui, menu, help, credits, death, end, music);
			break;
		case GameState::Help: //���������� ���� ������
			help.draw(window, cursor, gameState);
			break;
		case GameState::Credits: //����������� ���� "� ������������"
			credits.draw(window, cursor, gameState);
			break;
		case GameState::Death: //����������� ���� ������
			window.setView(window.getDefaultView());
			cursor.setScale(1, 1);
			death.draw(window, cursor, gameState);
			break;
		case GameState::End: //����������� ���� ����� ����
			window.setView(window.getDefaultView());
			cursor.setScale(1, 1);
			end.draw(window, cursor, gameState);
			break;
		case GameState::NewGame: //������������� ����� ����, ���� ������� ���������
			if (initNewGame == false)
			{
				level.LoadFromFile("resources/Maps/Level1.xml");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.
				create_LVL1();
				player.init(level.GetAllObjects(), level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
				initNewGame = true;
			}
			gameState = GameState::Game;
			break;
		case GameState::Game:// ����
			if (music.getStatus() == SoundSource::Status::Stopped)
			{
				music.play(); //������ ������
				clock.restart(); //���������� �����
				cursor.setScale(0.3f, 0.3f); //������������ ������
			}
			window.clear(Color::Black); //������� �����

			if (player.getHP() < 100) //���� �������� ������ 100
				player.hpRegen(); //�����������
			if (player.getHP() <= 0) //���� �������� ������ ���� ����� 0
			{
				initNewGame = false; //���� �������������
				gameState = GameState::Death; //����� ���������
				continue;
			}

			timeSinceLastUpdate += clock.restart(); //����� � ���������� ����������
			if (timeSinceLastUpdate > timePerFrame) //���� ����� �� ���� ��������
			{
				window.setView(view); //������������� ������

				timeSinceLastUpdate -= timePerFrame; //�������� ����� �� ����
				player.update(speed, window, vectEnemy); //��������� ������ ���������
				lines.clear(); //������� ������ �����
				for (int i = 0; i < vectEnemy.size(); i++) //���������� ������
				{
					enemyDmg = 0; 
					vectEnemy[i].update(player.getRect(), speed, enemyDmg);
					if (enemyDmg > player.getProtection() / 10)
						player.takeDamage(enemyDmg); //��������� ���� ���� ��������� ������
					tmpLines = vectEnemy[i].getLines(); //���������� ����� � ������ �������
					lines.reserve(lines.size() + tmpLines.size());
					lines.insert(lines.end(), tmpLines.begin(), tmpLines.end());
				}
			}
			level.Draw(window, player, vectEnemy); //��������� ����� ������ � ���������� � �������
			setPlayerCoordinateForView(player.getX() + 8, player.getY() + 8); //������� ������

			worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window)); //���������� ������� �� ����� ������
			cursor.setPosition(worldPos);

			for (int i = 0; i < vectNPC.size(); i++) //��������� ���� NPC
				vectNPC[i].drawSprites(window);
			tmpLines = player.getLines(); 
			lines.reserve(lines.size() + tmpLines.size());
			lines.insert(lines.end(), tmpLines.begin(), tmpLines.end());
			for (int i = 0; i < lines.size(); i++)
				window.draw(lines[i]); //��������� ���� �����

			collisionEvent = player.checkCollisionWithMap(vectNPC, vectSign, vectEnemy); //�������� ������� ������������ � ��������
			checkEvent(collisionEvent,window,player,gui); //���������� �������
			
			gui.drawGUI(window, player, gameState); //��������� ������������ ����������
			window.draw(cursor); //��������� �������
			window.display(); //����������� ����������� ����
			break;
		}
	}
}

void Game::setDefaultWindowSettings(sf::RenderWindow &window) //����������� ��������� ����
{
	font.loadFromFile("font.otf"); //�������� ������

	window.setMouseCursorVisible(false); //��������� �������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	textureCursor.loadFromFile("resources/img/cursor.png"); //�������� �������
	cursor.setTexture(textureCursor);
	cursor.setScale(0.3f, 0.3f);//��������������� ������� �������

	Image icon;
	icon.loadFromFile("resources/img/Icon.png"); 
	window.setIcon(16, 16, icon.getPixelsPtr()); //������������� ������ ����
}

void Game::createArmorSet(vector<Equip>&armorSet) //��������(��������) ���� ����������
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

void Game::giveItem(Player &player,string armorset) //������ ����������
{
	bool give = true; 
	int setID;
	for (int i = 0; i < armorSet.size(); i++) //���������� ��� ����������
	{
		if (armorSet[i].getName() == armorset)
		{
			setID = i;
			for (int j = 0; j < player.getEquipSets().size(); j++)//���������� ���������� ���������
			{
				if (player.getEquipSets()[j].getID() == armorSet[i].getID()) //���� ����� ���������� ��� �������
				{
					give = false; //�� ���������
					break;
				}
			}
			break;
		}
	}
	if (give == true) //���� ����� ���������� �� ����, �������� ����������
		player.addEquipSet(armorSet[setID]);
}