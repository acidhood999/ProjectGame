#pragma once
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace std;
using namespace sf;


Text createText(Font& font, int size, Color color) {
	Text text("", font, size);
	text.setFillColor(color);
	return text;
}

void displayText(RenderWindow& window, Text& text, int hcount, Vector2f position) {
	ostringstream playerScoreString;
	playerScoreString << hcount;
	text.setString(L"Собрано камней: " + playerScoreString.str());
	text.setPosition(position);
	window.draw(text);
}

void displaySprite(RenderWindow& window, Sprite& sprite, Vector2f position) {
	sprite.setPosition(position);
	window.draw(sprite);
}



void loadTextures(Image& barI, Texture& characterBackgroundTexture, Texture& d1, Texture& d2, Image& map_image, Image& heroImage) {
	if (!barI.loadFromFile("Game/Igrok/BAR1.png")) {
		cout << "Не удалось загрузить файл 'Game/Igrok/BAR1.png'\n";
	}
	if (!characterBackgroundTexture.loadFromFile("Game/Maps/FON.png")) {
		cout << "Не удалось загрузить файл 'Game/Maps/FON.png'\n";
	}
	if (!d1.loadFromFile("Game/Igrok/DEAD.png")) {
		cout << "Не удалось загрузить файл 'Game/Igrok/DEAD.png'\n";
	}
	if (!d2.loadFromFile("Game/Igrok/WIN.png")) {
		cout << "Не удалось загрузить файл 'Game/Igrok/WIN.png'\n";
	}
	if (!map_image.loadFromFile("Game/Maps/TilesMAP.png")) {
		cout << "Не удалось загрузить файл 'Game/Maps/TilesMAP.png'\n";
	}
	if (!heroImage.loadFromFile("Game/Igrok/igrok.png")) {
		cout << "Не удалось загрузить файл 'Game/Igrok/igrok.png'\n";
	}
}
Sprite createBackgroundSprite(Texture& characterBackgroundTexture) {
	Sprite characterBackgroundSprite(characterBackgroundTexture);
	Vector2u textureSize = characterBackgroundTexture.getSize();
	int mapWidth = WIDTH_MAP * 32;
	int mapHeight = HEIGHT_MAP * 30.7;
	float scaleX = (float)mapWidth / textureSize.x;
	float scaleY = (float)mapHeight / textureSize.y;
	characterBackgroundSprite.setScale(scaleX, scaleY);
	return characterBackgroundSprite;
}
bool isAnyKeyPressed()
{
	for (int i = 0; i < Keyboard::KeyCount; ++i)
	{
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(i)))
			return true;
	}
	return false;
}

bool isAnyKeyPressed1()
{
	for (int i = 0; i < Keyboard::KeyCount; ++i)
	{
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(i)))
			return false;
	}
	return true;
}