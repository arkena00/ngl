cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------
#                      Benchmark lib
#-------------------------------------------------------
set(THIRD_PARTY_BENCHMARK_LIB ${CMAKE_CURRENT_BINARY_DIR}/third_party_benchmark/src/${CMAKE_BUILD_TYPE}/benchmark${CMAKE_STATIC_LIBRARY_SUFFIX})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/third_party_benchmark)
add_custom_target(third_party_benchmark
        ALL
        COMMAND ${CMAKE_COMMAND} -DBENCHMARK_ENABLE_GTEST_TESTS=OFF ${NGLC_THIRD_PARTY_ROOT}/benchmark
        COMMAND ${CMAKE_COMMAND} --build . --target benchmark --config ${CMAKE_BUILD_TYPE}
        COMMAND ${CMAKE_COMMAND} -E copy ${THIRD_PARTY_BENCHMARK_LIB} ${NGLC_THIRD_PARTY_ROOT}/benchmark/lib/benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/third_party_benchmark"
        COMMENT "Building benchmark"
        )


function(bench_make target_file)
    set(targetname bench_${target_file})

    add_executable(${targetname} ${target_file}.cpp)
    target_include_directories(${targetname} PRIVATE ${NGLC_THIRD_PARTY_ROOT}/benchmark/include)
    target_link_libraries(${targetname} lib_nglc)
    target_link_libraries(${targetname} "${NGLC_THIRD_PARTY_ROOT}/benchmark/lib/benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}" shlwapi)
    add_dependencies(${targetname} lib_nglc)
    add_dependencies(${targetname} third_party_benchmark)
    set_target_properties(${targetname} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${NGLC_BIN_ROOT}/benchmark
            OUTPUT_NAME ${target_file})

endfunction()

bench_make(lexer)