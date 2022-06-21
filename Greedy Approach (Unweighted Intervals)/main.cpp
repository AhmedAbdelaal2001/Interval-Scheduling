#include "Request.h"
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

void printRequestsList(list<Request>& l);               //Given a list of requests, prints the contents of the list.

void requestsFromUser(int n, Request* requestsArr);     //Prompts the user for input, used to build an array of Requests.

//Custom comparison that will be used in the sort function.
bool sortingComparsion(Request request1, Request request2) { return request1.getFinishTime() < request2.getFinishTime(); }



//Solves the unweighted Interval Scheduling problem in O(n) time. Uses a greedy algorithm which processes the request having the
//earliest finishing time, removes all incompatible requests, then repeats the process.

int main() {

	int n, prevFinishTime = 0;               // n: number of requests.
	                                        // prevFinishTime: keeps track of the finishing time of the last request processed,
	                                       //                 helps in eliminating some requests in the greedy algorithm.


	cout << "Enter the number of requests: ";
	cin >> n;
	
	Request* requestsArr = new Request[n];                 //An array of requests.
	list<Request> maxCompatibleRequests;                  //A list containing the compatible requests, having the largest possible size.

	requestsFromUser(n, requestsArr);                                //Creates the requestsArr
	sort(requestsArr, requestsArr + n, sortingComparsion);          //Sorts the array in ascending order of finish time.



	for (int i = 0; i < n; i++) {
		if (requestsArr[i].getStartTime() >= prevFinishTime) {        //Prevents any requests which overlap with the previously processed
			                                                         //request from being considered.
			
			maxCompatibleRequests.push_back(requestsArr[i]);        //Adds the first compatible request (least finishing time)
			                                                       //to the list.
			
			prevFinishTime = requestsArr[i].getFinishTime();       //Updates prevFinishTime       


		}
	}
	delete[] requestsArr;


	//Output
	cout << "\n-----------------------------------------------------------------------------------------------------------------\n";
	cout << "\nMaximum Number Of Compatible Requests = " << maxCompatibleRequests.size() << endl;
	cout << "\nLargest Compatible Set Of Requests: " << endl;
	printRequestsList(maxCompatibleRequests);

	return 0;
}

void printRequestsList(list<Request>& l) {

	list<Request>::iterator it;
	for (it = l.begin(); it != l.end(); it++) {

		cout << "\nRequest " << it->getId() << ": " << endl;
		cout << "Start Time = " << it->getStartTime() << endl;
		cout << "Finish Time = " << it->getFinishTime() << endl;

	}
}

void requestsFromUser(int n, Request* requestsArr) {

	int startTime, finishTime;
	cout << "\nEnter the start and finishing times of each request:\n";
	for (int i = 0; i < n; i++)
	{
		cout << "\nRequest " << i + 1 << ": " << endl;
		cout << "Start Time = ";
		cin >> startTime;
		cout << "Finishing Time = ";
		cin >> finishTime;

		Request inputRequest(i + 1, startTime, finishTime);
		requestsArr[i] = inputRequest;
	}

}
