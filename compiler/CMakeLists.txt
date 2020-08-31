cmake_minimum_required(VERSION 3.14)

include(cmake/ccw.cmake)

set(NC_ROOT ${NGL_ROOT}/compiler)
set(NC_THIRD_PARTY_ROOT ${NGL_ROOT}/compiler/third_party)
set(NC_BIN_ROOT ${NGL_ROOT}/compiler/bin)

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

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND MSVC)
    set(NC_COMPILER_ID "Clang-cl")
else()
    set(NC_COMPILER_ID ${CMAKE_CXX_COMPILER_ID})
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if ("${NC_COMPILER_ID}" STREQUAL "MSVC" OR "${NC_COMPILER_ID}" STREQUAL "Clang-cl")
        add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
        add_compile_options(/MD)
    endif()
endif()

#
#add_compile_options(
#        /imsvc${NC_ROOT}/third_party/spdlog/include
#        /imsvc${NC_ROOT}/benchmark/third_party/PEGTL/include
#)

#-------------------------------------------------------
#                    dependencies
#-------------------------------------------------------

# lib_llvm
if (LLVM_PATH)
    set(CMAKE_PREFIX_PATH ${LLVM_PATH}/)
endif ()

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
        codegen core native nativecodegen support)
target_link_libraries(lib_llvm INTERFACE ${llvm_libs})

# lib_nds
add_subdirectory(third_party/nds)

# lib_speedlog
add_library(lib_speedlog INTERFACE)
target_include_directories(lib_speedlog INTERFACE "third_party/spdlog/include")
target_link_libraries(lib_speedlog INTERFACE lib_ccw)

#-------------------------------------------------------
#                         nc
#-------------------------------------------------------
# lib_nc_object
file(GLOB_RECURSE NGL_SOURCES
        "source/ngl/*.cpp"
        "source/ngl/*.hpp")
add_library(lib_nc_object OBJECT ${NGL_SOURCES})
target_include_directories(lib_nc_object PUBLIC include)
target_link_libraries(lib_nc_object
        lib_llvm
        lib_nds
        lib_speedlog)


# lib_nc interface
add_library(lib_nc INTERFACE)
target_include_directories(lib_nc INTERFACE include)
target_link_libraries(lib_nc INTERFACE
        lib_nc_object $<TARGET_OBJECTS:lib_nc_object>
        lib_ccw
        )


# nc binary
add_executable(nc source/main.cpp)
target_link_libraries(nc lib_nc)

set_target_properties(nc PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${NGL_ROOT}/bin"
            OUTPUT_NAME nc)

# common lib
# pegtl
add_library(lib_pegtl INTERFACE)
target_include_directories(lib_pegtl SYSTEM INTERFACE ${NC_THIRD_PARTY_ROOT}/PEGTL/include)

# experimental
if (NC_EXPERIMENTAL)
    add_subdirectory(experimental)
endif()

# test
if (NC_TEST)
    add_subdirectory(test)
endif()

# benchmark
if (NC_BENCHMARK)
    add_subdirectory(benchmark)
endif()