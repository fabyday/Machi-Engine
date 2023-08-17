function(TARGET_CONFIGURE_SETUP tgt_symbol tgt_name)
    set(MODULE_NAME ${tgt_name} PARENT_SCOPE)
    set(MODULE_NAME ${tgt_name})
    target_compile_definitions(${tgt_symbol} PRIVATE -DMACHI_${MODULE_NAME})
    set(lower_tgt_name)
    string(TOLOWER ${tgt_name} lower_tgt_name)
    configure_file(${PROJECT_SOURCE_DIR}/cmakes/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/${lower_tgt_name}_config.h @ONLY)
    message("$add config fille to ${tgt_name} : [ loc : ${CMAKE_CURRENT_BINARY_DIR} ]")
    message("mudule name : ${MODULE_NAME}/${tgt_name}")
    target_include_directories(${tgt_symbol} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()


function(ADD_MACHI_LIBRARY tgt_name src deps_library)

set(lib_object_name  ${tgt_name}_object)
set(deps_list)
# inflate deps_library
foreach(dep_name ${deps_library})
    list(APPEND deps_list ${dep_name}_static)
endforeach()

add_library(${lib_object_name} ${src})
target_compile_definitions(${lib_object_name} PRIVATE -DA_DLL_EXPORT)

set(lib_static_name ${tgt_name}_static)
add_library(${lib_static_name} STATIC $<TARGET_OBJECTS:${lib_object_name}>)

target_link_libraries(${lib_static_name} PUBLIC ${deps_list})
set_target_properties(${lib_static_name} PROPERTIES STATIC_LIBRARY_OPTIONS "/DEF") 
set_target_properties(${lib_static_name} PROPERTIES OUTPUT_NAME ${tgt_name})


add_library(${tgt_name} SHARED $<TARGET_OBJECTS:${lib_object_name}>)
target_link_libraries(${tgt_name} PRIVATE ${deps_list})
set_target_properties(${tgt_name} PROPERTIES RUNTIME_OUTPUT_NAME ${tgt_name})
add_library(${tgt_name} ALIAS Machi::${tgt_name})
endfunction()