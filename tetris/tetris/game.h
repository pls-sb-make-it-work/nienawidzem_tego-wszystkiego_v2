#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

class game
{private:
	struct point
	{
		int x, y;
	} a[4], b[4];

	RenderWindow window;
	Texture t1, t2, t3;

	int dx = 0;
	bool rotate = 0;
	int colorNum = 1;

	int M = 20;
	int N = 10;


	int field[20][10] = { 0 };

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

	float timer = 0;
	float delay = 0.3;

	Clock clock;

	Event e;

public:
	game();
	~game();
	void Run();
	void Update();
	void Move();
	void Rotate();
	void Tick();
	void Lines();
	void Draw();
	bool Check();
};



