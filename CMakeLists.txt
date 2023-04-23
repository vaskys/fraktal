cmake_minimum_required(VERSION 3.26)
set(PROJECT_NAME fraktal)

project(${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

FILE(GLOB_RECURSE source src/*.c)

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Xclang -fopenmp)
endif()

find_package(MPI REQUIRED) 

link_directories(
    /opt/homebrew/opt/libomp/lib
)

include_directories(
    include
    /opt/homebrew/opt/libomp/include
    SYSTEM ${MPI_INCLUDE_PATH}
)

add_executable(fraktal
    ${source}
)

target_link_libraries(fraktal omp)
target_link_libraries(fraktal ${MPI_C_LIBRARIES})
