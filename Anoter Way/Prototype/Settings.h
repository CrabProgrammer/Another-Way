#pragma once
#include"Header.h"
class Settings //класс настроек 
{
private:
	Texture menuBackground;
	Button backButton; //кнопка назад
	Button vsyncOnButton, vsyncOffButton; //кнопки :включение и отключение вертикальной синхронизации
	Button musicOn, musicOff; //конпки : включение и отключение музыки
	Button resolutonButton1, resolutonButton2, resolutonButton3, resolutonButton4, resolutonButton5; //кнопки : смена разрешений экрана
	Button fullscreenButtonOn, fullscreenButtonOff;//кнопки : включение и выхключени полноэкранного режима
	Sprite background;
	Label label;
public:
	void init(RenderWindow &window)//инициализация кнопок и текста, загрузка заднего фона
	{
		menuBackground.loadFromFile("resources/img/background.jpg");
		background.setTexture(menuBackground);
		background.setTextureRect(IntRect(1920 - window.getSize().x, 1200 - window.getSize().y, window.getSize().x, window.getSize().y));

		label.init("Settings", 72, window.getSize().x / 2 - 120, 40);
		vsyncOnButton.init("Vetrical SYNC. ON", 100, 160, true);
		vsyncOffButton.init("Vertical SYNC. OFF", 100, 240, true);
		musicOn.init("Music On", 100, 400, true);
		musicOff.init("Music Off", 100, 480, true);
		resolutonButton1.init("800x600", window.getSize().x / 2 - 85, 160, true);
		resolutonButton2.init("1280x1024", window.getSize().x / 2 - 85, 240, true);
		resolutonButton3.init("1366x768", window.getSize().x / 2 - 85, 320, true);
		resolutonButton4.init("1600x900", window.getSize().x / 2 - 85, 400, true);
		resolutonButton5.init("1920x1080", window.getSize().x / 2 - 85, 480, true);
		fullscreenButtonOn.init("Fullscreen on", window.getSize().x - 290, 160, true);
		fullscreenButtonOff.init("Fullscreen off", window.getSize().x - 290, 240, true);
		backButton.init("Back", window.getSize().x - 220, window.getSize().y - 90, true);
	}
	void draw(RenderWindow &window, Sprite &cursor, int &gameState, GUI &gui, MainMenu &menu,Help &help, Credits &credits,Death &death, End &end,Music &music)
	{
		cursor.setPosition(Vector2f(Mouse::getPosition(window))); //координаты курсора
		window.clear(Color::Green); //очистка экрана
		window.draw(background); //рисуем задний фон
												//ПРОВЕРКА НАЖАТИ КНОПОК И ДЕЙСТВИЯ
		if (vsyncOnButton.checkClick(window)) 
			window.setVerticalSyncEnabled(true);
		else if (vsyncOffButton.checkClick(window))
			window.setVerticalSyncEnabled(false);

		if (musicOn.checkClick(window))
			music.setVolume(100);
		else if (musicOff.checkClick(window))
			music.setVolume(0);

		else if (resolutonButton1.checkClick(window))
		{
			window.close();
			window.create(VideoMode(800, 600), "Another Way");
			window.setView(View(FloatRect(0, 0, 800, 600)));
			initOtherStates(window, gui, menu, help, credits, death,end);
		}
		else if (resolutonButton2.checkClick(window))
		{
			window.close();
			window.create(VideoMode(1280, 1024), "Another Way");
			window.setView(View(FloatRect(0, 0, 1280, 1024)));
			initOtherStates(window, gui, menu, help, credits,death, end);
		}
		else if (resolutonButton3.checkClick(window))
		{
			window.close();
			window.create(VideoMode(1366, 768), "Another Way");
			window.setView(View(FloatRect(0, 0, 1366, 768)));
			initOtherStates(window, gui, menu, help, credits, death, end);
		}
		else if (resolutonButton4.checkClick(window))
		{
			window.close();
			window.create(VideoMode(1600, 900), "Another Way");
			window.setView(View(FloatRect(0, 0, 1600, 900)));
			initOtherStates(window, gui, menu, help, credits, death, end);
		}
		else if (resolutonButton5.checkClick(window))
		{
			window.close();
			window.create(VideoMode(1920, 1080), "Another Way");
			window.setView(View(FloatRect(0, 0, 1920, 1080)));
			initOtherStates(window, gui, menu, help, credits, death, end);
		}
		else if (fullscreenButtonOn.checkClick(window))
		{
			window.close();
			window.create(VideoMode(window.getSize().x, window.getSize().y), "Another Way", sf::Style::Fullscreen);
			window.setMouseCursorVisible(false);
		}
		else if (fullscreenButtonOff.checkClick(window))
		{
			window.close();
			window.create(VideoMode(window.getSize().x, window.getSize().y), "Another Way");
			window.setMouseCursorVisible(false);
		}
		else if (backButton.checkClick(window))
			gameState = GameState::MainMenu;
								//ОТРИСОВКА КНОПОК
		backButton.draw(window);
		vsyncOnButton.draw(window);
		vsyncOffButton.draw(window);
		musicOn.draw(window);
		musicOff.draw(window);
		resolutonButton1.draw(window);
		resolutonButton2.draw(window);
		resolutonButton3.draw(window);
		resolutonButton4.draw(window);
		resolutonButton5.draw(window);
		fullscreenButtonOn.draw(window);
		fullscreenButtonOff.draw(window);

		label.draw(window);
		window.draw(cursor); //отрисовка курсора
		window.display();

	}
	void initOtherStates(RenderWindow &window, GUI &gui, MainMenu &menu, Help &help, Credits &credits,Death &death,End &end)
	{ //инициализация других игровых состояний под новое разрешение экрана
		gui.init(window);
		menu.init(window);
		help.init(window);
		credits.init(window);
		death.init(window);
		end.init(window);
		init(window);
		window.setMouseCursorVisible(false);
		Image icon;
		icon.loadFromFile("resources/img/Icon.png");
		window.setIcon(16, 16, icon.getPixelsPtr());
	}
};
