project(VeTest)


# Add your source files from the source folder
file(GLOB_RECURSE PROJECT_SRC RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        src/*.cpp
        src/*.hpp
        ../VisualExercises/src/*.hpp
        ../VisualExercises/src/*.cpp
        )
        
message("${PROJECT_NAME} Sources: ${PROJECT_SRC}")
foreach(source IN LISTS PROJECT_SRC)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

SET(SFML_INCLUDE_DIR "${INSTALL_DIR}/include")

include_directories(include ${SFML_INCLUDE_DIR})

enable_testing()

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main VeLib)
target_include_directories(${PROJECT_NAME}  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/../VisualExercises/src")

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


include(GoogleTest)
add_test(NAME "${PROJECT_NAME}.exe" COMMAND "${PROJECT_NAME}.exe")
set_tests_properties("${PROJECT_NAME}.exe"  PROPERTIES EXCLUDE_FROM_ALL TRUE)