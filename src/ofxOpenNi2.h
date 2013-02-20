#pragma once

#include "ofxOniDevice.h"

namespace ofxNi
{
	typedef map<const std::string, ofPtr<ofxOniDevice>> DeviceMap;

	struct ServerOptions
	{
		//bool threaded
		//bool init all
	};

	class Server
	{
	public:
		static void setup(ServerOptions = defaultOptions);
		static void update();
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

};
