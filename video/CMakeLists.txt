CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

Project(VideoProject)

INCLUDE_DIRECTORIES(/usr/include/Wt/)
LINK_DIRECTORIES(/usr/lib/Wt/)


ADD_EXECUTABLE(VideoWt Video.cpp)
TARGET_COMPILE_FEATURES(VideoWt PUBLIC  cxx_lambda_init_captures)

TARGET_LINK_LIBRARIES(VideoWt
  debug wtd      optimized wt
  debug wthttpd  optimized wthttp
  #  debug lhpdfd optimized lhpdf # only required for if you write pdfs
)


