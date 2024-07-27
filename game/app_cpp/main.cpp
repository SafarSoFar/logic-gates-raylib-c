#include "game_logic.h"
using namespace std;


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
	Connection startWireConnection;
	Connection endWireConnection;
	
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
				if(!is_connection_empty(startWireConnection)){
					curWireStart = startWireConnection.pos;
				}
				else{
					curWireStart = curMousePos;
				}

				isWireStarted = true;
			}
			
			endWireConnection = check_pos_to_connections_collision(connectionsVec, curMousePos);			
			if(!is_connection_empty(endWireConnection)){
				curWireEnd = endWireConnection.pos;
			}
			else{
				curWireEnd = curMousePos;
			}

			DrawLineEx(curWireStart, curWireEnd, 5.0f, BLACK);
		}
		else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
			isWireStarted = false;

			// means that new wire looped on the connection and can cause unwanted behaviour
			if(!is_connection_empty(startWireConnection) && startWireConnection.pos.x == endWireConnection.pos.x
			&& startWireConnection.pos.y == endWireConnection.pos.y){
				std::cout<<"\nWARNING: a shorted wire presented on the scheme\n";

				//std::cout<<"start connection address: "<<startWireConnection<<'\n';
				//std::cout<<"end connection address : "<<endWireConnection<<'\n';

				// immediate resetting
				isShortagePresented = true;
			}

			if(!isShortagePresented){
				Wire newWire = Wire(curWireStart, curWireEnd);


				wiresVec.push_back(newWire);

				if(!is_connection_empty(startWireConnection)){
					startWireConnection.add_wire(newWire);
				}			
				else{
					Connection newStartWireConnection = Connection(newWire.pos, LOGIC_OFF, newWire);
					connectionsVec.push_back(newStartWireConnection);
				}
				if(!is_connection_empty(endWireConnection)){
					endWireConnection.add_wire(newWire);
				}
				else{
					Connection newEndWireConnection = Connection(newWire.endPos, LOGIC_OFF, newWire);
					connectionsVec.push_back(newEndWireConnection);
				}

			}
			curWireStart = zeroVec;
			curWireEnd = zeroVec;
			startWireConnection = Connection();
			endWireConnection = Connection();

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

