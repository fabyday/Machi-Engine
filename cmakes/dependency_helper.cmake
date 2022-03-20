function (MACHI_FULL_DEPENDENCY_INJECTION TARGET_NAME)

    set(Machi_lib_list Machi::OS Machi::Application Machi::Platform)
    
    foreach(machi_component  ${Machi_lib_list}) 
        add_custom_command ( TARGET ${TARGET_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${machi_component}>
     $<TARGET_FILE_DIR:${TARGET_NAME}>)
    endforeach()
    
   
endfunction()