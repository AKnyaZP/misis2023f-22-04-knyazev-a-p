# TODO: Add tests and install targets if needed.
include_directories(.)
add_executable (photo_editor "photo_editors.cpp" "dialog/ImGuiFileDialog/ImGuiFileDialog.cpp" "include/photoeditor/photo_editors.h" "include/image/image.h" "include/flags/flags.h")
target_link_libraries(photo_editor PRIVATE imgui::imgui glfw glad::glad unofficial::gl3w::gl3w opencv_core opencv_imgproc opencv_highgui)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET photo_editor PROPERTY CXX_STANDARD 20)
endif()

#install (TARGETS prj.cw RUNTIME)	