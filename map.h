#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

const int HEIGHT_MAP = 24;
const int WIDTH_MAP = 60;

vector<string> TileMap =
{
	"000000000000000000000000000000000000000000000000000000000000",
	"0                                                          0",
	"0          0 0              00                           f 0",
	"0         00000            0  0                            0",
	"0          000            0    0                           0",
	"0           0     f      0      0                          0",
	"0                       0 fhf    0                         0",
	"0  f                   0000000    0                  0000000",
	"0                      0      0   0       f0h0             0",
	"0                                 0       00000  0       fh0",
	"0             00f                f0        000   0000   0000",
	"0      0 f0  0  0      000000000000         0     f 0      0",
	"0       00                                          00     0",
	"0                             f                     0f     0",
	"000                00h                     f        0h     0",
	"0                    0                              000    0",
	"0                    0                                    00",
	"0      00          00              00                     00",
	"0                                                          0",
	"0   f        00        f    00            00    0     0    0",
	"0                      0                        0  0  0    0",
	"0                     000                       0  0  0    0",
	"0         00         00000          0           0ff0ff0ffff0",
	"000000000000000000000000000000000000000000000000000000000000",
};

void drawMap(RenderWindow& window, Sprite& s_map, float time, float& frame1, float& frame2) {
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  continue;
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(361, 536, 32, 32));

			if ((TileMap[i][j] == 'h'))
			{

				frame1 += 0.0009 * time;

				if (frame1 > 8)
				{
					frame1 = 0;

				}
				s_map.setTextureRect(IntRect(548 + int(frame1) * 24, 414, 20, 20));

			}

			if ((TileMap[i][j] == 'f'))
			{
				frame2 += 0.0005 * time;

				if (frame2 > 3)
				{
					frame2 = 0;

				}

				s_map.setTextureRect(IntRect(542 + int(frame2) * 32, 470, 31, 31));
			}

			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}
}
