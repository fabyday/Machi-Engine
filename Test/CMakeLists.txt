

add_executable(testapp "test.cpp")
MACHI_FULL_DEPENDENCY_INJECTION(testapp)
#add_custom_command ( TARGET testapp POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Machi::OS>
# $<TARGET_FILE_DIR:testapp>)
# add_custom_command ( TARGET testapp POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Machi::Application>
# $<TARGET_FILE_DIR:testapp>)
# add_custom_command ( TARGET testapp POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Machi::Platform>
# $<TARGET_FILE_DIR:testapp>)
target_link_libraries(testapp Machi::Core)