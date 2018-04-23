#include <vector>
#include <functional>

#include "candidate_points.h"
#include "image_sources.h"

inline void processImage(cv::Mat &source) {
	std::vector<cv::Point2d> points;
	findCandidatePoints(source, points);


	// preview intermediate result
	const cv::Scalar colorRed(0, 0, 255.0);
	for (const cv::Point &pt : points) {
			cv::circle(source, pt, 3, colorRed);
	}

	cv::imshow("Source", source);
}


int main() {
	processSingleImage("img//sample1.bmp", processImage);
	//videoSource();
	return 0;


}

