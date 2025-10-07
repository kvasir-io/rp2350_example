cmake_minimum_required(VERSION 3.28)

# Cache KVASIR_ROOT and CHIP_ROOT from environment if not already set
if(NOT DEFINED KVASIR_ROOT AND DEFINED ENV{KVASIR_ROOT})
    set(KVASIR_ROOT $ENV{KVASIR_ROOT} CACHE PATH "Path to Kvasir SDK")
endif()

if(NOT DEFINED CHIP_ROOT AND DEFINED ENV{CHIP_ROOT})
    set(CHIP_ROOT $ENV{CHIP_ROOT} CACHE PATH "Path to chip_rp2350")
endif()

# Determine KVASIR_CMAKE_DIR
if(DEFINED KVASIR_ROOT)
    set(KVASIR_CMAKE_DIR ${KVASIR_ROOT}/cmake)
else()
    set(KVASIR_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/kvasir/cmake)
endif()

include(${KVASIR_CMAKE_DIR}/kvasir.cmake)

project("rp2350_example" VERSION 0.1.0)

include(${KVASIR_CMAKE_DIR}/util.cmake)

add_executable(debug src/main.cpp)
target_configure_kvasir(debug OPTIMIZATION_STRATEGY size USE_LOG)

add_executable(release src/main.cpp)
target_configure_kvasir(release OPTIMIZATION_STRATEGY size)

add_executable(sanitize src/main.cpp)
target_configure_kvasir(sanitize OPTIMIZATION_STRATEGY size USE_SANITIZER USE_LOG)
