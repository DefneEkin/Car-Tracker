#ifndef VIDEO_PROCESSOR_HPP
#define VIDEO_PROCESSOR_HPP

#include "YOLODetector.hpp"
#include "CarTracker.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;

class VideoProcessor {
public:
    VideoProcessor(const string & video_path, const string & output_path, YOLODetector & detector, CarTracker & tracker);
    void process();

private:
    string video_path;
    string output_path;
    YOLODetector & detector;
    CarTracker & tracker;
    vector<Car> car_vector;
};

#endif
