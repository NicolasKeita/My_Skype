cmake_minimum_required(VERSION 3.15)
project(My_Skype)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory("${CMAKE_HOME_DIRECTORY}/lib/uti/my_network")

add_executable(babel_client
        main.cpp
        NetworkHandler.cpp
        NetworkHandler.hpp)

target_include_directories(babel_client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/uti/my_network/BlockingMultiThread)

target_link_directories(babel_client PRIVATE
        $[CMAKE_CURRENT_SOURCE_DIR}/lib/uti/my_network)

target_link_libraries(babel_client PRIVATE
        my_network)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(babel_client PRIVATE -Wall -Wextra)
endif(CMAKE_COMPILER_IS_GNUCXX)

