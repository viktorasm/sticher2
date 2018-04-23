#include "candidate_points.h"

// detects bright spots and returns a list of centers
void findCandidatePoints(cv::Mat &source, std::vector<cv::Point2d> &points) {
	cv::Mat destination;
	cv::cvtColor(source, destination, cv::COLOR_BGR2GRAY);

	cv::threshold(destination, destination, 200, 255, cv::THRESH_BINARY);
	//cv::imshow("threshold", destination);
	//cv::invert(destination, destination);


	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(destination, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


	const cv::Scalar colorRed(0, 0, 255.0);

	for (const std::vector<cv::Point> &contour : contours) {
		const cv::Moments moments = cv::moments(contour);
		const double area = cv::contourArea(contour);
		if (area > 0) {
			const cv::Point2d center(moments.m10 / moments.m00, moments.m01 / moments.m00);
			points.push_back(center);
		}
	}
}