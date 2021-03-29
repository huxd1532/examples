
set(BIN_NAME demo-1)



find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(DtkCMake REQUIRED)
find_package(DtkWidget REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


file(GLOB SRCS "*.h" "*.cpp")

add_executable(${BIN_NAME} ${SRCS})

target_include_directories(${BIN_NAME} PUBLIC
    ${DtkWidget_INCLUDE_DIRS}
    ${Qt5DBus_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME}
    ${Qt5DBus_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${DtkWidget_LIBRARIES}
)

