#include <vector>
#include <functional>
#include <iostream>

#include "candidate_points.h"
#include "image_sources.h"


#define LOG(msg) std::cout << msg << std::endl;

inline double distance(const cv::Point2d &src, const cv::Point2d &dest) {
	// square distance will be fine probably
	auto dx = src.x - dest.x;
	auto dy = src.y - dest.y;
	return dx * dx + dy * dy;
}

inline void calcGrid(const std::vector<cv::Point2d> &points) {
	std::vector<double> distances;
	distances.resize(points.size()*points.size());
	LOG("reserved distances: " << distances.size());


	const size_t numPoints = points.size();
	for (size_t source = 0, const last = numPoints-1; source != last; source++) {
		for (size_t dest = source + 1, lastDest = numPoints; dest != lastDest; dest++) {
			const double d = distance(points.at(source), points.at(dest));
			distances.at(source*numPoints + dest) = d;
			distances.at(dest*numPoints + source) = d;
		}

	}
	LOG("distances calculated");


}

inline void processImage(cv::Mat &source) {
	std::vector<cv::Point2d> points;
	findCandidatePoints(source, points);
	calcGrid(points);


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

