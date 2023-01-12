function (MACHI_FULL_DEPENDENCY_INJECTION TARGET_NAME)

    set(Machi_lib_list Machi::Graphics Machi::OS Machi::Platform metal_wrapper )#Machi::Platform)
    message("first : ${Machi_lib_list}")
    foreach(machi_component  ${Machi_lib_list}) 
        add_custom_command ( TARGET ${TARGET_NAME} POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${machi_component}>
     $<TARGET_FILE_DIR:${TARGET_NAME}>)
    endforeach()
    message("test ${CMAKE_SOURCE_DIR}")
    add_custom_command( TARGET ${TARGET_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       "${CMAKE_SOURCE_DIR}/Engine/Resources" $<TARGET_FILE_DIR:${TARGET_NAME}>/"Resources")


    message("first : ${Machi_lib_list}")

endfunction()


function (ADD_MACHI_EXECUTABLE TARGET_NAME SRC MODE)

if(WIN32)
    add_executable(${TARGET_NAME} WIN32 ${SRC})
elseif(APPLE)
    message("${SRC}")
    add_executable(${TARGET_NAME} ${SRC})
elseif(UNIX AND NOT APPLE) # linux;

endif()
set(Machi_lib_list Machi::Graphics Machi::OS Machi::Platform metal_wrapper )#Machi::Platform)
MACHI_FULL_DEPENDENCY_INJECTION(testapp)
message("${Machi_lib_list} teswt")
target_include_directories(testapp PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Core)
target_link_libraries(testapp ${Machi_lib_list})
   
endfunction()