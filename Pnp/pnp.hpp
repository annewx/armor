//
// Created by anne on 10/28/23.
//

#ifndef ARMOR_PNP_HPP
#define ARMOR_PNP_HPP
#include <opencv2/opencv.hpp>
#include "vector"
#include "../Detect/detect.hpp"
#include "../vSerial/serial.hpp"



class pnp {
public:
    cv::Mat pre;
    cv::Mat P;
    detect *pnp_detect;
    cv::Mat distCoeffs = (Mat_<double>(5,1)<<-0.313818281448022,0.16042483,0,0,0);
    cv::Mat cameraMatrix = (Mat_<double>(3,3)<<1572.4,0,655,0,1572.4,503.4,0,0,1);
    void Pnp(class detect &detect);
    void pnpSolve(armor &armorPoint);
    double yaw,pitch,pitch_off;
    void offSet(armor &armorPoint);
    int iter = 20;
    double aim_y,ry,thera,t;
    double x,y;
    double k=0.01,g=9.8;
    double v= 16;
    double offset_t{0.5};
    double offset_y;


};


#endif //ARMOR_PNP_HPP
