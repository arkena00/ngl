#ifndef COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
#define COMPILER_INCLUDE_NGL_LEXER_HPP_NGL

#include <ngl/shape.hpp>

#include "shape_cluster.hpp"
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
        explicit lexer(ngl::shape_cluster);

        void process();
        void process(const std::string&);

        void process_v2(const std::string&);
        void asm_process();

        void add(ngl::shape_cluster);
        void add_shape(const std::string& name, ngl::location);

        void display();

        [[nodiscard]] std::string_view data() const;

        [[nodiscard]] const std::vector<shape>& shapes() const;
        [[nodiscard]] std::string_view shape_view(int index) const;

        [[nodiscard]] std::string to_string(const shape&) const;
        [[nodiscard]] std::string to_string() const;

    private:
        std::string_view data_;
        std::vector<shape> shapes_;
        std::vector<ngl::shape_cluster> shape_clusters_;

        std::vector<std::pair<element_type, element_type>> element_ranges_;
        std::vector<element_type> element_scalars_;
        std::vector<std::string> element_vectors_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
