function(TARGET_CONFIGURE_SETUP tgt_symbol tgt_name)
    set(MODULE_NAME ${tgt_name} PARENT_SCOPE)
    set(MODULE_NAME ${tgt_name})
    target_compile_definitions(${tgt_symbol}_object PRIVATE -DMACHI_${MODULE_NAME})
    set(lower_tgt_name)
    string(TOLOWER ${tgt_name} lower_tgt_name)
    configure_file(${PROJECT_SOURCE_DIR}/cmakes/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/${lower_tgt_name}_config.h @ONLY)
    message("$add config fille to ${tgt_name} : [ loc : ${CMAKE_CURRENT_BINARY_DIR} ]")
    message("mudule name : ${MODULE_NAME}/${tgt_name}")
    target_include_directories(${tgt_symbol}_dll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()


macro(ADD_MACHI_LIBRARY tgt_name src deps_library symbol_library)
message("add library tgt_name : ${tgt_name}")
message("src : ${src}")
message("deps : ${deps_library}")
message("symbol_deps : ${symbol_library}")
message("${deps_list} ${symbol_library}")
set(lib_object_name  ${tgt_name}_object)
set(deps_list)
# inflate deps_library
foreach(dep_name ${deps_library})
    list(APPEND deps_list ${dep_name}_static)
endforeach()
add_library(${lib_object_name} ${src})
#target_compile_definitions(${tgt_name}_object PRIVATE -DA_DLL_EXPORT)

set(lib_static_name ${tgt_name}_static)
message("static lib ; ${lib_object_name}")
message("static lib ; ${lib_static_name}")
add_library(${lib_static_name} STATIC $<TARGET_OBJECTS:${lib_object_name}>)

list(APPEND deps_list ${symbol_library})
message("full deps : ${deps_list}")    


target_link_libraries(${lib_static_name} PUBLIC ${deps_list} )
set_target_properties(${lib_static_name} PROPERTIES STATIC_LIBRARY_OPTIONS "/DEF") 
set_target_properties(${lib_static_name} PROPERTIES OUTPUT_NAME ${tgt_name})

set(tgt_dll ${tgt_name}_dll)
add_library(${tgt_dll} SHARED $<TARGET_OBJECTS:${lib_object_name}>)
target_link_libraries(${tgt_dll} PRIVATE ${deps_list} )
set_target_properties(${tgt_dll} PROPERTIES RUNTIME_OUTPUT_NAME ${tgt_name})
endmacro()


macro(add_namespace tgt_names)
message("add_namespace add tgt: ${tgt_names}")

foreach(tgt_name ${tgt_names})
add_library(Machi::${tgt_name} ALIAS ${tgt_name}_dll)
endforeach()
endmacro()