#pragma once
#include <vector>
#include "ofTypes.h"

namespace openni
{
	class Device;
	class VideoStream;
	class Recorder;
}

class ofxOniDevice;
class ofxRecorder
{

public:

	//void setup(ofPtr<openni::VideoStream> stream = ofPtr<openni::VideoStream>());
	void setup(const ofxOniDevice& device);

	void start(string filename);
	void stop();

	void exit();

	bool isRecording() const {return _isRecording;}

	//ofPtr<openni::Recorder> getRecorder() const { return recorder; }
	
protected:
	
	void addStream(ofPtr<openni::VideoStream> stream);
	std::vector<ofPtr<openni::VideoStream>> _streams; //make a list?
	ofPtr<openni::Recorder> recorder;

	bool _isRecording;
	bool allowLossyCompression;

};
