#ifndef COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
#define COMPILER_INCLUDE_NGL_LEXER_HPP_NGL

#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace ngl
{
    enum class shape_type : uint8_t
    {
        space = 0
        , scalar_element = 1
        , scalar_range
        , scalar_element_vector
        , vector_or
        , vector_many
        , vector_sequence
    };

    struct shape_data
    {
        uint64_t id = 0; // 1-64
        uint64_t type = 0; // scalar_*, vector_*, dynamic_*
        uint64_t data = 0; // (elem)':' | (range)'az' | (vector)'//' 8 char max
    };

    /*
    extern "C"
    {
        uint64_t lexer_process(const char*, shape_data*);
    }*/

    struct shape;
    struct shape_element;
    struct location
    {
        size_t origin;
        size_t size;
    };

    struct shape
    {
        std::string name;
        ngl::location location{};
    };

    class lexer
    {
    public:
        using element_type = char;

        explicit lexer(const std::string& data);

        void process();
        void process_v2();
        void asm_process();

        void add_shape(const std::string& name, ngl::location);

        uint64_t add_shape_data(ngl::shape_type, std::vector<uint64_t> data);
        uint64_t add_shape_data(ngl::shape_type, char data);
        uint64_t add_shape_data(ngl::shape_type, uint64_t data);

        void display();

        const std::vector<shape>& shapes() const;

        static std::string to_string(shape);
        static std::string to_string(std::vector<shape>);

    public:
        int cursor_;
        const std::string& data_;
        std::vector<shape> shapes_;
        std::vector<shape_data> shape_datas_;
        uint64_t shape_data_index_ = 1;
        uint64_t scalar_shapes_ = 0;

        std::vector<std::pair<element_type, element_type>> element_ranges_;
        std::vector<element_type> element_scalars_;
        std::vector<std::string> element_vectors_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
