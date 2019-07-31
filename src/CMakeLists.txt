cmake_minimum_required(VERSION 3.10)
project(opengl_tmp_poc VERSION 1.0.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -w")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -pthread")

#glfw
set(GLFW_DIR ${THIRDPARTY_DIR}/glfw-3.2)
set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include)
if (WIN32)
    set(GLFW_LIB_DIR ${GLFW_DIR}/lib/win)
    set(GLFW_LIBRARIES ${GLFW_LIB_DIR}/glfw3dll.lib)
    set(GLFW_BIN_DIR ${GLFW_LIB_DIR})
else()
    set(GLFW_LIB_DIR ${GLFW_DIR}/lib/linux)
    set(GLFW_LIBRARIES ${GLFW_LIB_DIR}/libglfw.so)
endif()

#glm
set(GLM_DIR ${THIRDPARTY_DIR}/glm-0.9.7.1)
set(GLM_INCLUDE_DIR ${GLM_DIR})

#glew
set(GLEW_DIR ${THIRDPARTY_DIR}/glew-1.13.0)
set(GLEW_INCLUDE_DIR ${GLEW_DIR}/include)
add_definitions(-DGLEW_STATIC)

#opengl
if (CMAKE_COMPILER_IS_GNUCC)
    set(OPENGL_LIBRARIES GL)
endif()

set(EIGEN_INCLUDE_DIR ${THIRDPARTY_DIR}/eigen3.2.10)

set(SOURCES
    ${GLEW_DIR}/src/glew.c
	main.cpp
    viewer/window/Window.cpp
    viewer/window/InputControl.cpp
    viewer/render/RendererContext.cpp
    viewer/render/PointCloudRenderer.cpp
    viewer/render/AxisRenderer.cpp
    viewer/render/PlotRenderer.cpp
    viewer/render/PolarGridRenderer.cpp
  	viewer/render/primitives/CubeRenderer.cpp
    examples/viewer_2d.cpp
    examples/viewer_3d.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${EIGEN_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})

#include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)

else()
    include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    #target_link_libraries(${PROJECT_NAME} stdc++fs rt)
    #target_link_libraries(${PROJECT_NAME} rt)
endif()

# if(WIN32)
#     copy_file_to_target_dir(${PROJECT_NAME} ${GLFW_BIN_DIR}/glfw3.dll)
# endif()
