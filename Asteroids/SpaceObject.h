#pragma once

class Space;

class SpaceObject
{
public:
	SpaceObject(int InX, int InY, float IndX, float IndY, int InSize, float InAngle);
	virtual void Update();
	virtual void Draw();

	float X;
	float Y;
	float dX;
	float dY;
	int Size;
	float Angle;

	Space* MySpace;
};