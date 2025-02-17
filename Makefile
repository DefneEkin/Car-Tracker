CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

TARGET = car_tracker

SRCS = main.cpp Car.cpp CarTracker.cpp YOLODetector.cpp VideoProcessor.cpp

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
