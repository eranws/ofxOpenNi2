#pragma once

#include "ofxOniDevice.h"

#include "ofxRecorder.h"

class ofxOpenNi2
{
public:
	ofxOpenNi2(void);
	~ofxOpenNi2(void);

	void setup();
	void update();
	void draw();

	typedef map<const std::string, ofPtr<ofxOniDevice>> DeviceMap;

	DeviceMap devices;

	friend class ofxOpenNi2Listener;
		//		oniDevice;
};

