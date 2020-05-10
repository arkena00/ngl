cmake_minimum_required(VERSION 3.7)

add_library(lib_gtest OBJECT ${NGLC_THIRD_PARTY_ROOT}/gtest/source/gtest-all.cc)
target_include_directories(lib_gtest PUBLIC ${NGLC_THIRD_PARTY_ROOT}/gtest/include)

file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(test_nglc ${SOURCES})
target_include_directories(test_nglc PUBLIC ${NGLC_THIRD_PARTY_ROOT}/gtest/include)
target_link_libraries(test_nglc lib_gtest lib_nglc)

add_dependencies(test_nglc lib_gtest lib_nglc)

set_target_properties(test_nglc PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${NGLC_BIN_ROOT}/test"
        OUTPUT_NAME  "test_nglc")

add_test(NAME test_nglc COMMAND "${NGLC_BIN_ROOT}/test/test_nglc")