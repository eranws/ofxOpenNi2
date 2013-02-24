#include "testApp.h"
#include "ofxOpenNi2.h"

void testApp::setup(){
	ofxNi::Server::setup();
	ofxNi::registerDepthFrameEvents(this);
}

void testApp::draw(){
	ofSetColor(255);
	//ofxNi::Server::draw();
}

void testApp::onDepthFrame( ofPtr<ofShortPixels>& frame )
{
	cout << frame->getWidth() << "!" << endl;
}
