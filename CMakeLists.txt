cmake_minimum_required(VERSION 3.16)

project(Traffic-DSA VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# We must add QtNetwork to handle API calls
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    graph.cpp
    graph.h
    traffic_simulator.cpp
    traffic_simulator.h
    notification_manager.h
    notification_manager.cpp
    map_loader.h
    map_loader.cpp
)

add_executable(Traffic-DSA ${PROJECT_SOURCES})

# Link all required Qt libraries
target_link_libraries(Traffic-DSA Qt6::Core Qt6::Widgets Qt6::Network)

# Set output directory
set_target_properties(Traffic-DSA PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
