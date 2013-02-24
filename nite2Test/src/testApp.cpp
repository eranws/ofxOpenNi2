#include "testApp.h"
#include "ofxOpenNi2.h"

void testApp::setup(){
	ofxNi::Server::setup();
	ofxNi::registerDepthFrameEvents(this);
	ofxNi::registerColorFrameEvents(this);
}

void testApp::draw(){
	ofSetColor(255);
	//ofxNi::Server::draw();
}

void testApp::onDepthFrame( ofPtr<ofShortPixels>& frame )
{
	cout << frame->getWidth() << "!" << endl;
}

void testApp::onColorFrame( ofPtr<ofPixels>& frame )
{
	cout << frame->getHeight() << "?" << endl;
}
