include_directories(.)
add_executable (scan_gui "scan_gui.cpp" "scan_gui.h")
target_link_libraries(scan_gui PRIVATE imgui::imgui glfw glad::glad unofficial::gl3w::gl3w opencv_core)
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET scan_gui PROPERTY CXX_STANDARD 20)
endif()

#install (TARGETS scan_gui RUNTIME)