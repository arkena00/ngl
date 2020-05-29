#ifndef COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
#define COMPILER_INCLUDE_NGL_LEXER_HPP_NGL

#include <ngl/shape.hpp>

#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace ngl
{


    /*
    extern "C"
    {
        uint64_t lexer_process(const char*, shape_data*);
    }*/

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

        ngl::shape_data add_shape_data(ngl::shape_type, std::vector<uint64_t> data, const std::string& name = "shape");
        ngl::shape_data add_shape_data(ngl::shape_type, char data, const std::string& name = "shape");
        ngl::shape_data add_shape_data(ngl::shape_type, uint64_t data, const std::string& name = "shape");


        ngl::shape_data add_shape_data(ngl::shape_element, const std::string& name = "shape");
        ngl::shape_data add_shape_data(ngl::shape_or, const std::string& name = "shape");
        ngl::shape_data add_shape_data(ngl::shape_range, const std::string& name = "shape");

        ngl::shape_data add_shape_data(ngl::shape_many, const std::string& name = "shape");

        void display();
        void display_shapes_description();

        [[nodiscard]] std::string_view data() const;

        [[nodiscard]] const std::vector<shape>& shapes() const;
        [[nodiscard]] std::string_view shape_view(int index) const;

        static std::string to_string(const shape&);
        static std::string to_string(const std::vector<shape>&);

    private:
        int cursor_;
        std::string_view data_;
        std::vector<shape> shapes_;
        std::vector<shape_data> shape_datas_;
        uint64_t shape_data_index_ = 0;
        uint64_t scalar_shapes_ = 0;

        std::vector<std::vector<uint64_t>> vec_datas_;

        std::vector<std::pair<element_type, element_type>> element_ranges_;
        std::vector<element_type> element_scalars_;
        std::vector<std::string> element_vectors_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
