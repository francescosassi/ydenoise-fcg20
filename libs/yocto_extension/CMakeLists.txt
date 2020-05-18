add_library(yocto_extension yocto_extension.h yocto_extension.cpp)

set(EXT_PATH  ${CMAKE_SOURCE_DIR}/libs/yocto_extension/ext/denoise)

if(WIN32)
    set(CMAKE_PREFIX_PATH ext/denoise/win32/lib/cmake/OpenImageDenoise)
        
    find_package(OpenImageDenoise CONFIG REQUIRED)

    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${EXT_PATH}/win32/bin/OpenImageDenoise.dll  $<TARGET_FILE_DIR:yocto_extension>)
    
    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${EXT_PATH}/win32/bin/tbb.dll  $<TARGET_FILE_DIR:yocto_extension>)
    
    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${EXT_PATH}/win32/bin/tbbmalloc.dll  $<TARGET_FILE_DIR:yocto_extension>)
endif(WIN32)

if(APPLE)
    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${CMAKE_SOURCE_DIR}/libs/yocto_extension/ext/denoise/bin/OpenImageDenoise.dll  $<TARGET_FILE_DIR:yocto_extension>)
    
    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${CMAKE_SOURCE_DIR}/libs/yocto_extension/ext/denoise/bin/tbb.dll  $<TARGET_FILE_DIR:yocto_extension>)
    
    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${CMAKE_SOURCE_DIR}/libs/yocto_extension/ext/denoise/bin/tbbmalloc.dll  $<TARGET_FILE_DIR:yocto_extension>)
endif(APPLE)

if(UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH ext/denoise/linux/lib/cmake/OpenImageDenoise)

    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${EXT_PATH}/bin/libOpenImageDenoise.so.1.2.0  $<TARGET_FILE_DIR:yocto_extension>)
    
    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${EXT_PATH}/bin/libtbb.so.2  $<TARGET_FILE_DIR:yocto_extension>)
    
    add_custom_command(TARGET yocto_extension POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${EXT_PATH}/bin/libtbbmalloc.so.2  $<TARGET_FILE_DIR:yocto_extension>)
endif(UNIX AND NOT APPLE)

set_target_properties(yocto_extension PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

target_link_libraries(yocto_extension yocto yocto_pathtrace OpenImageDenoise)
