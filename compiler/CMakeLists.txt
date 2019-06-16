cmake_minimum_required(VERSION 3.14)
project(nglc)

set(LLVM_PATH c:/lib/llvm8/install)

#-------------------------------------------------------
#                    dependencies
#-------------------------------------------------------
# lib_cli
add_subdirectory(third_party/argh)
add_library(lib_cli ALIAS argh)

# lib_llvm
#set(LLVM_DIR ${LLVM_PATH}/lib/cmake/llvm)
set(CMAKE_PREFIX_PATH ${LLVM_PATH}/)
find_package(LLVM REQUIRED CONFIG)
if (NOT LLVM_FOUND)
    message(FATAL_ERROR LLVM not found)
endif()

add_library(lib_llvm INTERFACE)
target_include_directories(lib_llvm INTERFACE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(lib_llvm INTERFACE ${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs Core ExecutionEngine Interpreter MC MCJIT Support nativecodegen)
target_link_libraries(lib_llvm INTERFACE ${llvm_libs})

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

#-------------------------------------------------------
#                         nglc
#-------------------------------------------------------
# lib_nglc_object
file(GLOB_RECURSE NGL_SOURCES "source/ngl/*.cpp" "source/ngl/*.hpp" "source/gen/ngl/*.cpp")
add_library(lib_nglc_object OBJECT ${NGL_SOURCES})
target_include_directories(lib_nglc_object PUBLIC source)
target_link_libraries(lib_nglc_object lib_llvm lib_antlr lib_cli)

# lib_nglc interface
add_library(lib_nglc INTERFACE)
target_link_libraries(lib_nglc INTERFACE
        lib_nglc_object $<TARGET_OBJECTS:lib_nglc_object>
        lib_antlr $<TARGET_OBJECTS:lib_antlr>)

# nglc binary
add_executable(nglc source/main.cpp)
target_link_libraries(nglc lib_nglc)


set_target_properties(nglc PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${NGL_ROOT}/bin"
            OUTPUT_NAME  nglc)

# experimental
add_subdirectory(experimental)