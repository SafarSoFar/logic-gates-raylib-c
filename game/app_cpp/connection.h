#ifndef CONNECTION_H_
#define CONNECTION_H_


#include "game_logic.h"
#include "wire.h"

class Wire;
class Connection : public Object{
	public:
		std::vector<Wire> connectedWires;
		LogicState curLogicState;

		Connection();

		/// @brief Connection constructor
		/// @param pos 
		/// @param curLogicState 
		Connection(Vector2 pos, LogicState curLogicState);

		/// @brief Connection constructor
		/// @param pos 
		/// @param curLogicState 
		/// @param initWire wire on which a new connection will be introduced
		Connection(Vector2 pos, LogicState curLogicState, Wire initWire);

		void add_wire(Wire wireToAdd);

		void change_connection_logic_state(LogicState logicState);

};



bool is_connection_empty(Connection connection);

/// @brief Returns collider connection or null connection (-1,-1 pos) if no connection collision happened 
/// @param connectionsVec 
/// @param collisionPos 
/// @return 
Connection check_pos_to_connections_collision(std::vector<Connection> &connectionsVec, Vector2 collisionPos);

#endif