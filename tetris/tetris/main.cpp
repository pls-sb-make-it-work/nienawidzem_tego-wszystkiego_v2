#include <SFML/Graphics.hpp>
#include <time.h>
#include "game.h"

int main()

{
	game dupa;

	dupa.Run();
	dupa.Update();
	dupa.Draw();
	dupa.Check();
	dupa.Move();
	dupa.Rotate();
	dupa.Tick();

	return 0;
}
