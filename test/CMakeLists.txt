set(POINT_SOURCE_FILES test.cpp)

add_executable(test_program ${POINT_SOURCE_FILES})
target_link_libraries(test_program ${GTEST_LIBRARY})
target_link_libraries(test_program ${GTEST_MAIN_LIBRARY})

add_test(NAME test_program COMMAND test_program)

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
