#include "Car.hpp"

void Car::update(const Car & c2) {
    if (this == &c2) return;
  
    frame_no = c2.frame_no;
    x_center = c2.x_center;
    y_center = c2.y_center;
    width = c2.width;
    height = c2.height;
}
