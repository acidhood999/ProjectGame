#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
View view;
const float viewHeight = 1080.0f;

View setPlayerCoordinateForView(float x, float y)
{

    float tempX = x; float tempY = y;

    float mapWidth = 1920.0f;

    float mapHeight = 1080.0f;

    if (x < 390) tempX = 390;
    if (y < 240) tempY = 240;
    if (x > mapWidth - 390) tempX = mapWidth - 390;
    if (y > mapHeight - 240) tempY = mapHeight - 240;
    if (y > mapHeight - viewHeight / 2) tempY = mapHeight - viewHeight / 2;

    view.setCenter(tempX, tempY);
    return view;
}