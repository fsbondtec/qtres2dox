cmake_minimum_required (VERSION 3.16)

add_executable(qtres2dox WIN32
	DoxGenerator.cpp
	DoxGenerator.h
	DoxygenExport.cpp
	DoxygenExport.h
	DoxygenExport.ui
	main.cpp
	MyResourceCollection.h
	MyUiForm.cpp
	MyUiForm.h
	qtres2dox.cpp
	qtres2dox.h
	qtres2dox.qrc
	qtres2dox.ui
)

target_link_libraries(qtres2dox PRIVATE
	Qt5::Core
	Qt5::Widgets
	Qt5::Xml
	Qt5::UiTools
)

add_custom_command(TARGET qtres2dox POST_BUILD
	# copy exe only in Release Mode
	COMMAND "${CMAKE_COMMAND}" -E
		$<$<NOT:$<CONFIG:Release>>:echo> $<$<NOT:$<CONFIG:Release>>:"skip command in none Release mode: ">
		copy_if_different "$<TARGET_FILE:qtres2dox>" "${CMAKE_SOURCE_DIR}/bin/qtres2dox.exe"

	# run windeployqt.exe only in Release mode
	COMMAND cmd.exe /c if "$(Configuration)" == "Release"
		${WINDEPLOYQT_EXECUTEABLE}
			--dir ${CMAKE_SOURCE_DIR}/bin --no-compiler-runtime --no-translations 
			${CMAKE_SOURCE_DIR}/bin/qtres2dox.exe
	)

# set visual studio working directory
set_target_properties(qtres2dox PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(qtres2dox PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=${QT_ROOT_DIR}/bin;$(PATH)")
