#
#add_executable(testapp "test.cpp")
#MACHI_FULL_DEPENDENCY_INJECTION(testapp)
#target_link_libraries(testapp Machi::Core)
message("Test App is ON")
ADD_MACHI_EXECUTABLE(testapp "test.cpp" "GAME")