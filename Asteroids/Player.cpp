#include "Player.h"
#include "Engine.h"
#include <math.h>
#include "Space.h"
#include "Type.h"
#include "Asteroid.h"

Player::Player(int InX, int InY, float IndX, float IndY, int InSize, float InAngle)
	: SpaceObject(InX, InY, IndX, IndY, InSize, InAngle)
{
	//Ship triangle
	vecModelShip =
	{
	{ 0.0f,	-5.0f},
	{-2.5f, +2.5f},
	{+2.5f, +2.5f}
	};
}

void Player::Update()
{

	if (engGetKey(Key::Right))
	{
		Angle += 5.0f * engDelta();
	}
	if (engGetKey(Key::Left))
	{
		Angle -= 5.0f * engDelta();
	}
	if (engGetKey(Key::Up))
	{
		dX += sin(Angle) * 40.0f * engDelta();
		dY += -cos(Angle) * 40.0f * engDelta();
	}

	if (engGetKeyUp(Key::Space))
	{
		MySpace->SpawnSpaceObject(new Bullet(X, Y, (100.0f * sinf(Angle)), (-100.0f * cosf(Angle)), 1, 0.0f));
	}

	X += dX * engDelta();
	Y += dY * engDelta();

	engWrapCoordinates(X, Y, X, Y);

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
				MySpace->bDead = true;
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

void Player::Draw()
{
	engDrawWireFrame(vecModelShip, X, Y, Angle, Size);
}

