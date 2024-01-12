cmake_minimum_required(VERSION 3.18)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

project ("misis2023f-22-04-knyazev-a-p")
enable_testing()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(gl3w CONFIG REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Tesseract CONFIG REQUIRED)
find_package(Leptonica CONFIG REQUIRED)
find_package(Doxygen REQUIRED)

add_subdirectory ("prj.codeforces")
add_subdirectory ("prj.cw")

#if(DOXYGEN_FOUND)
 #   set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/prj.cw/doxygen/Doxyfile)
  #  set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_IN})

  #  add_custom_target(doc ALL
   #         COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
    #        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
     #       COMMENT "Generating API documentation with Doxygen"
      #      VERBATIM
       #     )

#endif()

#if(DOXYGEN_FOUND)
 #   install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/prj.cw/doxygen/rtf
  #          DESTINATION docs)
#endif()

#install(DIRECTORY ${CMAKE_SOURCE_DIR}/prj.cw/scan/image_for_scan/
#        DESTINATION image_for_scan
#        )
#install(IMPORTED_RUNTIME_ARTIFACTS ${OpenCV_LIBS} glfw unofficial::gl3w::gl3w RUNTIME)

