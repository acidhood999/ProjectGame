#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void menu(RenderWindow& window)
{

    Image icon;
    if (!icon.loadFromFile("Game/Menu/logo.png")) {
        cout << "Не удалось загрузить 'Game/Menu/logo.png'\n";
    }
    Texture characterBackgroundTexture;
    if (!characterBackgroundTexture.loadFromFile("Game/Menu/FON.png")) {
        cout << "Не удалось загрузить 'Game/Menu/FON.png'\n";
    }
    Texture menuTexture1;
    if (!menuTexture1.loadFromFile("Game/Menu/NEWGM.png")) {
        cout << "Не удалось загрузить 'Game/Menu/NEWGM.png'\n";
    }
    Texture menuTexture2;
    if (!menuTexture2.loadFromFile("Game/Menu/EXIT.png")) {
        cout << "Не удалось загрузить 'Game/Menu/EXIT.png'\n";
    }


    window.setIcon(32, 32, icon.getPixelsPtr());


    Sprite characterBackgroundSprite(characterBackgroundTexture);
    Sprite menu1(menuTexture1), menu2(menuTexture2);


    menu1.setPosition(770, 400);
    menu2.setPosition(881, 475);


    Vector2u tex = characterBackgroundTexture.getSize();
    int mapW = WIDTH_MAP * 32;
    int mapH = HEIGHT_MAP * 45;
    characterBackgroundSprite.setScale((float)mapW / tex.x, (float)mapH / tex.y);

    bool isMenu = true;
    int menuNum = 0;

    while (isMenu)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(129, 181, 221));

        if (IntRect(770, 400, 331, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Black); menuNum = 1; }
        if (IntRect(881, 475, 111, 46).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Black); menuNum = 2; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;
            if (menuNum == 2) { window.close(); isMenu = false; }
        }

        window.draw(characterBackgroundSprite);
        window.draw(menu1);
        window.draw(menu2);
        window.display();
    }
}
