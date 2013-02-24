#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void draw();


		void onDepthFrame( ofPtr<ofShortPixels>& frame);
		void onColorFrame( ofPtr<ofPixels>& frame);
		


};
