#pragma once
#include"Header.h"
class Inventory : private Panel //��������� ���� ������ Panel
{
private:
	bool isShown; //������������ ��
	bool spriteInit; //������������� ��������
	Texture texture; 
	vector<Sprite> sprites; //������� ����������
	Label damage; //�������
	Label protection;
	Label attackSpeed;
	Label attackRange;
	Arrow leftArrow;// �������
	Arrow rightArrow;
public:
	void init(RenderWindow &window) //�������������
	{
		texture.loadFromFile("resources/Characters/Characters.png"); //�������� ��������
		spriteInit = false;
		text.setString("INVENTORY"); //������� �� �������� ������
		Panel::init(window); //������������� ������
		isShown=false; // �� ������������
		damage.init("Damage  ->", 17, getPos().x + 30, getPos().y + 275); //������������� ����� � ����������
		protection.init("Defence ->", 17, getPos().x + 30, getPos().y + 302);
		attackSpeed.init("Att. Speed ->", 17, getPos().x + 30, getPos().y + 327);
		attackRange.init("Att. Range ->", 17, getPos().x + 30, getPos().y + 352);
		leftArrow.init("resources/img/arrowLeft.png", getPos().x + 90,getPos().y+170); //�������������� �������
		rightArrow.init("resources/img/arrowRight.png", getPos().x + 270, getPos().y + 170);
	}
	void checkShow(bool show) //���� ������������
	{
		if (show)
			isShown = !isShown;
	}
	void draw(RenderWindow &window,Player &player) //���������� ���������
	{
		if (isShown)
		{
			if (spriteInit == false) //���� �� ���� �������������
			{
				initDrawEquip(player);
				spriteInit = true;
			}
			Panel::draw(window); //��������� ���������
			damage.draw(window,player.getDMG());
			protection.draw(window, player.getProtection());
			attackSpeed.draw(window, player.getAttackSpeed());
			attackRange.draw(window, player.getAttackRange());
			leftArrow.draw(window);
			rightArrow.draw(window);
			if (leftArrow.checkClick(window) == true) //�������� �� ������� �������
			{
				if (player.getCurrentSetID() - 1 >= 0)
				{
					player.setEquip(player.getCurrentSetID() - 1);
					sprites.clear();
					initDrawEquip(player);
					player.getCurrentEquip().init();
				}
			}
			if (rightArrow.checkClick(window) == true)
			{
				if (player.getCurrentSetID() + 1 < player.getEquipSets().size())
				{
					player.setEquip(player.getCurrentSetID() + 1);
					sprites.clear();
					initDrawEquip(player);
					player.getCurrentEquip().init();

				}
			}
			for (int i = 0; i < 6; i++) //��������� ����������
				window.draw(sprites[i]);
		}
	}	
	void initDrawEquip(Player &player) //������������� ����������
	{
		Sprite tmp;
		tmp.setPosition(getPos().x + 170, getPos().y + 150);
		tmp.setTexture(texture);
		tmp.setScale(4.f, 4.f); //������������ ������� � 4 ����
		tmp.setTextureRect(IntRect(player.getCurrentEquip().getlegsID() * 16 - int(player.getCurrentEquip().getlegsID() / 57) * 16 * 57, int((player.getCurrentEquip().getlegsID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(player.getCurrentEquip().getShoesID() * 16 - int(player.getCurrentEquip().getShoesID() / 57) * 16 * 57, int((player.getCurrentEquip().getShoesID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(player.getCurrentEquip().getArmorID() * 16 - int(player.getCurrentEquip().getArmorID() / 57) * 16 * 57, int((player.getCurrentEquip().getArmorID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(player.getCurrentEquip().getHelmetID() * 16 - int(player.getCurrentEquip().getHelmetID() / 57) * 16 * 57, int((player.getCurrentEquip().getHelmetID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(player.getCurrentEquip().getWeaponID() * 16 - int(player.getCurrentEquip().getWeaponID() / 57) * 16 * 57, int((player.getCurrentEquip().getWeaponID() / 57) * 16), 16, 16));
		sprites.push_back(tmp);
		tmp.setTextureRect(IntRect(player.getCurrentEquip().getShieldID() * 16 - int(player.getCurrentEquip().getShieldID() / 57) * 16 * 57, int((player.getCurrentEquip().getShieldID() / 56) * 16), 16, 16));
		sprites.push_back(tmp);
	}
};