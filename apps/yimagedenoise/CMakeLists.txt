add_executable(yimagedenoise yimagedenoise.cpp ext/utils/image_io.h ext/utils/image_io.cpp)

set_target_properties(yimagedenoise PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

target_include_directories(yimagedenoise PUBLIC ${CMAKE_SOURCE_DIR}/libs)

target_link_libraries(yimagedenoise yocto yocto_pathtrace yocto_extension)
