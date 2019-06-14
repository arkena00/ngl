cmake_minimum_required(VERSION 3.14)
project(ngl_compiler)

file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.hpp")

file(GLOB_RECURSE ANTLR4_SOURCES
        "third_party/antlr4/*.cpp"
        "third_party/antlr4/atn/*.cpp"
        "third_party/antlr4/dfa/*.cpp"
        "third_party/antlr4/misc/*.cpp"
        "third_party/antlr4/support/*.cpp"
        "third_party/antlr4/tree/*.cpp"
        "third_party/antlr4/tree/pattern/*.cpp"
        "third_party/antlr4/tree/xpath/*.cpp"
        "source/gen/ngl/*.cpp"
        )

add_executable(ngl_compiler ${SOURCES} ${ANTLR4_SOURCES})

target_include_directories(ngl_compiler PRIVATE third_party/antlr4)
target_compile_definitions(ngl_compiler PRIVATE -DANTLR4CPP_STATIC)