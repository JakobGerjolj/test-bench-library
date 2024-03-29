cmake_minimum_required(VERSION 3.14)

project(test-bench-library LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core SerialPort)
find_package(Qt6 REQUIRED COMPONENTS SerialBus)

add_library(test-bench-library SHARED
  test-bench-library_global.h
  testbenchlibrary.cpp
  testbenchlibrary.h
  keycardsactuator.h keycardsactuator.cpp
  leversactuator.h leversactuator.cpp
  buttons.h buttons.cpp
  canbusrouter.h canbusrouter.cpp
  canframecache.h canframecache.cpp
)

target_link_libraries(test-bench-library PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::SerialPort
    Qt${QT_VERSION_MAJOR}::SerialBus

)

target_compile_definitions(test-bench-library PRIVATE TESTBENCHLIBRARY_LIBRARY)
