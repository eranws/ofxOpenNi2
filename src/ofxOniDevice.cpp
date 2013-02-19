#include "ofxOniDevice.h"
#include "OpenNI.h"
#include "ofLog.h"
#include "ofUtils.h"

void ofxOniDevice::setup(const char* uri)
{
	using namespace openni;
	device = ofPtr<openni::Device>(new openni::Device);
	openni::Status rc = device->open(uri);
	if (rc != ONI_STATUS_OK)
	{
		ofLogWarning(__FILE__, "in line:" + ofToString(__LINE__) + string(OpenNI::getExtendedError()));
		throw std::exception(OpenNI::getExtendedError());
	}

	depthStream.setup(device);
	colorStream.setup(device);

	//isFile ? don't start
	//startThread(false);
}

void ofxOniDevice::exit()
{
	device->close();
}

void ofxOniDevice::setRegistration( bool b )
{
	if(device->isImageRegistrationModeSupported(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR))
	{
		device->setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	}
	else
	{
		ofLogWarning() << "Image Registration Unsupported";
	}
	
}

bool ofxOniDevice::isValid()
{
	return (device.use_count() > 0 && device->isValid());
}

void ofxOniDevice::setStreamSync( bool b )
{
	device->setDepthColorSyncEnabled(b);
}

void ofxOniDevice::draw()
{
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

void ofxOniDevice::update()
{
	depthStream.readFrame(); //update?
	colorStream.readFrame(); //update?
}

