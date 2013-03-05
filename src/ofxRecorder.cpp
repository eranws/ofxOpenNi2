#include "ofxRecorder.h"
#include "OpenNI.h"
#include "ofxOniDevice.h"


void ofxRecorder::setup(const ofxOniDevice& device)
{
	recorder = ofPtr<openni::Recorder>(new openni::Recorder);
	_isRecording = false;
	allowLossyCompression = false;

	addStream(device.getColorStream().getStream());
	addStream(device.getDepthStream().getStream());
}

void ofxRecorder::start(string filename)
{
	recorder->create(filename.append(".oni").c_str()); 
	for (int i = 0; i < _streams.size(); i++)
	{
		recorder->attach(*_streams[i], allowLossyCompression);
	}
	openni::Status rc = recorder->start();
	if (rc == openni::STATUS_OK)
	{
		_isRecording = true;
	}
}

void ofxRecorder::stop()
{
	_isRecording = false;

	recorder->stop();
	recorder->destroy();
}

void ofxRecorder::exit()
{
	stop();
}

void ofxRecorder::addStream( ofPtr<openni::VideoStream> stream )
{
	_streams.push_back(stream);
}
