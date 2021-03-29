cmake_minimum_required(VERSION 3.1)

set(BIN_NAME qdbus_server)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5DBus REQUIRED)

file(GLOB SRCS "*.h" "*.cpp")

add_executable(${BIN_NAME} ${SRCS})

target_include_directories(${BIN_NAME} PUBLIC
    ${Qt5DBus_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME}
    ${Qt5DBus_LIBRARIES}
)

# dbus conf
install(FILES data/com.deepin.qdbus_server.conf
        DESTINATION share/dbus-1/system.d/)


