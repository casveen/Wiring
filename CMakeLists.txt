cmake_minimum_required(VERSION 3.5.0)





















# Project
project(Wiring VERSION 0.1.0 LANGUAGES C CXX)
# LIB
#add_library(wiring wiring.cpp)
#target_include_directories(wiring PUBLIC
#                           "${CMAKE_CURRENT_BINARY_DIR}"
#                           "${CMAKE_CURRENT_SOURCE_DIR}"
#                           )


# MAIN
add_executable(Wiring source/main.cpp)
target_include_directories(
    Wiring  
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/source
)
#target_link_libraries(Wiring PRIVATE wiring)





# CPACK
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)





# TEST
#add_executable(test_wiring_connection test/test_wiring_connection.cpp)
#*/
#target_link_libraries(test_wiring_connection PRIVATE wiring)
#enable_testing()
#add_test(
#   NAME test_wiring_connection
#   COMMAND $<TARGET_FILE:test_wiring_connection>
#)




include(CTest)
enable_testing()
add_subdirectory(lib/Catch2)
# These tests can use the Catch2-provided main
add_executable(tests test/test_connections.cpp)
target_link_libraries(tests Catch2::Catch2WithMain)
target_include_directories(
    tests
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/source
)
include(Catch)
catch_discover_tests(tests) 


# These tests need their own main
# add_executable(custom-main-tests test.cpp test-main.cpp)
# target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)