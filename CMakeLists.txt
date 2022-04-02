cmake_minimum_required(VERSION 3.16)

# Not ideal to use this global variable, but necessary to make sure
# that tooling and projects use the same version
set(CMAKE_CXX_STANDARD 23)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  randomexamples
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES CXX C)

#set(GIT_SHA
#    "Unknown"
#    CACHE STRING "SHA this build was generated from")
#string(
#  SUBSTRING "${GIT_SHA}"
#            0
#            8
#            GIT_SHORT_SHA)


# Adding the src:
add_subdirectory(01_asio_timeout)

## If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
## so that it behaves well with MSVC's debugger, and we can run the target from visual studio
#if(MSVC)
#  get_all_targets(all_targets)
#  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
#endif()

