# -*- CMake -*-

####################################################################################################
#
# Include directories
#

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

####################################################################################################
#
# Executable
#

foreach(name
    pooled_string
    )
  add_executable(test_${name} test_${name}.cpp)
  target_link_libraries(test_${name} Qt5::Test qtcarto) # Qt5::Xml
  add_test(NAME ${name} COMMAND test_${name})
endforeach(name)
