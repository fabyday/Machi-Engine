add_library(metal_wrapper STATIC ${CMAKE_CURRENT_SOURCE_DIR}/metal.h ${CMAKE_CURRENT_SOURCE_DIR}/metal_impl.cpp)
message(" ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(metal_wrapper PUBLIC metal-cpp-extensions metal-cpp)
target_link_libraries(metal_wrapper PRIVATE
        "-framework Metal"
        "-framework MetalKit"
        "-framework AppKit"
        "-framework Foundation"
        "-framework QuartzCore"
        )