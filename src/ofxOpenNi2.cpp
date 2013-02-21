#include "ofxOpenNi2.h"

#include "OpenNI.h"

using namespace openni;


namespace ofxNi
{
	ServerOptions Server::defaultOptions;
	DeviceMap Server::devices;
	ofPtr<Server> instance;

	
	string toString(Server o)
	{
		stringstream ss;
		ss << "ofxOpenNi2: ";
		// list of known/open devices
		return ss.str();

	}

	string toString(const openni::DeviceState& ds)
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
	Server::Server(void)
	{
		Version v = OpenNI::getVersion();
		ofLog() << "OpenNI Version: " << toString(v);
	}


	Server::~Server(void)
	{
		openni::OpenNI::shutdown();
	}

	void Server::setup(ServerOptions options)
	{
		if (instance.use_count() > 0) return;

		instance = ofPtr<Server>(new Server());

		openni::Status rc = openni::OpenNI::initialize();
		if (rc != ONI_STATUS_OK)
		{
			ofLogError() << openni::OpenNI::getExtendedError();
			throw ("Initialize failed\n%s\n", openni::OpenNI::getExtendedError());
		}

		Array<DeviceInfo> deviceInfoList;
		OpenNI::enumerateDevices(&deviceInfoList);

		int deviceCount = deviceInfoList.getSize();
		ofLog() << deviceCount << " device" << ((deviceCount != 1) ? "s" : "") << " found";
		for (int i = 0; i < deviceInfoList.getSize(); i++)
		{
			const DeviceInfo& deviceInfo = deviceInfoList[i];
			ofLog() << "#" << i << ": " << toString(deviceInfo);

			devices[string(deviceInfo.getUri())] = ofPtr<ofxOniDevice>(new ofxOniDevice);//ofxOniDevice();
		}

		OpenNI::addListener(&listener);

		for(DeviceMap::iterator it = devices.begin(); it != devices.end(); it++)
		{
			it->second->setup(it->first.c_str());
		}
	}

	void Server::update()
	{
		for(DeviceMap::iterator it = devices.begin(); it != devices.end(); it++)
		{
			it->second->update();
		}
	}

	void Server::draw()
	{
		ofPushMatrix();
		for(DeviceMap::iterator it = devices.begin(); it != devices.end(); it++)
		{
			it->second->draw();
			ofTranslate(0, it->second->depthStream.getPixels()->getHeight(),0); 
		}
		ofPopMatrix();
	}

}