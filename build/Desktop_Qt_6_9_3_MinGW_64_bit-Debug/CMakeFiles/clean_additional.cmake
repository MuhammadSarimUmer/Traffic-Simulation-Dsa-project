# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Traffic-Simulation-Dsa-project_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Traffic-Simulation-Dsa-project_autogen.dir\\ParseCache.txt"
  "Traffic-Simulation-Dsa-project_autogen"
  )
endif()
