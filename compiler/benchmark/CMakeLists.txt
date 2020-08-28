cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------
#                      Benchmark lib
#-------------------------------------------------------
set(THIRD_PARTY_BENCHMARK_LIB ${CMAKE_CURRENT_BINARY_DIR}/third_party_benchmark/src/${CMAKE_BUILD_TYPE}/benchmark${CMAKE_STATIC_LIBRARY_SUFFIX})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/third_party_benchmark)
add_custom_target(third_party_benchmark
        ALL
        COMMAND ${CMAKE_COMMAND} -DBENCHMARK_ENABLE_GTEST_TESTS=OFF ${NC_THIRD_PARTY_ROOT}/benchmark
        COMMAND ${CMAKE_COMMAND} --build . --target benchmark --config ${CMAKE_BUILD_TYPE}
        COMMAND ${CMAKE_COMMAND} -E copy ${THIRD_PARTY_BENCHMARK_LIB} ${NC_THIRD_PARTY_ROOT}/benchmark/lib/benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/third_party_benchmark"
        COMMENT "Building benchmark"
        )

# asm
enable_language(ASM_NASM)

set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT
        "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set(CMAKE_ASM_NASM_FLAGS "${ASM_NASM_FLAGS}")

function(bench_target target)
    target_include_directories(${target} PRIVATE ${NC_THIRD_PARTY_ROOT}/benchmark/include)
    target_link_libraries(${target} lib_nc lib_pegtl)
    target_link_libraries(${target} "${NC_THIRD_PARTY_ROOT}/benchmark/lib/benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}" shlwapi)
    add_dependencies(${target} lib_nc third_party_benchmark lib_pegtl)
    set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${NC_BIN_ROOT}/benchmark
            OUTPUT_NAME ${target})
endfunction()

add_executable(bench_lexer lexer.cpp test.asm)
bench_target(bench_lexer)
