#pragma once
#include "ofThread.h"
#include "ofPixels.h"
#include "ofTexture.h"

namespace openni
{
	class Device;
	class VideoStream;
}

class ofxColorStream : public ofThread
{

public:

	void setup(ofPtr<openni::Device> device = ofPtr<openni::Device>(), bool isVerbose = false);
	void draw();
	void exit();

	ofPtr<openni::Device> getDevice() const { return device; }
	ofPtr<openni::VideoStream> getStream() const { return stream; }
	
	int readFrame();
	bool isValid();
	int getFrameIndex() const { return frameIndex; }
	uint64_t getTimestamp() const { return timestamp; }

	const ofPtr<ofPixels> getPixels() const { return pixels[0]; }

protected:
	ofPtr<ofPixels> pixels[2];
	ofTexture texture;
	int frameIndex;
	uint64_t timestamp;
	
	virtual void threadedFunction();
	void allocateBuffers();
	ofPtr<openni::Device> device;
	ofPtr<openni::VideoStream> stream;

};
