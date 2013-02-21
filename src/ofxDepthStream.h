#pragma once
#include "ofMain.h"


namespace openni
{
	class Device;
	class VideoStream;
}

class ofxDepthStream
{

public:

	void setup(ofPtr<openni::Device> device = ofPtr<openni::Device>(), bool isVerbose = false);
	void draw();
	void exit();

	ofPtr<openni::Device> getDevice() const { return device; }
	ofPtr<openni::VideoStream> getStream() const { return stream; }
	bool isValid();

	ofPtr<ofShortPixels> getPixels() const { return pixels[0]; }
	ofPtr<ofTexture> getTexture() const { return textures[0]; }

	int readFrame();

	ofVec3f cameraToWorld(ofVec2f p); //Depth Camera?

protected:
	ofPtr<ofShortPixels> pixels[2];
	ofPtr<ofTexture> textures[2];


	void allocateBuffers();
	ofPtr<openni::Device> device;
	ofPtr<openni::VideoStream> stream;
	

};
