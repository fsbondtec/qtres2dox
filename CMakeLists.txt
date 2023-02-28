cmake_minimum_required (VERSION 3.16)

project(qtres2dox)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Xml UiTools)

set(WINDEPLOYQT_EXECUTEABLE "${Qt5_DIR}/../../../bin/windeployqt.exe")
if(NOT EXISTS "${WINDEPLOYQT_EXECUTEABLE}")
	message(SEND_ERROR "windeplayqt executable (${WINDEPLOYQT_EXECUTEABLE}) does not exists ")
endif()

add_subdirectory(src)

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT qtres2dox)
