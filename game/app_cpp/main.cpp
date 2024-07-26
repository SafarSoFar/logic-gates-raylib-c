#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;

//#define LOGIC_OFF = 0;
//#define LOGIC_ON = 1;

#define CONNECTION_RADIUS 15.0f

// to make more human-readable while writing functions
enum LogicState{
	LOGIC_OFF = 0,
	LOGIC_ON = 1,
};

class Wire{
	public:
		Vector2 startPos;
		Vector2 endPos;
		LogicState curLogicState;


		Wire(Vector2 _startPos, Vector2 _endPos){
			this->startPos = _startPos;	
			this->endPos = _endPos;	
		}
	
};

class Connection{
	public:
		Vector2 pos;
		vector<Wire> connectedWires;

		Connection(Vector2 _pos){
			this->pos = _pos;
			connectedWires = vector<Wire>();
		}

		void AddWire(Wire wireToAdd){
			connectedWires.push_back(wireToAdd);
		}

		void ChangeLogicState(LogicState logicState){
			for(int i = 0; i < this->connectedWires.size(); i++){
				connectedWires[i].curLogicState = logicState;
			}
		}
};



/// @brief Returns pointer to a collider connection or nullptr if no connection collision happened 
/// @param connectionsVec 
/// @param collisionPos 
/// @return 
Connection* CheckPosCollisionToConnections(vector<Connection> &connectionsVec, Vector2 collisionPos){
	for(int i = 0; i < connectionsVec.size(); i++){
		if(CheckCollisionPointCircle(collisionPos,connectionsVec[i].pos, CONNECTION_RADIUS)){
			return &connectionsVec[i];
		}
	}
	return nullptr;
}


int main ()
{
	const int windowWidth = 800;
	const int windowHeight = 640;
	bool isWireStarted = false;

	InitWindow(windowWidth, windowHeight, "Logic gates");

	vector<Wire> wiresVec = vector<Wire>();
	vector<Connection> connectionsVec = vector<Connection>();

	Vector2 zeroVec = Vector2{0,0};

	Vector2 curWireStart;
	Vector2 curWireEnd;
	Connection* startWireConnection;
	Connection* endWireConnection;
	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(GRAY);
		DrawText("Press Q to remove everything", 0,0, 30, BLACK);
		for(int i = 0; i < wiresVec.size();i++){
			DrawLineEx(wiresVec[i].startPos, wiresVec[i].endPos, 5.0f, BLACK);
		}
		for(int i = 0; i < connectionsVec.size(); i++){
			DrawCircleV(connectionsVec[i].pos, CONNECTION_RADIUS,YELLOW);			
		}

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){

			Vector2 curMousePos = GetMousePosition();
			bool hasConnection = false;

			if(!isWireStarted){
				startWireConnection = CheckPosCollisionToConnections(connectionsVec, curMousePos);
				if(startWireConnection != nullptr){
					curWireStart = startWireConnection->pos;
				}
				else{
					curWireStart = curMousePos;
				}

				isWireStarted = true;
			}
			
			endWireConnection = CheckPosCollisionToConnections(connectionsVec, curMousePos);			
			if(endWireConnection != nullptr){
				curWireEnd = endWireConnection->pos;
			}
			else{
				curWireEnd = curMousePos;
			}

			DrawLineEx(curWireStart, curWireEnd, 5.0f, BLACK);
		}
		else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
			isWireStarted = false;

			// means that new wire looped on the connection and can cause unwanted behaviour
			if(startWireConnection == endWireConnection){
				std::cout<<"\nWARNING: a shorted wire presented on the scheme\n";
			}

			Wire newWire = Wire(curWireStart, curWireEnd);

			curWireStart = zeroVec;
			curWireEnd = zeroVec;

			wiresVec.push_back(newWire);

			if(startWireConnection != nullptr){
				startWireConnection->AddWire(newWire);
			}			
			else{
				Connection newStartWireConnection = Connection(newWire.startPos);
				connectionsVec.push_back(newStartWireConnection);
			}

			if(endWireConnection != nullptr){
				endWireConnection->AddWire(newWire);
			}
			else{
				Connection newEndWireConnection = Connection(newWire.endPos);
				connectionsVec.push_back(newEndWireConnection);
			}
		}
			
		if(IsKeyPressed(KEY_Q)){
			wiresVec.clear();
			connectionsVec.clear();
		}
		
		EndDrawing();
	}
	wiresVec.clear();
	connectionsVec.clear();
	CloseWindow();
	return 0;
}

