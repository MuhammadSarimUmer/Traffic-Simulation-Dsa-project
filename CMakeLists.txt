cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Traffic-Simulation-Dsa-project VERSION 1.0 LANGUAGES CXX)

# Tell CMake to use moc, uic, and rcc tools automatically
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt 6 and the necessary modules for a Widgets application
# NOTE: Using 'Qt6' components now, which matches your installed version.
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network)

# Define source, header, and UI files based on your project structure
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    graph.cpp
    map_loader.cpp
    notification_manager.cpp
    traffic_simulator.cpp
)

set(PROJECT_HEADERS
    mainwindow.h
    graph.h
    map_loader.h
    notification_manager.h
    traffic_simulator.h
)

set(PROJECT_FORMS
    mainwindow.ui
)

# Create the executable target
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
    mapwidget.h mapwidget.cpp
)

# Link the executable to the required Qt 6 libraries
# NOTE: Linking to the 'Qt6::' namespace now.
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
    Qt6::Network
)

# Install the executable (optional, but good practice)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
#add_subdirectory(untitled)
