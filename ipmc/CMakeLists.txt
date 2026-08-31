cmake_minimum_required(VERSION 3.10)

project(ipmc
  LANGUAGES C)

set(INSTALL_PREFIX  "")

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  set(INSTALL_PREFIX "${PROJECT_NAME}/")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Named 'ipmc', not 'ipmc_adaptor': the point is a libipmc.so with the same
# SONAME the real one carries, so a plugin linked here records the DT_NEEDED
# a licensed build records and resolves it against the real library at load
# time.  CasADi does not install this file -- same as knitro/snopt/worhp.
add_library(ipmc SHARED src/ipmc.c include/ipmc/ipmc.h)

# Plain lib/ + bin/, no vendor-specific extern/lib/win64/... layout: ipmc has
# no such convention, and casadi looks for the import library in lib/.
install(TARGETS ipmc EXPORT ipmcTargets
  LIBRARY DESTINATION ${INSTALL_PREFIX}lib
  ARCHIVE DESTINATION ${INSTALL_PREFIX}lib
  RUNTIME DESTINATION ${INSTALL_PREFIX}bin
  INCLUDES DESTINATION ${INSTALL_PREFIX}include)

# The public header is <include>/ipmc/ipmc.h, so consumers say
# #include <ipmc/ipmc.h> and put <include> on the path -- what
# casadi's FindIPMC.cmake reports as IPMC_INCLUDE_DIR.
target_include_directories(ipmc PUBLIC
  $<BUILD_INTERFACE:${ipmc_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${INSTALL_PREFIX}include>
)

install(DIRECTORY include/ DESTINATION ${INSTALL_PREFIX}include)

install(EXPORT ipmcTargets
  FILE ipmcTargets.cmake
  NAMESPACE ipmc::
  DESTINATION cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/ipmcConfigVersion.cmake
  VERSION 1.0
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION
  cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/ipmcConfigVersion.cmake"
  DESTINATION cmake
)
