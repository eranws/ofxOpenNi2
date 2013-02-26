#pragma once
#include "ofTypes.h"

#include "ofxDepthStream.h"
#include "ofxColorStream.h"
#include "ofThread.h"

namespace openni
{
	class Device;
}

class ofxOniDevice : public ofThread
{

public:

	void setup(const char* uri = NULL);
	void draw();
	void exit();

	bool isValid();

	ofPtr<openni::Device> getDevice() const { return device; }
	const ofxDepthStream& getDepthStream() const { return depthStream; }
	const ofxColorStream& getColorStream() const { return colorStream; }
	
	void setRegistration( bool b ); //TODO: access via settings object
	void setStreamSync( bool b );

	template<class ListenerClass>
	void addListener(ListenerClass * listener){
		ofAddListener(getNiEvents().onDeviceUpdate, listener, &ListenerClass::onDeviceUpdate);
	}
	//TODO: SensorMap, template/inheritance
	
protected:
	ofPtr<openni::Device> device;
	virtual void threadedFunction();

	ofxDepthStream depthStream;
	ofxColorStream colorStream;

};

