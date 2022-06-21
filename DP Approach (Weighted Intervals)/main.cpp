#include "Request.h"
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

//Predicate that will be used when sorting the list of requests.
bool sortingComparsion(Request request1, Request request2) { return request1.getFinishTime() < request2.getFinishTime(); }

//Predicate that will be used to determine the latest compatible request/s.
bool prevCompatibleComparison(Request request, int startTime) { return request.getFinishTime() <= startTime; }

//Predicate that will be used when reconstructing the sequence of requests giving the most optimized schedule.
bool reconstructingComparison(pair<int, int> memoItem, int weight) { return memoItem.first != weight; }

//Assigns a list to the request at index "requestIndex" containing the latest compatible request/s.
void calcPrevCompatibles(Request* requestsArr, int arrSize, int requestIndex);

//Prompts the user for input.
void requestsFromUser(Request* requestsArr, int n);

//Uses dynamic programming to calculate the most optimized scheduling possible (maximizing the sum of weights.)
//The memo will be used reconstruct the sequence of requests later in the main() function.
//Complexity: O(n)
int optimizeScheduling(Request* requestsArr, int index, pair<int, int>* memo);


//Solves the Weighted Intreval Scheduling problem. To calculate the maximum sum of compatible weights, the algorithm first sorts all
//requests in ascending order of finishing time. Then for each request at position i, it calculate its weight + the optimized weight sum of all the
//requests starting from the beginning of requestsArr until the latest previous compatible request, and compares that value to the optimized
//weight sum of the requests ending at position i+1. Whenever a subproblem is solved, it is stored in the memo.
//Complexity = O(nlogn), due to sorting.
int main() {

	int n, prevFinishTime = 0;

	cout << "Enter the number of requests: ";
	cin >> n;

	Request* requestsArr = new Request[n];

	requestsFromUser(requestsArr, n);

	forward_list<int> optimumScheduling;
	int optimumSchedulingWeight;
	pair<int, int>* memo = new pair<int, int>[n];
	
	for (int i = 0; i < n; i++)
	{
		memo[i].first = -1;
		memo[i].second = -2;
	}

	optimumSchedulingWeight = optimizeScheduling(requestsArr, n - 1, memo);
	cout << "\n-----------------------------------------------------------------------------------------------------------------\n";
	cout << "\nMaximum Weight Of Compatible Requests = " << optimumSchedulingWeight << endl;
	cout << "\nOptimum Compatible Set Of Requests: " << endl;

	//Reconstructing the most optimized schedule from the memo.

	while (n >= 0) {

		pair<int, int>* parentRequest = lower_bound(memo, memo + n, optimumSchedulingWeight, reconstructingComparison);
		int index = parentRequest - memo;

		optimumSchedulingWeight -= requestsArr[index].getWeight();

		optimumScheduling.push_front(index);
		n = parentRequest->second;
	
	}
	
	forward_list<int>::iterator it;
	for (it = optimumScheduling.begin(); it != optimumScheduling.end(); it++) {

		cout << "\nRequest " << requestsArr[*it].getId() << ": " << endl;
		cout << "Starting Time = " << requestsArr[*it].getStartTime() << endl;
		cout << "Finishing Time = " << requestsArr[*it].getFinishTime() << endl;
		cout << "Weight = " << requestsArr[*it].getWeight() << endl;

	}

	return 0;
}

void calcPrevCompatibles(Request* requestsArr, int arrSize, int requestIndex) {

	int prevIndex;
	forward_list<int> prevCompatibles;
	Request* prevRequest = lower_bound(requestsArr, requestsArr + arrSize, requestsArr[requestIndex].getStartTime(), prevCompatibleComparison) - 1;

	prevIndex = prevRequest - requestsArr;
	if (prevIndex >= 0) prevCompatibles.push_front(prevIndex);

	while (prevIndex - 1 >= 0 && requestsArr[prevIndex].getFinishTime() == requestsArr[prevIndex - 1].getFinishTime()) {

		prevCompatibles.push_front(prevIndex - 1);
		prevIndex--;

	}

	requestsArr[requestIndex].setLatestCompatibles(prevCompatibles);

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

	sort(requestsArr, requestsArr + n, sortingComparsion);
	for (int i = 0; i < n; i++) calcPrevCompatibles(requestsArr, n, i);

}

int optimizeScheduling(Request* requestsArr, int index, pair<int, int>* memo) {

	if (index == -1) return 0;
	if (memo[index].first != -1) return memo[index].first;

	forward_list<int> latestCompatibles = requestsArr[index].getlatestCompatibles();
	forward_list<int>::iterator it;
	int maxPrevRequest = -1;
	int maxWeight = -1;

	for (it = latestCompatibles.begin(); it != latestCompatibles.end(); it++) {

		if (optimizeScheduling(requestsArr, *it, memo) > maxWeight) {
			maxWeight = optimizeScheduling(requestsArr, *it, memo);
			maxPrevRequest = *it;
		}
		else if (optimizeScheduling(requestsArr, *it, memo) == maxWeight)
		{
			maxPrevRequest = requestsArr[*it].getWeight() > requestsArr[maxPrevRequest].getWeight() ? *it : maxPrevRequest;
		}

	}

	if (requestsArr[index].getWeight() + optimizeScheduling(requestsArr, maxPrevRequest, memo) > optimizeScheduling(requestsArr, index - 1, memo)) {
		memo[index].first = requestsArr[index].getWeight() + optimizeScheduling(requestsArr, maxPrevRequest, memo);
		memo[index].second = maxPrevRequest;
	}
	else memo[index].first = optimizeScheduling(requestsArr, index - 1, memo);

	return memo[index].first;

}