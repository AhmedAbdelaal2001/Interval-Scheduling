#include "Request.h"

//Constructors.

Request::Request() { setId(0); setStartTime(0); setFinishTime(0); }

Request::Request(int id, int startTime, int finishTime, int weight) { 
	
	setId(id); 
	setStartTime(startTime); 
	setFinishTime(finishTime);
	setWeight(weight);

}

//Setters and Getters.

void Request::setId(int id) { this->id = id; }
int Request::getId() const { return id; }

void Request::setStartTime(int startTime) { this->startTime = startTime; }
int Request::getStartTime() const { return startTime; }

void Request::setFinishTime(int finishTime) { this->finishTime = finishTime; }
int Request::getFinishTime() const { return finishTime; }

void Request::setWeight(int weight){ this->weight = weight; }
int Request::getWeight() const { return weight; }	

