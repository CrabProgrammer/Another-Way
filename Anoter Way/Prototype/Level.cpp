#include"Header.h"
bool Level::LoadFromFile(string filename)//двоеточия-обращение к методам класса вне класса 
{
	layers.clear();
	objects.clear();

	tinyxml2::XMLDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument												 
	levelFile.LoadFile(filename.c_str()); // загружаем XML-карту
	tinyxml2::XMLElement *map;// работаем с контейнером map
	map = levelFile.FirstChildElement("map");
	width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
	height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в 
	tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
	tileHeight = atoi(map->Attribute("tileheight"));

	// Берем описание тайлсета и идентификатор первого тайла
	tinyxml2::XMLElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	// source - путь до картинки в контейнере image
	tinyxml2::XMLElement *image;
	image = tilesetElement->FirstChildElement("image");
	string imagepath = image->Attribute("source");
	// пытаемся загрузить тайлсет
	sf::Image img;
	img.loadFromFile("resources/Maps/" + imagepath);
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);//сглаживание

								  // получаем количество столбцов и строк тайлсета
	int columns = tilesetImage.getSize().x / (tileWidth);
	int rows = tilesetImage.getSize().y / (tileHeight);
	// вектор из прямоугольников изображений (TextureRect)
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

	// работа со слоями
	tinyxml2::XMLElement *layerElement;
	layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		Layer layer;
		//  контейнер <data> 
		tinyxml2::XMLElement *layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		//  контейнер <tile> - описание тайлов каждого слоя
		tinyxml2::XMLElement *tileElement;
		tileElement = layerDataElement->FirstChildElement("tile");
		int x = 0;
		int y = 0;

		while (tileElement)
		{
			int tileGID = atoi(tileElement->Attribute("gid"));
			int subRectToUse = tileGID - firstTileID;

			// Устанавливаем TextureRect каждого тайла
			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);

				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, 255));

				layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
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
	// работа с объектами
	tinyxml2::XMLElement *objectGroupElement;

	objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
		//  контейнер <object>
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
			// экземпляр объекта
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
	// только первый объект с заданным именем
	for (int i = 0; i < objects.size(); i++)
		if (objects[i].name == name)
			return objects[i];
}

vector<Object> Level::GetObjects(string name)
{
	// все объекты с заданным именем
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