cmake_minimum_required(VERSION 3.15)
project(myspice VERSION 1.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#set_target_properties(dllname PROPERTTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#set(CMAKE_DEBUG_POSTFIX "_d")
#set(CMAKE_RELEASE_POSTFIX "_r")
#set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d") 
#set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")

#set(XXLIB_PATH "XXlib" CACHE PATH "path to XXlib")
#set(SHARED FALSE CACHE BOOL "build a shared library")

#include_directories($(XXLIB_PATH))
include_directories(include)

#add_subdirectory("libxx")
add_subdirectory("src")