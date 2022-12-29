function (MACHI_FULL_DEPENDENCY_INJECTION TARGET_NAME)

    set(Machi_lib_list Machi::Core)#Machi::Platform)
    
    foreach(machi_component  ${Machi_lib_list}) 
        add_custom_command ( TARGET ${TARGET_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${machi_component}>
     $<TARGET_FILE_DIR:${TARGET_NAME}>)
    endforeach()
    message("test ${CMAKE_SOURCE_DIR}")
    add_custom_command( TARGET ${TARGET_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       "${CMAKE_SOURCE_DIR}/Engine/Resources" $<TARGET_FILE_DIR:${TARGET_NAME}>/"Resources")

    
   
endfunction()


function (ADD_MACHI_EXECUTABLE TARGET_NAME SRC MODE)

if(WIN32)
    add_executable(${TARGET_NAME} WIN32 ${SRC})
elseif(APPLE)
    message("${SRC}")
    add_executable(${TARGET_NAME} ${SRC})
elseif(UNIX AND NOT APPLE) # linux;

endif()
MACHI_FULL_DEPENDENCY_INJECTION(testapp)
target_link_libraries(testapp Machi::Core)
   
endfunction()