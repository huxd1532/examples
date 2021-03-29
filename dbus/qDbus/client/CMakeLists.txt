cmake_minimum_required(VERSION 3.1)

set(BIN_NAME qdbus_client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5DBus REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/utils/)

file(GLOB SRCS "*.h" "*.cpp")

add_executable(${BIN_NAME} ${SRCS} ${UTILS_FILES})

target_include_directories(${BIN_NAME} PUBLIC
    ${Qt5DBus_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME}
    ${Qt5DBus_LIBRARIES}
)



