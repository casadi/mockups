cmake_minimum_required(VERSION 3.10)

project(clarabel
  LANGUAGES C)

set(INSTALL_PREFIX  "")

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  set(INSTALL_PREFIX "${PROJECT_NAME}/")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Output name must be clarabel_c to match the real Clarabel C library that the
# CasADi clarabel plugin links against (libclarabel_c / clarabel_c.lib).
add_library(clarabel_c SHARED src/clarabel.c include/Clarabel.h)

target_include_directories(clarabel_c PUBLIC
  $<BUILD_INTERFACE:${clarabel_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${INSTALL_PREFIX}include>
)

install(DIRECTORY include/ DESTINATION ${INSTALL_PREFIX}include)

install(TARGETS clarabel_c EXPORT clarabelTargets
  LIBRARY DESTINATION ${INSTALL_PREFIX}lib
  ARCHIVE DESTINATION ${INSTALL_PREFIX}lib
  RUNTIME DESTINATION ${INSTALL_PREFIX}bin
  INCLUDES DESTINATION ${INSTALL_PREFIX}include)

install(EXPORT clarabelTargets
  FILE clarabelTargets.cmake
  NAMESPACE clarabel::
  DESTINATION cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/clarabelConfigVersion.cmake
  VERSION 0.0.0
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION
  cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/clarabelConfigVersion.cmake"
  DESTINATION cmake
)
