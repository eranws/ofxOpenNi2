#pragma once

#include "ofMain.h"

#include "..\ofxOniDevice.h"
#include "..\ofxDepthStream.h"
#include "..\ofxColorStream.h"
#include "ofxNiteUI.h"

#define OFX_UI_NO_XML


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxOniDevice oniDevice;
		ofxDepthStream depthStream;
		ofxColorStream colorStream;

		ofxNiteUI niteUI;

};
