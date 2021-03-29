cmake_minimum_required(VERSION 3.1)

project(qdbus-test)

configure_file(${CMAKE_SOURCE_DIR}/utils/environments.h.in ${CMAKE_SOURCE_DIR}/utils/environments.h @ONLY)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fpie -pie")

# Install settings
set(CMAKE_INSTALL_PREFIX /usr)

execute_process(COMMAND bash "-c" "qdbuscpp2xml -A server/qdbus_server.h -o com.deepin.daemon.qdbus_server.xml"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#execute_process(COMMAND bash "-c" "qdbusxml2cpp ../com.deepin.daemon.qdbus_server.xml -i qdbus_server.h -a qdbus_server_adaptor"
#    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/server)

execute_process(COMMAND bash "-c" "qdbusxml2cpp ../com.deepin.daemon.qdbus_server.xml -p qdbus_server_proxy"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/utils)

file(GLOB UTILS_FILES "${CMAKE_SOURCE_DIR}/utils/*.h" "${CMAKE_SOURCE_DIR}/utils/*.cpp")

add_subdirectory(server)
add_subdirectory(client)
