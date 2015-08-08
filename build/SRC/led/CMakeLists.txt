cmake_minimum_required (VERSION 2.6)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (PROJECT 
	led
)

set (HEADERS
	led_global.h 
	led.h
)

set (SOURCES 
	led.cpp
)

source_group ("Headers Files" FILES ${HEADERS})
source_group ("Sources Files" FILES ${SOURCES})

add_definitions (-DLED_LIBRARY)

add_library(${PROJECT} SHARED ${HEADERS} ${SOURCES})
qt5_use_modules(${PROJECT} Core Gui Widgets)


