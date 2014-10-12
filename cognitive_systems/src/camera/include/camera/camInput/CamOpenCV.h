#ifndef CAMOPENCV_H_
#define CAMOPENCV_H_

#include "Cam.h"

using namespace std;

using namespace cv;

namespace caminput
{

	class CamOpenCV : public caminput::Cam
	{

	public:

        CamOpenCV(int id, std::string service_name);

        virtual ~CamOpenCV();

		void start();

		void stop();

		void getImageCopy(cv::Mat& inputImage);

	private:

		cv::VideoCapture cam;



	};

};

#endif /*CAMOPENCV_H_*/
