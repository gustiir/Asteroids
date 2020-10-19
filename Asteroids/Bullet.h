#pragma once
#include "SpaceObject.h"

class Bullet : public SpaceObject
{
public:
	Bullet(int InX, int InY, float IndX, float IndY, int InSize, float InAngle)
		: SpaceObject(InX, InY, IndX, IndY, InSize, InAngle) 
		{}


	void Update() override;
	void Draw() override;

private:
	bool DestroyBullet = false;
};