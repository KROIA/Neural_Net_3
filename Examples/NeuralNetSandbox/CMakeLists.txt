
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)   
string(REPLACE " " "_" ProjectId ${PROJECT_NAME})
if(NEURAL_NET_3_PROFILING)
    set(PROJECT_NAME ${PROJECT_NAME}_profile)
endif()
project(${PROJECT_NAME})


# Macro to search for files with given file ending.
# call:
#   FILE_DIRECTORIES(H_FILES *.h)
#
# all *.h files will be saved in the H_FILES variable
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



include_directories(inc)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Get all source files
FILE_DIRECTORIES(H_FILES *.h)
FILE_DIRECTORIES(CPP_FILES *.cpp)


set(Files 
	${H_FILES}
	${CPP_FILES})

add_executable(${PROJECT_NAME} ${Files})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

if(NEURAL_NET_3_PROFILING)
    target_link_libraries(${PROJECT_NAME} Neural_Net_3_static_profile)
else()
    target_link_libraries(${PROJECT_NAME} Neural_Net_3_static)
endif()
target_compile_definitions(${PROJECT_NAME} PUBLIC BUILD_STATIC)


install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
