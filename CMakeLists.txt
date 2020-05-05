
cmake_minimum_required(VERSION 3.12)
project(csc305_assignments LANGUAGES CXX C)

set(TRACER_ROOT "${PROJECT_SOURCE_DIR}")

include(FetchContent)
FetchContent_Declare(
    atlas
    GIT_REPOSITORY https://github.com/marovira/atlas.git)
FetchContent_Populate(atlas)
add_subdirectory(${atlas_SOURCE_DIR} ${atlas_BINARY_DIR})

set(TRACER_INCLUDE
    "${TRACER_ROOT}/utilities.hpp"
    )
set(TRACER_SOURCE 
    "${TRACER_ROOT}/main.cpp"
    )

set(PATH_INCLUDE "${TRACER_ROOT}/paths.hpp")
configure_file("${TRACER_ROOT}/paths.hpp.in" ${PATH_INCLUDE})
list(APPEND TRACER_INCLUDE ${PATH_INCLUDE})

source_group("include" FILES ${TRACER_INCLUDE})
source_group("source" FILES ${TRACER_SOURCE})

add_executable(a5 ${TRACER_INCLUDE} ${TRACER_SOURCE} ${TRACER_SHADER})
target_link_libraries(a5 PUBLIC atlas::atlas)
