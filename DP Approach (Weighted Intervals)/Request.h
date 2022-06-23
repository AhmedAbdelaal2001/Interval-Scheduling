#pragma once

//This class reperesents the requests that we will schedule, each having weighted intervals.
class Request
{
private:
	int id;                             //Request Id.
	int startTime;                     //Starting time (in hours).
	int finishTime;                   //Finishing time (in hours).
	int weight;                      //Weight of the request.

public:
	Request();                                  //Default Constructor.
	Request(int, int, int, int);               //Non-Default Constructor.


	//Setters and Getters.


	void setId(int);
	int getId() const;

	void setStartTime(int);
	int getStartTime() const;

	void setFinishTime(int);
	int getFinishTime() const;

	void setWeight(int);
	int getWeight() const;
};

