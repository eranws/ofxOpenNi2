#include "ofxOniDevice.h"
#include "OpenNI.h"
#include "ofLog.h"
#include "ofUtils.h"
#include "NiEvents.h"

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

	//TODO: setup here. (query for devices)
	depthStream.setup(device);
	colorStream.setup(device);

	recorder.setup(*this);
	//isFile ? don't start
	startThread(false);
}

void ofxOniDevice::exit()
{
	stopThread();
	waitForThread();

	//TODO: Dtor
	depthStream.exit();
	colorStream.exit();
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
	return (this != 0 && device.use_count() > 0 && device->isValid());
}

void ofxOniDevice::setStreamSync( bool b )
{
	device->setDepthColorSyncEnabled(b);
}

void ofxOniDevice::draw()
{
	depthStream.draw();
	ofTranslate(depthStream.getPixels()->getWidth(), 0);
	colorStream.draw();
}

void ofxOniDevice::threadedFunction()
{
	while (isThreadRunning())
	{
		depthStream.readFrame();
		colorStream.readFrame();

		DeviceData dd;
		dd.depthFrameIndex = depthStream.getFrameIndex();
		dd.depthTimestamp = depthStream.getTimestamp();

		dd.depthFrame = depthStream.getPixels();
		dd.colorFrame = colorStream.getPixels();
		ofNotifyEvent(getNiEvents().onDeviceUpdate, dd); //TODO send id
	}
}

