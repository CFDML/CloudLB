cmake_minimum_required( VERSION 3.16 )
project( cloud VERSION 0.1.0 LANGUAGES CXX )

### COMPILER ###
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( RELEASE_OPTIONS -march=native -w )
set( RELWITHDEBINFO_OPTIONS -march=native -pg -no-pie )
set( DEBUG_OPTIONS -Wall -Wextra -Wpedantic )

### LIBRARIES ###
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package( OpenMP REQUIRED )

find_package( LAPACK REQUIRED )
include_directories( ${LAPACK_INCLUDE_DIR} )

find_package( BLAS )
add_compile_definitions( BLAZE_USE_SHARED_MEMORY_PARALLELIZATION=0 )
message( STATUS "Blaze: Shared memory parallelization disabled" )
if( BLAS_FOUND )
    message( STATUS "Blaze: BLAS mode enabled" )
    add_compile_definitions( BLAZE_BLAS_MODE=1 )
    include_directories( ${BLAS_INCLUDE_DIR} )
else()
    message( STATUS "Blaze: BLAS mode disabled" )
    add_compile_definitions( BLAZE_BLAS_MODE=0 )
endif()

include_directories( ${CMAKE_SOURCE_DIR}/ext/blaze )
include_directories( ${CMAKE_SOURCE_DIR}/ext/blaze_tensor )

set( CORE_LIBRARIES OpenMP::OpenMP_CXX -lstdc++fs )

### BUILD ###
file( GLOB_RECURSE SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "include/*.h" )
include_directories( ${CMAKE_SOURCE_DIR}/include )

add_executable( ${CMAKE_PROJECT_NAME} ${SRCS} )
target_link_libraries( ${CMAKE_PROJECT_NAME} ${CORE_LIBRARIES} )
target_compile_options( ${CMAKE_PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>" )
target_compile_options( ${CMAKE_PROJECT_NAME} PUBLIC "$<$<CONFIG:RELWITHDEBINFO>:${RELWITHDEBINFO_OPTIONS}>" )
target_compile_options( ${CMAKE_PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>" )
