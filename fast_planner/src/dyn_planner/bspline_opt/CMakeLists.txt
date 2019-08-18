cmake_minimum_required(VERSION 2.8.3)
project(bspline_opt)

find_package(Eigen3 REQUIRED)
find_package(PCL 1.7 REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  visualization_msgs
  plan_env
)

find_package(NLopt
          PATHS  ${PROJECT_SOURCE_DIR}/../lib/nlopt-2.6.1/install/lib/cmake/nlopt
)

set(NLopt_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/../lib/nlopt-2.6.1/install/include)
 message("my nlopt include :  ${NLopt_INCLUDE_DIRS}" ) 

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES bspline_opt
 CATKIN_DEPENDS plan_env
#  DEPENDS system_lib
)

include_directories( 
    SYSTEM 
    include 
    ${catkin_INCLUDE_DIRS}
    ${Eigen3_INCLUDE_DIRS} 
    ${PCL_INCLUDE_DIRS}
    ${NLopt_INCLUDE_DIRS}
)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -O3 -Wall")

add_library( bspline_opt 
    src/bspline_optimizer.cpp 
    src/non_uniform_bspline.cpp 
    )

target_link_libraries( bspline_opt
    ${catkin_LIBRARIES} 
    ${PROJECT_SOURCE_DIR}/../lib/nlopt-2.6.1/install/lib/libnlopt.so.0
    )  
