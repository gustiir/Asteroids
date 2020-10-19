#include "SpaceObject.h"
#include "Engine.h"


SpaceObject::SpaceObject(int InX, int InY, float IndX, float IndY, int InSize, float InAngle) 
: X(InX), Y(InY), dX(IndX), dY(IndY), Size(InSize), Angle(InAngle)
{}
void SpaceObject::Update()
{}

void SpaceObject::Draw()
{
	engSetColor(0xFFFFFFFF);
}