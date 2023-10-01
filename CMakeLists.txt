cmake_minimum_required(VERSION 3.2...3.2)
project(VisualCpp)
set(INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Install")
set(CMAKE_INSTALL_PREFIX  "${INSTALL_DIR}")
message("Install dir: ${INSTALL_DIR}")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(SFML)
add_subdirectory(VisualExercises)
