#pragma once
#include "SpaceObject.h"
#include "Bullet.h"
#include <vector>

class Player : public SpaceObject
{
public:
	Player(int InX, int InY, float IndX, float IndY, int InSize, float InAngle);

	void Update() override;
	void Draw() override;

private:
	std::vector<std::pair<float, float>> vecModelShip;
};