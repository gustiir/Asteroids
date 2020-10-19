#pragma once

class SpaceObject;

const int MAX_SPACEOBJECTS = 250;

class Space
{
public:
	Space();
	~Space();
	SpaceObject* ObjectList[MAX_SPACEOBJECTS];

	void Update();
	void Draw();

	void SpawnSpaceObject(SpaceObject* InSpaceObject);
	void DestorySpaceObject(SpaceObject* InSpaceObject);

	void SplitAsteroids(int InX, int InY, int InSize);

	bool bDead = false;
};