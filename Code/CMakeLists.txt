cmake_minimum_required (VERSION 2.8.9)
project(project)

SET(LIBRS_LIBRARIES realsense)
SET(LINUXSDK_LIBRARIES realsense_image realsense_projection realsense_playback realsense_record realsense_log_utils)

set(OPENCV_LIBRARIES opencv_imgproc opencv_core opencv_highgui)
#set(RS_SDK_LIBRARIES rs_projection rs_image rs_playback rs_record rs_log_utils)
set(PROJECT_LINK_LIBS
    #${RS_SDK_LIBRARIES}
    ${LIBRS_LIBRARIES}
    ${LINUXSDK_LIBRARIES}
    realsense
    pthread
    realsense_object_recognition
    #mraa
    ${OPENCV_LIBRARIES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -pthread -fPIC -std=c++0x -fexceptions -frtti ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

set(SOURCES AudioManager.cpp ObstacleManager.cpp NavigationUtils.cpp Object_Recognition.cpp AudioManager.h ObstacleManager.h NavigationUtils.h Object_Recognition.h main.cpp camera_utils.h camera_utils.cpp displaymanager.cpp processingmanager.cpp processingmanager.h)

include_directories(
    ${SYSROOT}/usr/include
    ${SYSROOT}/usr/include/librealsense 
    ${SYSROOT}/usr/include/librealsense/object_recognition
    ${SYSROOT}/home/ntuser-chavy/workspace/realsense_sdk/sdk/include
    #${SYSROOT}/usr/local/include/mraa
)

link_directories(
    ${SYSROOT}/usr/lib)

add_executable(${PROJECT_NAME} AudioManager.cpp ObstacleManager.cpp NavigationUtils.cpp Object_Recognition.cpp
                               AudioManager.h ObstacleManager.h NavigationUtils.h Object_Recognition.h main.cpp camera_utils.h camera_utils.cpp displaymanager.cpp displaymanager.h processingmanager.cpp processingmanager.h)

target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)




