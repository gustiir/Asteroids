#include "Engine.h"
#include <SDL.h>
#include <chrono>

// Variables controlling the SDL context
static SDL_Window* Window;
static SDL_Renderer* Renderer;
static bool IsOpen = false;

static SDL_Color CurrentColor = { 255, 255, 255, 255 };

// Delta tracking
using namespace std::chrono;
using hr_clock = high_resolution_clock;

static hr_clock::time_point LastFrameTime;
static float FrameDelta = 0.f;

//Added this for wanted resolution
extern const int ScreenWidth = 320;
extern const int ScreenHeight = 240;

// Input stuff
struct InputState
{
	bool Pressed;
	int FrameNum;
};
static InputState KeyStates[(unsigned int)Key::MAX];
static int CurrentFrameNum = 1;

void engInit()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Open window (Resolution here is for the window and not perceived, change wanted resolution above instead)
	Window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1440, 1080, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	//Added this to get the low resolution feel
	SDL_RenderSetLogicalSize(Renderer, ScreenWidth, ScreenHeight);

	IsOpen = true;

	// Set last frame time to now, so that delta doesnt get messed up later
	LastFrameTime = hr_clock::now();
}

void engClear()
{
	// Clear for next frame
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(Renderer);
}

void engUpdate()
{
	CurrentFrameNum++;

	// Poll window events
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			engClose();

		if (e.type == SDL_KEYDOWN)
		{
			// We dont care about repeats
			if (e.key.repeat == 0)
			{
				InputState& state = KeyStates[e.key.keysym.scancode];
				state.Pressed = true;
				state.FrameNum = CurrentFrameNum;
			}
		}

		if (e.type == SDL_KEYUP)
		{
			InputState& state = KeyStates[e.key.keysym.scancode];
			state.Pressed = false;
			state.FrameNum = CurrentFrameNum;
		}
	}

	// Calculate next frame delta
	hr_clock::time_point Now = hr_clock::now();
	FrameDelta = duration_cast<microseconds>(Now - LastFrameTime).count() * 1e-6f;  // 10^6 microseconds in a second
	LastFrameTime = Now;

	// Present SDL renderer
	SDL_RenderPresent(Renderer);
	engClear();

	// Do a small delay so we dont fry the CPU
	SDL_Delay(1);
}

void engClose()
{
	// 'Closes' the window (sets the flag to close, actual closing happens in Destroy
	IsOpen = false;
}

void engDestroy()
{
	// Destroys the inner APIs and does a clean exit
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

	Renderer = nullptr;
	Window = nullptr;

	SDL_Quit();
}

bool engIsOpen()
{
	// Return if the window is open
	return IsOpen;
}

void engDelay(int Milliseconds)
{
	// Draw whats up, so its not just black
	SDL_RenderPresent(Renderer);
	SDL_Delay(Milliseconds);
}

Key engWaitKey()
{
	// Draw whats up, so its not just black
	SDL_RenderPresent(Renderer);

	SDL_Event e;

	do
	{
		SDL_WaitEvent(&e);
	} while (e.type != SDL_KEYDOWN && e.type != SDL_QUIT);

	if (e.type == SDL_QUIT)
	{
		// We want to handle quitting messages, so people dont think we're locked
		engClose();
		return Key::Undefined;
	}
	else
		return (Key)e.key.keysym.scancode;
}

float engDelta()
{
	// Returns the deltatime for this frame
	return FrameDelta;
}

void engSetColor(uint8 Red, uint8 Green, uint8 Blue)
{
	CurrentColor.r = Red;
	CurrentColor.g = Green;
	CurrentColor.b = Blue;
	CurrentColor.a = 255;
}

void engSetColor(unsigned int Color)
{
	CurrentColor.r = (Color >> 24) & 0xFF;
	CurrentColor.g = (Color >> 16) & 0xFF;
	CurrentColor.b = (Color >> 8) & 0xFF;
	CurrentColor.a = Color & 0xFF;
}

void engDrawRect(int X, int Y, int Width, int Height)
{
	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);

	SDL_Rect rect = { X, Y, Width, Height };
	SDL_RenderFillRect(Renderer, &rect);
}
//Reworked this to use the drawpixel function, instead of the build in line function
void engDrawLine(int X1, int Y1, int X2, int Y2)
{
	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

	dx = X2 - X1; dy = Y2 - Y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;

	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = X1; y = Y1; xe = X2;
		}
		else
		{
			x = X2; y = Y2; xe = X1;
		}

		engDrawPixel(x, y);

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}

			engDrawPixel(x, y);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = X1; y = Y1; ye = Y2;
		}
		else
		{
			x = X2; y = Y2; ye = Y1;
		}

		engDrawPixel(x, y);

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			engDrawPixel(x, y);
		}
	}
}
//Added this as it was needed to draw pixels
void engDrawPixel(int X, int Y)
{
	SDL_SetRenderDrawColor(Renderer, CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);

	float fX, fY;
	engWrapCoordinates(X, Y, fX, fY);

	SDL_RenderDrawPoint(Renderer, fX, fY);
}
//Added this to draw the ship and asteroids
void engDrawWireFrame(const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f)
{
	// X coordinates is first
	// Y coordinates is second

	//Create translated model vector of coordinate pairs
	std::vector<std::pair<float, float>> vecTransformedCoordinates;
	int verts = vecModelCoordinates.size();
	vecTransformedCoordinates.resize(verts);

	//Rotation
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
		vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
	}

	// Scale
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
		vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
	}

	// Translate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
		vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
	}

	// Draw Closed Polygon
	for (int i = 0; i < verts + 1; i++)
	{
		int j = (i + 1);
		engDrawLine(vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second,
			vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second);
	}

}

//Added this as wraping was needed
void engWrapCoordinates(float InX, float InY, float& OutX, float& OutY)
{
	OutX = InX;
	OutY = InY;
	if (InX < 0.0f) OutX = InX + (float)ScreenWidth;
	if (InX >= (float)ScreenWidth) OutX = InX - (float)ScreenWidth;

	if (InY < 0.0f) OutY = InY + (float)ScreenHeight;
	if (InY >= (float)ScreenHeight) OutY = InY - (float)ScreenHeight;
}

//Added this for collision detection
bool engIsPointInsideCircle(float cx, float cy, float radius, float x, float y)
{
	return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
}

bool engGetKey(Key InKey)
{
	return KeyStates[(int)InKey].Pressed;
}

bool engGetKeyDown(Key InKey)
{
	// Is pressed and changed this frame
	InputState& State = KeyStates[(int)InKey];
	return State.Pressed && State.FrameNum == CurrentFrameNum;
}

bool engGetKeyUp(Key InKey)
{
	// Is not pressed and changed this frame
	InputState& State = KeyStates[(int)InKey];
	return !State.Pressed && State.FrameNum == CurrentFrameNum;
}

