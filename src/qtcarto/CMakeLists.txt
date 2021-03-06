# -*- CMake -*-

####################################################################################################
#
# Include directories
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/imports/QtCarto/)

include_directories(${Qt5Quick_PRIVATE_INCLUDE_DIRS})

####################################################################################################

# Generate in source !
foreach(shader_name location_circle path)
  add_custom_command(
    OUTPUT map/shaders/${shader_name}_shader.h
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/map/shaders/make-shader ${shader_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/map/shaders
    DEPENDS
    map/shaders/${shader_name}_vertex_shader.glsl
    map/shaders/${shader_name}_fragment_shader.glsl
    )
endforeach(shader_name)

# add_subdirectory(openstreetmap)
# Generate in source !
# https://cmake.org/cmake/help/v3.6/module/FindProtobuf.html
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS openstreetmap/fileformat.proto openstreetmap/osmformat.proto)

####################################################################################################
#
# Library
#

# geometry/polygon_seidler_triangulation.cpp

set(qtcarto_files
  cache/file_tile_cache.cpp
  cache/offline_cache.cpp
  cache/offline_cache_database.cpp
  cache/tile_image.cpp

  coordinate/mercator.cpp
  coordinate/projection.cpp
  coordinate/sexagesimal_angle.cpp
  coordinate/wgs84.cpp
  coordinate/debug_tools.cpp

  data_structure/pooled_string.cpp
  data_structure/simd.cpp

  database/database.cpp

  geo_data_format/gpx.cpp
  geo_data_format/route.cpp
  geo_data_format/waypoint.cpp
  geo_data_format/xml_reader.cpp
  geo_data_format/wkb.cpp

  geometry/line.cpp
  geometry/path.cpp
  geometry/polygon.cpp
  geometry/polygon_seidler_triangulation.cpp
  geometry/vector.cpp

  logging/logger.cpp

  map/location_circle_data.cpp
  map/map_event_router.cpp
  map/map_path_editor.cpp
  map/map_view.cpp
  map/path_property.cpp
  map/viewport.cpp
  map/decorated_path.cpp

  math/interval.cpp
  math/qc_math.cpp
  math/rational.cpp

  openstreetmap/osm.cpp
  openstreetmap/osm_database.cpp
  openstreetmap/osm_pbf.cpp
  ${PROTO_SRCS}
  # ${PROTO_HDRS}

  scene/location_circle_material_shader.cpp
  scene/location_circle_node.cpp
  scene/map_layer_scene.cpp
  scene/map_scene.cpp
  scene/path_material_shader.cpp
  scene/path_node.cpp
  scene/point_material_shader.cpp

  wmts/elevation_service_reply.cpp
  wmts/location_service_query.cpp
  wmts/location_service_reply.cpp
  wmts/network_reply.cpp
  wmts/providers/artic_web_map/artic_web_map_plugin.cpp
  wmts/providers/austria/austria_plugin.cpp
  wmts/providers/esri/esri_plugin.cpp
  wmts/providers/geoportail/geoportail_elevation_service_reply.cpp
  wmts/providers/geoportail/geoportail_license.cpp
  wmts/providers/geoportail/geoportail_location_service_reply.cpp
  wmts/providers/geoportail/geoportail_plugin.cpp
  wmts/providers/germany/germany_plugin.cpp
  wmts/providers/osm/osm_plugin.cpp
  wmts/providers/spain/spain_plugin.cpp
  wmts/providers/swiss_confederation/swiss_confederation_plugin.cpp
  wmts/tile_matrix_index.cpp
  wmts/tile_matrix_set.cpp
  wmts/tile_spec.cpp
  wmts/wmts_manager.cpp
  wmts/wmts_network_reply.cpp
  wmts/wmts_network_tile_fetcher.cpp
  wmts/wmts_plugin.cpp
  wmts/wmts_plugin_manager.cpp
  wmts/wmts_reply.cpp
  wmts/wmts_request_manager.cpp
  wmts/wmts_tile_fetcher.cpp

  ../../imports/QtCarto/declarative_map_item.cpp
  ../../imports/QtCarto/geo_coordinate_animation.cpp
  ../../imports/QtCarto/map_gesture_area.cpp
  ../../imports/QtCarto/plugin_data.cpp
  )
add_library(qtcarto SHARED ${qtcarto_files})
target_link_libraries(qtcarto
  alpine_toolkit_common
  Qt5::Core
  Qt5::Gui
  Qt5::Network
  Qt5::Positioning
  Qt5::Qml
  Qt5::Quick
  Qt5::Sql
  ${PROJ4_LIBRARIES}
  ${ZLIB_LIBRARY}
  ${PROTOBUF_LITE_LIBRARIES}
  )
