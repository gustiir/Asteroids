#include "Asteroid.h"
#include "Engine.h"
#include "Type.h"


Asteroid::Asteroid(int InX, int InY, float IndX, float IndY, int InSize, float InAngle) 
	: SpaceObject(InX, InY, IndX, IndY, InSize, InAngle)
{
	int verts = 20;
	for (int i =0; i < verts; i++)
	{
		float radius = (float)rand() / RAND_MAX * 0.4f + 0.8f;
											/*2 x PI*/
		float a = ((float)i / (float)verts) * 6.28318f;
		vecModelAsteroid.push_back(std::make_pair(radius *sinf(a), radius * cosf(a)));
	}
}

void Asteroid::Update()
{
	X += dX * engDelta();
	Y += dY * engDelta();

	engWrapCoordinates(X, Y, X, Y);
}

void Asteroid::Draw()
{
	engDrawWireFrame(vecModelAsteroid, X, Y, Angle, Size);
}

