cmake_minimum_required(VERSION 2.8.0)
project(wmr_ros)

find_package(catkin REQUIRED COMPONENTS roscpp nav_msgs geometry_msgs sensor_msgs std_msgs tf)
find_package(Qt5Core)
find_package(Qt5Network)

catkin_package( #INCLUDE_DIRS
#  include
# CATKIN_DEPENDS
#  qt_build roscpp
# DEPENDS
#  Qt4
)

include_directories(include)
#include(${QT_USE_FILE})
include_directories(${catkin_INCLUDE_DIRS})

rosbuild_prepare_qt4(QtCore QtNetwork)

file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/wmr_ros/*.hpp)

QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp include/wmr_ros/*.hpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

#link_directories(/usr/include/WMR/)
add_executable(wmr_ros ${QT_SOURCES} ${QT_MOC_HPP})
qt5_use_modules(wmr_ros Network Core)
target_link_libraries(wmr_ros ${QT_LIBRARIES} ${catkin_LIBRARIES} -lWMR -lpthread)
install(TARGETS wmr_ros RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
add_dependencies(wmr_ros ${PROJECT_NAME}_gencpp)
