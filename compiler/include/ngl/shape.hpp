#ifndef COMPILER_INCLUDE_NGL_SHAPE_HPP_NGL
#define COMPILER_INCLUDE_NGL_SHAPE_HPP_NGL

#include <cstdint>
#include <string>

namespace ngl
{
    enum class shape_type : uint8_t
    {
        space = 0
        , scalar_element = 1
        , scalar_range
        , scalar_element_vector
        , scalar_or
        , vector_many
        , vector_sequence
    };

    struct shape_data
    {
        uint64_t index = 0; // 0-63
        uint64_t id = 1; // 1 << index
        uint64_t type = 0; // scalar_*, vector_*, dynamic_*
        uint64_t data = 0; // (elem)':' | (range)'az' | (vector)'//' 8 char max
        std::string name;
        uint64_t vector_size = 0;
        uint64_t vector_index = 0;
        uint64_t vector_id = 0;
    };

    struct shape_range
    {
        shape_range(uint8_t b, uint8_t e) : data{ static_cast<uint64_t>(b << 8u | e) } {}
        uint64_t data;
    };

    struct shape_or
    {
        template<class... Shapes>
        explicit shape_or(Shapes... shapes) : data{ (shapes.id  | ...) } {}
        uint64_t data;
    };

    struct shape_element
    {
        explicit shape_element(char e) : data{ e } {}
        char data;
    };

    struct shape_many
    {
        explicit shape_many(uint64_t shape_id) : data{ shape_id } {}
        uint64_t data;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_SHAPE_HPP_NGL
