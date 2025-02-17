#ifndef CAR_TRACKER_HPP
#define CAR_TRACKER_HPP

#include "Car.hpp"
#include <vector>

class CarTracker {

public:
    int check_and_update_cars(std::vector<Car> & car_vector, Car & detected_car);
};

#endif
