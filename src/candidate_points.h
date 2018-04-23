#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

void findCandidatePoints(cv::Mat &source, std::vector<cv::Point2d> &points);
