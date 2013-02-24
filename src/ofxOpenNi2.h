#pragma once

#include "ofxOniDevice.h"
#include "NiEvents.h"

namespace ofxNi
{
	typedef map<const std::string, ofPtr<ofxOniDevice>> DeviceMap;

	struct ServerOptions
	{
		//bool threaded
		//bool init all
		//bool noThrow
	};

	class Server
	{
	public:
		static void setup(ServerOptions = defaultOptions);
		static void draw();


		static ofPtr<ofxOniDevice> open(std::string uri);
		
		static DeviceMap devices;
		static ServerOptions defaultOptions;

		~Server();
	private:
		Server(void);
		Server(const Server&);
		Server&operator=(const Server &);
	};


	template<class ListenerClass>
	void registerDepthFrameEvents(ListenerClass * listener){
		ofAddListener(getNiEvents().onDepthFrame, listener, &ListenerClass::onDepthFrame);
	}

	template<class ListenerClass>
	void registerColorFrameEvents(ListenerClass * listener){
		ofAddListener(getNiEvents().onColorFrame, listener, &ListenerClass::onColorFrame);
	}

};
