#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <vector>


void processImage(cv::Mat &source) {
	cv::Mat destination;
	cv::cvtColor(source, destination, cv::COLOR_BGR2GRAY);

	cv::threshold(destination, destination, 200, 255, cv::THRESH_BINARY);
	//cv::imshow("threshold", destination);
	//cv::invert(destination, destination);


	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(destination, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


	const cv::Scalar colorRed(0, 0, 255.0);

	int contourId = 0;
	for (const std::vector<cv::Point> &contour : contours) {
		contourId++;

		const cv::Moments moments = cv::moments(contour);
		const double area = cv::contourArea(contour);
		if (area > 0) {
			const cv::Point2d center(moments.m10 / moments.m00, moments.m01 / moments.m00);
			cv::circle(source, center, 3, colorRed);

			// grid.addPoint(center.x, center.y);
		}
	}


	// grid.calculateNeighbours();


/*	for (const Grid::Point &pt : grid.points) {
		if (pt.neighbours[0] != NULL) {
			cv::line(source, pt.location, pt.neighbours[0]->location, colorRed, 2);
		}

		for (const Grid::Point *neighbour : pt.neighbours) {
			if (neighbour == NULL) {
				continue;
			}
			cv::line(source, pt.location, neighbour->location, colorRed, 1);
		}
	}
	*/
	//cv::imshow("contours", destination);




	cv::imshow("Source", source);
}




inline void singleImage() {
	cv::Mat img = cv::imread("img//sample1.bmp");
	processImage(img);
	cv::waitKey(0);
}

inline void videoSource() {
	cv::Mat original;
	cv::Mat final;

	cv::VideoCapture cap;          //initialize capture
	cap.open(1);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1024);
	cap.set(CV_CAP_PROP_SETTINGS, 1);

	while (1) {
		cap >> original;          //copy webcam stream to image

		processImage(original);
		cv::waitKey(33);
	}
}

int main() {

	singleImage();
	//videoSource();
	return 0;


}

