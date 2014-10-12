#include "CamOpenCV.h"

namespace caminput
{

    CamOpenCV::CamOpenCV(int id, std::string service_name):
    Cam(id, service_name)
	{
		cam.open(id);

		cam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
		cam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

		cv::Mat img;
		cam >> img;

		std::cout <<" cam ptr " << &cam << std::endl;

		if(!cam.isOpened())  // check if we succeeded
			throw;

		mWidth  = img.size().width;
		mHeight = img.size().height;

	}

	CamOpenCV::~CamOpenCV()
	{
		cam.release();
	}

	void CamOpenCV::start()
	{

	}

	void CamOpenCV::stop()
	{

	}

	void CamOpenCV::getImageCopy(cv::Mat& inputImage)
	{

		cam >> inputImage;
	}

}



