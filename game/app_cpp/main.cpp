#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;
//using std::pair;

int main ()
{
	const int windowWidth = 800;
	const int windowHeight = 640;
	bool isWireStarted = false;

	InitWindow(windowWidth, windowHeight, "Logic gates");

	//vector<Wire> wiresVec;

	Vector2 zeroVec = Vector2{0,0};

	Vector2 curWireStart;
	Vector2 curWireEnd;
	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(GRAY);

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			if(!isWireStarted){
				curWireStart = GetMousePosition();
				isWireStarted = true;
			}
			curWireEnd = GetMousePosition();
			DrawLineEx(curWireStart, curWireEnd, 5.0f, BLACK);
		}
		else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
			isWireStarted = false;
			curWireStart = zeroVec;
			curWireEnd = zeroVec;
		}
			
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

class Wire{
	public:
		Vector2 startPos;
		Vector2 endPos;

		Wire(Vector2 _startPos, Vector2 _endPos){
			this->startPos = _startPos;	
			this->endPos = _endPos;	
		}
	
};