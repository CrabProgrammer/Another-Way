#include"Header.h"
void Game::checkEvent(string collisionEvent,RenderWindow &window, Player &player,GUI &gui) //обработчик событий
{
	if (collisionEvent != "")//если событие произошло 
	{
		if (collisionEvent.substr(0, 3) == "NPC")//если событие - NPC
		{
			for (int i = 0; i < vectNPC.size(); i++)
			{
				if (collisionEvent == "NPC" + vectNPC[i].getName()) //взаимодействие с определенным NPC
				{
					gui.drawTextPanel(window, vectNPC[i].getText());
					if (vectNPC[i].getName() == "blacksmith")
						giveItem(player, "Weapon");
					else if (vectNPC[i].getName() == "ranger")
						giveItem(player, "Bandit");
					else if (vectNPC[i].getName() == "elder")
					{
						if (player.getCurrentEquipName() == "Blacksmith")
							giveItem(player, "Thief");
					}
					else if (vectNPC[i].getName() == "magus")
						giveItem(player, "Magus");
					else if (vectNPC[i].getName() == "miner")
					{
						if (player.getCurrentEquipName() == "Miner")
							giveItem(player, "Jester");
					}
					else if (vectNPC[i].getName() == "silver")
					{
						if (player.getCurrentEquipName() == "Thief")
							giveItem(player, "Dfguard");
					}
					else if (vectNPC[i].getName() == "sheikh")
						giveItem(player, "Dguard");
					else if (vectNPC[i].getName() == "dforester")
					{
						if (player.getCurrentEquipName() == "Jester")
							giveItem(player, "Priest");
					}
					else if (vectNPC[i].getName() == "pastor")
					{
						if (player.getCurrentEquipName() == "Priest")
							giveItem(player, "Kguard");
					}
					else if (vectNPC[i].getName() == "darmor")
						giveItem(player, "Cguard");
				}
			}
		}
		else if (collisionEvent.substr(0, 4) == "Sign") //если событие - надпись
		{
			for (int i = 0; i < vectSign.size(); i++)
			{
				if (collisionEvent == "Sign" + vectSign[i].getName()) //взаимодействие с определенной надписью
				{
					gui.drawTextPanel(window, vectSign[i].getText());

					if (vectSign[i].getName() == "chest1")
						giveItem(player, "Ranger");
					else if (vectSign[i].getName() == "chest2")
						giveItem(player, "Blacksmith");
					else if (vectSign[i].getName() == "chest3")
						giveItem(player, "Miner");
				}
			}
		}
		else if (collisionEvent == "lvl1") //если событие уровн€ - переход по уровню и загрузка объектов данного уровн€
		{
			level.LoadFromFile("resources/Maps/Level1.xml");
			player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			player.setObj(level.GetAllObjects());
			create_LVL1();
		}
		else if (collisionEvent.substr(0, 4) == "lvl2")
		{
			level.LoadFromFile("resources/Maps/Level2.xml");
			if (collisionEvent == "lvl2-1")
				player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			else if (collisionEvent == "lvl2-2")
				player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			else if (collisionEvent == "lvl2-3")
				player.setPosition(level.GetObject("start3").rect.left, level.GetObject("start3").rect.top);
			else if (collisionEvent == "lvl2-4")
				player.setPosition(level.GetObject("start4").rect.left, level.GetObject("start4").rect.top);
			player.setObj(level.GetAllObjects());
			create_LVL2();
		}
		else if (collisionEvent.substr(0, 4) == "lvl3")
		{
			level.LoadFromFile("resources/Maps/Level3.xml");
			if (collisionEvent == "lvl3-1")
				player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			if (collisionEvent == "lvl3-2")
				player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			else if (collisionEvent == "lvl3-3")
				player.setPosition(level.GetObject("start3").rect.left, level.GetObject("start3").rect.top);

			player.setObj(level.GetAllObjects());
			create_LVL3();
		}
		else if (collisionEvent.substr(0, 4) == "lvl4")
		{
			level.LoadFromFile("resources/Maps/Level4.xml");
			if (collisionEvent == "lvl4-1")
				player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			if (collisionEvent == "lvl4-2")
				player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			else if (collisionEvent == "lvl4-3")
				player.setPosition(level.GetObject("start3").rect.left, level.GetObject("start3").rect.top);
			else if (collisionEvent == "lvl4-4")
				player.setPosition(level.GetObject("start4").rect.left, level.GetObject("start4").rect.top);
			player.setObj(level.GetAllObjects());
			create_LVL4();
		}
		else if (collisionEvent.substr(0, 4) == "lvl5")
		{
			level.LoadFromFile("resources/Maps/Level5.xml");
			if (collisionEvent == "lvl5-1")
				player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			if (collisionEvent == "lvl5-2")
				player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			player.setObj(level.GetAllObjects());
			create_LVL5();
		}
		else if (collisionEvent.substr(0, 7) == "castle1")
		{
			level.LoadFromFile("resources/Maps/Castle1.xml");
			if (collisionEvent == "castle1-1")
				player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			if (collisionEvent == "castle1-2")
				player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			player.setObj(level.GetAllObjects());
			create_Castle1();
		}
		else if (collisionEvent.substr(0, 7) == "castle2")
		{
			level.LoadFromFile("resources/Maps/Castle2.xml");
			player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			player.setObj(level.GetAllObjects());
			create_Castle2();
		}
		else if (collisionEvent.substr(0, 6) == "prison")
		{
			level.LoadFromFile("resources/Maps/Prison.xml");
			player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			player.setObj(level.GetAllObjects());
			create_Prison();
		}
		else if (collisionEvent.substr(0, 7) == "desert1")
		{
			level.LoadFromFile("resources/Maps/Desert1.xml");
			if (collisionEvent == "desert1-1")
				player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			if (collisionEvent == "desert1-2")
				player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			if (collisionEvent == "desert1-3")
				player.setPosition(level.GetObject("start3").rect.left, level.GetObject("start3").rect.top);
			player.setObj(level.GetAllObjects());
			create_Desert1();
		}
		else if (collisionEvent.substr(0, 7) == "desert2")
		{
			level.LoadFromFile("resources/Maps/Desert2.xml");
			if (collisionEvent == "desert2-1")
				player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			if (collisionEvent == "desert2-2")
				player.setPosition(level.GetObject("start2").rect.left, level.GetObject("start2").rect.top);
			player.setObj(level.GetAllObjects());
			create_Desert2();
		}
		else if (collisionEvent == "cave1")
		{
			level.LoadFromFile("resources/Maps/Cave1.xml");
			player.setPosition(level.GetObject("start").rect.left, level.GetObject("start").rect.top);
			player.setObj(level.GetAllObjects());
			create_Cave();
		}
		else if (collisionEvent == "house1")
		{
			level.LoadFromFile("resources/Maps/House1.xml");
			player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			player.setObj(level.GetAllObjects());
			create_House1();
		}
		else if (collisionEvent == "house2")
		{
			level.LoadFromFile("resources/Maps/House2.xml");
			player.setPosition(level.GetObject("start").rect.left, level.GetObject("start").rect.top);
			player.setObj(level.GetAllObjects());
			create_House2();
		}
		else if (collisionEvent == "house3")
		{
			level.LoadFromFile("resources/Maps/House3.xml");
			player.setPosition(level.GetObject("start1").rect.left, level.GetObject("start1").rect.top);
			player.setObj(level.GetAllObjects());
			create_House3();
		}
		else if (collisionEvent == "house4")
		{
			level.LoadFromFile("resources/Maps/House4.xml");
			player.setPosition(level.GetObject("start").rect.left, level.GetObject("start").rect.top);
			player.setObj(level.GetAllObjects());
			create_House4();
		}
		else if (collisionEvent == "church")
		{
			level.LoadFromFile("resources/Maps/Church.xml");
			player.setPosition(level.GetObject("start").rect.left, level.GetObject("start").rect.top);
			player.setObj(level.GetAllObjects());
			create_Church();
		}
		else if (collisionEvent == "end") //если конец игры - переключение состо€ни€ игры
		{
			gameState = GameState::End;
			initNewGame = false;
		}

	}
}