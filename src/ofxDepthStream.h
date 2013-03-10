#pragma once
#include "ofMain.h"


namespace openni
{
	class Device;
	class VideoStream;
}

class ofxDepthStream : public ofThread
{

public:

	void setup(ofPtr<openni::Device> device = ofPtr<openni::Device>(), bool isVerbose = false);
	void draw() const;
	void exit();

	ofPtr<openni::Device> getDevice() const { return device; }
	ofPtr<openni::VideoStream> getStream() const { return stream; }
	bool isValid();

	uint64_t getTimestamp() { return currentTimestamp; }
	ofPtr<ofShortPixels> getPixels() const { return pixels[0]; }

	int readFrame();

	ofVec3f cameraToWorld(ofVec2f p); //Depth Camera?
	int getFrameIndex() const { return frameIndex; }
	uint64_t getTimestamp() const { return timestamp; }

protected:
	ofPtr<ofShortPixels> pixels[2];
	ofTexture texture;
	uint64_t currentTimestamp;

	virtual void threadedFunction();
	int frameIndex;
	uint64_t timestamp;
	void allocateBuffers();
	ofPtr<openni::Device> device;
	ofPtr<openni::VideoStream> stream;
};
