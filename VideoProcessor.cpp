#include "VideoProcessor.hpp"
#include <fcntl.h>
#include <unistd.h>

VideoProcessor::VideoProcessor(const string & video_path, const string & output_path, YOLODetector & detector, CarTracker & tracker)
    : video_path(video_path), output_path(output_path), detector(detector), tracker(tracker) {}

void VideoProcessor::process() {
    cv::VideoCapture cap(video_path);
    if (!cap.isOpened()) {
        throw runtime_error("Failed to open video file");
    }

    int frameCount = 0;
    cv::TickMeter tm;
    const int car_class_index = 2;
    float obj_threshold = 0.98;
    float conf_threshold = 0.98;

    cv::Mat frame;
    while (cap.read(frame)) {
        tm.start();
        vector<cv::Mat> outs;
        detector.detect(frame, outs);

        for (const auto& out : outs) {
            float* data = (float*)out.data;
            for (int j = 0; j < out.rows; j++) {
                float* pred = data + j * out.cols;
                float objectness = pred[4];

                if (objectness < obj_threshold) continue;

                cv::Mat class_scores = out.row(j).colRange(5, out.cols);
                cv::Point max_class_point;
                double confidence = 0;
                cv::minMaxLoc(class_scores, NULL, &confidence, NULL, &max_class_point);

                if (confidence < conf_threshold || max_class_point.x != car_class_index) continue;

                Car detected_car;
                detected_car.x_center = pred[0] * frame.cols;
                detected_car.y_center = pred[1] * frame.rows;
                detected_car.width = pred[2] * frame.cols;
                detected_car.height = pred[3] * frame.rows;
                detected_car.frame_no = frameCount;

                int car_id = tracker.check_and_update_cars(car_vector, detected_car);

                cv::rectangle(frame, cv::Point(detected_car.x_center - detected_car.width / 2, detected_car.y_center - detected_car.height / 2),
                              cv::Point(detected_car.x_center + detected_car.width / 2, detected_car.y_center + detected_car.height / 2),
                              cv::Scalar(0, 0, 255), 2);
                cv::putText(frame, "Car " + to_string(car_id), cv::Point(detected_car.x_center, detected_car.y_center - 10),
                            cv::FONT_HERSHEY_SIMPLEX, 2.0, cv::Scalar(0, 0, 255), 4);
            }
        }
        tm.stop();
        frameCount++;
    }
}
