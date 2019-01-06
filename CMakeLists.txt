project(opengl-tutorials)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("--std=c++17")

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE source_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE headers_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.hpp")

file(GLOB_RECURSE vert_shaders_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.vert")
file(GLOB_RECURSE frag_shaders_list RELATIVE ${CMAKE_SOURCE_DIR} "src/*.frag")

file(MAKE_DIRECTORY "bin/shaders")

foreach(vertshader IN LISTS vert_shaders_list)
    get_filename_component(source_path "${vertshader}" NAME)    
    configure_file("${vertshader}" "bin/shaders/${source_path}" COPYONLY)
endforeach()

foreach(fragshader IN LISTS frag_shaders_list)
    get_filename_component(source_path "${fragshader}" NAME)
    configure_file("${fragshader}" "bin/shaders/${source_path}" COPYONLY)
endforeach()

foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(source IN LISTS headers_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

add_executable(opengl-tutorials ${source_list} ${headers_list})

add_custom_command(TARGET opengl-tutorials POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src/data $<TARGET_FILE_DIR:opengl-tutorials>/data)

target_include_directories(opengl-tutorials PRIVATE "src")
target_link_libraries(opengl-tutorials ${CONAN_LIBS})