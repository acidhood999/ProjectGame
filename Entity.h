#pragma once
#include "Function.h"

using namespace sf;
using namespace std;

class Entity {
public:
	bool animationPlayed = false;
	Keyboard::Key lastKeyPressed;
	Keyboard::Key secondLastKeyPressed;
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	float frame = 0;

	Clock rotationClock;
	bool isRotating = true;
	String name;
	virtual void handleInput(const Event& event) {}
	Entity(Image& image, float X, float Y, int W, int H, String Name) : x(X), y(Y), w(W), h(H), name(Name), moveTimer(0), speed(0), health(100), dx(0), dy(0), life(true), onGround(false), isMove(false) {
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	virtual ~Entity() {}
};

class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay } state;
	int playerScore; int hcount = 0;

	Player(Image& image, float X, float Y, int W, int H, String Name) : Entity(image, X, Y, W, H, Name), playerScore(0), state(stay) {
		if (name == "Player1") {
			sprite.setTextureRect(IntRect(75, 70, w, h));
		}
	}

	void handleInput(const Event& event) override {
		if (event.type == Event::KeyPressed && (event.key.code == Keyboard::A || event.key.code == Keyboard::D)) {
			secondLastKeyPressed = lastKeyPressed;
			lastKeyPressed = event.key.code;
		}
	}

	Keyboard::Key getLastKeyPressed() const {
		return lastKeyPressed;
	}

	Keyboard::Key getSecondLastKeyPressed() const {
		return secondLastKeyPressed;
	}

	void control(float time)
	{
		if (isAnyKeyPressed && life)
		{
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))
			{
				state = Keyboard::isKeyPressed(Keyboard::A) ? left : right;
				speed = Keyboard::isKeyPressed(Keyboard::LShift) ? 0.2 : 0.1;
				frame += 0.005 * time;
				if (frame > 8) frame = 0;
				if (Keyboard::isKeyPressed(Keyboard::LShift)) {
					if (frame > 12 || frame < 4) frame = 5;
					sprite.setTextureRect(IntRect(50 * int(frame) + 5 + (Keyboard::isKeyPressed(Keyboard::A) ? 45 : 0), 275, Keyboard::isKeyPressed(Keyboard::A) ? -45 : 45, 50));
				}
				else {
					sprite.setTextureRect(IntRect(32 * int(frame) + 18 + (Keyboard::isKeyPressed(Keyboard::A) ? 30 : 0), 131, Keyboard::isKeyPressed(Keyboard::A) ? -30 : 30, 51));
				}
			}

			if ((Keyboard::isKeyPressed(Keyboard::S)) && (onGround))
			{
				sprite.setTextureRect(IntRect(75, 70, 30, 51));
				state = jump; dy = -0.6; onGround = false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::D) && Keyboard::Keyboard::isKeyPressed(Keyboard::S)) && (onGround))
			{
				sprite.setTextureRect(IntRect(int(frame) + 55, 275, 45, 50));
				state = jump; dy = -0.6; onGround = false;
			}

			if ((Keyboard::isKeyPressed(Keyboard::A) && (Keyboard::isKeyPressed(Keyboard::D))))
			{
				speed = 0;
				sprite.setTextureRect(IntRect(75, 70, 30, 50));
			}

			if (getLastKeyPressed() == Keyboard::A || getLastKeyPressed() == Keyboard::D)
			{
				if (isAnyKeyPressed1())
				{
					frame += 0.005 * time;
					if (frame > 14) frame = 0;
					sprite.setTextureRect(IntRect(35 * int(frame) + 15 + (getLastKeyPressed() == Keyboard::A ? 35 : 0), 9, getLastKeyPressed() == Keyboard::A ? -35 : 35, 52));
				}
			}
		}
		if (!life)
		{
			if (getLastKeyPressed() == Keyboard::D || getLastKeyPressed() == Keyboard::A)
			{
				if (!animationPlayed) {
					frame += 0.005 * time;

					if (frame > 5) {
						frame = 0;
						animationPlayed = true;
					}
					else {
						sprite.setTextureRect(IntRect(35 * int(frame) + 27 + (getLastKeyPressed() == Keyboard::A ? 35 : 0), 662, getLastKeyPressed() == Keyboard::A ? -35 : 35, 52));
					}
				}
			}
		}

	}



	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (Dy > 0) { y = i * 32 - h; dy = 0; onGround = true; }
					else if (Dy < 0) { y = i * 32 + 32; dy = 0; }

					if (Dx > 0) { x = j * 32 - w; }
					else if (Dx < 0) { x = j * 32 + 32; }
				}
			}
	}




	void update(float time)
	{
		control(time);
		dx = (state == right ? speed : (state == left ? -speed : 0));
		x += dx * time;
		checkCollisionWithMap(dx, 0);
		y += dy * time;
		checkCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);

		if (health <= 1)
		{
			if (isRotating && rotationClock.getElapsedTime().asSeconds() < 3) {
				view.rotate(0.001);
			}
			else {
				isRotating = false;
			}
			life = false;
			speed = 0;
		}

		if (!isMove) { speed = 0; }
		dy += 0.0015 * time;
		interactionWithMap();
	}

	void interactionWithMap()
	{

		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == '0')
				{

					if (dx > 0)
					{
						x = j * 32 - w;
					}
					if (dx < 0)
					{
						x = j * 32 + 32;
					}
				}

				if (TileMap[i][j] == 'h')
				{

					TileMap[i][j] = ' ';
					hcount++;
				}
				if (TileMap[i][j] == 'f')
				{

					health -= 20;

					TileMap[i][j] = ' ';
				}
			}
	}

	~Player() override {}
};
