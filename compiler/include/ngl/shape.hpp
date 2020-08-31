#ifndef COMPILER_INCLUDE_NGL_SHAPE_HPP_NGL
#define COMPILER_INCLUDE_NGL_SHAPE_HPP_NGL

#include <ngl/assert.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace ngl
{
    enum class shape_type : uint8_t
    {
        space = 0
        , scalar_element
        , scalar_range
        , scalar_element_vector
        , logical_or
        , logical_not
        , vector_many
        , vector_sequence
    };

    enum class shape_property : uint8_t
    {
        fragment = 1,
        capture = 2
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
        uint64_t is_fragment = 0;
        uint64_t is_parser = 0;
        bool ignore = false;
    };

    struct shape_ignore : shape_data
    {
        explicit shape_ignore(const shape_data& sh)
        {
            static_cast<shape_data>(*this) = sh;
            ignore = true;
        }
    };

    struct shape_element
    {
        static constexpr auto name = "shape_element";
        static constexpr auto type = shape_type::scalar_element;

        explicit shape_element(char e) : data{ e } {}
        char data;
    };

    struct shape_element_vector
    {
        static constexpr auto name = "shape_element_vector";
        static constexpr auto type = shape_type::scalar_element_vector;

        explicit shape_element_vector(std::string_view e)
            : data{ 0 }
        {
            ngl_assert(e.size() <= 8);
            uint8_t i = 0;
            for (auto c : e)
            {
                data = data | (static_cast<uint64_t>(c) << 8 * i++);
            }
        }
        uint64_t data;
    };

    struct shape_many
    {
        static constexpr auto name = "shape_many";
        static constexpr auto type = shape_type::vector_many;

        template<class Shape>
        explicit shape_many(Shape shape) : data{ shape.index } {}
        uint64_t data;
    };

    struct shape_not
    {
        static constexpr auto name = "shape_not";
        static constexpr auto type = shape_type::logical_not;

        template<class Shape>
        explicit shape_not(Shape shape) : data{ shape.id } {}
        uint64_t data;
    };

    struct shape_or
    {
        static constexpr auto name = "shape_or";
        static constexpr auto type = shape_type::logical_or;

        template<class... Shapes>
        explicit shape_or(Shapes... shapes) : data{ (shapes.id  | ...) } {}
        uint64_t data;
    };

    struct shape_range
    {
        static constexpr auto name = "shape_range";
        static constexpr auto type = shape_type::scalar_range;

        shape_range(uint8_t b, uint8_t e) : data{ static_cast<uint64_t>(b << 8u | e) } {}
        uint64_t data;
    };

    struct shape_sequence
    {
        static constexpr auto name = "shape_sequence";
        static constexpr auto type = shape_type::vector_sequence;

        template<class... Shapes>
        explicit shape_sequence(Shapes&&... shapes) : data{ std::forward<Shapes>(shapes).id... }
        {}

        explicit shape_sequence(std::vector<uint64_t> v) : data{ std::move(v) }
        {}
        std::vector<uint64_t> data;
    };

    struct shape_space
    {
        static constexpr auto name = "shape_space";
        static constexpr auto type = shape_type::space;

        explicit shape_space(char s) : data{ static_cast<uint64_t>(s) } {}
        uint64_t data;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_SHAPE_HPP_NGL
