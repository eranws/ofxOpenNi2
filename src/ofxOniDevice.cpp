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

