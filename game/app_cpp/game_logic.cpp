#include "game_logic.h"


Wire::Wire(Vector2 pos, Vector2 endPos){
    this->pos = pos;	
    this->endPos = endPos;	
}
	


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

Connection::Connection(){
	this->pos = Vector2{-1,-1}; // null pos
	this->curLogicState = LOGIC_OFF;
}

bool is_connection_empty(Connection connection){
	return connection.pos.x == -1;
}

Connection::Connection(Vector2 pos, LogicState curLogicState, Wire initWire){
	this->pos = pos;
	this->curLogicState = curLogicState;
	connectedWires = std::vector<Wire>();
	connectedWires.push_back(initWire);
}

void Connection::add_wire(Wire wireToAdd){
	std::cout<<"\nadding wire to the existing connection\nconnection logic state: " << this->curLogicState;
	connectedWires.push_back(wireToAdd);
	if(this->curLogicState == LOGIC_ON){
		wireToAdd.curLogicState = LOGIC_ON;
	}
	if(wireToAdd.curLogicState == LOGIC_ON){
		this->change_connection_logic_state(LOGIC_ON);
	}
}

void Connection::change_connection_logic_state(LogicState logicState){
	this->curLogicState = logicState;
	for(int i = 0; i < this->connectedWires.size(); i++){
		connectedWires[i].curLogicState = logicState;
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

