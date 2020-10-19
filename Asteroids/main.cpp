#include "Engine.h"
#include "Player.h"
#include "SpaceObject.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Space.h"
#include <cstdlib>
#include <math.h>
#include <time.h>

void main()
{
	engInit();
	srand(time(NULL));
		
	while (engIsOpen())
	{
		Space GameSpace;

		//Put these in a vector if a game over function is wanted, then check if empty, create reset game function.
		GameSpace.SpawnSpaceObject(new Asteroid(100, 100, 30.0f, -60.0f, 16, 0.0f));
		GameSpace.SpawnSpaceObject(new Asteroid(200, 100, 10.0f, -50.0f, 16, 0.0f));
		GameSpace.SpawnSpaceObject(new Asteroid(150, 100, 50.0f, -20.0f, 16, 0.0f));
		GameSpace.SpawnSpaceObject(new Player((ScreenWidth / 2), (ScreenHeight / 2), 0.0f, 0.0f, 1, 0.0f));

		while (engIsOpen())
		{
			if (engGetKeyDown(Key::Escape))
				engClose();

			GameSpace.Update();
			GameSpace.Draw();
			if (GameSpace.bDead)
			{
				engDelay(3000);
				break;
			}
			engUpdate();
		}
	}

	engDestroy();
}