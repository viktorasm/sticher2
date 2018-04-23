#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>


inline void processSingleImage(const char * const file, std::function<void(cv::Mat &)> callback) {
	cv::Mat img = cv::imread(file);
	callback(img);
	cv::waitKey(0);
}

inline void videoSource(std::function<void(cv::Mat &)> callback) {
	cv::Mat original;
	cv::Mat final;

	cv::VideoCapture cap;          //initialize capture
	cap.open(1);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1024);
	cap.set(CV_CAP_PROP_SETTINGS, 1);

	while (1) {
		cap >> original;          //copy webcam stream to image

		callback(original);
		cv::waitKey(33);
	}
}
