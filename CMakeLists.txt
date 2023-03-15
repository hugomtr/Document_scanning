cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
SET(OpenCV_INCLUDE_DIRS "${OpenCV_INSTALL_PATH}/include/opencv;${OpenCV_INSTALL_PATH}/include")

SET(OpenCV_LIB_DIR "${OpenCV_INSTALL_PATH}/lib")
LINK_DIRECTORIES(${OpenCV_LIB_DIR})

SET(OpenCV_LIB_COMPONENTS opencv_contrib opencv_legacy opencv_objdetect opencv_calib3d opencv_features2d opencv_video opencv_highgui opencv_ml opencv_imgproc opencv_flann opencv_core )


project(CV)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_compile_options(-lOpenCV)

file(GLOB_RECURSE SOURCES_FILES CONFIGURE_DEPENDS src/*)
add_executable(CV main.cpp ${SOURCES_FILES})

target_link_libraries(CV ${OpenCV_LIBS})

