cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(MotionDetection)
project(DetectionSystem)

set(CMAKE_CPP_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/area.cpp
)

find_package(OpenCV REQUIRED)
add_executable(MotionDetection motion_detection.cpp)
add_executable(DetectionSystem ${SRC_FILES})
target_include_directories(MotionDetection PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(DetectionSystem PRIVATE ${OpenCV_INCLUDE_DIRS} ${INC_DIR})
target_link_libraries(MotionDetection PRIVATE ${OpenCV_LIBS})
target_link_libraries(DetectionSystem PRIVATE ${OpenCV_LIBS})
