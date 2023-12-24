include_directories(.)
add_executable (scan "scan.cpp" "scan.h")
#target_link_libraries(scan PRIVATE imgui::imgui glfw glad::glad unofficial::gl3w::gl3w opencv_core)
target_link_libraries(scan PRIVATE opencv_core)

#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET scan PROPERTY CXX_STANDARD 20)
endif()

#install (TARGETS scan RUNTIME)