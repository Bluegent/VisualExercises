project(VeLibrary)

# Set the path to the directory containing SFMLConfig.cmake
SET(SFML_INCLUDE_DIR "${INSTALL_DIR}/include")

# Add your source files from the source folder
file(GLOB_RECURSE PROJECT_SRC RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        include/*.cpp
        include/*.hpp
        src/*.cpp
        src/*.hpp
        )
        
set(PROJECT_SRC "${PROJECT_SRC};")

add_library(${PROJECT_NAME} STATIC ${PROJECT_SRC})
message("Project Sources: ${PROJECT_SRC}")

foreach(source IN LISTS PROJECT_SRC)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()  

target_include_directories(${PROJECT_NAME} INTERFACE include ${SFML_INCLUDE_DIR})
include_directories(include ${SFML_INCLUDE_DIR})

# Link the SFML libraries to your executable
target_link_libraries(${PROJECT_NAME}  sfml-graphics sfml-audio)


