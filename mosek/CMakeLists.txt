cmake_minimum_required(VERSION 3.10)

project(mosek
  LANGUAGES C)

set(INSTALL_PREFIX  "")

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
  set(INSTALL_PREFIX "${PROJECT_NAME}/")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# On Windows, build as an adaptor DLL: at runtime mosek_adaptor_load()
# LoadLibrarys the versioned mosek64_<MOSEK_VERSION>.dll, since Mosek
# doesn't ship an unversioned Windows DLL.  On Linux/Mac the
# unversioned libmosek64 stays a link-time stub that gets shadowed by
# the real library on the loader path.
if(WIN32)
  set(LIBRARY_NAME mosek_adaptor)
else()
  set(LIBRARY_NAME mosek64)
endif()

add_library(${LIBRARY_NAME} SHARED src/mosek.c include/mosek.h)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(NBITS_TWO "32")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(NBITS_TWO "64")
endif()

set(ARCHIVE_DIR lib)
set(RUNTIME_DIR bin)

if(${CMAKE_GENERATOR} MATCHES "Visual Studio*")
  set(ARCHIVE_DIR extern/lib/win${NBITS_TWO}/microsoft)
  set(RUNTIME_DIR bin/win${NBITS_TWO})
elseif(${CMAKE_GENERATOR} MATCHES "MSYS Makefiles")
  set(ARCHIVE_DIR extern/lib/win${NBITS_TWO}/mingw${NBITS_TWO})
  set(RUNTIME_DIR bin/win${NBITS_TWO})
endif()

install(TARGETS ${LIBRARY_NAME} EXPORT mosekTargets
  LIBRARY DESTINATION ${INSTALL_PREFIX}lib
  ARCHIVE DESTINATION ${INSTALL_PREFIX}${ARCHIVE_DIR}
  RUNTIME DESTINATION ${INSTALL_PREFIX}${RUNTIME_DIR}
  INCLUDES DESTINATION ${INSTALL_PREFIX}include)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${mosek_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${INSTALL_PREFIX}include>
)

install(DIRECTORY include/ DESTINATION ${INSTALL_PREFIX}include)

install(EXPORT mosekTargets
  FILE mosekTargets.cmake
  NAMESPACE mosek::
  DESTINATION cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/mosekConfigVersion.cmake
  VERSION 11.1
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION
  cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/mosekConfigVersion.cmake"
  DESTINATION cmake
)
