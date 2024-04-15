# Install script for directory: C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/pkgs/libflac_x64-windows")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC/targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC/targets.cmake"
         "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/CMakeFiles/Export/baf7b64a9c1b56d368d1c4c52c93ff8a/targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC/targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC/targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC" TYPE FILE FILES "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/CMakeFiles/Export/baf7b64a9c1b56d368d1c4c52c93ff8a/targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC" TYPE FILE FILES "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/CMakeFiles/Export/baf7b64a9c1b56d368d1c4c52c93ff8a/targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC" TYPE FILE FILES
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/flac-config.cmake"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/flac-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/FLAC" TYPE FILE FILES
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/flac-config.cmake"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/flac-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FLAC" TYPE FILE FILES
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/all.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/assert.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/callback.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/export.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/format.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/metadata.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/ordinals.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/stream_decoder.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC/stream_encoder.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FLAC++" TYPE FILE FILES
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC++/all.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC++/decoder.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC++/encoder.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC++/export.h"
    "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/src/1.4.2-128554d938.clean/include/FLAC++/metadata.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/src/cmake_install.cmake")
  include("C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/microbench/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Dev/GameWrench/GameWrench/vcpkg_installed/x64-windows/vcpkg/blds/libflac/x64-windows-rel/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")