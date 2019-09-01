#pragma once
#include"Header.h"
class MainMenu //класс главное меню
{
private:
	Texture menuBackground; //текстура заднего фона
	Button startButton, helpButton,settingsButton, creditsButton, exitButton; //кнопки для перехода по состояниям
	Sprite background;
	Label label; //надпись
public:
	void init(RenderWindow &window) //инициализация кнопок и текста, загрузка заднего фона
	{
		menuBackground.loadFromFile("resources/img/background.jpg");
		background.setTexture(menuBackground);
		background.setTextureRect(IntRect(1920- window.getSize().x,1200-window.getSize().y,window.getSize().x,window.getSize().y));

		label.init("Another Way", 82, window.getSize().x / 2 - 150, 30);
		startButton.init("Start", window.getSize().x - 220, window.getSize().y - 410, true);
		helpButton.init("Help", window.getSize().x - 220, window.getSize().y - 330, true);
		settingsButton.init("Settings", window.getSize().x - 220, window.getSize().y - 250, true);
		creditsButton.init("Credits", window.getSize().x - 220, window.getSize().y - 170, true);
		exitButton.init("Exit", window.getSize().x - 220, window.getSize().y - 90, true);
	}
	void draw(RenderWindow &window, Sprite &cursor, int &gameState) //отрисовка кнопок, курсора, текста // проверка на нажатие кнопок с переходами по игровым состояниям
	{
		cursor.setPosition(Vector2f(Mouse::getPosition(window)));
		window.clear(Color::Green);
		window.draw(background);
		if (startButton.checkClick(window))
			gameState = GameState::NewGame;
		else if (helpButton.checkClick(window))
			gameState = GameState::Help;
		else if (settingsButton.checkClick(window))
			gameState = GameState::Settings;
		else if (creditsButton.checkClick(window))
			gameState = GameState::Credits;
		else if (exitButton.checkClick(window))
			exit(0);
		startButton.draw(window);
		helpButton.draw(window);
		settingsButton.draw(window);
		creditsButton.draw(window);
		exitButton.draw(window);
		label.draw(window);
		window.draw(cursor);
		window.display();

	}
};
class Help //класс помощи
{
private:
	Texture menuBackground;
	Button backButton;
	Sprite background;
	Label label, text;
public:
	void init(RenderWindow &window)//инициализация кнопок и текста, загрузка заднего фона
	{
		menuBackground.loadFromFile("resources/img/background.jpg");
		background.setTexture(menuBackground);
		background.setTextureRect(IntRect(1920 - window.getSize().x, 1200 - window.getSize().y, window.getSize().x, window.getSize().y));
		label.init("Help", 72, window.getSize().x / 2 - 60, 40);
		text.init("Use arrows or wasd buttons for moving \n\nUse left mouse button for attack\n\nUse inventory for change your wear\n\nGood luck!", 28, 100, 200);
		backButton.init("Back", window.getSize().x - 220, window.getSize().y - 90, true);
	}
	void draw(RenderWindow &window, Sprite &cursor, int &gameState)//отрисовка кнопок, курсора, текста // проверка на нажатие кнопок с переходами по игровым состояниям
	{
		cursor.setPosition(Vector2f(Mouse::getPosition(window)));
		window.clear(Color::Green);
		window.draw(background);

		if (backButton.checkClick(window))
			gameState = GameState::MainMenu;//возврат в меню

		backButton.draw(window);
		label.draw(window);
		text.draw(window);
		window.draw(cursor);
		window.display();
	}
};

class Credits
{
private:
	Texture menuBackground;
	Button backButton;
	Sprite background;
	Label label, text;
public:
	void init(RenderWindow &window)//инициализация кнопок и текста, загрузка заднего фона
	{
		menuBackground.loadFromFile("resources/img/background.jpg");
		background.setTexture(menuBackground);
		background.setTextureRect(IntRect(1920 - window.getSize().x, 1200 - window.getSize().y, window.getSize().x, window.getSize().y));
		label.init("Credits", 72, window.getSize().x / 2 - 130, 40);
		text.init("Atmosphere Games Studio \n\nDeveloped by Artem Nalivkin", 28, 100, 200);
		backButton.init("Back", window.getSize().x - 220, window.getSize().y - 90, true);
	}
	void draw(RenderWindow &window, Sprite &cursor, int &gameState)//отрисовка кнопок, курсора, текста // проверка на нажатие кнопок с переходами по игровым состояниям
	{
		cursor.setPosition(Vector2f(Mouse::getPosition(window)));
		window.clear(Color::Green);
		window.draw(background);

		if (backButton.checkClick(window))
			gameState = GameState::MainMenu;//возврат в меню

		backButton.draw(window);
		label.draw(window);
		text.draw(window);
		window.draw(cursor);
		window.display();

	}
};

class Death
{
private:
	Texture menuBackground;
	Button backButton;
	Sprite background;
	Label label;
public:
	void init(RenderWindow &window)//инициализация кнопок и текста, загрузка заднего фона
	{
		menuBackground.loadFromFile("resources/img/background.jpg");
		background.setTexture(menuBackground);
		background.setTextureRect(IntRect(1920 - window.getSize().x, 1200 - window.getSize().y, window.getSize().x, window.getSize().y));
		label.init("Death", 72, window.getSize().x / 2 - 80, 240);
		backButton.init("Main menu", window.getSize().x / 2 - 95, window.getSize().y - 90, true);
	}
	void draw(RenderWindow &window, Sprite &cursor, int &gameState)//отрисовка кнопок, курсора, текста // проверка на нажатие кнопок с переходами по игровым состояниям
	{
		cursor.setPosition(Vector2f(Mouse::getPosition(window)));
		window.clear(Color::Green);
		window.draw(background);
		if (backButton.checkClick(window))
			gameState = GameState::MainMenu;//возврат в меню

		backButton.draw(window);
		label.draw(window);
		window.draw(cursor);
		window.display();
	}
};
class End
{
private:
	Texture menuBackground;
	Button backButton;
	Sprite background;
	Label label;
public:
	void init(RenderWindow &window)//инициализация кнопок и текста, загрузка заднего фона
	{
		menuBackground.loadFromFile("resources/img/background.jpg");
		background.setTexture(menuBackground);
		background.setTextureRect(IntRect(1920 - window.getSize().x, 1200 - window.getSize().y, window.getSize().x, window.getSize().y));
		label.init("\tCongratulations!\n\n\t    The End.", 72, window.getSize().x / 2 - 300, 140);
		backButton.init("Main menu", window.getSize().x / 2 - 95, window.getSize().y - 90, true);
	}
	void draw(RenderWindow &window, Sprite &cursor, int &gameState)//отрисовка кнопок, курсора, текста // проверка на нажатие кнопок с переходами по игровым состояниям
	{
		cursor.setPosition(Vector2f(Mouse::getPosition(window)));
		window.clear(Color::Green);
		window.draw(background);

		if (backButton.checkClick(window))
			gameState = GameState::MainMenu; //возврат в меню

		backButton.draw(window);
		label.draw(window);
		window.draw(cursor);
		window.display();
	}
};