#pragma once
#include "SpaceObject.h"
#include <vector>


class Asteroid : public SpaceObject
{
public:
	Asteroid(int InX, int InY, float IndX, float IndY, int InSize, float InAngle);

	void Update() override;
	void Draw() override;

private:
	std::vector<std::pair<float, float>> vecModelAsteroid;
};