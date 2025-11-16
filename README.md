# Traffic Control Simulator

This document outlines the features and architecture of the Traffic Control Simulator, a comprehensive Qt-based application for pathfinding and real-time traffic simulation.

## Overview

The Traffic Control Simulator is a sophisticated C++/Qt application that allows users to:
* Log in and create user accounts.
* Load real-world map data for specific areas of Karachi from the OpenStreetMap Overpass API.
* Find the shortest and alternative routes between any two points on the map.
* Run a dynamic, real-time traffic simulation on the loaded map, complete with vehicles, adaptive traffic lights, and congestion.
* Manually create traffic jams to see how the system and vehicles react.
* Participate in a community-driven incident reporting system, allowing users to post and view live traffic incidents.

## Core Features

* **User Authentication:** Secure login and sign-up system with hashed passwords.
* **Dynamic Map Loading:** Fetches and parses live road data from the Overpass API.
* **Interactive Map UI:** A custom-built map widget with tile-based rendering (from OpenStreetMap), panning, and zooming.
* **Pathfinding:** Implements the algorithm for efficient shortest-path calculation, considering traffic jams.
* **Alternative Rerouting:** A dedicated feature to find a new path that avoids the currently displayed route.
* **Complex Traffic Simulation:** A multi-threaded simulation engine that manages vehicle movement, queuing, and traffic light logic.
* **Adaptive Traffic Lights:** Automatically placed traffic lights at intersections that adapt their cycle timing based on vehicle queue length.
* **Live Incident Feed:** A built-in, database-backed system for users to report and view live traffic incidents.

---

## 1. User Authentication System

The application is secured by a complete user authentication flow.

* **Login & Sign-Up:** Users are presented with a `LoginDialog` or `SignUpDialog` (`login_dialog.ui`, `signup_dialog.ui`). The entire application is inaccessible until a user successfully logs in (`main.cpp`).
* **Password Hashing:** Passwords are not stored in plaintext. The `DatabaseManager` (`database_manager.cpp`) uses `QCryptographicHash::Sha256` to hash all passwords before storing them.
* **Database:** A local **SQLite** database (`users.db`) is used to store user credentials (`database_manager.cpp`). The `users` table enforces unique usernames and emails.
* **UI Enhancements:** The login and sign-up screens feature a modern UI with a background image, fade-in/out animations (`QPropertyAnimation`), and password visibility toggles (`login_dialog.cpp`, `signup_dialog.cpp`).

## 2. Map & Routing System

The core of the application is its ability to load and route on real-world map data.

### Dynamic Map Loading
* **Area Selection:** Users select a predefined area of Karachi (e.g., "Karachi South (Clifton)", "Gulshan-e-Iqbal") from a dropdown (`mainwindow.ui`).
* **API Integration:** The `MapLoader` class (`map_loader.cpp`) constructs a query and fetches data from the **Overpass API** (`https://overpass-api.de/`).
* **Data Parsing:** The `Graph` class (`graph.cpp`) includes a powerful `loadFromOverpassJSON` function that parses the API's JSON response. It builds a complete graph structure by identifying all nodes (intersections) and "highway" ways (roads).
* **Graph Structure:** The graph (`graph.h`) is composed of `Node` and `Edge` structs. Edge distances are calculated using the **Haversine formula** (`graph.cpp`) to determine the real-world distance between two latitude/longitude points.

### Pathfinding
* **A* Search Algorithm:** The primary pathfinding algorithm is **A* Search** (`graph.cpp`). It is used to find the shortest path and is capable of accepting a set of "blocked edges" (traffic jams) to route around.
* **Route Calculation:** Users select a source and destination from searchable dropdowns. Clicking "Find Shortest Path" (`mainwindow.cpp`) runs the A* algorithm.
* **Alternative Rerouting:** A dedicated "Find Alternative Route" button (`mainwindow.ui`) allows users to find a different path. This feature works by taking the *currently displayed path*, adding all of its edges to the "blocked" set, and re-running the A* algorithm to find the next-best-path (`mainwindow.cpp`, `onRerouteClicked`).
* **Turn-by-Turn Directions:** After a
path is found, the route details panel (`mainwindow.ui`) is populated with HTML-formatted, turn-by-turn directions, including distance per segment (`mainwindow.cpp`, `displayRouteDetails`).

### Interactive Visualization
* **Custom Map Widget:** All rendering is done by a custom `MapWidget` (`mapwidget.cpp`).
* **Tile-Based Rendering:** The widget downloads and caches map tiles from OpenStreetMap (`https://tile.openstreetmap.org/`) to provide a visual background.
* **Pan & Zoom:** The map is fully interactive, supporting click-and-drag panning and mouse-wheel zooming (`mapwidget.cpp`).
* **Path & Jam Drawing:** The widget draws the calculated path, traffic jams, vehicles, and traffic lights as overlays on top of the map tiles.

## 3. Advanced Traffic Simulation

The application includes a comprehensive simulation engine (`traffic_simulator.cpp`) that brings the map to life.

### Vehicle Simulation
* **Spawning:** Users can add "Regular" or "Priority (Ambulance)" vehicles between any two points (`mainwindow.ui`).
* **Movement:** The simulator (`TrafficSimulator`) runs on a `QTimer` (20 updates/sec). It moves each vehicle along its pre-calculated A* path, interpolating its `QPointF` position for smooth rendering (`mapwidget.cpp`, `drawVehicles`).
* **Collision Avoidance:** Vehicles check for other vehicles on the same edge and will slow down or stop to avoid collisions, maintaining a minimum gap (`traffic_simulator.cpp`).

### Adaptive Traffic Lights
* **Automatic Placement:** When a map is loaded, the simulator automatically places `TrafficLight` objects at all intersections with 3 or more connecting roads (`traffic_simulator.cpp`).
* **Adaptive Cycles:** The traffic light cycle duration is not fixed. It adapts based on the number of vehicles in its queue (`lightQueues`), allowing for longer green lights at busier intersections.
* **Vehicle Queuing:** Vehicles correctly identify red lights, stop, and enqueue themselves. Priority vehicles (ambulances) are dequeued first when the light turns green.

### Congestion & Rerouting
* **Manual Jams:** Users can manually add a "Jam" between any two locations (`mainwindow.ui`). This blocks the corresponding edges in the graph, visualized as a thick red line on the map (`mapwidget.cpp`).
* **Automatic Rerouting:**
    1.  **Vehicle-Side:** When a vehicle (e.g., Car A) is spawned or moving, its A* path calculation will automatically avoid any pre-existing manual jams.
    2.  **Jam-Side:** If a jam is added *after* a vehicle is already on its path, the vehicle's `updateVehicles` logic will detect it is on a jammed edge, stop, and run the A* algorithm again to find a new path from its current location to its destination (`traffic_simulator.cpp`, `handleRerouting`).

## 4. Community Incident Reporting

A key feature of the application is a user-driven, database-backed incident reporting system. This system is tied to the logged-in user.

### Incident Feed
* A "Live Community Feed" (`incidentfeeddialog.ui`) can be opened from the main window's toolbar.
* This dialog queries the central `users.db` database and retrieves all entries from the `incidents` table (`database_manager.cpp`, `getAllIncidents`).
* Each incident is displayed as a custom `IncidentWidget` (`incidentwidget.ui`), which shows the title, description, timestamp, and the username/email of the user who posted it.

### Report Submission
* From the feed, users can click "Report Incident" to open the `IncidentReportDialog` (`incidentreportdialog.ui`).
* This form allows the user to enter a title, a detailed description, and an optional image (using `QFileDialog` to browse for a PNG/JPG).
* On submission, the data (including the logged-in user's username and email) is saved to the `incidents` table in the SQLite database (`database_manager.cpp`, `addIncident`).

## 5. (Simulated) Notification System

The project includes a `NotificationManager` (`notification_manager.cpp`) to demonstrate how alerts could be integrated.
* **Simulated Emails:** The `sendCongestionEmail` function does *not* send real network emails. Instead, it simulates the action by printing the email's "To", "Subject", and "Body" to the `qDebug` console output.
* **Automatic Alerts:** The `TrafficSimulator` calls this notification manager when a vehicle automatically reroutes due to congestion, "alerting" the vehicle's "owner" about the delay.
