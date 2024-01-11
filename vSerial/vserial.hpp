//
// Created by anne on 1/11/24.
//

#ifndef ARMOR_VSERIAL_HPP
#define ARMOR_VSERIAL_HPP
#ifndef ARMOR_SERIAL_HPP
#define ARMOR_SERIAL_HPP



#include <thread>
#include <vector>
#include <memory>
#include <unistd.h>
#include <CSerialPort/SerialPort.h>
#include "../vSerial/packet.h"
#include <string.h>


using namespace itas109;

class visionSerial {
public:

    explicit visionSerial(const char* devName_, const int baudRate_)
            :isOk{false},devName{devName_},baudRate{baudRate_},ser{new CSerialPort(devName_)}
    {
        watchDogThread=std::thread(&visionSerial::watchDogThredFun,std::ref(*this));
        // ser.setReadIntervalTimeout(5);
        sendThread=std::thread(&visionSerial::sendThreadFun,std::ref(*this));
        reciveThread=std::thread(&visionSerial::receiveThreadFun,std::ref(*this));
    };
    ~visionSerial(){
        reciveThread.detach();
        sendThread.detach();
        watchDogThread.detach();
        isOk=false;
        if(ser->isOpen()){
            ser->close();
        }
    };
    inline void visionUpdate(visionData &vision){
        vision.head=0xa5;
        visionArray_.data=vision;
    };
    inline void robotUpdate(robotData &robot){
        robot=robotArray_.data;
    };

    bool isOk;
private:

    void sendThreadFun(){
        while(true){
            // usleep(5000);
            ser->writeData(visionArray_.array,sizeof(visionArray));
            isOk=ser->isOpen();
        }
    };
    void receiveThreadFun(){
        while(true){
            // usleep(5000);
            std::vector<uint8_t> head(2);
            std::vector<uint8_t> array(sizeof(robotArray)-2);
            ser->readData(head.data(),2);
            if(head[0]==0xa5 && head[1]==0x00){
                ser->readData(array.data(),sizeof(robotArray)-2);
                array.reserve(sizeof(robotArray));
                array.insert(array.begin(),head[1]);array.insert(array.begin(),head[0]);
                memcpy(robotArray_.array,array.data(),sizeof(robotArray));
            }
            isOk=ser->isOpen();
        }
    };
    void watchDogThredFun() {
        while (true) {
            if (isOk) {
                std::this_thread::sleep_for(std::chrono::seconds(2));
            } else {
                ser->init(devName, baudRate);
                isOk = ser->open();
            }
        }
    };
    const char* devName;
    const int baudRate;
    std::unique_ptr<CSerialPort> ser;
    std::thread sendThread;
    std::thread reciveThread;
    std::thread watchDogThread;
    visionArray visionArray_;
    robotArray robotArray_;
};



#endif //ARMOR_SERIAL_HPP

#endif //ARMOR_VSERIAL_HPP
