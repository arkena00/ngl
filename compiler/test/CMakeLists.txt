cmake_minimum_required(VERSION 3.7)

add_library(lib_gtest OBJECT ${NC_THIRD_PARTY_ROOT}/gtest/source/gtest-all.cc)
target_include_directories(lib_gtest PUBLIC ${NC_THIRD_PARTY_ROOT}/gtest/include)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(test_nc ${SOURCES})
target_include_directories(test_nc PUBLIC ${NC_THIRD_PARTY_ROOT}/gtest/include)
target_link_libraries(test_nc lib_gtest lib_nc)

add_dependencies(test_nc lib_gtest lib_nc)

set_target_properties(test_nc PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${NC_BIN_ROOT}/test"
        OUTPUT_NAME  "test_nc")

add_test(NAME test_nc COMMAND "${NC_BIN_ROOT}/test/test_nc")