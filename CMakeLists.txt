cmake_minimum_required(VERSION 3.12)
project(SmoothParticleHydrodynamics C)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


add_executable(SmoothParticleHydrodynamics src/main.c src/dynamic-array.c src/dynamic-array.h src/particle.c src/particle.h src/particle-list.h src/smooting-function.h src/smoothing-function.c src/particle-list.c)
target_link_libraries(SmoothParticleHydrodynamics m)
