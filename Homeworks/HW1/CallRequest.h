#pragma once
#include "Request.h"

class CallRequest : public Request {
private : 
	string dir;
public : 
	CallRequest(unsigned _floor = 0, unsigned _time = 0, string _dir = "");
};