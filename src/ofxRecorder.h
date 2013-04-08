#pragma once
#include <vector>
#include "ofTypes.h"
//#include "ofxOniDevice.h"

namespace openni
{
	class Device;
	class VideoStream;
	class Recorder;
}

typedef enum
{
	RECORD_DEPTH_STREAM = 0x0001,
	RECORD_COLOR_STREAM = 0x0010,
	RECORD_BOTH = RECORD_DEPTH_STREAM | RECORD_COLOR_STREAM
} RecordStreams;

class ofxOniDevice;
class ofxRecorder
{

public:

	//void setup(ofPtr<openni::VideoStream> stream = ofPtr<openni::VideoStream>());
	void setup();

	void start(string filename, const ofxOniDevice& device, RecordStreams recordStraems);
	void stop();

	void exit();

	bool isRecording() const {return _isRecording;}

	//ofPtr<openni::Recorder> getRecorder() const { return recorder; }
	
protected:
	
	void addStream(ofPtr<openni::VideoStream> stream);
	std::vector<ofPtr<openni::VideoStream>> _streams; //make a list?
	ofPtr<openni::Recorder> recorder;
	
	//ofxOniDevice _device;
	bool _isRecording;
	bool allowLossyCompression;
};
