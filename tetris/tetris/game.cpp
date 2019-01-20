#include "game.h"
//using namespace sf;

game::game()
{
	srand(time(0));
	t1.loadFromFile("obrazy/klocek.png");
	t2.loadFromFile("obrazy/tlo.png");
	t3.loadFromFile("obrazy/ramka.png");

	s.setTexture(t1);
	background.setTexture(t2);
	frame.setTexture(t3);

	a[0].x = 0, a[0].y = 1;
	a[1].x = 1, a[1].y = 1;
	a[2].x = 1, a[2].y = 2;
	a[3].x = 1, a[3].y = 3;
}

game::~game()
{
}

void game::Run()
{
	window.create(VideoMode(320, 480, 32), "The Game!", Style::Close);

}

void game::Update()
{
	while (window.isOpen())

	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		while (window.pollEvent(e))

		{
			if (e.type == Event::Closed)

				window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Up) rotate = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

		Move();
		Rotate();
		Tick();
		Lines();
		Draw();

	}
}

void game::Move()
{
	for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
	if (!Check()) for (int i = 0; i < 4; i++) a[i] = b[i];
}

void game::Rotate()
{
	if (rotate)
	{
		point p = a[1]; //center of rotation
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!Check()) for (int i = 0; i < 4; i++) a[i] = b[i];
	}
}

void game::Tick()
{
	if (timer > delay)
	{
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

		if (!Check())
		{
			for (int i = 0; i < 4; i++) 
				field[b[i].y][b[i].x] = colorNum;
				//zakomentowanie tego nie psuje gry xD

			colorNum = 1 + rand() % 7;
			int n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}

		timer = 0;
	}
}

void game::Lines()
{
	int k = M - 1;
	for (int i = M - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
		}
		if (count < N) k--;
	}

	dx = 0; rotate = 0; delay = 0.3;
}

void game::Draw()
{
	//Sprite s(t1), background(t2), frame(t3);

	window.clear(Color::White);
	window.draw(background);

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
		{
			if (field[i][j] == 0) continue;
			s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
			s.setPosition(j * 18, i * 18);
			s.move(28, 31); //offset
			window.draw(s);
		}

	for (int i = 0; i < 4; i++)
	{
		s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
		s.setPosition(a[i].x * 18, a[i].y * 18);
		s.move(28, 31); //offset
		window.draw(s);
	}

	window.draw(frame);
	window.display();
}


bool game::Check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;
};
