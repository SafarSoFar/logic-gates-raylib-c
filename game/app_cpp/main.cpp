#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;
//using std::pair;


class Wire{
	public:
		Vector2 startPos;
		Vector2 endPos;

		Wire(Vector2 _startPos, Vector2 _endPos){
			this->startPos = _startPos;	
			this->endPos = _endPos;	
		}
	
};

int main ()
{
	const int windowWidth = 800;
	const int windowHeight = 640;
	bool isWireStarted = false;

	InitWindow(windowWidth, windowHeight, "Logic gates");

	vector<Wire> wiresVec = vector<Wire>();

	Vector2 zeroVec = Vector2{0,0};

	Vector2 curWireStart;
	Vector2 curWireEnd;
	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(GRAY);
		DrawText("Press Q to remove all wires", 0,0, 30, BLACK);
		for(int i = 0; i < wiresVec.size();i++){
			DrawLineEx(wiresVec[i].startPos, wiresVec[i].endPos, 5.0f, BLACK);
		}

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

			wiresVec.push_back(Wire(curWireStart,curWireEnd));
			curWireStart = zeroVec;
			curWireEnd = zeroVec;
		}
			
		if(IsKeyPressed(KEY_Q)){
			wiresVec.clear();
		}
		
		EndDrawing();
	}
	wiresVec.clear();
	CloseWindow();
	return 0;
}
