#ifndef CAMGIGE_H_
#define CAMGIGE_H_

#include "Cam.h"
#undef signals
#include <arv.h>

#define XSIZE 640
#define YSIZE 480
#define UPDATE_RATE 0.05

using namespace std;

using namespace cv;

namespace caminput
{

	class CamGigE : public caminput::Cam
	{

	public:

		CamGigE(int id);

		virtual ~CamGigE();

		void start();

		void stop();

		void getImageCopy(cv::Mat& inputImage);

	private:

		unsigned char* grab(double timeout=1.0f);

	private:

		ArvCamera *camera;
		ArvStream *stream;

		int width, height;

		int xshift, yshift, exposure, gain, payload;

		bool isCapturing;

		double framerate;

		unsigned char *rawdata;

	};

};

#endif /*CAMGIGE_H_*/
