#include"Header.h"
bool Level::LoadFromFile(string filename)//���������-��������� � ������� ������ ��� ������ 
{
	layers.clear();
	objects.clear();

	tinyxml2::XMLDocument levelFile(filename.c_str());//��������� ���� � TiXmlDocument												 
	levelFile.LoadFile(filename.c_str()); // ��������� XML-�����
	tinyxml2::XMLElement *map;// �������� � ����������� map
	map = levelFile.FirstChildElement("map");
	width = atoi(map->Attribute("width"));//��������� �� ����� ����� �� ��������
	height = atoi(map->Attribute("height"));//�� ��������, ������� �������� ��� ������ � 
	tileWidth = atoi(map->Attribute("tilewidth"));//������� ���������
	tileHeight = atoi(map->Attribute("tileheight"));

	// ����� �������� �������� � ������������� ������� �����
	tinyxml2::XMLElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - ���� �� �������� � ���������� image
	tinyxml2::XMLElement *image;
	image = tilesetElement->FirstChildElement("image");
	string imagepath = image->Attribute("source");
	// �������� ��������� �������
	sf::Image img;
	img.loadFromFile("resources/Maps/" + imagepath);
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//�����������

								  // �������� ���������� �������� � ����� ��������
	int columns = tilesetImage.getSize().x / (tileWidth);
	int rows = tilesetImage.getSize().y / (tileHeight);
	// ������ �� ��������������� ����������� (TextureRect)
	std::vector<sf::Rect<int>> subRects;
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;

			rect.left = (x)* tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	// ������ �� ������
	tinyxml2::XMLElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;
		// ���������� <data> 
		tinyxml2::XMLElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		// ���������� <tile> - �������� ������ ������� ����
		tinyxml2::XMLElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");
		int x = 0;
		int y = 0;

		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;

			// ������������� TextureRect ������� �����
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);

				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, 255));

				layer.tiles.push_back(sprite);//���������� � ���� ������� ������
			}

			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}
		layers.push_back(layer);
		layerElement = layerElement->NextSiblingElement("layer");	
	}
	// ������ � ���������
	tinyxml2::XMLElement *objectGroupElement;

	objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
		// ���������� <object>
		tinyxml2::XMLElement *objectElement;
		objectElement = objectGroupElement->FirstChildElement("object");
		while (objectElement)
		{
			std::string objectName;
			if (objectElement->Attribute("name") != NULL)
			{
				objectName = objectElement->Attribute("name");
			}
			int x = atoi(objectElement->Attribute("x"));
			int y = atoi(objectElement->Attribute("y"));

			int width, height;

			if (objectElement->Attribute("width") != NULL)
			{
				width = atoi(objectElement->Attribute("width"));
				height = atoi(objectElement->Attribute("height"));
			}
			else
			{
				width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
				height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
			}
			// ��������� �������
			Object object;
			object.name = objectName;
			sf::Rect <float> objectRect;
			objectRect.top = y;
			objectRect.left = x;
			objectRect.height = height;
			objectRect.width = width;
			object.rect = objectRect;
			objects.push_back(object);
			objectElement = objectElement->NextSiblingElement("object");
		}
		objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
	}
	return true;
}

Object Level::GetObject(string name)
{
	// ������ ������ ������ � �������� ������
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}

vector<Object> Level::GetObjects(string name)
{
	// ��� ������� � �������� ������
	vector<Object> vec;
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}

vector<Object> Level::GetAllObjects()
{
	return objects;
}

void Level::Draw(RenderWindow &window,Player &player, vector<Enemy>&enemy)
{
	for (int layer = 0; layer < layers.size(); layer++)
	{
		if (layer == layers.size() - 1)
		{
			player.drawSprites(window);
			for (int i = 0; i < enemy.size(); i++)
				enemy[i].drawSprites(window);
		}
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		{
			if (layers[layer].tiles[tile].getPosition().x > player.getPosition().x - 220 && layers[layer].tiles[tile].getPosition().x < player.getPosition().x + 220)
				if(layers[layer].tiles[tile].getPosition().y > player.getPosition().y - 200 && layers[layer].tiles[tile].getPosition().y < player.getPosition().y + 200)
					window.draw(layers[layer].tiles[tile]);
		}
	}
}