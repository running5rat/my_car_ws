cmake_minimum_required(VERSION 3.0.2)
project(zmq_node)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  actionlib
  robot_msgs
  roscpp
  roslib
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ libzmq)
pkg_check_modules(JSONCPP jsoncpp)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

link_directories(${ZMQ_LIBRARY_DIRS})

catkin_package()


#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# FIND GTest
#########################################################
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})


file(GLOB_RECURSE BTHeadLibrary include/draw_node/*.h)
set(BTSrcLibrary
src/zmq_node/pddl_sub_ctl/lib/openGL_lib.cpp
src/zmq_node/pddl_sub_ctl/tree_node.cpp
)
add_library(${PROJECT_NAME} ${BTSrcLibrary} ${BTHeadLibrary})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${GTEST_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
set(libs ${catkin_LIBRARIES}  ${ZMQ_LIBRARIES}  ${JSONCPP_LIBRARIES})
set(incs ./include/zmq_node   ./include/draw_node ./include/sim_perception ../robot_library/my_lib/include ${catkin_INCLUDE_DIRS}${ZMQ_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIRS} )

include_directories(${incs})

aux_source_directory(src/zmq_node/pddl_sub_ctl/.  SRC_LIST1)
add_executable(pddl_sub ${SRC_LIST1} )
target_link_libraries(pddl_sub  ${libs} ${PROJECT_NAME})

add_executable(pddl_pub src/zmq_node/pddl_pub.cpp  )
target_link_libraries(pddl_pub  ${libs} )

add_executable(sim_perception_node src/sim_perception_node/sim_perception.cpp  )
target_link_libraries(sim_perception_node  ${libs} )



