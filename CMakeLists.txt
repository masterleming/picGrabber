#PicGrabber
cmake_minimum_required (VERSION 2.6)
project (MT_OpenCV_PicGrabber)
# The version number.
set (MT_OpenCV_PicGrabber_VERSION_MAJOR 1)
set (MT_OpenCV_PicGrabber_VERSION_MINOR 0)

set (OutputName picGrabber)

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/MT_OpenCV_PicGrabberConfig.h.in"
#  "${PROJECT_BINARY_DIR}/MT_OpenCV_PicGrabberConfig.h"
#  )

# add the binary tree to the search path for include files
# so that we will find PointCloudConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
add_subdirectory(src)

# build a CPack driven installer package
set(CPACK_PACKAGE_VERSION_MAJOR "${MT_OpenCV_PicGrabber_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${MT_OpenCV_PicGrabber_VERSION_MINOR}")
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
set(CPACK_PACKAGE_DIRECTORY "cpack")
include (CPack)