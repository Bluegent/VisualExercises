cmake_minimum_required(VERSION 3.2...3.2)
project(VisualCpp)

set(SFML_CHECKOUT "${CMAKE_SOURCE_DIR}/SFML")
if(NOT EXISTS "${SFML_CHECKOUT}/cmake")
execute_process(
    COMMAND git clone --depth 1 --branch 2.6.0 https://github.com/SFML/SFML.git "${SFML_CHECKOUT}"
)
endif()

set(INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Install")
set(CMAKE_INSTALL_PREFIX  "${INSTALL_DIR}")
message("Install dir: ${INSTALL_DIR}")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(SFML)
add_subdirectory(VeLib)
add_subdirectory(VisualExercises)

# Set the output directory for the test executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${INSTALL_DIR}")

SET(GTEST_CHECKOUT "${CMAKE_CURRENT_SOURCE_DIR}/gtest")
if(NOT EXISTS "${GTEST_CHECKOUT}/googletest")
execute_process(
    COMMAND git clone --depth 1 --branch v1.14.x https://github.com/google/googletest.git "${GTEST_CHECKOUT}"
)
endif()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(gtest)
add_subdirectory(Test)

