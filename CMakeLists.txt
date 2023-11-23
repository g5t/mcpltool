cmake_minimum_required(VERSION 3.15...3.27)
project(nanobound_mcpl)

#set(CMAKE_CXX_STANDARD 17)

# Warn if the user invokes CMake directly
if (NOT SKBUILD)
    message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build-core'.
  Running it directly will almost certainly not produce the desired
  result. If you are a user trying to install this package, use the
  command below, which will install all necessary build dependencies,
  compile the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to rerun the above
  after editing C++ files.")
endif()

find_package(MCPL REQUIRED)
find_library(MCPL_LIB mcpl)

if (SKBUILD)
    find_package(Python 3.8
            COMPONENTS REQUIRED COMPONENTS Interpreter Development.Module
            OPTIONAL_COMPONENTS Development.SABIModule
    )
else()
    find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
    # If we are not using scikit-build, we need to find Nanobind ourselves
    message(STATUS "Looking for Nanobind")
    execute_process(
            COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
            OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_DIR
    )
    message(STATUS "Nanobind CMake dir: ${nanobind_DIR}")
    list(APPEND CMAKE_MODULE_PATH "${nanobind_DIR}")
    find_package(nanobind CONFIG REQUIRED)
endif()

find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(
        # Name of the module
        _mcpl_impl
        # Target the stable ABI for Python 3.12+, which reduces
        # the number of binary wheels that must be built. This
        # does nothing on older Python versions
        STABLE_ABI

        # Source code goes here
        src/mcpl.cpp
)
target_link_libraries(_mcpl_impl PRIVATE ${MCPL_LIB})

install(TARGETS _mcpl_impl LIBRARY DESTINATION nanobound_mcpl)
