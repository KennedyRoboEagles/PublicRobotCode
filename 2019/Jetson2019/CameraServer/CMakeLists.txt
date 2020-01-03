cmake_minimum_required(VERSION 3.5.0)

project(CameraServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wpilib REQUIRED)
find_package(OpenCV REQUIRED)

find_package(PkgConfig)
pkg_check_modules(LOG4CXX REQUIRED liblog4cxx)


include_directories(
	include
	${OpenCV_INCLUDE_DIRS}
    /usr/local/wpilib/include
    /usr/local/wpilib/include/wpiutil
    /usr/local/wpilib/include/ntcore
    /usr/local/wpilib/include/cscore
    /usr/local/wpilib/include/cameraserver
)

add_executable(camera_server src/main.cpp)

target_link_libraries(camera_server 
    ${LOG4CXX_LIBRARIES}
	${OpenCV_LIBS}
    gflags::gflags
	cameraserver ntcore cscore wpiutil
)

install(TARGETS camera_server DESTINATION bin)
install(FILES config/logger.config DESTINATION config/CameraServer)
