cmake_minimum_required(VERSION 3.0)

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

set(GODOT_CUSTOM_API_FILE "${CMAKE_CURRENT_SOURCE_DIR}/api/extension_api.json")

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

include(ExternalProject)

SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/3rd_party)

ExternalProject_Add(
    godot-cpp

    GIT_REPOSITORY    https://github.com/godotengine/godot-cpp.git
    #GIT_TAG           master
    #GIT_SHALLOW       TRUE
    GIT_TAG           f71c71164687ccb8049ce6d3506591c9c2b006dc

    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    INSTALL_COMMAND ""

    #SOURCE_DIR "${CMAKE_SOURCE_DIR}/,,/3rd_party/godot-cpp"
    CMAKE_ARGS
        #"-G@CMAKE_GENERATOR@"
        -DBuildShared=ON
        -DBuildExamples=OFF
        -DCMAKE_INSTALL_PREFIX=${GLOBAL_OUTPUT_PATH}/godot-cpp
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}

    TEST_COMMAND ""

    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
)

message(${CMAKE_CURRENT_BINARY_DIR})

MACRO(ADDGODOT)

    FOREACH(subdir ${SUBDIRS})
        if(EXISTS "${subdir}/CMakeLists.txt")
            ADD_SUBDIRECTORY(${subdir})
        else()
            target_link_directories(${PROJECT_NAME} PRIVATE ${subdir})
        endif()
    ENDFOREACH()

    ExternalProject_Get_Property(godot-cpp source_dir)
    message("source")
    message(${source_dir})
    include_directories(${PROJECT_NAME} PUBLIC
        ${source_dir}/godot-headers
        ${source_dir}/include
        ${source_dir}/include/godot_cpp
        ${source_dir}/src

        ${source_dir}/misc
    )

    ExternalProject_Get_Property(godot-cpp binary_dir)
    message("binary")
    message(${binary_dir})
    include_directories(${PROJECT_NAME} PUBLIC
        ${binary_dir}/gen
        ${binary_dir}/gen/include
        ${binary_dir}/gen/src

        ${binary_dir}/bin
    )

    #string(TOLOWER ${CMAKE_HOST_SYSTEM_NAME} system)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${binary_dir}/bin/libgodot-cpp.${CMAKE_SYSTEM_NAME}.${CMAKE_BUILD_TYPE}.64.a)

    #target_link_libraries(${PROJECT_NAME} PRIVATE ${binary_dir}/bin)

    set_property(TARGET ${PROJECT_NAME} PROPERTY IMPORTED_LOCATION ${LIBRARY_PATH})

    add_dependencies(${PROJECT_NAME} godot-cpp)
ENDMACRO()
