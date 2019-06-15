cmake_minimum_required(VERSION 3.14)
project(nglc)

# lib_argh
add_subdirectory(third_party/argh)

# lib_antlr
file(GLOB_RECURSE ANTLR4_SOURCES
        "third_party/antlr4/*.cpp"
        "third_party/antlr4/atn/*.cpp"
        "third_party/antlr4/dfa/*.cpp"
        "third_party/antlr4/misc/*.cpp"
        "third_party/antlr4/support/*.cpp"
        "third_party/antlr4/tree/*.cpp"
        "third_party/antlr4/tree/pattern/*.cpp"
        "third_party/antlr4/tree/xpath/*.cpp"
        )
add_library(lib_antlr OBJECT ${ANTLR4_SOURCES})
target_include_directories(lib_antlr PUBLIC third_party/antlr4)
target_compile_definitions(lib_antlr PUBLIC -DANTLR4CPP_STATIC)

# nglc
file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.hpp" "source/gen/ngl/*.cpp")
add_executable(nglc ${SOURCES})
add_dependencies(nglc lib_antlr)
target_link_libraries(nglc lib_antlr argh)

target_include_directories(nglc PRIVATE ../compiler/source)


set_target_properties(nglc PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${NGL_ROOT}/bin"
            OUTPUT_NAME  nglc)