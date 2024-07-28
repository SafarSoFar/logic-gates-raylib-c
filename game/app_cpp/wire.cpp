#include "wire.h"

Wire::Wire(Vector2 pos, Vector2 endPos, Connection* startConnection, Connection* endConnection){
    this->pos = pos;	
    this->endPos = endPos;
	this->startConnection = startConnection;	
	this->curLogicState = LOGIC_OFF;
	this->endConnection = endConnection;
}

Wire::Wire(Vector2 pos, Vector2 endPos){
	this->pos = pos;
	this->endPos = endPos;
    this->startConnection = new Connection();
    this->endConnection = new Connection();
}

void Wire::set_start_connection(Connection* connection){
	this->startConnection = connection;
}
void Wire::set_end_connection(Connection* connection){
	this->endConnection = connection;
}


void Wire::try_change_state(){
	if(this->startConnection->curLogicState == LOGIC_ON || this->endConnection->curLogicState == LOGIC_ON){
		this->curLogicState = LOGIC_ON;
	}
	else
		this->curLogicState = LOGIC_OFF;
}