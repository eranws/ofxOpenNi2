#include "ofxOpenNi2.h"

#include "OpenNI.h"
using namespace openni;

string toString(ofxOpenNi2 o)
{
	stringstream ss;
	ss << "ofxOpenNi2: ";
	// list of known/open devices
	return ss.str();

}

string toString(const DeviceState& ds)
{
	string s = "DeviceState";
	switch(ds)
	{
		case DEVICE_STATE_OK: return s + "ok";
		case DEVICE_STATE_ERROR: return s + "error";
		case DEVICE_STATE_NOT_READY: return s + "not ready";
		case DEVICE_STATE_EOF: return s + "eof";
		default: return s + "?";
	}
}



string toString(const openni::DeviceInfo& deviceInfo)
{
	stringstream ss;
	ss  << "DeviceInfo: "
		"Name: " << deviceInfo.getName() << endl <<
		"Uri: " << deviceInfo.getUri() <<  endl <<
		"UsbProductId: " << deviceInfo.getUsbProductId() << endl <<
		"UsbVendorId: " << deviceInfo.getUsbVendorId() << endl <<
		"Vendor: " << deviceInfo.getVendor();

	return ss.str();
}


string toString(const openni::Version& v)
{
	stringstream ss;
	string sep = ".";
	ss << v.major << sep << v.minor << sep << v.build << sep << v.maintenance;
	return ss.str();
}



class ofxOpenNi2Listener : public openni::OpenNI::Listener
{
	virtual void onDeviceStateChanged( const DeviceInfo* di, DeviceState ds) 
	{
		ofLog() << "onDeviceStateChanged: " << toString(ds);
		ofLog() << toString(*di);
	}

	virtual void onDeviceConnected( const DeviceInfo* di) 
	{
		ofLog() << "onDeviceConnected: " << toString(*di);
	}

	virtual void onDeviceDisconnected( const DeviceInfo* di) 
	{
		ofLog() << "onDeviceDisconnected: " << toString(*di);
	}

} listener;




//TOOD: use setup/exit callbacks, to use as a standalone app, inherit from some base class 'ofxModule'
ofxOpenNi2::ofxOpenNi2(void)
{
	Version v = OpenNI::getVersion();
	ofLog() << "OpenNI Version: " << toString(v);

	openni::Status rc = openni::OpenNI::initialize();
	if (rc != ONI_STATUS_OK)
	{
		ofLogError() << openni::OpenNI::getExtendedError();
		//throw ("Initialize failed\n%s\n", openni::OpenNI::getExtendedError());
	}

	Array<DeviceInfo> deviceInfoList;
	OpenNI::enumerateDevices(&deviceInfoList);
	
	int deviceCount = deviceInfoList.getSize();
	ofLog() << deviceCount << " device" << ((deviceCount != 1) ? "s" : "") << " found";
	for (int i = 0; i < deviceInfoList.getSize(); i++)
	{
		const DeviceInfo& deviceInfo = deviceInfoList[i];
			ofLog() << "#" << i << ": " << toString(deviceInfo);
	}

	OpenNI::addListener(&listener);
}


ofxOpenNi2::~ofxOpenNi2(void)
{
	openni::OpenNI::shutdown();
}

void ofxOpenNi2::setup()
{
	try
	{
		oniDevice.setup();
	}
	catch (exception e)
	{
		try
		{

			
			system("dir");
			oniDevice.setup(ofToDataPath("1.oni").c_str());
		}
		catch(exception e)
		{
			throw(e);
		}
	}

	depthStream.setup(oniDevice.getDevice());
	colorStream.setup(oniDevice.getDevice());

	oniDevice.setRegistration(true);

}

void ofxOpenNi2::draw()
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
