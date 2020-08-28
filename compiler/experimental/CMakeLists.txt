cmake_minimum_required(VERSION 3.14)

function(exp_target target)
    target_link_libraries(${target} lib_nc)
    add_dependencies(${target} lib_nc)
    set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${NC_BIN_ROOT}/experimental
            OUTPUT_NAME ${target})

endfunction()

function(exp_make target_file)
    set(targetname exp_${target_file})

    add_executable(${targetname} ${target_file}.cpp)
    exp_target(${targetname} )

endfunction()

#exp_make(lexer lexer.cpp)



exp_make(ngl_syntax)
exp_make(parser)
exp_make(graph)


#cl /subsystem:console ucrt.lib vcruntime.lib msvcrt.lib  output.o
# lld ... output

