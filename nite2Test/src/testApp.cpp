#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){

	//list<Command>
	//Command :
	// name
	// list<Args>

	_ofxOpenNi2.setup();
}

//--------------------------------------------------------------
void testApp::update(){
	_ofxOpenNi2.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	_ofxOpenNi2.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}



