cmake_minimum_required(VERSION 3.1.0)
# Neural net core 
set(Neural_Net_3_filename "Neural_Net_3")
set(Neural_Net_3_Include "inc")
set(EASY_PROFILER_NO_GUI True)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



if(NOT EASY_PROFILER_NO_GUI)
    include(../QtLocator.cmake)
    message("Search for QT5 finished")
    find_package(Qt5Widgets REQUIRED)
    message("find_package for Qt5Widgets finished")

    if (Qt5Widgets_FOUND)
        message(STATUS "Using Qt v ${Qt5Widgets_VERSION}")
    else()
        message(STATUS "INFO\n\n\tQt5 not found!\n")
    endif()
endif()

include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/dependencies")

# Easy Profiler
set(BUILD_SHARED_LIBS OFF)
set(EASY_PROFILER_NO_SAMPLES True)
FetchContent_Declare(
 EASY_PROFILER
 GIT_REPOSITORY ${EASY_GIT_REPO}
 GIT_TAG ${EASY_GIT_TAG}
)
message("Download dependency: ${EASY_GIT_REPO}")
FetchContent_MakeAvailable(EASY_PROFILER)


FetchContent_Declare(
 LOGGER
 GIT_REPOSITORY ${LOGGER_GIT_REPO}
 GIT_TAG main
)
message("Download dependency: ${LOGGER_GIT_REPO}")
FetchContent_MakeAvailable(LOGGER)





set_target_properties(easy_profiler PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")
set_target_properties(easy_profiler PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")
set_target_properties(easy_profiler PROPERTIES CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")


if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()



MACRO(FILE_DIRECTORIES return_list ending)
    FILE(GLOB_RECURSE new_list ${ending})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()


FILE_DIRECTORIES(H_FILES *.h)
FILE_DIRECTORIES(CPP_FILES *.cpp)



set(SOURCES
    ${CPP_FILES}
    ${H_FILES}
)



message("Create library with files:")
 FOREACH(file ${SOURCES})
    message("  File: " ${file})
 ENDFOREACH()

 
#set(Neural_Net_3_dependencies )

add_library(Neural_Net_3_shared SHARED ${SOURCES})
add_library(Neural_Net_3_static STATIC ${SOURCES})
add_library(Neural_Net_3_static_profile STATIC ${SOURCES})


target_compile_definitions(easy_profiler PRIVATE  EASY_PROFILER_STATIC)
target_compile_definitions(Neural_Net_3_shared PRIVATE  NEURAL_NET_3_LIB)
target_compile_definitions(Neural_Net_3_static PRIVATE  BUILD_STATIC NEURAL_NET_3_LIB)
target_compile_definitions(Neural_Net_3_static_profile PRIVATE NEURAL_NET_3_PROFILING BUILD_STATIC NEURAL_NET_3_LIB)


set_target_properties(easy_profiler PROPERTIES DEBUG_POSTFIX "-d" CXX_STANDARD 17)
set_target_properties(Neural_Net_3_shared PROPERTIES LINKER_LANGUAGE CXX  OUTPUT_NAME "${Neural_Net_3_filename}" DEBUG_POSTFIX "-d" CXX_STANDARD 17)
set_target_properties(Neural_Net_3_static PROPERTIES LINKER_LANGUAGE CXX  OUTPUT_NAME "${Neural_Net_3_filename}-s" DEBUG_POSTFIX "-d" CXX_STANDARD 17)
set_target_properties(Neural_Net_3_static_profile PROPERTIES LINKER_LANGUAGE CXX  OUTPUT_NAME "${Neural_Net_3_filename}-s-p" DEBUG_POSTFIX "-d" CXX_STANDARD 17)


target_link_libraries(Neural_Net_3_shared ${Neural_Net_3_dependencies} Logger_static)
target_link_libraries(Neural_Net_3_static ${Neural_Net_3_dependencies} Logger_static)
target_link_libraries(Neural_Net_3_static_profile ${Neural_Net_3_dependencies} easy_profiler Logger_static)
if(NOT EASY_PROFILER_NO_GUI)
    target_link_libraries(Neural_Net_3_static_profile Qt5::Widgets)
endif()

target_include_directories(Neural_Net_3_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
	# $<INSTALL_INTERFACE:inc>  # <prefix>/inc 
)
target_include_directories(Neural_Net_3_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
	# $<INSTALL_INTERFACE:inc>  # <prefix>/inc 
)
target_include_directories(Neural_Net_3_static_profile PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
	# $<INSTALL_INTERFACE:inc>  # <prefix>/inc 
)
# Define the install path
message("Installation to path: ${CMAKE_INSTALL_PREFIX}/bin")
message("Installation to path: ${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")
install(TARGETS Neural_Net_3_shared DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
install(TARGETS Neural_Net_3_shared DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")
install(TARGETS Neural_Net_3_static DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")
install(TARGETS Neural_Net_3_static_profile DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")
install(TARGETS easy_profiler DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")
