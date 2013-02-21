#pragma once
#include "ofTypes.h"

#include "ofxDepthStream.h"
#include "ofxColorStream.h"

namespace openni
{
	class Device;
}

class ofxOniDevice
{

public:

	void setup(const char* uri = NULL);
	void draw();
	void exit();

	bool isValid();

	ofPtr<openni::Device> getDevice() const { return device; }
	
	void setRegistration( bool b ); //TODO: access via settings object
	void setStreamSync( bool b );

	//TODO: SensorMap, template/inheritance
	ofxDepthStream depthStream;
	ofxColorStream colorStream;

protected:
	ofPtr<openni::Device> device;
};

