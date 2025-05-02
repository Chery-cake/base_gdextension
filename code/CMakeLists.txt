cmake_minimum_required(VERSION 3.30)

include(FetchContent)
FetchContent_Declare(
    godot-cpp
    GIT_REPOSITORY  https://github.com/godotengine/godot-cpp.git
    GIT_TAG         4.4
    GIT_SHALLOW     TRUE
)
FetchContent_MakeAvailable(godot-cpp)

set(PROJECT_NAME World)

project(${PROJECT_NAME} LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_COLOR_MAKEFILE ON)

set(BUILD_PATH ${CMAKE_SOURCE_DIR}/../godot/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h*")

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

#add_dependencies(${PROJECT_NAME} godot-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE godot-cpp)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    
    ${CMAKE_CURRENT_SOURCE_DIR}/include

    #PRIVATE
    
    #${SOURCE_DIR}/gdextension
    #${SOURCE_DIR}/include
    #${SOURCE_DIR}/src

    #${BINARY_DIR}/gen/include
    #${BINARY_DIR}/gen/src
)
