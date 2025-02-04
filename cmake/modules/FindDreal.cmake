# This sets the following variables:
# DREAL_FOUND - True if dReal was found.
# DREAL_VERSION - dReal Version
# DREAL_INCLUDE_DIRS - Directories containing the dReal include files.
# DREAL_LIBRARY_DIRS - Directories containing the dReal library files.
# DREAL_LIBRARIES - dReal library names.
# DREAL_DEFINITIONS - Compiler flags for dReal.

# ===========
#    CLP
# ===========
if(APPLE)
  set(CLP_PKG_CONFIG_PATH "/usr/local/opt/clp@1.17/lib/pkgconfig")
  set(ENV{PKG_CONFIG_PATH} "${CLP_PKG_CONFIG_PATH}:$ENV{PKG_CONFIG_PATH}")
endif(APPLE)

# ===========
#    IBEX
# ===========
if(APPLE)
  set(IBEX_SEARCH_PATH "/usr/local/opt/ibex*/share/pkgconfig")
endif(APPLE)
if(UNIX AND NOT APPLE)
  set(IBEX_SEARCH_PATH "/opt/libibex/*/share/pkgconfig")
endif()
file(GLOB IBEX_PKG_CONFIG_PATH "${IBEX_SEARCH_PATH}")
# The result of file-glob is sorted lexicographically. We pick the
# last element (-1) to pick the latest.
list(GET IBEX_PKG_CONFIG_PATH -1 IBEX_PKG_CONFIG_PATH)
set(ENV{PKG_CONFIG_PATH} "${IBEX_PKG_CONFIG_PATH}:$ENV{PKG_CONFIG_PATH}")

# ===========
#    dReal
# ===========
if(UNIX AND NOT APPLE)
  file(GLOB DREAL_PKG_CONFIG_PATH "/opt/dreal/*/lib/pkgconfig")
  # The result of file-glob is sorted lexicographically. We pick the
  # last element (-1) to pick the latest.
  list(GET DREAL_PKG_CONFIG_PATH -1 DREAL_PKG_CONFIG_PATH)
  set(ENV{PKG_CONFIG_PATH} "${DREAL_PKG_CONFIG_PATH}:$ENV{PKG_CONFIG_PATH}")
endif()

find_package(PkgConfig)
pkg_check_modules(DREAL dreal)

set(DREAL_DEFINITIONS ${DREAL_CFLAGS_OTHER})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DREAL
  FOUND_VAR DREAL_FOUND
  REQUIRED_VARS DREAL_INCLUDE_DIRS DREAL_LIBRARIES DREAL_DEFINITIONS
  VERSION_VAR DREAL_VERSION)
