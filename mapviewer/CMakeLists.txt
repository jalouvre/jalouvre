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

add_executable(mapviewer main.cpp mapviewer.qrc)
target_link_libraries(mapviewer
  Qt5::Core
  Qt5::Gui
  Qt5::Qml
  Qt5::Quick
  Qt5::QuickWidgets
  Qt5::Svg
  alpine_toolkit_common
  )
