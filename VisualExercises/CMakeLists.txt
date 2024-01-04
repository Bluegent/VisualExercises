project(VisualExercises)

# Set the path to the directory containing SFMLConfig.cmake (modify this path as needed)
#set(SFML_DIR "${INSTALL_DIR}/lib/cmake/SFML")
SET(SFML_INCLUDE_DIR "${INSTALL_DIR}/include")

# Find the SFML library
#find_package(SFML 2.6.0 COMPONENTS graphics audio REQUIRED)

# Add your source files from the source folder
file(GLOB_RECURSE PROJECT_SRC RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        include/*.cpp
        include/*.h
        src/*.cpp
        src/*.h
        )

#on windows, the resolution of Sleep() is typically 15.6ms, so we need to set a lower resolution for a decent way to limit framerate
if(WIN32)
    set(PROJECT_SRC "${PROJECT_SRC};pd/WinSleepUnfucker.hpp;pd/WinSleepUnfucker.cpp")
endif()
add_executable(${PROJECT_NAME} ${PROJECT_SRC})
message("Project Sources: ${PROJECT_SRC}")

foreach(source IN LISTS PROJECT_SRC)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()  

target_include_directories(${PROJECT_NAME} INTERFACE include)
include_directories(include ${SFML_INCLUDE_DIR})

# Link the SFML libraries to your executable
target_link_libraries(${PROJECT_NAME}  sfml-graphics sfml-audio)

#on windows, the resolution of Sleep() is typically 15.6ms, so we need to set a lower resolution for a decent way to limit framerate
if(WIN32)
   target_include_directories(${PROJECT_NAME} INTERFACE pd)
   include_directories(include pd)
   target_link_libraries(${PROJECT_NAME}  winmm.lib)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SFML_INCLUDE_DIR}
)

message("SFML include dir: ${SFML_INCLUDE_DIR}")

set_target_properties(${PROJECT_NAME}  PROPERTIES
    VS_DEBUGGER_COMMAND "${INSTALL_DIR}/${PROJECT_NAME}.exe"
    VS_DEBUGGER_COMMAND_ARGUMENTS ""  # Add any command-line arguments here
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --config $<CONFIG>
)


install(TARGETS ${PROJECT_NAME}  DESTINATION ${INSTALL_DIR})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
       "${INSTALL_DIR}/bin/"
       "${INSTALL_DIR}"
    COMMENT "Copying file after build **************"
)
