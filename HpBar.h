#pragma once
#include <SFML/Graphics.hpp>
#include "view.h"
using namespace sf;
using namespace std;

class Bar
{
public:
	Texture texture;
	Sprite sprite;

	Bar(const Image& image)
	{
		if (!texture.loadFromImage(image)) {
			cout << "Не удалось загрузить текстуру для Bar.\n";
		}
		sprite.setTexture(texture);
		sprite.setPosition(5, 323);
		sprite.setTextureRect(IntRect(0, 0, 26, 90));
	}
	void updateBarPosition() {
		Vector2f viewCenter = view.getCenter();
		sprite.setPosition(viewCenter - Vector2f(view.getSize().x / 2, view.getSize().y / 2));
	}
};

class Life
{
public:
	Image image;
	Texture t;
	Sprite s;
	Sprite s2;
	int max;
	RectangleShape bar;

	Life()
	{
		if (!image.loadFromFile("Game/Igrok/HP1.png")) {
			cout << "Не удалось загрузить изображение для Life.\n";
		}
		image.createMaskFromColor(Color(50, 96, 166));
		if (!t.loadFromImage(image)) {
			cout << "Не удалось загрузить текстуру для Life.\n";
		}
		s.setTexture(t);
		s.setTextureRect(IntRect(4, 0, 11, 81));
		s2.setTexture(t);
		s2.setTextureRect(IntRect(18, 0, 11, 81));


		max = 100;
	}

	void update(int k)
	{
		if (k > 0 && k <= max)
		{
			s2.setTextureRect(IntRect(18, 0, 10, (max - k) * 82 / max));
		}
		else
			s2.setTextureRect(IntRect(18, 0, 10, 82));
	}
	void draw(RenderWindow& window)
	{
		Vector2f viewCenter = view.getCenter();
		Vector2f offset = Vector2f(30, 4);
		s.setPosition(viewCenter - view.getSize() / 2.f + offset);
		s2.setPosition(viewCenter - view.getSize() / 2.f + offset);

		window.draw(s);
		window.draw(s2);
	}

};

