cmake_minimum_required(VERSION 3.10)
project(edu-github-fast-search)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(edu-github-fast-search
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
)

target_link_libraries(edu-github-fast-search Qt5::Widgets)
