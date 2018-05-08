#include "EventHandle.h"


bool operator<(const EventHandle &lhs, const EventHandle &rhs) {
	return lhs.priority < rhs.priority;
}
