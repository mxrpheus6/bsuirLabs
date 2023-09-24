# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\agency_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\agency_autogen.dir\\ParseCache.txt"
  "agency_autogen"
  )
endif()
