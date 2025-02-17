#include "CarTracker.hpp"

int CarTracker::check_and_update_cars(std::vector<Car> & car_vector, Car & detected_car) {
  
    float x_variance = 240;
    float y_variance = 240;
    float error_margin = 110;

    bool car_exists = false;
    int car_index = -1;

    for (size_t i = 0; i < car_vector.size(); i++) {
        Car & car = car_vector[i];

        if (((detected_car.x_center > (car.x_center - x_variance)) && (detected_car.x_center < (car.x_center + x_variance))) &&
            ((detected_car.y_center > (car.y_center - error_margin)) && (detected_car.y_center < (car.y_center + y_variance)))) {

            if (car.frame_no == detected_car.frame_no) {
                car_exists = true;
                car_index = car.id;
            } else {
                car_vector[i].update(detected_car);
                return i;
            }
        }
    }

    if (car_exists) return car_index;

    detected_car.id = car_vector.size();
    car_vector.push_back(detected_car);
    return detected_car.id;
}
