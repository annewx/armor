//
// Created by anne on 12/31/23.
//

#include<math.h>
#include "vector"
#include "offset.hpp"
#include "iostream"
#include <thread>
#include <cmath>
void pitch_off() {
    double offset_time;
    double offset_y;
    double g = 9.8;
    int iteration = 20;
    double air_k = 0.01;
    double aim_y, real_y, theta, time;
    double x_distance, y_distance;
    x_distance = 10;
    y_distance = 10;
    aim_y = y_distance;
    double speed = 16;
    for (int i = 0; i < iteration; i++) {
        theta = atan2(aim_y, x_distance);
        time = (exp(air_k * x_distance) - 1) / (air_k * speed * cos(theta));
        real_y = speed * sin(theta) * time - g * (time * time) / 2;
        aim_y = aim_y + (y_distance - real_y);
        if (abs(real_y - y_distance) < 0.001) {
            offset_time = time;
            offset_y = aim_y * 100;
        }
    }
}