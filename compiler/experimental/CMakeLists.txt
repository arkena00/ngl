cmake_minimum_required(VERSION 3.14)

enable_language(ASM_NASM)

set(CMAKE_ASM_NASM_OBJECT_FORMAT win64)
set(CMAKE_ASM_NASM_COMPILE_OBJECT
        "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set(CMAKE_ASM_NASM_FLAGS "${ASM_NASM_FLAGS}")

function(exp_target target)
    target_link_libraries(${target} lib_nglc lib_pegtl)
    add_dependencies(${target} lib_nglc)
    set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${NGLC_BIN_ROOT}/experimental
            OUTPUT_NAME ${target})

endfunction()

function(exp_make target_file)
    set(targetname exp_${target_file})

    add_executable(${targetname} ${target_file}.cpp)
    exp_target(${targetname} )

endfunction()

#exp_make(lexer lexer.cpp)

add_executable(exp_lexer lexer.cpp test.asm)
exp_target(exp_lexer)


#cl /subsystem:console ucrt.lib vcruntime.lib msvcrt.lib  output.o
# lld ... output

