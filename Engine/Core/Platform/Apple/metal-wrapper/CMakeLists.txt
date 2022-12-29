add_library(metal_wrapper metal_core.h metal_wrapper.cpp)
message("${CMAKE_CURRENT_SOURCE_DIR}/metal-cpp")
target_include_directories(metal_wrapper PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
        "metal-cpp"
        "metal-cpp-extensions")
target_link_libraries(metal_wrapper PRIVATE
        "-framework Metal"
        "-framework MetalKit"
        "-framework AppKit"
        "-framework Foundation"
        "-framework QuartzCore"
        )