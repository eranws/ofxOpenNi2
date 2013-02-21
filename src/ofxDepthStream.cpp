#include "ofxDepthStream.h"
#include "OpenNI.h"


void ofxDepthStream::setup(ofPtr<openni::Device> device, bool isVerbose)
{
	this->device = device;

	openni::Status rc;

	if (device->getSensorInfo(openni::SENSOR_DEPTH) != NULL)
	{
		stream = ofPtr<openni::VideoStream>(new openni::VideoStream);
		rc = stream->create(*device, openni::SENSOR_DEPTH);
		if (rc != openni::STATUS_OK)
		{
			throw ("Couldn't create depth stream\n%s\n", openni::OpenNI::getExtendedError());
		}
	}

	allocateBuffers();

	rc = stream->start();
	if (rc != openni::STATUS_OK)
	{
		throw ("Couldn't start the depth stream\n%s\n", openni::OpenNI::getExtendedError());

	}
}

void ofxDepthStream::exit()
{
	stopThread();
	waitForThread();

	stream->stop();
	stream->destroy();
}

void ofxDepthStream::threadedFunction()
{
	while (isThreadRunning())
	{
		readFrame();
	}
}

ofVec3f ofxDepthStream::cameraToWorld(ofVec2f p)
{
	ofVec3f world;

	ofPtr<ofShortPixels> pix = getPixels();

	int index = pix->getPixelIndex(int(p.x), int(p.y));
	unsigned short z = (*pix)[index];

	openni::CoordinateConverter::convertDepthToWorld(*stream, p.x, p.y, float(z), &world.x, &world.y, &world.z);
	return world;
}



void ofxDepthStream::allocateBuffers()
{
	int w = stream->getVideoMode().getResolutionX();
	int h = stream->getVideoMode().getResolutionY();

	for (int i = 0; i < 2; i++)
	{
		pixels[i] = ofPtr<ofShortPixels>(new ofShortPixels);
		pixels[i]->allocate(w, h, OF_IMAGE_GRAYSCALE);

		texture.allocate(*pixels[i]);
	}
	
}

bool ofxDepthStream::isValid()
{
	return (getStream().use_count() > 0 && getStream()->isValid());
}

int ofxDepthStream::readFrame()
{
	openni::VideoFrameRef frame;
	openni::Status rc;
	rc = stream->readFrame(&frame);
	if (rc != openni::STATUS_OK)
	{
		printf("Wait failed\n");
		return rc;
	}

	if (frame.getVideoMode().getPixelFormat() != openni::PIXEL_FORMAT_DEPTH_1_MM && frame.getVideoMode().getPixelFormat() != openni::PIXEL_FORMAT_DEPTH_100_UM)
	{
		printf("Unexpected frame format\n");
		return rc;
	}

	//openni::DepthPixel* pDepth = (openni::DepthPixel*)frame.getData();
	//int middleIndex = (frame.getHeight()+1)*frame.getWidth()/2;
	//printf("[%08llu] %8d fps:%d\n", (long long)frame.getTimestamp(), pDepth[middleIndex], stream->getVideoMode().getFps());

	pixels[1]->setFromPixels((const unsigned short*)frame.getData(), pixels[1]->getWidth(), pixels[1]->getHeight(), OF_IMAGE_GRAYSCALE);

	swap(pixels[0], pixels[1]);

	return openni::STATUS_OK;
}

ofTexture depthTextureToColor(const ofShortPixels& raw)
{
	ofTexture depthTexture;

	ofPixels depthPixels;
	depthPixels.allocate(raw.getWidth(), raw.getHeight(), OF_PIXELS_RGBA);

	const unsigned short* prd = raw.getPixels();
	unsigned char* pd = depthPixels.getPixels();
	for (int i = 0; i < raw.size(); i++)
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

	return depthTexture;
}


void ofxDepthStream::draw()
{
	ofPtr<ofShortPixels> depthRawPixels = getPixels();
	texture = depthTextureToColor(*depthRawPixels);
	texture.draw(0, 0);
}

