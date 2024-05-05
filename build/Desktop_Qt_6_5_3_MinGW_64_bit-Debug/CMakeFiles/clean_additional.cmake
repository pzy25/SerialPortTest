# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SerialTest0_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SerialTest0_autogen.dir\\ParseCache.txt"
  "SerialTest0_autogen"
  )
endif()
