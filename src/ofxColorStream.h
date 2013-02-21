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

	ofPtr<ofPixels> getPixels() const { return pixels[0]; }
	ofPtr<ofTexture> getTexture() const { return textures[0]; }

protected:
	ofPtr<ofPixels> pixels[2];
	ofPtr<ofTexture> textures[2];
	
	void allocateBuffers();
	ofPtr<openni::Device> device;
	ofPtr<openni::VideoStream> stream;

};
