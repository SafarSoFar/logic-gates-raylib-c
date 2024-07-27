#include "objects.h"
// to make more human-readable while writing functions



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



		/// @brief Connection constructor
		/// @param pos 
		/// @param curLogicState 
		/// @param initWire wire on which a new connection will be introduced
		Connection::Connection(Vector2 pos, LogicState curLogicState, Wire initWire){
			this->pos = pos;
			this->curLogicState = curLogicState;
			connectedWires = std::vector<Wire>{initWire};
		}

		void Connection::add_wire(Wire wireToAdd){
			std::cout<<"\nadding wire to the existing connection\nconnection logic state: " << this->curLogicState;
			wireToAdd.curLogicState = this->curLogicState;
			connectedWires.push_back(wireToAdd);
		}

		void Connection::change_logic_state(LogicState logicState){
			this->curLogicState = logicState;
			for(int i = 0; i < this->connectedWires.size(); i++){
				connectedWires[i].curLogicState = logicState;
			}
		}

