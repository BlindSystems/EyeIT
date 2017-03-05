cmake_minimum_required(VERSION 2.8)
project(offlineReader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g" )
include_directories()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} realsense_image realsense_samples_time_sync realsense_playback realsense_record realsense_log_utils realsense opencv_imgproc opencv_core pthread realsense
                                        opencv_videoio opencv_highgui opencv_core  opencv_video  opencv_imgcodecs
                                      boost_filesystem boost_system)




install(TARGETS ${PROJECT_NAME} DESTINATION bin)
