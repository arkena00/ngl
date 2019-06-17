cmake_minimum_required(VERSION 3.14)
project(nglc_experimental)

add_executable(nglc_exp_test test.cpp)

target_link_libraries(nglc_exp_test lib_nglc)

#cl /subsystem:console ucrt.lib vcruntime.lib msvcrt.lib  output.o
# lld ... output