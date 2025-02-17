#ifndef YOLO_DETECTOR_HPP
#define YOLO_DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <vector>

using namespace std;

class YOLODetector {
public:
    YOLODetector(const string & model_config, const string & model_weights);
    vector<cv::String> getOutputsNames();
    void detect(cv::Mat & frame, vector<cv::Mat> & outs);

private:
    cv::dnn::Net net;
};

#endif
