cmake_minimum_required(VERSION 3.5.0)

# Sub projects
add_subdirectory(CameraServer)
add_subdirectory(Logger)

# Vendor libraries
add_subdirectory(vendor/gflags)
add_subdirectory(vendor/SQLiteCpp)

install(PROGRAMS scripts/start_camera_server.sh DESTINATION bin)
install(PROGRAMS scripts/start_nt_logger.sh DESTINATION bin)
