//
// Created by anne on 12/25/23.
//

#ifndef ARMOR_PACKET_H
#define ARMOR_PACKET_H

#include  <cstdint>
#include <vector>
#include <algorithm>

#pragma pack(2)
struct visionData{
    uint16_t head;
    float aimYaw;
    float aimPitch;
};

struct robotData{
    uint16_t head;
    uint8_t mode;
    uint8_t foeColor;
    float robotYaw;
    float robotPitch;
    float muzzleSpeed;
};

union visionArray{
    struct visionData data;
    uint8_t array[sizeof(struct visionData)];
};

union robotArray{
    struct robotData data;
    uint8_t array[sizeof(struct robotData)];
};

#pragma pack()

#endif //ARMOR_PACKET_H
