# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Traffic-DSA_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Traffic-DSA_autogen.dir\\ParseCache.txt"
  "Traffic-DSA_autogen"
  )
endif()
