#include "Bullet.h"
#include "Engine.h"
#include "Space.h"
#include "Type.h"
#include "Asteroid.h"

void Bullet::Update()
{
	X += dX * engDelta();
	Y += dY * engDelta();

	//Collision check with asteroids
	for (int i = 0; i < MAX_SPACEOBJECTS; i++)
	{
		SpaceObject* SpaceObjectPtr = MySpace->ObjectList[i];

		if (SpaceObjectPtr == nullptr ||
			SpaceObjectPtr == this)
			continue;

		if (IsA<Asteroid>(SpaceObjectPtr))
		{
			if (engIsPointInsideCircle(SpaceObjectPtr->X, SpaceObjectPtr->Y, SpaceObjectPtr->Size, X, Y))
		{		
				//Asteroids should split into smaller ones until they are tiny
				if (SpaceObjectPtr->Size > 4)
				{
					MySpace->SplitAsteroids(SpaceObjectPtr->X, SpaceObjectPtr->Y, SpaceObjectPtr->Size);
				}

				MySpace->DestorySpaceObject(SpaceObjectPtr);
				//Add score here if wanted
				MySpace->DestorySpaceObject(this);
				return;
			}
		}

		//If the bullet is off screen destroy it
		if ((X < 0.0f) || (X >= (float)ScreenWidth) || (Y < 0.0f) || (Y >= (float)ScreenHeight))
		{
			MySpace->DestorySpaceObject(this);
			return;
		}
	}
}

void Bullet::Draw()
{
	engDrawPixel(X, Y);
}

