#pragma once
#include"Header.h"

class GUI //����� ������������ ����������������� ����������
{
private:
	Label healthLabel; //������� ��������
	Button menuButton,inventoryButton; //������ ���� � ���������
	StatBar hpBar; //������ ��������
	View view; //������
	TextPanel textPanel; //������ ��� ����������� ������
	Inventory inventory; //���������

public:
	GUI(RenderWindow &window) //���������� 
	{
		healthLabel.init("HEALTH", 20, 25, 10); //������������� ��������� ��������
		menuButton.init("MENU", window.getSize().x - 75,  25,false);
		inventoryButton.init("INV", window.getSize().x - 135, 25,false);
		hpBar.init(25, 35, 200, 10, Color::Red);
		textPanel.init(window);
		inventory.init(window);
	}
	void init(RenderWindow &window)//����� ��� ��������� �������������
	{
		healthLabel.init("HEALTH", 14, 25, 10); 
		menuButton.init("MENU", window.getSize().x - 75, 25, false);
		inventoryButton.init("INV", window.getSize().x - 135, 25, false);
		hpBar.init(25, 35, 200, 10, Color::Red);
		textPanel.init(window);
		inventory.init(window);
	}
	void drawGUI(RenderWindow &window,Player &player,int &gameStete) //��������� GUI
	{
		
		inventory.checkShow(inventoryButton.checkClick(window));  //�������� ������� ���������
		view = window.getView(); //���������� ������� ������
		window.setView(window.getDefaultView()); //������������� �����������
		if (menuButton.checkClick(window)) //��������� �������
			gameStete = GameState::MainMenu;
		healthLabel.draw(window); //������
		menuButton.draw(window);
		inventoryButton.draw(window);
		hpBar.draw(player.getHP(),window);
		inventory.draw(window,player);
		window.setView(view);//���������� ������
	}
	void drawTextPanel(RenderWindow &window,string txt) //����������� ������ �� ����������� ������
	{
		view = window.getView();
		window.setView(window.getDefaultView());
		textPanel.draw(window, txt);
		window.setView(view);
	}
};