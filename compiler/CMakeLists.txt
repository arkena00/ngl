cmake_minimum_required(VERSION 3.14)
project(nglc)

set(LLVM_PATH D:/dev/lib/llvm-9.0.0)

# disable libs warning
add_compile_options(/wd4267 /wd4244 /wd4996)

#-------------------------------------------------------
#                    dependencies
#-------------------------------------------------------

# lib_llvm
set(CMAKE_PREFIX_PATH ${LLVM_PATH}/)
find_package(LLVM REQUIRED CONFIG)
if (NOT LLVM_FOUND)
    message(FATAL_ERROR LLVM not found)
endif()
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_library(lib_llvm INTERFACE)
target_include_directories(lib_llvm INTERFACE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(lib_llvm INTERFACE ${LLVM_DEFINITIONS})
target_link_directories(lib_llvm INTERFACE ${LLVM_PATH}/lib)
llvm_map_components_to_libnames(llvm_libs
        x86asmparser x86codegen x86desc x86disassembler x86info x86utils
        codegen core native nativecodegen)
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
add_library(lib_antlr_object OBJECT ${ANTLR4_SOURCES})
target_include_directories(lib_antlr_object PUBLIC third_party/antlr4)
target_compile_definitions(lib_antlr_object PUBLIC -DANTLR4CPP_STATIC)

# lib_nds
add_subdirectory(third_party/nds)

# lib_speedlog
add_library(lib_speedlog INTERFACE)
target_include_directories(lib_speedlog INTERFACE "third_party/spdlog/include")

#-------------------------------------------------------
#                         nglc
#-------------------------------------------------------
# lib_nglc_object
file(GLOB_RECURSE NGL_SOURCES
        "source/ngl/*.cpp"
        "source/ngl/ast/*.cpp"
        "source/ngl/*.hpp"
        "source/gen/antlr4/*.cpp")
add_library(lib_nglc_object OBJECT ${NGL_SOURCES})
target_include_directories(lib_nglc_object PUBLIC include source/gen)
target_link_libraries(lib_nglc_object
        lib_llvm
        lib_nds
        lib_speedlog
        lib_antlr_object $<TARGET_OBJECTS:lib_antlr_object>)


# lib_nglc interface
add_library(lib_nglc INTERFACE)
target_link_libraries(lib_nglc INTERFACE
        lib_nglc_object $<TARGET_OBJECTS:lib_nglc_object>)


# nglc binary
add_executable(nglc source/main.cpp)
target_link_libraries(nglc lib_nglc)


set_target_properties(nglc PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${NGL_ROOT}/bin"
            OUTPUT_NAME  nglc)

# experimental
add_subdirectory(experimental)