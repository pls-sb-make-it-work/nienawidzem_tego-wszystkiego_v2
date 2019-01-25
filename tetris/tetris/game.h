#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include "point.h"
using namespace sf;

class Game
{
private:

	Point a[4], b[4];
	RenderWindow window;
	Texture t1, t2, t3;
	Clock clock;
	Event e;
	Sprite s, background, frame;

	int colorNum = 1;
	float timer = 0;
	float delay = 0.3;

	const int M = 20; // height
	const int N = 10; // width

	int **field; // 2d array in constructor

	int figures[7][4] =
	{
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};

public:
	Game();
	~Game();

	void Update();
	void Move(int direction);
	void Rotate();
	void Tick();
	void Lines();
	void Draw();
	bool Check();
	bool End();
};



