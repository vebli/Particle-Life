cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME ParticleLife)
project(${PROJECT_NAME})
find_package(
  SFML 2.5
  COMPONENTS system window graphics
  REQUIRED)
# Copy image files to the build directory
set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fno-omit-frame-pointer -fsanitize=address")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")  

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/colorToStr.cpp
    ${CMAKE_SOURCE_DIR}/src/findDistance.cpp
    ${CMAKE_SOURCE_DIR}/src/config.cpp
    ${CMAKE_SOURCE_DIR}/src/Rule.cpp
    ${CMAKE_SOURCE_DIR}/src/Particle.cpp
    ${CMAKE_SOURCE_DIR}/src/applyPhysics.cpp
    ${CMAKE_SOURCE_DIR}/src/initParticles.cpp
    ${CMAKE_SOURCE_DIR}/src/Field.cpp
    ${CMAKE_SOURCE_DIR}/src/SpatialHashGrid.cpp
    ${CMAKE_SOURCE_DIR}/src/Particles.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window
                                              sfml-graphics)
