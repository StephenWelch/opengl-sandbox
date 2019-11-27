cmake_minimum_required(VERSION 3.15)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
        if(NOT WIN32)
                set(GLAD_LIBRARIES dl)
        endif()
endif()

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(include/glfw)

add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(learn_opengl src/main.cpp src/Window.cpp src/Window.h src/Renderer.cpp src/Renderer.h src/util.h src/Log.cpp src/Log.h)

include_directories(
        include/glad/include
        include/glfw/include
        include/spdlog/include
)


add_library(glad include/glad/src/glad.c)
#find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} glad glfw ${GLFW_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_gl_LIBRARY})
