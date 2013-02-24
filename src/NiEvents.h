#pragma once
#include "ofEvents.h"
#include "ofUtils.h"
#include "ofPixels.h"

class TrackedPoint
{
public:

	TrackedPoint() : status(untracked)
	{
	}

	enum TrackedPointStatus
	{
		found,
		tracked,
		lost,
		untracked
	} status;

	int id;
	int time;
	ofPoint pos;

	bool isTracked(){ return status == tracked;}
	bool isFound(){ return status == found;}
	bool isLost() {	return status == lost;}
};



class NiEvents{
public:
	ofEvent<TrackedPoint> handUpdate;
	ofEvent<ofPtr<ofShortPixels> > onDepthFrame;
	ofEvent<ofPtr<ofPixels> > onColorFrame;

	//TODO: more events here...
};

NiEvents& getNiEvents();


template<class ListenerClass>
void registerHandEvents(ListenerClass * listener){
	ofAddListener(getNiEvents().handUpdate, listener, &ListenerClass::handUpdate);
}


