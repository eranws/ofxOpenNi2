#include "testApp.h"

void testApp::setup(){
	ofxNi::Server::setup();
	//ofxNi::registerDepthFrameEvents(this);
	//ofxNi::registerColorFrameEvents(this);
	ofxNi::registerDeviceEvents(this);
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

void testApp::onDeviceUpdate( DeviceData& dd)
{
	cout << "DD: " << dd.colorFrame->getWidth() << "!" << endl;
	cout << "DD: " << dd.depthFrame->getHeight() << "?" << endl;
	
}
