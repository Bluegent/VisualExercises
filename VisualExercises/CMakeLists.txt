project(VisualExercises)

# Add your source files from the source folder
file(GLOB_RECURSE PROJECT_SRC RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        include/*.cpp
        include/*.hpp
        src/*.cpp
        src/*.hpp
        main.cpp
        )

add_executable(${PROJECT_NAME} ${PROJECT_SRC})
message("Project Sources: ${PROJECT_SRC}")

foreach(source IN LISTS PROJECT_SRC)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()  

target_include_directories(${PROJECT_NAME} INTERFACE include)
include_directories(include)

# Link the SFML libraries to your executable
target_link_libraries(${PROJECT_NAME}  VeLib VeLibrary)

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
