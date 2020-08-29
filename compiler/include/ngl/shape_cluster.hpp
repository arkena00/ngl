#ifndef COMPILER_INCLUDE_NGL_SHAPE_CLUSTER_HPP_NGL
#define COMPILER_INCLUDE_NGL_SHAPE_CLUSTER_HPP_NGL

#include <ngl/shape.hpp>

#include <memory>
#include <string>
#include <vector>

namespace ngl
{
    class shape_cluster
    {
    public:
        explicit shape_cluster(std::string name = "shape_cluster")
            : name_{ std::move(name) } {}

        void display() const;

        ngl::shape_data add(ngl::shape_type, std::vector<uint64_t> data, const std::string& name = "shape", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_type, char data, const std::string& name = "shape", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_type, uint64_t data, const std::string& name = "shape", bool is_fragment = false, bool is_parser = false);

        ngl::shape_data add(ngl::shape_element, const std::string& name = "shape_element", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_element_vector, const std::string& name = "shape_element_vector", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_many, const std::string& name = "shape_many", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_not, const std::string& name = "shape_not", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_or, const std::string& name = "shape_or", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_range, const std::string& name = "shape_range", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_sequence, const std::string& name = "shape_sequence", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_space space, const std::string& name = "shape_space", bool is_fragment = false, bool is_parser = false);

        template<class T>
        auto add_fragment(T&& shape, const std::string& name = "fragment")
        {
            return add(shape, name, true);
        }

        template<class T>
        auto add_parser(T&& shape, const std::string& name = "parser_shape")
        {
            return add(shape, name, false, true);
        }

        template<class T>
        auto add_parser_fragment(T&& shape, const std::string& name = "parser_fragment")
        {
            return add(shape, name, true, true);
        }

        bool is_fragment(uint64_t shape_id) const;
        bool is_parser(uint64_t shape_id) const;
        bool is_scalar(uint64_t shape_index) const;

        const std::string& name_of(uint64_t shape_id) const;

        [[nodiscard]] const std::string& name() const;
        [[nodiscard]] std::vector<ngl::shape_data>& datas();

        uint64_t scalar_shapes_count() const;
        uint64_t vector_shapes_count() const;
        std::vector<uint64_t>& vector_data(unsigned int index) { return vector_datas_[index]; }

        uint64_t fragment_state() const { return fragment_state_; }
        uint64_t parser_state() const { return parser_state_; }

    private:
        std::string name_;
        std::vector<ngl::shape_data> shape_datas_;
        std::vector<std::vector<uint64_t>> vector_datas_;
        uint64_t scalar_shapes_ = 0;
        uint64_t vector_shapes_ = 0;
        uint64_t shape_data_index_ = 0;

        uint64_t parser_index = 0;
        uint64_t parser_state_ = 0;
        uint64_t fragment_state_ = 0;
        uint64_t scalar_state_ = 0;
    };


    namespace
    {
        ngl::shape_cluster ngl_shape_cluster{ "ngl" };
        auto newline            = ngl_shape_cluster.add(ngl::shape_space('\n'));
        auto space              = ngl_shape_cluster.add(ngl::shape_space(' '));
        auto tab                = ngl_shape_cluster.add(ngl::shape_space('\t'));
        auto whitespace         = ngl_shape_cluster.add(ngl::shape_or(space, tab, newline));
        auto whitespaces        = ngl_shape_cluster.add(ngl::shape_many(whitespace));

        auto left_chevron       = ngl_shape_cluster.add(ngl::shape_element('<'), "left_chevron");
        auto right_chevron      = ngl_shape_cluster.add(ngl::shape_element('>'), "right_chevron");
        auto left_brace         = ngl_shape_cluster.add(ngl::shape_element('['), "left_brace");
        auto right_brace        = ngl_shape_cluster.add(ngl::shape_element(']'), "right_brace");
        auto underscore         = ngl_shape_cluster.add(ngl::shape_element('_'), "underscore");
        auto colon              = ngl_shape_cluster.add(ngl::shape_element(':'), "colon");
        auto left_curly_brace   = ngl_shape_cluster.add(ngl::shape_element('{'), "left_curly_brace");
        auto right_curly_brace  = ngl_shape_cluster.add(ngl::shape_element('}'), "right_curly_brace");
        auto comma              = ngl_shape_cluster.add(ngl::shape_element(','), "comma");

        auto digit              = ngl_shape_cluster.add_fragment(ngl::shape_range('0', '9'), "digit");
        auto lower_letter       = ngl_shape_cluster.add_fragment(ngl::shape_range('a', 'z'), "lower_letter");
        auto upper_letter       = ngl_shape_cluster.add_fragment(ngl::shape_range('A', 'Z'), "upper_letter");

        auto letter             = ngl_shape_cluster.add_fragment(ngl::shape_or(lower_letter, upper_letter), "letter");

        auto number             = ngl_shape_cluster.add(ngl::shape_many(digit), "number");

        auto identifier_symbol  = ngl_shape_cluster.add(ngl::shape_or(letter, digit, underscore), "identifier_symbol");
        auto identifier_symbols = ngl_shape_cluster.add(ngl::shape_many(identifier_symbol), "identifier_symbols");
        auto raw_identifier     = ngl_shape_cluster.add(ngl::shape_sequence(letter, identifier_symbol), "raw_identifier");
    }
} // ngl

#endif // COMPILER_INCLUDE_NGL_SHAPE_CLUSTER_HPP_NGL
