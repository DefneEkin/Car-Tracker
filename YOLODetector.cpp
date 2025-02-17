#include "YOLODetector.hpp"

YOLODetector::YOLODetector(const string & model_config, const string & model_weights) {
    net = cv::dnn::readNetFromDarknet(model_config, model_weights);
    if (net.empty()) {
        throw runtime_error("Failed to load YOLO model");
    }
}

vector<cv::String> YOLODetector::getOutputsNames() {
    static vector<cv::String> names;
    if (names.empty()) {
        vector<int> outLayers = net.getUnconnectedOutLayers();
        vector<cv::String> layersNames = net.getLayerNames();
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i) {
            names[i] = layersNames[outLayers[i] - 1];
        }
    }
    return names;
}

void YOLODetector::detect(cv::Mat & frame, vector<cv::Mat> & outs) {
    cv::Mat blob;
    cv::dnn::blobFromImage(frame, blob, 1/255.0, cv::Size(416, 416), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);
    net.forward(outs, getOutputsNames());
}
