cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

File(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
File(GLOB headers ${PROJECT_SOURCE_DIR}/headers/*.hh)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(sim ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})
add_custom_target(Simulation DEPENDS sim)
