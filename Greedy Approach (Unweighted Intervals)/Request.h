#pragma once

//This class represents the requests that we will schedule.
class Request
{

private:
	int id;                         //Id of the request.
	int startTime;                 //Starting time (in hours) of the request.
	int finishTime;               // Ending time (in hours) of the request

public:
	Request();                    //Default Constructor
	Request(int, int, int);       //Non-Default Constructor

	//Setters and Getters.

	void setId(int);
	int getId() const;

	void setStartTime(int);
	int getStartTime() const;

	void setFinishTime(int);
	int getFinishTime() const;
};

