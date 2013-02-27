#pragma once
#include "ofTypes.h"

#include "ofxDepthStream.h"
#include "ofxColorStream.h"
#include "ofThread.h"
#include "ofxRecorder.h"

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
	void addListener(ListenerClass * listener)
	{
		ofAddListener(getNiEvents().onDeviceUpdate, listener, &ListenerClass::onDeviceUpdate);
	}
	
	template<class ListenerClass>
	void removeListener(ListenerClass * listener)
	{
		ofRemoveListener(getNiEvents().onDeviceUpdate, listener, &ListenerClass::onDeviceUpdate);
	}
	//TODO: SensorMap, template/inheritance
	
	void startRecording(string recordingFilename) 
	{
		recorder.start(recordingFilename);
	}


	bool isRecording() 
	{
		return recorder.isRecording();
	}


	void stopRecording() 
	{
		recorder.stop();
	}

protected:
	ofPtr<openni::Device> device;
	virtual void threadedFunction();

	ofxDepthStream depthStream;
	ofxColorStream colorStream;
	ofxRecorder recorder;
};

