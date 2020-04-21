cmake_minimum_required(VERSION 3.10)

project(benchmark C CXX)

set(CMAKE_CXX_STANDARD 17)

function(benchmark_make target_file)
    set(targetname ${target_file})

    add_executable(bench_${targetname} ${targetname}.cpp)
    target_link_libraries(bench_${targetname} lib_nglc)
    add_dependencies(bench_${targetname} lib_nglc)
endfunction()


benchmark_make(lexer)

target_link_libraries(bench_lexer lib_nglc)
