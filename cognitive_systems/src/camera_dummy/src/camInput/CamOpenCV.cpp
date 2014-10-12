#include <camera/camInput/CamOpenCV.h>

namespace caminput
{

    CamOpenCV::CamOpenCV(int id, std::string service_name):
    Cam(id, service_name)
	{

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



