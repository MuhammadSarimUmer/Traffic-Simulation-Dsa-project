cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Traffic-Simulation-Dsa-project VERSION 1.0 LANGUAGES CXX)

# Tell CMake to use moc, uic, and rcc tools automatically
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt 6 and the necessary modules
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network Sql)

# Define source, header, and UI files based on your project structure
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    graph.cpp
    map_loader.cpp
    notification_manager.cpp
    traffic_simulator.cpp
    database_manager.cpp
    login_dialog.cpp
    signup_dialog.cpp
    mapwidget.cpp               # <-- MOVED HERE
    # --- ADD NEW CPP FILES ---
    incidentfeeddialog.cpp
    incidentreportdialog.cpp
    incidentwidget.cpp
)

set(PROJECT_HEADERS
    mainwindow.h
    graph.h
    map_loader.h
    notification_manager.h
    traffic_simulator.h
    database_manager.h
    login_dialog.h
    signup_dialog.h
    mapwidget.h                 # <-- MOVED HERE
    # --- ADD NEW H FILES ---
    incidentfeeddialog.h
    incidentreportdialog.h
    incidentwidget.h
)

set(PROJECT_FORMS
    mainwindow.ui
    login_dialog.ui
    signup_dialog.ui
    # --- ADD NEW UI FILES ---
    incidentfeeddialog.ui
    incidentreportdialog.ui
    incidentwidget.ui
)

# Create the executable target
add_executable(${PROJECT_NAME} WIN32
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
    resources.qrc
)

# Link the executable to the required Qt 6 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
    Qt6::Network
    Qt6::Sql
)

# Install the executable (optional, but good practice)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
#add_subdirectory(untitled)
