cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0072)
  set(OpenGL_GL_PREFERENCE LEGACY)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fpie -pie")


find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(DtkCMake REQUIRED)
find_package(DtkWidget REQUIRED)


file(GLOB SRCS "*.h" "*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/utils/)

add_executable(gltest ${SRCS} ${UTILS_FILES})
target_link_libraries(gltest
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${DtkWidget_LIBRARIES}
    ${Qt5DBus_LIBRARIES}
)

#target_include_directories(installer PUBLIC
#    ${OPENGL_INCLUDE_DIRS}
#    ${GLUT_INCLUDE_DIRS}
#    ${Qt5Widgets_INCLUDE_DIRS}
#    ${DtkWidget_INCLUDE_DIRS}
#    ${Qt5DBus_INCLUDE_DIRS}

#)
