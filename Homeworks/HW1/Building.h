#pragma once
#include <list>
#include "Lift.h"
#include "LList.h"
#include "Request.h"
#include "GoRequest.h"
#include "CallRequest.h"
#include <fstream>
#include "FileNotFoundException.hpp"
#include <cmath>

class Building {
private : 
	int requestsNumber;
	int sizeFloors;
	Lift first;
	Lift second;
	LList<Request*> requests;

private : 
	static const string firstLiftCharacter;
	static const string secondLiftCharacter;
	static const string upDirection;
	static const string downDirection;
	static const string callRequest;
	static const string goRequest;
private : 
	void unserializeDigits(ifstream& file);
	void unserializeRequests(ifstream& file);

	void choiceForLift(int&,int&) const;
	bool isInTheSameDirectionAsRequest();
	void getCapacityLifts(int&, int&) const;
	
	void liftHandling(Request*,const string&);
	bool hasIntermediateRequest(int, int, int, int);
	void printRequestsInfo(Request* request,const string& lift,int dir) const;
	void checkAndProcessIntermediateRequest(int&,int,const string&);
	void deleteGoRequest(list<Request*>&, const string&, int& );
	void printGoRequests(list<Request*>& goRequests,const string&,int&,int);
	void sortByFloor(list<Request*>&,Request*,int);
	void requestsPerformance(int& liftCap,const string& lift);
public : 
	explicit Building(const char* filename);
	Building(const Building&) = delete;
	Building& operator=(const Building&) = delete;
	~Building();
	void runRequests();
};