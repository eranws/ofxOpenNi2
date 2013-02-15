#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){

	//list<Command>
	//Command :
	// name
	// list<Args>

	try
	{
		oniDevice.setup();
	}
	catch (exception e)
	{
		try
		{
			oniDevice.setup("c:\\1.oni");
		}
		catch(exception e)
		{
			throw(e);
		}
	}

	depthStream.setup(oniDevice.getDevice());
	colorStream.setup(oniDevice.getDevice());

	oniDevice.setRegistration(true);

	//handTracker.setup(depthStream.getDevice());

	niteUI.setup();


}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	niteUI.draw();

	ofSetColor(255);

	ofTexture colorTexture;
	ofPixels colorPixels = *colorStream.getPixels(); 
	colorTexture.allocate(colorPixels);
	colorTexture.loadData(colorPixels);
	colorTexture.draw(0,0);

	ofTexture depthTexture;

	ofPtr<ofShortPixels> depthRawPixels = depthStream.getPixels();

	ofPixels depthPixels;
	depthPixels.allocate(depthRawPixels->getWidth(), depthRawPixels->getHeight(), OF_PIXELS_RGBA);

	const unsigned short* prd = depthRawPixels->getPixels();
	unsigned char* pd = depthPixels.getPixels();
	for (int i = 0; i < depthRawPixels->size(); i++)
	{
		const short minDepth = 450;
		short s = prd[i];
		char x = (s < minDepth) ? 0 : powf(s - minDepth, 0.7f);
		pd[4 * i + 0] = 255 - x;
		pd[4 * i + 1] = 255 - x;
		pd[4 * i + 2] = 255 - x;
		pd[4 * i + 3] = x;

	}

	depthTexture.allocate(depthPixels);
	depthTexture.loadData(depthPixels);
	depthTexture.draw(640,0);

	colorTexture.draw(320,0);
	depthTexture.draw(320,0);


	ofSetColor(255);
	colorTexture.draw(0,0);


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	niteUI.keyPressed(key);
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



