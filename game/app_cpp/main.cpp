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

class Object{
	public:
		Vector2 pos;
		virtual ~Object(){}

};


class Wire : public Object{
	public:
		Vector2 endPos;
		LogicState curLogicState;


		Wire(Vector2 pos, Vector2 endPos){
			this->pos = pos;	
			this->endPos = endPos;	
		}
	
};

/*class SelfHostingConnection{
	public:
		Vector2 pos;
		vector<Wire> connectedWires;
		LogicState logicState;

		/// @brief Connection constructor
		/// @param pos 
		/// @param curLogicState 
		/// @param initWire wire on which a new connection will be introduced
		SelfHostingConnection(Vector2 pos, LogicState logicState, Wire initWire){
			this->pos = pos;
			this->logicState = logicState;
			connectedWires = vector<Wire>{initWire};
		}

		void add_wire(Wire wireToAdd){
			std::cout<<"\nadding wire to the existing connection\nconnection logic state: " << this->logicState;
			wireToAdd.curLogicState = this->logicState;
			connectedWires.push_back(wireToAdd);
		}

		void change_logic_state(LogicState logicState){
			this->logicState = logicState;
			for(int i = 0; i < this->connectedWires.size(); i++){
				connectedWires[i].curLogicState = logicState;
			}
		}
};*/

class Connection : public Object{
	public:
		vector<Wire> connectedWires;
		LogicState curLogicState;

		/// @brief Connection constructor
		/// @param pos 
		/// @param curLogicState 
		/// @param initWire wire on which a new connection will be introduced
		Connection(Vector2 pos, LogicState curLogicState, Wire initWire){
			this->pos = pos;
			this->curLogicState = curLogicState;
			connectedWires = vector<Wire>{initWire};
		}

		void add_wire(Wire wireToAdd){
			std::cout<<"\nadding wire to the existing connection\nconnection logic state: " << this->curLogicState;
			wireToAdd.curLogicState = this->curLogicState;
			connectedWires.push_back(wireToAdd);
		}

		void change_logic_state(LogicState logicState){
			this->curLogicState = logicState;
			for(int i = 0; i < this->connectedWires.size(); i++){
				connectedWires[i].curLogicState = logicState;
			}
		}

};



/// @brief Returns pointer to a collider connection or nullptr if no connection collision happened 
/// @param connectionsVec 
/// @param collisionPos 
/// @return 
Connection* check_pos_to_connections_collision(vector<Connection> &connectionsVec, Vector2 collisionPos){
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
	bool isShortagePresented = false;

	InitWindow(windowWidth, windowHeight, "Logic gates");

	Wire initWire = Wire(Vector2{100,100}, Vector2{100,150});
	vector<Wire> wiresVec = vector<Wire>{initWire};

	Connection initConnectionOn = Connection(Vector2{100,100}, LOGIC_ON, initWire);
	vector<Connection> connectionsVec = vector<Connection>{initConnectionOn};

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
			if(wiresVec[i].curLogicState == LOGIC_ON){
				DrawLineEx(wiresVec[i].pos, wiresVec[i].endPos, 5.0f, RED);
			}
			else{
				DrawLineEx(wiresVec[i].pos, wiresVec[i].endPos, 5.0f, BLACK);
			}
		}
		for(int i = 0; i < connectionsVec.size(); i++){
			if(connectionsVec[i].curLogicState == LOGIC_ON){
				DrawCircleV(connectionsVec[i].pos, CONNECTION_RADIUS, RED);			
			}
			else{
				DrawCircleV(connectionsVec[i].pos, CONNECTION_RADIUS, BLACK);			
			}
		}

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){

			Vector2 curMousePos = GetMousePosition();
			bool hasConnection = false;
			isShortagePresented = false;

			if(!isWireStarted){
				startWireConnection = check_pos_to_connections_collision(connectionsVec, curMousePos);
				if(startWireConnection != nullptr){
					curWireStart = startWireConnection->pos;
				}
				else{
					curWireStart = curMousePos;
				}

				isWireStarted = true;
			}
			
			endWireConnection = check_pos_to_connections_collision(connectionsVec, curMousePos);			
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
			if(startWireConnection != nullptr && startWireConnection == endWireConnection){
				std::cout<<"\nWARNING: a shorted wire presented on the scheme\n";

				//std::cout<<"start connection address: "<<startWireConnection<<'\n';
				//std::cout<<"end connection address : "<<endWireConnection<<'\n';

				// immediate resetting
				isShortagePresented = true;
			}

			if(!isShortagePresented){
				Wire newWire = Wire(curWireStart, curWireEnd);


				wiresVec.push_back(newWire);

				if(startWireConnection != nullptr){
					startWireConnection->add_wire(newWire);
				}			
				else{
					Connection newStartWireConnection = Connection(newWire.pos, LOGIC_OFF, newWire);
					connectionsVec.push_back(newStartWireConnection);
				}
				if(endWireConnection != nullptr){
					endWireConnection->add_wire(newWire);
				}
				else{
					Connection newEndWireConnection = Connection(newWire.endPos, LOGIC_OFF, newWire);
					connectionsVec.push_back(newEndWireConnection);
				}

			}
			curWireStart = zeroVec;
			curWireEnd = zeroVec;
			startWireConnection = nullptr;
			endWireConnection = nullptr;
			//isShortagePresented = false;

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

