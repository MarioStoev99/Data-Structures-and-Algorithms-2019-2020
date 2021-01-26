#include "Lift.h"

Lift::Lift(int _maxCapPlaces,int _currentFloor)
	: maxCapPlaces(_maxCapPlaces) , currentFloor(_currentFloor ) {}
void Lift::setMaxCapPlaces(int _maxCapPlaces) {
	if (_maxCapPlaces <= 0) {
		throw logic_error("Invalid Lift's cap.Enter positive number!");
	}
	maxCapPlaces = _maxCapPlaces;
}