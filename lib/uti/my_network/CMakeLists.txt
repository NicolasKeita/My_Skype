cmake_minimum_required(VERSION 3.15)
project(my_network_library)

set(CMAKE_CXX_STANDARD		    17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

if (CONAN_BOOST_ROOT)
    set(BOOST_ROOT CONAN_BOOST_ROOT)
endif(CONAN_BOOST_ROOT)

if (DEFINED ENV{BOOST_ROOT})
    set(Boost_NO_SYSTEM_PATHS TRUE)
    set(BOOST_ROOT $ENV{BOOST_ROOT})
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif()

find_package(Boost 1.71.0 COMPONENTS serialization REQUIRED)
find_package(Threads REQUIRED)

add_library(my_network STATIC
        Async/ServerTcpAsyncWrapper.cpp
        Async/ClientTcpAsyncWrapper.cpp
        BlockingMultiThread/ServerUdpMultiThreadWrapper.cpp
        BlockingMultiThread/ClientUdpMultiThreadWrapper.cpp)

target_include_directories(my_network PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${BOOST_INCLUDE_DIRS}
        ./../my_string/
        Async
        BlockingMultiThread)

target_link_libraries(my_network ${CMAKE_THREAD_LIBS_INIT})

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(my_network PRIVATE -Wall -Wextra)
endif(CMAKE_COMPILER_IS_GNUCXX)

enable_testing()
add_subdirectory(tests/)
