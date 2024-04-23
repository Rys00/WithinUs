cmake_minimum_required(VERSION 3.11.0)
project(WithinUs VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set(PROJECT_SOURCES
   ${PROJECT_SOURCE_DIR}/main.cpp)

find_package(Vulkan)
set(VULKAN_LIB_LIST "vulkan-1")
include_directories(${PROJECT_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${VULKAN_LIB_LIST})


# include(FetchContent)
# FetchContent_Declare( 
#    googletest
#    GIT_REPOSITORY      https://github.com/google/googletest.git
#    GIT_TAG main
# )
# FetchContent_MakeAvailable(googletest)
# add_executable(testGoogle testGoogle.cpp ${PROJECT_SOURCES})
# target_link_libraries(testGoogle PUBLIC gtest_main)
