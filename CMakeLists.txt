cmake_minimum_required(VERSION 3.5)

project(exchange-server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
FIND_PACKAGE( Boost 1.78 COMPONENTS program_options REQUIRED )
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(exchange-server main.cpp)

TARGET_LINK_LIBRARIES(exchange-server LINK_PUBLIC ${Boost_LIBRARIES} Threads::Threads ${Boost_LIBRARIES}  boost_system boost_thread)
