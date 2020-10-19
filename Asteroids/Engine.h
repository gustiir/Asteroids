#pragma once
#include "Key.h"
#include <vector>



typedef unsigned char uint8;

extern const int ScreenWidth; 
extern const int ScreenHeight;


/*** ENGINE CONTROL ***/
// Starts the engine and opens a window
void engInit();
// Updates window, drawing, input and frame delta
void engUpdate();
// Flags the engine to shut down
void engClose();
// Destroys engine and shuts everything down. DONT call any engine functions after this.
void engDestroy();

// Gets if the engine is currently running
bool engIsOpen();

/*** FLOW CONTROL ***/
// Updates drawing and halts program for a set amount of time
void engDelay(int Milliseconds);
// Updates drawing and halts until the user hits a key, then returns that key
Key engWaitKey();

// Current frame delta time, NOTE: This wont be valid unless you're using engUpdate()
float engDelta();

/*** RENDERING ***/
// Clears the screen
void engClear();

// Sets current drawing color (RGB or HEX)
void engSetColor(uint8 Red, uint8 Green, uint8 Blue);
void engSetColor(unsigned int Color);

// Draws a filled rectangle at (X, Y) with dimensions (Width, Height)
void engDrawRect(int X, int Y, int Width, int Height);

void engDrawLine(int X1, int Y1, int X2, int Y2);

void engDrawPixel(int X, int Y);

void engDrawWireFrame(const std::vector<std::pair<float, float>> &vecModelCoordinates,
	float x, float y, float r, float s);

//Wraps coordinates in x and y so that things go to the other side of the screen
void engWrapCoordinates(float InX, float InY, float& OutX, float& OutY);

bool engIsPointInsideCircle(float cx, float cy, float radius, float x, float y);

/*** INPUT ***/
/*** Note: None of these will do anything unless you call engUpdate() ***/
// Get if a key is pressed
bool engGetKey(Key InKey);
// Get if a key was pressed this frame
bool engGetKeyDown(Key InKey);
// Get if a key was released this frame
bool engGetKeyUp(Key InKey);