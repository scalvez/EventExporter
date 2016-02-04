# CMAKE_COMPILER
# - Basic CMake setup
# Check version meets ou requirements
# Declare project, which will configure compiler for us
cmake_minimum_required(VERSION 2.8)
project(FalaiseEventExporterPlugin)

# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Ensure our code can see the Falaise headers
#include_directories(${Falaise_INCLUDE_DIRS})
include_directories(${Falaise_BUILDPRODUCT_DIR}/include)
include_directories(${Falaise_BUILDPRODUCT_DIR}/include/falaise)
include_directories(${Bayeux_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

###########################################################################################
# - GammaTracking modules:
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/falaise)

# - Headers:
list(APPEND FalaiseEventExporterPlugin_HEADERS
  source/falaise/snemo/exports/topology_exporter.h
  source/falaise/snemo/exports/base_export_data_bank.h
  source/falaise/snemo/exports/base_data_bank_exporter.h
  source/falaise/snemo/exports/export_topology.h
  source/falaise/snemo/exports/export_root_topology.h
  source/falaise/snemo/processing/root_export_module.h
  )

# - Sources:
list(APPEND FalaiseEventExporterPlugin_SOURCES
  source/falaise/snemo/exports/topology_exporter.cc
  source/falaise/snemo/exports/base_export_data_bank.cc
  source/falaise/snemo/exports/base_data_bank_exporter.cc
  source/falaise/snemo/exports/export_topology.cc
  source/falaise/snemo/exports/export_root_topology.cc
  source/falaise/snemo/processing/root_export_module.cc
  )

###########################################################################################

# Build a dynamic library from our sources
add_library(Falaise_EventExporter SHARED
  ${FalaiseEventExporterPlugin_HEADERS}
  ${FalaiseEventExporterPlugin_SOURCES})

target_link_libraries(Falaise_EventExporter Falaise)

# Apple linker requires dynamic lookup of symbols, so we
# add link flags on this platform
if(APPLE)
  set_target_properties(Falaise_EventExporter
    PROPERTIES LINK_FLAGS "-undefined dynamic_lookup"
    )
endif()

# Install it:
install(TARGETS Falaise_EventExporter DESTINATION ${CMAKE_INSTALL_LIBDIR}/Falaise/modules)

# - Publish headers
foreach(_hdrin ${FalaiseEventExporterPlugin_HEADERS})
  string(REGEX REPLACE "source/falaise/" "" _hdrout "${_hdrin}")
  configure_file(${_hdrin} ${Falaise_BUILDPRODUCT_DIR}/include/falaise/${_hdrout} @ONLY)
endforeach()

# Test support:
option(FalaiseEventExporterPlugin_ENABLE_TESTING "Build unit testing system for FalaiseEventExporter" ON)
if(FalaiseEventExporterPlugin_ENABLE_TESTING)
  enable_testing()
  add_subdirectory(testing)

endif()
