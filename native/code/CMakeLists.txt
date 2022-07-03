cmake_minimum_required(VERSION 3.22)

MACRO(FILE_FINDER return_list)
    FILE(GLOB_RECURSE new_list *.h *.hpp *.cpp *.c *.o *.obj *.d *.a *.lib)
    
    set (EXCLUDE_DIR "/unused/")

    SET(dir_list "")
    FOREACH(file_path ${new_list})

    	string (FIND ${file_path} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)

    	if (${EXCLUDE_DIR_FOUND} EQUAL -1)
	        SET(dir_list ${dir_list} ${file_path})
	    endif ()

    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

project(world)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(GODOT_CUSTOM_API_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/api/api.json")

set(CMAKE_BUILD_TYPE Release)

string(TOLOWER "${CMAKE_SYSTEM_NAME}" SYSTEM_NAME)
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
set(MY_SYSTEM_OUTPUT_PATH ${CMAKE_SYSTEM_NAME})

set(BUILD_PATH ${CMAKE_SOURCE_DIR}/../../godot/native/bin/${MY_SYSTEM_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")

set(MY_LINKER_FLAGS )
set(MY_COMPILER_FLAGS "-fPIC -Wwrite-strings")
set(LINK_DIRS )

FILE_FINDER(FILES)

add_library(${PROJECT_NAME} SHARED ${FILES})

set(LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

# that's just quick and dirty folder cleanup, actually CMake would detect what has changed
file(REMOVE_RECURSE ${BUILD_PATH})
file(MAKE_DIRECTORY  ${BUILD_PATH})

add_definitions(-DNDEBUG)

add_subdirectory(../../lib build)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/gdextension)

ADDGODOT()

set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS ${COMPILER_FLAGS})
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS ${LINKER_FLAGS})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR})
