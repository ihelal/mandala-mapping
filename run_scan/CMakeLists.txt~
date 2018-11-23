cmake_minimum_required(VERSION 2.8.3)
project(run_scan)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
)


catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(run_scan src/run_scan.cpp)

target_link_libraries(run_scan ${catkin_LIBRARIES})


