#include "testApp.h"
#include "ofxOpenNi2.h"

void testApp::setup(){
	ofxNi::Server::setup();
}

void testApp::draw(){
	ofSetColor(255);
	ofxNi::Server::draw();
}