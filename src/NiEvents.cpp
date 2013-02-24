#include "NiEvents.h"

NiEvents& getNiEvents()
{
	static NiEvents* events = new NiEvents;
	return *events;
}

