project(marchingCube)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST} main.cpp prog.h functions.cpp)


FIND_PACKAGE(DGtal REQUIRED)
if ( DGtal_FOUND )
     message(DGtal_FOUND)
endif()
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

add_definitions(-g)

TARGET_LINK_LIBRARIES(marchingCube ${DGTAL_LIBRARIES})
