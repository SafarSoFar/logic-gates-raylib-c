#include "connection.h"

Connection::Connection(){
	this->pos = Vector2{-1,-1}; // null pos
	this->curLogicState = LOGIC_OFF;
    //this->connectedWires = std::vector<Wire>();
}


Connection::Connection(Vector2 pos, LogicState curLogicState){
	this->pos = pos;
	this->curLogicState = curLogicState;
	connectedWires = std::vector<Wire>();
}

Connection::Connection(Vector2 pos, LogicState curLogicState, Wire initWire){
	this->pos = pos;
	this->curLogicState = curLogicState;
	connectedWires = std::vector<Wire>();
	connectedWires.push_back(initWire);
}

bool is_connection_empty(Connection connection){
	return connection.pos.x == -1;
}

void Connection::add_wire(Wire wireToAdd){
	std::cout<<"\nadding wire to the existing connection\nconnection logic state: " << this->curLogicState;
	if(wireToAdd.curLogicState == LOGIC_ON){
		this->change_connection_logic_state(LOGIC_ON);
	}
	connectedWires.push_back(wireToAdd);
	
}

void Connection::change_connection_logic_state(LogicState logicState){
	this->curLogicState = logicState;
	for(int i = 0; i < this->connectedWires.size(); i++){
		connectedWires[i].try_change_state();
	}
}


Connection check_pos_to_connections_collision(std::vector<Connection> &connectionsVec, Vector2 collisionPos){
	for(int i = 0; i < connectionsVec.size(); i++){
		if(CheckCollisionPointCircle(collisionPos,connectionsVec[i].pos, CONNECTION_RADIUS)){
			return connectionsVec[i];
		}
	}
	return Connection();
}