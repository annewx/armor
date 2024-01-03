cmake_minimum_required(VERSION 3.25)
project(armor)

set(CMAKE_CXX_STANDARD 14)


add_executable(armor

        main.hpp  main.cpp Detect/detect.hpp Detect/detect.cpp Pnp/pnp.hpp Pnp/pnp.cpp  Serial/serial.hpp Serial/serial.cpp hik_camera/HikCam.cpp  vSerial/serial.hpp vSerial/packet.h offset/offset.hpp offset/offset.cpp)
find_package(OpenCV REQUIRED)
find_package(CSerialPort)
find_library(MVS_LIB libMvCameraControl.so /opt/MVS/lib/64/)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CSerialPort_INCLUDE_DIR})
target_link_libraries(armor ${OpenCV_LIBS} -lserialport)
target_link_libraries(armor ${MVS_LIB})
target_link_libraries(armor ${CSerialPort_LIBRARY})