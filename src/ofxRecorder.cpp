#include "ofxRecorder.h"
#include "OpenNI.h"
#include "ofxOniDevice.h"

void ofxRecorder::setup()
{
	recorder = ofPtr<openni::Recorder>(new openni::Recorder);
	_isRecording = false;
	allowLossyCompression = false;
}

void ofxRecorder::start(string filename, const ofxOniDevice& device, RecordStreams recordStreams)
{
	_streams.clear();
	if (recordStreams & RECORD_COLOR_STREAM)
	{
		addStream(device.getColorStream().getStream());
	}

	if (recordStreams & RECORD_DEPTH_STREAM)
	{
		addStream(device.getDepthStream().getStream());	
	}

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
