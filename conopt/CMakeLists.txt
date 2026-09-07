cmake_minimum_required(VERSION 3.10)

project(conopt
  LANGUAGES C)

set(INSTALL_PREFIX  "")

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  set(INSTALL_PREFIX "${PROJECT_NAME}/")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(conopt SHARED src/conopt.c include/conopt.h)

# Match the real CONOPT 4 library naming so a real install on the loader path
# shadows this stub: libconopt.so.4 / libconopt.4.dylib on Unix, conopt4.dll on Windows.
if(WIN32)
  set_target_properties(conopt PROPERTIES
    OUTPUT_NAME conopt4 PREFIX "" IMPORT_PREFIX "")
else()
  set_target_properties(conopt PROPERTIES VERSION 4.39.2 SOVERSION 4)
endif()

target_include_directories(conopt PUBLIC
  $<BUILD_INTERFACE:${conopt_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${INSTALL_PREFIX}include>
)

install(DIRECTORY include/ DESTINATION ${INSTALL_PREFIX}include)

install(TARGETS conopt EXPORT conoptTargets
  LIBRARY DESTINATION ${INSTALL_PREFIX}lib
  ARCHIVE DESTINATION ${INSTALL_PREFIX}lib
  RUNTIME DESTINATION ${INSTALL_PREFIX}bin
  INCLUDES DESTINATION ${INSTALL_PREFIX}include)

install(EXPORT conoptTargets
  FILE conoptTargets.cmake
  NAMESPACE conopt::
  DESTINATION cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/conoptConfigVersion.cmake
  VERSION 4.39.2
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION
  cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/conoptConfigVersion.cmake"
  DESTINATION cmake
)
