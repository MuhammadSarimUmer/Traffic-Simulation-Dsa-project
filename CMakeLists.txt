cmake_minimum_required(VERSION 3.16)

project(Traffic-DSA VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    graph.cpp
    graph.h
)

add_executable(Traffic-DSA ${PROJECT_SOURCES})

target_link_libraries(Traffic-DSA Qt6::Core Qt6::Widgets)

# Set output directory
set_target_properties(Traffic-DSA PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
