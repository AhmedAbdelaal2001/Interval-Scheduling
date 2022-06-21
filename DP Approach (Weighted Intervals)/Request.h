#pragma once
#include <forward_list>

//This class reperesents the requests that we will schedule, each having weighted intervals.
class Request
{
private:
	int id;                             //Request Id.
	int startTime;                     //Starting time (in hours).
	int finishTime;                   //Finishing time (in hours).
	int weight;                      //Weight of the request.
	std::forward_list<int> latestCompatibles;            //A list which contains the index of LATEST previous compatible request, will contain n
	                                                    //request if the n latest compatible requests have the same finishing time. 
	                                                   //Will be used when the requests are stored in an array.

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

	void setLatestCompatibles(std::forward_list<int>&);
	std::forward_list<int>& getlatestCompatibles();
};

