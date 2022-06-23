#include "Request.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <utility>

using namespace std;

//Predicate that will be used when sorting the list of requests.
bool sortingComparsion(Request request1, Request request2) { return request1.getFinishTime() < request2.getFinishTime(); }

//Predicate that will be used to determine the latest compatible request/s.
bool nextCompatibleComparison(Request request, int finishTime) { return request.getStartTime() < finishTime; }

//Predicate that will be used when reconstructing the sequence of requests giving the most optimized schedule.
bool reconstructingComparison(pair<int, int> memoItem, int weight) { return memoItem.first == weight; }

//Finds the earliest compatible request that occurs after the one at position requestIndex.
int nextCompatible(Request* requestsArr, int arrSize, int requestIndex);

//Prompts the user for input.
void requestsFromUser(Request* requestsArr, int n);

//Uses dynamic programming to calculate the most optimized scheduling possible (maximizing the sum of weights.)
//The memo will be used reconstruct the sequence of requests later in the main() function.
//Complexity: O(n)
int optimizeScheduling(Request* requestsArr,int arrSize, int index, pair<int, int>* memo);


//Solves the Weighted Intreval Scheduling problem. To calculate the maximum sum of compatible weights, the algorithm first sorts all
//requests in ascending order of finishing time. Then for each request at position i, it calculate its weight + the optimized weighted
//sum of all the requests starting from the next compatible request until the end of requestArr, and compares that value to the 
//optimized weighted sum of the requests starting at position i+1, returning the higher value between those two. Whenever a subproblem
//is solved, it is stored in the memo. Complexity = O(nlogn), due to sorting.
int main() {

	int n, prevFinishTime = 0;

	cout << "Enter the number of requests: ";
	cin >> n;

	Request* requestsArr = new Request[n];

	requestsFromUser(requestsArr, n);
	sort(requestsArr, requestsArr + n, sortingComparsion);

	list<int> optimumScheduling;
	int optimumSchedulingWeight;
	pair<int, int>* memo = new pair<int, int>[n];
	
	for (int i = 0; i < n; i++)
	{
		memo[i].first = -1;
		memo[i].second = -2;
	}

	optimumSchedulingWeight = optimizeScheduling(requestsArr, n, 0, memo);
	cout << "\n-----------------------------------------------------------------------------------------------------------------\n";
	cout << "\nMaximum Weight Of Compatible Requests = " << optimumSchedulingWeight << endl;
	cout << "\nOptimum Compatible Set Of Requests: " << endl;

	//Reconstructing the most optimized schedule from the memo.

	int startingIndex = lower_bound(memo, memo + n, optimumSchedulingWeight, reconstructingComparison) - memo - 1;
	
	while (startingIndex < n) {
		optimumScheduling.push_back(startingIndex);
		startingIndex = memo[startingIndex].second;
	}
	
	list<int>::iterator it;
	for (it = optimumScheduling.begin(); it != optimumScheduling.end(); it++) {

		cout << "\nRequest " << requestsArr[*it].getId() << ": " << endl;
		cout << "Starting Time = " << requestsArr[*it].getStartTime() << endl;
		cout << "Finishing Time = " << requestsArr[*it].getFinishTime() << endl;
		cout << "Weight = " << requestsArr[*it].getWeight() << endl;

	}

	return 0;
}

int nextCompatible(Request* requestsArr, int arrSize, int requestIndex) {

	Request* nextRequest = lower_bound(requestsArr, requestsArr + arrSize, requestsArr[requestIndex].getFinishTime(), nextCompatibleComparison);
	return nextRequest - requestsArr;

}

void requestsFromUser(Request* requestsArr, int n) {

	int startTime, finishTime, weight;
	cout << "\nEnter the start and finishing times of each request:\n";

	for (int i = 0; i < n; i++)
	{
		cout << "\nRequest " << i + 1 << ": " << endl;
		cout << "Start Time = ";
		cin >> startTime;
		cout << "Finishing Time = ";
		cin >> finishTime;
		cout << "Weight = ";
		cin >> weight;

		Request inputRequest(i + 1, startTime, finishTime, weight);
		requestsArr[i] = inputRequest;
	}
}

int optimizeScheduling(Request* requestsArr,int arrSize, int index, pair<int, int>* memo) {

	if (index >= arrSize) return 0;
	if (memo[index].first != -1) return memo[index].first;

	int nextCompatibleIndex = nextCompatible(requestsArr, arrSize, index);

	int firstRequestTaken = requestsArr[index].getWeight() + optimizeScheduling(requestsArr, arrSize,
							nextCompatibleIndex, memo);

	int firstRequestNotTaken = optimizeScheduling(requestsArr, arrSize, index + 1, memo);

	if (firstRequestTaken > firstRequestNotTaken)
	{
		memo[index].first = firstRequestTaken;

		while (memo[nextCompatibleIndex].second == -2) nextCompatibleIndex++;

		memo[index].second = nextCompatibleIndex;
	}
	else memo[index].first = firstRequestNotTaken;

	return memo[index].first;

	

}