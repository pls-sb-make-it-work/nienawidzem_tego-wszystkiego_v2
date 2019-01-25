#include "game.h"

Game::Game()
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

	window.create(VideoMode(320, 480, 32), "Tetris!", Style::Close);

	field = new int*[M];
	for (int i = 0; i < M; i++)
	{
		field[i] = new int[N];

		for (int j = 0; j < N; j++)
			field[i][j] = 0;
	}
}

Game::~Game()
{
	for (int i = 0; i < M; ++i)
		delete[] field[i];

	delete[] field;
}


void Game::Update()
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
				switch (e.key.code)
				{
				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::Up:
					Rotate();
					break;
				case Keyboard::Left:
					Move(-1);
					break;
				case Keyboard::Right:
					Move(1);
					break;
				default:
					break;
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;
		else
			delay = 0.3;

		Draw();
		Tick();
		Lines();
	}
}

void Game::Move(int direction)
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += direction;
	}

	if (!Check())
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
}

void Game::Rotate()
{
	Point p = a[1]; //center of rotation

	for (int i = 0; i < 4; i++)
	{
		int x = a[i].y - p.y;
		int y = a[i].x - p.x;
		a[i].x = p.x - x;
		a[i].y = p.y + y;
	}

	if (!Check())
		for (int i = 0; i < 4; i++)
			a[i] = b[i];
}

void Game::Tick()
{
	if (timer > delay)
	{
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].y += 1;
		}

		if (!Check())
		{
			for (int i = 0; i < 4; i++)
				field[b[i].y][b[i].x] = colorNum;

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

void Game::Lines()
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

		if (count < N)
			k--;
	}
}

void Game::Draw()
{
	window.clear(Color::White);
	window.draw(background);

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
		{
			if (field[i][j] == 0)
				continue;

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


bool Game::Check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return 0;
		else if (field[a[i].y][a[i].x])
			return 0;

	return 1;
};

bool Game::End()
{
	for (int i = 0; i < N; i++)
		if (field[M][i] == 1)
			return 1;
	return 0;
}
