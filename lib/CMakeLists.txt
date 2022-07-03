MACRO(LIB_FINDER return_list)
    FILE(GLOB_RECURSE new_list *.o *.obj *.a *.lib *.dll *.so)

    message(${CMAKE_CURRENT_SOURCE_DIR})

    SET(dir_list "")
    FOREACH(file_path ${new_list})

        SET(dir_list ${dir_list} ${file_path})

    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

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

LIB_FINDER(LIBS)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

set(GODOT_CUSTOM_API_FILE "${CMAKE_CURRENT_SOURCE_DIR}/api/extension_api.json")

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

FOREACH(subdir ${SUBDIRS})
    if(EXISTS "${subdir}/CMakeLists.txt")
        ADD_SUBDIRECTORY(${subdir})
    else()
        target_link_directories(${PROJECT_NAME} PRIVATE ${subdir})
    endif()
ENDFOREACH()

include(ExternalProject)

SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

ExternalProject_Add(godot-cpp
    GIT_REPOSITORY    https://github.com/godotengine/godot-cpp.git
    GIT_TAG           master
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
)

message(${CMAKE_CURRENT_BINARY_DIR})

MACRO(ADDGODOT)
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

    target_link_libraries(${PROJECT_NAME} PRIVATE ${binary_dir}/bin/libgodot-cpp.${SYSTEM_NAME}.debug.64.a)

    set_property(TARGET ${PROJECT_NAME} PROPERTY IMPORTED_LOCATION ${LIBRARY_PATH})
    add_dependencies(${PROJECT_NAME} godot-cpp)
ENDMACRO()