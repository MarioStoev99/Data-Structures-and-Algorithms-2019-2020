#include "Building.h"

const string Building::firstLiftCharacter = "L";
const string Building::secondLiftCharacter = "S";
const string Building::upDirection = "up";
const string Building::downDirection = "down";
const string Building::callRequest = "call";
const string Building::goRequest = "go";

void Building::unserializeDigits(ifstream& file) {
	int F, L, S, R;
	file >> F >> L >> S >> R;
	if (F <= 0) {
		throw logic_error("Negative size for Building's floors");
	}
	if (R < 0) {
		throw logic_error("The requests must be Zero or positive");
	}
	requestsNumber = R;
	sizeFloors = F;
	first.setMaxCapPlaces(L);
	second.setMaxCapPlaces(S);
	file.get(); // new line
}
void Building::unserializeRequests(ifstream& file) {
	while (!file.eof()) {
		string requestType, dir;
		int time, floorsNumber;
		getline(file, requestType, ' ');
		if (requestType == callRequest) {
			getline(file, dir, ' ');
		}
		file >> floorsNumber >> time;
		if (floorsNumber > sizeFloors || floorsNumber <= 0) {
			throw logic_error("Invalid floor number.Enter positive");
		}
		if (time < 0) {
			throw logic_error("The time request can't be negative number or zero");
		}
		file.get();
		if (requestType == callRequest) {
			Request* request = new CallRequest(floorsNumber, time, dir);
			requests.push_end(request);
		}
		else if (requestType == goRequest) {
			Request* request = new GoRequest(floorsNumber, time);
			requests.push_end(request);
		}
		else {
			throw logic_error("Such request doesn't exist");
		}
	}
}
Building::Building(const char* filename) {
	ifstream file(filename);
	if (!file) {
		throw FileNotFoundException();
	}
	unserializeDigits(file);
	unserializeRequests(file);
}
Building::~Building() {
	while (!requests.is_empty()) {
		Request* ptr = requests.front();
		requests.pop_front();
		delete ptr;
	}
}
void Building::choiceForLift(int& differenceBetweenFirstLiftAndTargetRequest,int& differenceBetweenSecondLiftAndTargetRequest) const {
	int targetRequestFloor = requests.front()->getFloor();
	differenceBetweenFirstLiftAndTargetRequest = abs(targetRequestFloor - first.getCurrentFloor());
	differenceBetweenSecondLiftAndTargetRequest = abs(targetRequestFloor - second.getCurrentFloor());
}
bool Building::isInTheSameDirectionAsRequest() {
	Request* callRequest = requests.front();
	requests.pop_front();
	int goRequestFloor = requests.front()->getFloor();
	requests.push_front(callRequest);
	int targetRequestFloor = requests.front()->getFloor();
	return second.getCurrentFloor() < targetRequestFloor &&
		targetRequestFloor < goRequestFloor ||
		goRequestFloor < targetRequestFloor &&
		targetRequestFloor < second.getCurrentFloor();
}
void Building::getCapacityLifts(int& firstLiftCap,int& secondLiftCap) const {
	firstLiftCap = first.getMaxCapPlaces();
	secondLiftCap = second.getMaxCapPlaces();
}
void Building::liftHandling(Request* request,const string& lift) {
	if (lift == firstLiftCharacter) {
		printRequestsInfo(request, lift, first.getCurrentFloor() - request->getFloor());
		first.setCurrentFloor(request->getFloor());
	}
	else {
		printRequestsInfo(request, lift, second.getCurrentFloor() - request->getFloor());
		second.setCurrentFloor(request->getFloor());
	}
}
bool Building::hasIntermediateRequest(int liftFloor,int callRequestFloor,int goRequestFloor,int lastCallRequestFloor) {
	return liftFloor <= callRequestFloor && callRequestFloor < goRequestFloor &&
		goRequestFloor <= lastCallRequestFloor || lastCallRequestFloor <= goRequestFloor &&
		goRequestFloor < callRequestFloor && callRequestFloor <= liftFloor;
}
void Building::deleteGoRequest(list<Request*>& goRequests,const string& lift,int& liftCap) {
	Request* goRequest = goRequests.front();
	goRequests.pop_front();
	liftHandling(goRequest, lift);
	++liftCap;
	delete goRequest;
	goRequest = nullptr;
}
void Building::printGoRequests(list<Request*>& goRequests,const string& lift,int& liftCap,int direction) {
	int releasePlace = 0;
	while (!goRequests.empty()) {
		if (!requests.is_empty()) {
			if (liftCap == 0 || direction == 0) {
				deleteGoRequest(goRequests, lift, releasePlace);
			}
			else if (goRequests.front()->getFloor() <= requests.front()->getFloor() && direction < 0) {
				deleteGoRequest(goRequests, lift, releasePlace);
			}
			else if (goRequests.front()->getFloor() >= requests.front()->getFloor() && direction > 0) {
				deleteGoRequest(goRequests, lift, releasePlace);
			}
			else {
				return;
			}
		}
		else {
			deleteGoRequest(goRequests, lift, releasePlace);
		}
	}
	liftCap += releasePlace;
}
void Building::sortByFloor(list<Request*>& goRequests,Request* request,int direction) {
	if (goRequests.empty()) {
		goRequests.push_front(request);
		return;
	}
	list<Request*>::iterator it = goRequests.begin();
	for (it; it != goRequests.end(); ++it) {
		if (request->getFloor() < (*it)->getFloor() && direction < 0) {
			goRequests.insert(it, request);
			return;
		}
		if (request->getFloor() > (*it)->getFloor() && direction > 0) {
			goRequests.insert(it, request);
			return;
		}
	}
	goRequests.push_back(request);
}
void Building::checkAndProcessIntermediateRequest(int& liftCap,int lastCallRequestFloor,const string& lift) {
	list<Request*> goRequests;
	int liftFloor = liftFloor = lift == firstLiftCharacter ? first.getCurrentFloor() : second.getCurrentFloor(); 
	int getDirection = liftFloor - lastCallRequestFloor;
	while (liftCap && !requests.is_empty()) {
		Request* intermediateCallRequest = requests.front();
		requests.pop_front();
		Request* intermediateGoRequest = requests.front();
		requests.pop_front();
		liftFloor = lift == firstLiftCharacter ? first.getCurrentFloor() : second.getCurrentFloor();
		getDirection = liftFloor - lastCallRequestFloor;
		if (hasIntermediateRequest(liftFloor, intermediateCallRequest->getFloor(), intermediateGoRequest->getFloor(), lastCallRequestFloor)) {
			--liftCap;
			liftHandling(intermediateCallRequest, lift);
			sortByFloor(goRequests, intermediateGoRequest, getDirection);
			printGoRequests(goRequests, lift, liftCap, getDirection);
		}
		else {
			requests.push_front(intermediateGoRequest);
			requests.push_front(intermediateCallRequest);
			break;
		}
		delete intermediateCallRequest;
		intermediateCallRequest = nullptr;
	}
	getDirection = 0;
	printGoRequests(goRequests, lift, liftCap,getDirection);
}
void Building::requestsPerformance(int& liftCap,const string& lift) {
	Request* callRequest = requests.front();
	requests.pop_front();
	Request* goRequest = requests.front();
	requests.pop_front();
	checkAndProcessIntermediateRequest(liftCap, callRequest->getFloor(), lift);
	liftHandling(callRequest, lift);
	delete callRequest;
	callRequest = nullptr;
	--liftCap;
	checkAndProcessIntermediateRequest(liftCap, goRequest->getFloor(), lift);
	liftHandling(goRequest, lift);
	++liftCap;
	delete goRequest;
	goRequest = nullptr;
}
void Building::printRequestsInfo(Request* request,const string& lift,int dir) const {
	if (lift == firstLiftCharacter) {
		cout << firstLiftCharacter << " ";
	}
	else {
		cout << secondLiftCharacter << " ";
	}
	cout << request->getFloor() << " " << request->getTime() << " ";
	if (dir > 0) {
		cout << upDirection << endl;
	}
	else {
		cout << downDirection << endl;
	}
}
void Building::runRequests() {
	while (!requests.is_empty()) {
		int differenceBetweenFirstLiftAndTargetRequest,differenceBetweenSecondLiftAndTargetRequest,firstLiftCap, secondLiftCap;
		bool sameDirectionSecondLift;
		choiceForLift(differenceBetweenFirstLiftAndTargetRequest, differenceBetweenSecondLiftAndTargetRequest);
		getCapacityLifts(firstLiftCap, secondLiftCap);
		sameDirectionSecondLift = isInTheSameDirectionAsRequest();
		if (differenceBetweenFirstLiftAndTargetRequest > differenceBetweenSecondLiftAndTargetRequest)
		{
			requestsPerformance(secondLiftCap,secondLiftCharacter);
			if (!requests.is_empty()) {
				requestsPerformance(firstLiftCap,firstLiftCharacter);
			}
		}
		else if (differenceBetweenFirstLiftAndTargetRequest == differenceBetweenSecondLiftAndTargetRequest &&
			sameDirectionSecondLift) {
			requestsPerformance(secondLiftCap, secondLiftCharacter);
			if (!requests.is_empty()) {
				requestsPerformance(firstLiftCap, firstLiftCharacter);
			}
		}
		else {
			requestsPerformance(firstLiftCap,firstLiftCharacter);
			if (!requests.is_empty()) {
				requestsPerformance(secondLiftCap,secondLiftCharacter);
			}
		}
	}
}