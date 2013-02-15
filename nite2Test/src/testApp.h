#pragma once

#include "ofMain.h"

#include "ofxOpenNi2.h"
#include "ofxNiteUI.h"



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

		ofxOpenNi2 _ofxOpenNi2;
		ofxOniDevice oniDevice;
		ofxDepthStream depthStream;
		ofxColorStream colorStream;

		ofxNiteUI niteUI;

};
