cmake_minimum_required (VERSION 2.8.9)
project(project)

set(OPENCV_LIBRARIES opencv_imgproc opencv_core opencv_highgui)
set(RS_SDK_LIBRARIES rs_projection rs_image rs_playback rs_record rs_log_utils)
set(PROJECT_LINK_LIBS
    ${RS_SDK_LIBRARIES}
    realsense
    pthread
    object_recognition
    mraa
    ${OPENCV_LIBRARIES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -pthread -fPIC -std=c++0x -fexceptions -frtti")

set(SOURCES Obstacle_Utils.cpp Object_Recognition.cpp
    main.cpp
)

include_directories(
    ${SYSROOT}/usr/include
    ${SYSROOT}/usr/include/librealsense 
    ${SYSROOT}/usr/include/librealsense/object_recognition
    ${SYSROOT}/usr/local/include/mraa
)

link_directories(
    ${SYSROOT}/usr/lib)

add_executable(${PROJECT_NAME} AudioManager.cpp ObstacleManager.cpp Object_Recognition.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
