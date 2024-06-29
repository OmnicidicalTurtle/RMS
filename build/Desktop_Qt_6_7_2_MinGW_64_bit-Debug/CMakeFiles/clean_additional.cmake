# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\RMS_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RMS_autogen.dir\\ParseCache.txt"
  "RMS_autogen"
  )
endif()
