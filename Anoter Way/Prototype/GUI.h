#pragma once
#include"Header.h"

class GUI //класс графического пользовательского интерфейса
{
private:
	Label healthLabel; //надпись здоровья
	Button menuButton,inventoryButton; //кнопки меню и инвентаря
	StatBar hpBar; //полоса здоровья
	View view; //камера
	TextPanel textPanel; //панель для отображения текста
	Inventory inventory; //инвентарь

public:
	GUI(RenderWindow &window) //коструктор 
	{
		healthLabel.init("HEALTH", 20, 25, 10); //инициализация координат объектов
		menuButton.init("MENU", window.getSize().x - 75,  25,false);
		inventoryButton.init("INV", window.getSize().x - 135, 25,false);
		hpBar.init(25, 35, 200, 10, Color::Red);
		textPanel.init(window);
		inventory.init(window);
	}
	void init(RenderWindow &window)//метод для повторной инициализации
	{
		healthLabel.init("HEALTH", 14, 25, 10); 
		menuButton.init("MENU", window.getSize().x - 75, 25, false);
		inventoryButton.init("INV", window.getSize().x - 135, 25, false);
		hpBar.init(25, 35, 200, 10, Color::Red);
		textPanel.init(window);
		inventory.init(window);
	}
	void drawGUI(RenderWindow &window,Player &player,int &gameStete) //отрисовка GUI
	{
		
		inventory.checkShow(inventoryButton.checkClick(window));  //проверка нажатия инвентаря
		view = window.getView(); //сохранение текущей камеры
		window.setView(window.getDefaultView()); //устанавливаем стандартную
		if (menuButton.checkClick(window)) //проверяме нажатие
			gameStete = GameState::MainMenu;
		healthLabel.draw(window); //рисуем
		menuButton.draw(window);
		inventoryButton.draw(window);
		hpBar.draw(player.getHP(),window);
		inventory.draw(window,player);
		window.setView(view);//возвращаем камеру
	}
	void drawTextPanel(RenderWindow &window,string txt) //отображение текста на стандартной камере
	{
		view = window.getView();
		window.setView(window.getDefaultView());
		textPanel.draw(window, txt);
		window.setView(view);
	}
};