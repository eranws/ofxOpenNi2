#pragma once

#include "ofxOniDevice.h"

#include "ofxRecorder.h"

class ofxOpenNi2
{
public:
	ofxOpenNi2(void);
	~ofxOpenNi2(void);

	void setup();
	void draw();

	ofxOniDevice oniDevice;
};

