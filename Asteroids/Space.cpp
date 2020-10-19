#include "Space.h"
#include "Engine.h"
#include "SpaceObject.h"
#include "Asteroid.h"

Space::Space()
{
	for (int i = 0; i < MAX_SPACEOBJECTS; i++)
		ObjectList[i] = nullptr;
}

Space::~Space()
{
	for (int i = 0; i < MAX_SPACEOBJECTS; i++)
	{
		if (ObjectList[i] != nullptr)
		{
			delete ObjectList[i];
			ObjectList[i] = nullptr;
		}
	}
}

void Space::Update()
{
	for (int i = 0; i < MAX_SPACEOBJECTS; i++)
	{
		if (ObjectList[i] == nullptr)
			continue;

		ObjectList[i]->Update();
	}
}

void Space::Draw()
{
	for (int i = 0; i < MAX_SPACEOBJECTS; i++)
	{
		if (ObjectList[i] == nullptr)
			continue;

		ObjectList[i]->Draw();
	}
}

void Space::SpawnSpaceObject(SpaceObject* InSpaceObject)
{
	for (int i = 0; i < MAX_SPACEOBJECTS; i++)
	{
		if (ObjectList[i] == nullptr)
		{
			ObjectList[i] = InSpaceObject;
			break;
		}
	}

	InSpaceObject->MySpace = this;
}

void Space::DestorySpaceObject(SpaceObject* InSpaceObject)
{
	for (int i = 0; i < MAX_SPACEOBJECTS; i++)
	{
		if (ObjectList[i] == InSpaceObject)
		{
			ObjectList[i] = nullptr;
			delete InSpaceObject;

			break;
		}
	}
}

void Space::SplitAsteroids(int InX, int InY, int InSize)
{
														/*2 x PI*/
	float tmpAngle1 = ((float)rand() / (float)RAND_MAX) * 6.28318f;
	float tmpAngle2 = ((float)rand() / (float)RAND_MAX) * 6.28318f;

	SpawnSpaceObject(new Asteroid(InX, InY, 10.0f * sinf(tmpAngle1), 10.0f * cosf(tmpAngle1), InSize >> 1, 0.0f));
	SpawnSpaceObject(new Asteroid(InX, InY, 10.0f * sinf(tmpAngle2), 10.0f * cosf(tmpAngle2), InSize >> 1, 0.0f));
}
