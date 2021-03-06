cmake_minimum_required(VERSION 3.15)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)

# Set up libraries with CMake projects
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
add_subdirectory(include/glfw)
add_subdirectory(include/glm)
add_subdirectory(include/assimp)

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

# Add project files in bulk - this means we have to reload our project when we add a class, but we don't have to add every single class to this list.
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp src/*.frag src/*.vert)
file(GLOB_RECURSE PROJECT_HEADERS src/*.h)

add_executable(
        ${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES}
        include/imgui/imconfig.h
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_internal.h
        include/imgui/imgui_widgets.cpp
        include/imgui/imgui.cpp
        include/imgui/imgui.h
        include/imgui/imstb_rectpack.h
        include/imgui/imstb_textedit.h
        include/imgui/imstb_truetype.h
)

# Define where to look for headers
include_directories(
        src/
        include/glad/include
        include/glfw/include
        include/spdlog/include
        include/glm
        include/stb_image
        include/imgui
)


add_library(glad include/glad/src/glad.c)
#add_library(stb_image include/stb_image/stb_image.cpp)
#find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} assimp glad glfw glm ${GLFW_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_gl_LIBRARY})

if(MSVC)
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4 /wd4458)
else()
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++17)
        if(NOT WIN32)
                set(GLAD_LIBRARIES dl)
        endif()
endif()

set (resourceSourcePath "${CMAKE_SOURCE_DIR}/res")
set (resourceDestPath "${CMAKE_BINARY_DIR}/res")
set (shaderSourcePath "${CMAKE_SOURCE_DIR}/src/shaders")
set (shaderDestPath "${CMAKE_BINARY_DIR}/shaders")

add_custom_command(
 TARGET ${PROJECT_NAME} PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E create_symlink ${resourceSourcePath} ${resourceDestPath} 
 DEPENDS ${resourceDestPath}
 COMMENT "Symlinking resources folder ${resourceSourcePath} => ${resourceDestPath}"
)

add_custom_command(
 TARGET ${PROJECT_NAME} PRE_BUILD
 COMMAND ${CMAKE_COMMAND} -E create_symlink ${shaderSourcePath} ${shaderDestPath} 
 DEPENDS ${shaderDestPath}
 COMMENT "Symlinking shaders folder from ${shaderSourcePath} => ${shaderDestPath}"
)

