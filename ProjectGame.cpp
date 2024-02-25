// ProjectGame.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include "Menu.h"
#include <stdio.h>
#include "Menu.h"
#include "HpBar.h"
#include "Entity.h"
#include <fstream>

using namespace std;
using namespace sf;





bool start() {
	RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);
	view.reset(FloatRect(0, 0, 768, 432));

	menu(window);


	Font font;
	font.loadFromFile("Game/Shrift/shrift.otf");
	Text text = createText(font, 10, Color::Magenta);


	Image barI;
	Texture characterBackgroundTexture;
	Texture d1, d2;
	Image map_image;
	Image heroImage;
	loadTextures(barI, characterBackgroundTexture, d1, d2, map_image, heroImage);

	Sprite characterBackgroundSprite = createBackgroundSprite(characterBackgroundTexture);

	Sprite dead(d1);
	dead.setPosition(770, 400);
	Sprite win(d2);
	win.setPosition(770, 400);
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Player p(heroImage, 50, 700, 30, 51, "Player1");


	ifstream loadFile("savegame.txt");
	if (loadFile.is_open()) {
		loadFile >> p.x >> p.y >> p.health;
		loadFile.close();
	}
	static float infoDisplayTime;

	Bar a(barI);
	float frame1{}, frame2{};
	Life a1;
	Clock clock;
	vector<string> originalTileMap = TileMap;
	Texture infoTexture;
	infoTexture.loadFromFile("Game/Maps/info.png");
	Sprite infoSprite(infoTexture);
	static Clock infoClock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{


				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Tab)
			{

				ofstream saveFile("savegame.txt");
				saveFile << 50 << " " << 700 << " " << 100;
				TileMap = originalTileMap;
				saveFile.close();

			}


			p.handleInput(event);
		}
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			ofstream saveFile("savegame.txt");
			if (saveFile.is_open()) {
				saveFile << p.x << " " << p.y << " " << p.health << " " << infoDisplayTime;
				saveFile.close();
			}
			else {

				cerr << "Ошибка: Не удалось открыть файл для сохранения игры." << endl;
			}
			return false;
		}


		window.setView(view);
		setPlayerCoordinateForView(p.x, p.y);
		a1.update(p.health);
		a.updateBarPosition();




		window.draw(characterBackgroundSprite);

		drawMap(window, s_map, time, frame1, frame2);
		window.draw(a.sprite);
		window.draw(a1.s);
		a1.draw(window);
		displayText(window, text, p.hcount, view.getCenter() - Vector2f(383, 125));

		if (infoClock.getElapsedTime().asSeconds() < 5)
		{
			infoSprite.setPosition(view.getCenter().x - 398, view.getCenter().y - 210);
			window.draw(infoSprite);
			infoDisplayTime = infoClock.getElapsedTime().asSeconds();

		}
		else
		{
			p.update(time);
		}



		window.draw(p.sprite);







		if (p.hcount != 5 && p.health <= 0) {
			displaySprite(window, dead, view.getCenter() - Vector2f(95, 30));
		}
		if (p.hcount >= 5) {
			displaySprite(window, win, view.getCenter() - Vector2f(80, 30));
			p.health = 100;
		}
		window.display();
	}
	return 0;
}

void gameRunning()
{
	if (start())
	{
		gameRunning();
	}
}
int main()
{
	gameRunning();
}
