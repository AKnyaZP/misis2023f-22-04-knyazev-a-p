include_directories(.)
add_executable (my_scan "scan.cpp" "scan.h")
target_link_libraries(my_scan PRIVATE  opencv_core opencv_imgproc opencv_highgui Tesseract::libtesseract)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET my_scan PROPERTY CXX_STANDARD 20)
endif()

#install (TARGETS scan RUNTIME)