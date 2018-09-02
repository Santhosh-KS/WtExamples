CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

Project(NewUiProject)

INCLUDE_DIRECTORIES(/usr/local/include/Wt/ /usr/inlclude/Wt)
LINK_DIRECTORIES(/usr/local/lib/ /usr/lib/Wt)

#ADD_DEFINITIONS(-DHPDF_DLL)

ADD_EXECUTABLE(NewUiWt NewUi.cpp main.cpp)
TARGET_COMPILE_FEATURES(NewUiWt PUBLIC  cxx_lambda_init_captures)

TARGET_LINK_LIBRARIES(NewUiWt
  debug wtd      optimized wt
  debug wthttpd  optimized wthttp
  #  debug lhpdfd optimized lhpdf # only required for if you write pdfs
)


