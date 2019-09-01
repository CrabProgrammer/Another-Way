#include"Header.h"

void Game::create_LVL1() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC ranger("resources/Characters/Ranger.xml", "ranger", level.GetObject("ranger").rect.left + 16, level.GetObject("ranger").rect.top + 16); //создание NPC по координатам объектов
	NPC fisher("resources/Characters/Fisher.xml", "fisher", level.GetObject("fisher").rect.left + 16, level.GetObject("fisher").rect.top + 16);
	NPC fguard("resources/Characters/Fguard.xml", "fguard", level.GetObject("fguard").rect.left + 16, level.GetObject("fguard").rect.top + 16);
	NPC bandit("resources/Characters/Bandit.xml", "bandit", level.GetObject("bandit").rect.left + 16, level.GetObject("bandit").rect.top + 16);
	NPC blacksmith("resources/Characters/Blacksmith.xml", "blacksmith", level.GetObject("blacksmith").rect.left + 16, level.GetObject("blacksmith").rect.top + 16);
	ranger.setText("Hi , stranger. I'm surprised how easy you deceit our guardian,\nyou can take this one."); //устанавливаем текст каждому из NPC
	fisher.setText("Good morning. Did you hear that one of our rangers \nbecame a coach and ready to fight with anyone who wants");
	bandit.setText("You can pass, bro ");
	blacksmith.setText("Oh, I see you need an armor. You can take this one.");
	fguard.setText("Come in, ranger");
	vectNPC.push_back(ranger);//добавляем NPC в вектор
	vectNPC.push_back(fisher);
	vectNPC.push_back(fguard);
	vectNPC.push_back(bandit);
	vectNPC.push_back(blacksmith);
	Sign chest1("chest1", "Ranger chest"); //создаём надпись
	vectSign.push_back(chest1);//добавляем надпись в вектор
	//создание врага по координатам объекта, передавая ему все непроходимые объекты текущей карты
	Enemy trainer("resources/Characters/Trainer.xml", level.GetObjects("solid"), level.GetObject("trainer").rect.left + 16, level.GetObject("trainer").rect.top + 16);
	trainer.setProtection(45); //устанавливаем защиту выравнивающую баланс игры
	vectEnemy.push_back(trainer); //добавляем врага вектор
	//повторно инициализируем векторы для предотвращения потери спрайтов
	for (int i = 0; i < vectNPC.size(); i++) 
		vectNPC[i].init();

	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_LVL2() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC villager1("resources/Characters/Villager1.xml", "villager1", level.GetObject("villager1").rect.left + 16, level.GetObject("villager1").rect.top + 16); //создание NPC по координатам объектов
	NPC villager2("resources/Characters/Villager2.xml", "villager2", level.GetObject("villager2").rect.left + 16, level.GetObject("villager2").rect.top + 16);
	NPC eguard("resources/Characters/Eguard.xml", "eguard", level.GetObject("eguard").rect.left + 16, level.GetObject("eguard").rect.top + 16);
	villager1.setText("Welcome to our town ");//устанавливаем текст каждому из NPC
	villager2.setText("Woah! It's nicely to see new person in our town ");
	eguard.setText("The path is always opened for the great magus");
	vectNPC.push_back(villager1);
	vectNPC.push_back(villager2);
	vectNPC.push_back(eguard);

	Sign sign1("sign1", "Welcome to Emerald Town");
	Sign sign2("sign2", "From a long time there is legend about the\ngrand magus who lives in darkness but no one haven't seen him alive");
	Sign chest2("chest2", "Blacksmith chest");
	Sign chest3("chest3", "Miner chest");
	Sign statue("statue", "Statue of Emerald Magus");
	vectSign.push_back(sign1);
	vectSign.push_back(statue);
	vectSign.push_back(sign2);
	vectSign.push_back(chest2);
	vectSign.push_back(chest3);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_LVL3() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	Sign sign1("sign1", "Road to Silver house\nRoad to port\nRoad to forge");
	Sign sign2("sign2", "Road to port");
	Sign sign3("sign3", "Silver House");

	vectSign.push_back(sign1);
	vectSign.push_back(sign2);
	vectSign.push_back(sign3);
	NPC miner("resources/Characters/Miner.xml", "miner", level.GetObject("miner").rect.left + 16, level.GetObject("miner").rect.top + 16); //создание NPC по координатам объектов
	miner.setText("I was told to give the new form of the jester to the new miner");//устанавливаем текст каждому из NPC
	vectNPC.push_back(miner);
	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_LVL4() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();
	Sign sign1("sign1", "Road to the market");
	Sign sign2("sign2", "Road to port");
	NPC villager3("resources/Characters/Villager3.xml", "villager3", level.GetObject("villager3").rect.left + 16, level.GetObject("villager3").rect.top + 16); //создание NPC по координатам объектов
	NPC villager4("resources/Characters/Villager4.xml", "villager4", level.GetObject("villager4").rect.left + 16, level.GetObject("villager4").rect.top + 16);
	NPC villager5("resources/Characters/Villager5.xml", "villager5", level.GetObject("villager5").rect.left + 16, level.GetObject("villager5").rect.top + 16);
	NPC villager6("resources/Characters/Villager6.xml", "villager6", level.GetObject("villager6").rect.left + 16, level.GetObject("villager6").rect.top + 16);
	NPC villager7("resources/Characters/Villager7.xml", "villager7", level.GetObject("villager7").rect.left + 16, level.GetObject("villager7").rect.top + 16);
	NPC sailorman("resources/Characters/Sailorman.xml", "sailorman", level.GetObject("sailorman").rect.left + 16, level.GetObject("sailorman").rect.top + 16);

	villager3.setText("I've heard that the castle to the which the\nrailways leads is closed and only guardians are able to come in");//устанавливаем текст каждому из NPC
	villager4.setText("Spicy spices from far far away islands ");
	villager5.setText("You can find the most seasoned alcohol from\nroyal cellars only at my store");
	villager6.setText("I have all meat that runs and flies");
	villager7.setText("The freshest vegetables, what do you wish for ");
	sailorman.setText("I sail to the desert oasis. Do you want to go with me?");
	vectNPC.push_back(villager3);
	vectNPC.push_back(villager4);
	vectNPC.push_back(villager5);
	vectNPC.push_back(villager6);
	vectNPC.push_back(villager7);
	vectNPC.push_back(sailorman);
	vectSign.push_back(sign1);
	vectSign.push_back(sign2);
	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_LVL5() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();
	Sign sign1("sign1", "Castle is closed. Exit forbidden");	
	NPC cguard1("resources/Characters/Cguard.xml", "cguard1", level.GetObject("cguard1").rect.left + 16, level.GetObject("cguard1").rect.top + 16); //создание NPC по координатам объектов
	NPC cguard2("resources/Characters/Cguard.xml", "cguard2", level.GetObject("cguard2").rect.left + 16, level.GetObject("cguard2").rect.top + 16);

	cguard1.setText("Where have you been all the time? Come in faster until guard haven't seen u");//устанавливаем текст каждому из NPC
	cguard2.setText("Where have you been all the time? Come in faster until guard haven't seen u");

	vectNPC.push_back(cguard1); //очистка векторов объектов уровня
	vectNPC.push_back(cguard2);

	vectSign.push_back(sign1);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_Castle1() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();
	NPC citizen1("resources/Characters/Citizen1.xml", "citizen1", level.GetObject("citizen1").rect.left + 16, level.GetObject("citizen1").rect.top + 16); //создание NPC по координатам объектов
	NPC citizen2("resources/Characters/Citizen2.xml", "citizen2", level.GetObject("citizen2").rect.left + 16, level.GetObject("citizen2").rect.top + 16);
	NPC citizen3("resources/Characters/Citizen3.xml", "citizen3", level.GetObject("citizen3").rect.left + 16, level.GetObject("citizen3").rect.top + 16);
	NPC citizen4("resources/Characters/Citizen4.xml", "citizen4", level.GetObject("citizen4").rect.left + 16, level.GetObject("citizen4").rect.top + 16);
	NPC citizen5("resources/Characters/Citizen2.xml", "citizen5", level.GetObject("citizen5").rect.left + 16, level.GetObject("citizen5").rect.top + 16);

	NPC pguard1("resources/Characters/Pguard.xml", "pguard1", level.GetObject("pguard1").rect.left + 16, level.GetObject("pguard1").rect.top + 16);
	NPC pguard2("resources/Characters/Pguard.xml", "pguard2", level.GetObject("pguard2").rect.left + 16, level.GetObject("pguard2").rect.top + 16);

	citizen1.setText("The profit from my alcohol shop has tripled after the castle was closed.\nNowadays everybody just drink and only.");//устанавливаем текст каждому из NPC
	citizen2.setText("Even king buys vegetables at me. Why don't you follow his example?");
	citizen3.setText("Stout beer and dried fish! What else do you need for happiness?");
	citizen4.setText("There are rumors that king's jester died from plague. Interesting, who will\ntake his place?");
	citizen5.setText("Hello there");
	pguard1.setText("Here you are! The new king's jester! Come in, the king was waiting for you");
	pguard2.setText("Here you are! The new king's jester! Come in, the king was waiting for you");

	vectNPC.push_back(citizen1);
	vectNPC.push_back(citizen2);
	vectNPC.push_back(citizen3);
	vectNPC.push_back(citizen4);
	vectNPC.push_back(pguard1);
	vectNPC.push_back(pguard2);
	
	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_Castle2() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();
	NPC king("resources/Characters/King.xml", "king", level.GetObject("king").rect.left + 16, level.GetObject("king").rect.top + 16); //создание NPC по координатам объектов
	NPC kguard("resources/Characters/Kguard.xml", "kguard", level.GetObject("kguard").rect.left + 16, level.GetObject("kguard").rect.top + 16);
	Enemy kguard1("resources/Characters/Kguard.xml", level.GetObjects("solid"), level.GetObject("kguard1").rect.left + 16, level.GetObject("kguard1").rect.top + 16);
	Enemy kguard2("resources/Characters/Kguard.xml", level.GetObjects("solid"), level.GetObject("kguard2").rect.left + 16, level.GetObject("kguard2").rect.top + 16);
	Enemy kguard3("resources/Characters/Kguard.xml", level.GetObjects("solid"),-100, -100);

	king.setText("Guard, grab him");//устанавливаем текст каждому из NPC
	kguard.setText("Oh, probably you're newbie, come here");

	vectNPC.push_back(king);
	vectNPC.push_back(kguard);

	vectEnemy.push_back(kguard1);
	vectEnemy.push_back(kguard2);
	vectEnemy.push_back(kguard3);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
	vectEnemy.erase(vectEnemy.begin() + 2);
}
void Game::create_Prison() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();
	NPC prisoner1("resources/Characters/Prisoner1.xml", "prisoner1", level.GetObject("prisoner1").rect.left + 16, level.GetObject("prisoner1").rect.top + 16); //создание NPC по координатам объектов
	NPC prisoner2("resources/Characters/Prisoner2.xml", "prisoner1", level.GetObject("prisoner2").rect.left + 16, level.GetObject("prisoner2").rect.top + 16);
	NPC brother("resources/Characters/brother.xml", "brother", level.GetObject("brother").rect.left + 16, level.GetObject("brother").rect.top + 16);
	//устанавливаем текст каждому из NPC
	brother.setText("Can not be, brother, you've done all this path to save me.\nNow the guards are not a hindrance to us.\nHere is the tunnel, leading straight from the castle, come on!");

	vectNPC.push_back(prisoner1);
	vectNPC.push_back(prisoner2);
	vectNPC.push_back(brother);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_Cave() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();
	NPC magus("resources/Characters/Magus.xml", "magus", level.GetObject("magus").rect.left + 16, level.GetObject("magus").rect.top + 16); //создание NPC по координатам объектов
	magus.setText("That was a hard path. I have not seen people for a very long\ntime. Thanks for the company. You can take this...");//устанавливаем текст каждому из NPC
	vectNPC.push_back(magus);

	Enemy orc1("resources/Characters/Orc.xml", level.GetObjects("solid"), level.GetObject("orc1").rect.left + 16, level.GetObject("orc1").rect.top + 16);
	Enemy orc2("resources/Characters/Orc.xml", level.GetObjects("solid"), level.GetObject("orc2").rect.left + 16, level.GetObject("orc2").rect.top + 16);
	Enemy orc3("resources/Characters/Orc.xml", level.GetObjects("solid"), -100, -100);

	vectEnemy.push_back(orc1);
	vectEnemy.push_back(orc2);
	vectEnemy.push_back(orc3);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_Desert1() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();
	NPC sailorman("resources/Characters/Sailorman.xml", "sailorman", level.GetObject("sailorman").rect.left + 16, level.GetObject("sailorman").rect.top + 16); //создание NPC по координатам объектов

	sailorman.setText("I've done my business. We can go back");//устанавливаем текст каждому из NPC
	vectNPC.push_back(sailorman);
	NPC dguard("resources/Characters/Dguard.xml", "dguard", level.GetObject("dguard").rect.left + 16, level.GetObject("dguard").rect.top + 16);
	dguard.setText("Desert raiders are always respected");
	vectNPC.push_back(dguard);
	NPC dfguard("resources/Characters/Dfguard.xml", "dfguard", level.GetObject("dfguard").rect.left + 16, level.GetObject("dfguard").rect.top + 16);
	dfguard.setText("I'm always glad to see our sheikh's friends");
	vectNPC.push_back(dfguard);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_Desert2() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC dforester("resources/Characters/Dforester.xml", "dforester", level.GetObject("dforester").rect.left + 16, level.GetObject("dforester").rect.top + 16); //создание NPC по координатам объектов
	dforester.setText("I would give away this priest's robe to whom who will laugh me.\nI don't need this anyway");//устанавливаем текст каждому из NPC
	vectNPC.push_back(dforester);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
	for (int i = 0; i < vectEnemy.size(); i++)
		vectEnemy[i].init();
}
void Game::create_House1() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC elder("resources/Characters/Elder.xml", "elder", level.GetObject("elder").rect.left + 16, level.GetObject("elder").rect.top + 16);
	elder.setText("Blacksmith forgot some strange thief's clothing");//устанавливаем текст каждому из NPC
	vectNPC.push_back(elder);
	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
}

void Game::create_House2() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC silver("resources/Characters/Silver.xml", "silver", level.GetObject("silver").rect.left + 16, level.GetObject("silver").rect.top + 16); //создание NPC по координатам объектов
	NPC barman("resources/Characters/Barman.xml", "barman", level.GetObject("barman").rect.left + 16, level.GetObject("barman").rect.top + 16);
	silver.setText("Only members of the thieves' guild are able to wear\nclothing that masks you under the guardian");//устанавливаем текст каждому из NPC
	barman.setText("Do you want some food or drink?");

	vectNPC.push_back(silver);
	vectNPC.push_back(barman);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
}
void Game::create_House3() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC sheikh("resources/Characters/Sheikh.xml", "sheikh", level.GetObject("sheikh").rect.left + 16, level.GetObject("sheikh").rect.top + 16); //создание NPC по координатам объектов

	sheikh.setText("I'm always glad to see guests at my house. You want to join our desert\nraiders clan, didn't you? Take it. Maybe you would like to join us"); //устанавливаем текст каждому из NPC

	vectNPC.push_back(sheikh);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
}void Game::create_House4() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC darmor("resources/Characters/Darmor.xml", "darmor", level.GetObject("darmor").rect.left + 16, level.GetObject("darmor").rect.top + 16); //создание NPC по координатам объектов
	darmor.setText("You've done a hard path to visit me. I wonder you would need my old castle\nguardian's armor when you would come back");//устанавливаем текст каждому из NPC

	vectNPC.push_back(darmor);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
}
void Game::create_Church() //создание объектов уровня 
{
	vectNPC.clear(); //очистка векторов объектов уровня
	vectSign.clear();
	vectEnemy.clear();

	NPC pastor("resources/Characters/Pastor.xml", "pastor", level.GetObject("pastor").rect.left + 16, level.GetObject("pastor").rect.top + 16); //создание NPC по координатам объектов
	pastor.setText("My disciples are able to wear royal guard's armor for come through into\njail and preach to prisoners");//устанавливаем текст каждому из NPC

	vectNPC.push_back(pastor);

	for (int i = 0; i < vectNPC.size(); i++)
		vectNPC[i].init();
}