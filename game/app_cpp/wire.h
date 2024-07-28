#ifndef WIRE_H_
#define WIRE_H_

#include "game_logic.h"
#include "connection.h"


class Connection;
class Wire : public Object{
	public:
		Vector2 endPos;
		LogicState curLogicState;
		Connection* startConnection;
		Connection* endConnection;

		Wire(Vector2 pos, Vector2 endPos, Connection* startConnection, Connection* endConnection);
		Wire(Vector2 pos, Vector2 endPos); 

		void set_start_connection(Connection* connection);
		void set_end_connection(Connection* connection);
		void try_change_state();
};
#endif