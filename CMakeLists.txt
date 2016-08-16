cmake_minimum_required(VERSION 2.8)
project(MultichannelNumerovCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

set(SOURCE_FILES main.cpp Parameters.cpp Parameters.h State.cpp State.h Solver.cpp Solver.h MN.h Tester.cpp Tester.h)
add_executable(MultichannelNumerovCPP ${SOURCE_FILES})
set(LIBS -larmadillo)
target_link_libraries(${PROJECT_NAME} ${LIBS})