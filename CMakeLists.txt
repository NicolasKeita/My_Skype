cmake_minimum_required(VERSION 3.15)
project(My_Skype)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Portaudio REQUIRED)

add_subdirectory("${CMAKE_HOME_DIRECTORY}/lib/uti/my_network")

add_executable(babel_client
        srcs/main.cpp
        srcs/NetworkHandler.cpp
        srcs/NetworkHandler.hpp
        srcs/GraphicWrapper.cpp
        srcs/AudioWrapper.cpp)

target_compile_options(babel_client PRIVATE -fPIC -DQT_NO_VERSION_TAGGING)

target_include_directories(babel_client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/uti/my_network/BlockingMultiThread
        ${CONAN_INCLUDE_DIRS})

target_link_directories(babel_client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/uti/my_network
        ${CONAN_LIB_DIRS})

target_link_libraries(babel_client PRIVATE
        my_network
        ${CONAN_LIBS_PORTAUDIO}
        Qt5::Widgets)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(babel_client PRIVATE -Wall -Wextra -fPIC -DQT_NO_VERSION_TAGGING)
endif(CMAKE_COMPILER_IS_GNUCXX)

