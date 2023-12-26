//
// Created by anne on 12/22/23.
//

#ifndef ARMOR_PACKET_H
#define ARMOR_PACKET_H


#include <cstdint>
#include <algorithm>



struct visionMsg{
    uint16_t head;
    float aimYaw;
    float aimPitch;
};

struct robotMsg{
    uint16_t head;
    uint8_t color;
    uint8_t model;
    float speed;
    float robotYaw;
    float robotPitch;

};
#endif //ARMOR_PACKET_H
