#include "VideoProcessor.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Incorrect number of parameters" << endl;
        return 0;
    }

    YOLODetector detector("yolov4.cfg", "yolov4.weights");
    CarTracker tracker;
    VideoProcessor processor(argv[1], argv[2], detector, tracker);
    
    processor.process();
    return 0;
}
