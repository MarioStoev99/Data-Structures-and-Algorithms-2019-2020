#pragma once
#include "Request.h"

class GoRequest : public Request {
public:
	GoRequest(unsigned _floor = 0, unsigned _time = 0);
};