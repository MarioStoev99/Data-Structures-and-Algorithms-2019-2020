#include "CallRequest.h"

CallRequest::CallRequest(unsigned _floor, unsigned _time,string _dir) : Request(_floor,_time) {
	if (_dir != "UP" && _dir != "DOWN")
		throw logic_error("The direction can be only up or down");
	dir = _dir;
}