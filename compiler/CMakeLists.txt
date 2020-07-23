cmake_minimum_required(VERSION 3.14)

include(cmake/ccw.cmake)

set(LLVM_PATH D:/dev/lib/llvm-9.0.0)
set(NGLC_ROOT ${NGL_ROOT}/compiler)
set(NGLC_THIRD_PARTY_ROOT ${NGL_ROOT}/compiler/third_party)
set(NGLC_BIN_ROOT ${NGL_ROOT}/compiler/bin)

set(CMAKE_CXX_STANDARD 17)


# compiler options
jln_target_interface(lib_ccw INTERFACE
        WARNINGS strict
        EXCEPTIONS on
        BUILD_TYPE release
            OPTIMIZATION 3
        BUILD_TYPE debug
            DEBUG ON
            OPTIMIZATION 0
        )


add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
add_compile_options(/MD)

#
#add_compile_options(
#        /imsvc${NGLC_ROOT}/third_party/spdlog/include
#        /imsvc${NGLC_ROOT}/benchmark/third_party/PEGTL/include
#)

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
target_include_directories(lib_llvm INTERFACE SYSTEM ${LLVM_INCLUDE_DIRS})
target_compile_definitions(lib_llvm INTERFACE ${LLVM_DEFINITIONS})
target_link_directories(lib_llvm INTERFACE ${LLVM_PATH}/lib)
llvm_map_components_to_libnames(llvm_libs
        x86asmparser x86codegen x86desc x86disassembler x86info x86utils
        codegen core native nativecodegen)
target_link_libraries(lib_llvm INTERFACE ${llvm_libs})

# lib_nds
add_subdirectory(third_party/nds)

# lib_speedlog
add_library(lib_speedlog INTERFACE)
target_include_directories(lib_speedlog INTERFACE "third_party/spdlog/include")
target_link_libraries(lib_speedlog INTERFACE lib_ccw)

#-------------------------------------------------------
#                         nglc
#-------------------------------------------------------
# lib_nglc_object
file(GLOB_RECURSE NGL_SOURCES
        "source/ngl/*.cpp"
        "source/ngl/*.hpp")
add_library(lib_nglc_object OBJECT ${NGL_SOURCES})
target_include_directories(lib_nglc_object PUBLIC include)
target_link_libraries(lib_nglc_object
        lib_llvm
        lib_nds
        lib_speedlog)


# lib_nglc interface
add_library(lib_nglc INTERFACE)
target_include_directories(lib_nglc INTERFACE include)
target_link_libraries(lib_nglc INTERFACE
        lib_nglc_object $<TARGET_OBJECTS:lib_nglc_object>
        lib_ccw
        )


# nglc binary
add_executable(nglc source/main.cpp)
target_link_libraries(nglc lib_nglc)

set_target_properties(nglc PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${NGL_ROOT}/bin"
            OUTPUT_NAME nglc)

# common lib
# pegtl
add_library(lib_pegtl INTERFACE)
target_include_directories(lib_pegtl SYSTEM INTERFACE ${NGLC_THIRD_PARTY_ROOT}/PEGTL/include)

# experimental
add_subdirectory(experimental)

# test
add_subdirectory(test)

# benchmark
add_subdirectory(benchmark)