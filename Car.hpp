#ifndef CAR_HPP
#define CAR_HPP

#include <vector>

struct Car {
    int id;
    int frame_no;
    float x_center;
    float y_center;
    float width;
    float height; 

    void update(const Car & c2);
};

#endif
