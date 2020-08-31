#include <ngl/shape_cluster.hpp>

#include <algorithm>
#include <bitset>
#include <iostream>

namespace ngl
{
    void shape_cluster::display() const
    {
        for (int i = 0; i < shape_datas_.size(); ++i)
        {
            std::cout << "index " << shape_datas_[i].index
                      << " | id " << std::bitset<16>{ shape_datas_[i].id }
                      << " | vector_id " << std::bitset<16>{ shape_datas_[i].vector_id }
                      << " | data " << std::bitset<16>{ shape_datas_[i].data }
                      << " | fragment " << shape_datas_[i].is_fragment
                      << " | parser " << shape_datas_[i].is_parser
                      << " | " << shape_datas_[i].name << "\n";
        }
        std::cout << std::endl;
    }

    ngl::shape_data shape_cluster::add(ngl::shape_type shape_type, std::vector<uint64_t> data, const std::string& name, bool is_fragment, bool is_parser)
    {
        vector_datas_.emplace_back(std::move(data));

        ngl::shape_data shape;

        shape.index = shape_data_index_++;
        shape.id = 1u << shape.index;
        uint64_t vector_state_mask{ ~uint64_t(0) << scalar_shapes_ };
        shape.vector_id = shape.id & vector_state_mask;
        shape.type = static_cast<uint64_t>(shape_type);
        shape.data = vector_datas_.size() - 1; // index
        shape.name = name;

        shape.is_fragment = is_fragment;
        shape.is_parser = is_parser;

        if (shape.is_fragment) fragment_state_ |= shape.id;
        if (shape.is_parser) parser_state_ |= shape.id;

        shape_datas_.push_back(shape);

        return shape;
    }

    ngl::shape_data shape_cluster::add(ngl::shape_type shape_type, char data, const std::string& name, bool is_fragment, bool is_parser)
    {
        return add(shape_type, static_cast<uint64_t>(data), name, is_fragment, is_parser);
    }

    ngl::shape_data shape_cluster::add(ngl::shape_type shape_type, uint64_t data, const std::string& name, bool is_fragment, bool is_parser)
    {
        ngl::shape_data shape;

        shape.index = shape_data_index_++;
        shape.id = 1u << shape.index;
        uint64_t vector_state_mask{ ~uint64_t(0) << scalar_shapes_ };
        shape.vector_id = shape.id & vector_state_mask;
        shape.type = static_cast<uint64_t>(shape_type);
        shape.data = data;
        shape.name = name;

        shape.is_fragment = is_fragment;
        shape.is_parser = is_parser;

        if (shape.is_fragment) fragment_state_ |= shape.id;
        if (shape.is_parser) parser_state_ |= shape.id;

        switch (shape_type)
        {
        case ngl::shape_type::scalar_element:
        case ngl::shape_type::scalar_element_vector:
        case ngl::shape_type::scalar_range:
            scalar_shapes_++;
            scalar_state_ |= shape.id;
            break;

        case ngl::shape_type::vector_many:
        case ngl::shape_type::vector_sequence:
            vector_shapes_++;
            break;
            [[fallthrough]];
        default:;
        }

        shape_datas_.push_back(shape);
        return shape;
    }

    const std::string& shape_cluster::name() const { return name_; }
    std::vector<ngl::shape_data>& shape_cluster::datas() { return shape_datas_; }
    uint64_t shape_cluster::scalar_shapes_count() const { return scalar_shapes_; }
    uint64_t shape_cluster::vector_shapes_count() const { return vector_shapes_; }

    bool shape_cluster::is_fragment(uint64_t shape_id) const
    {
        return fragment_state_ & shape_id;
    }

    bool shape_cluster::is_parser(uint64_t shape_id) const
    {
        return parser_state_ & shape_id;
    }

    bool shape_cluster::is_scalar(uint64_t shape_id) const
    {
        return scalar_state_ & shape_id;
    }
    const std::string& shape_cluster::name_of(uint64_t shape_id) const
    {
        auto it = std::find_if(shape_datas_.begin(), shape_datas_.end(), [&shape_id](auto&& shape) { return shape.id == shape_id; });
        if (it == shape_datas_.end()) throw std::logic_error("shape name not found");
        return it->name;
    }

    ngl::shape_cluster& get_shape_cluster()
    {
        static ngl::shape_cluster ngl_shape_cluster{ "ngl" };
        auto newline            = ngl_shape_cluster.add_element<ngl::shape_space>("newline", '\n');
        auto space              = ngl_shape_cluster.add_element<ngl::shape_space>("space", ' ');
        auto tab                = ngl_shape_cluster.add_element<ngl::shape_space>("tab", '\t');
        auto whitespace         = ngl_shape_cluster.add_element<ngl::shape_or>("whitespace", space, tab, newline);
        auto whitespaces        = ngl_shape_cluster.add_element<ngl::shape_many>("whitespaces", whitespace);

        auto left_chevron       = ngl_shape_cluster.add_element<ngl::shape_element>("left_chevron", '<');
        auto right_chevron      = ngl_shape_cluster.add_element<ngl::shape_element>("right_chevron", '>');
        auto left_brace         = ngl_shape_cluster.add_element<ngl::shape_element>("left_brace", '[');
        auto right_brace        = ngl_shape_cluster.add_element<ngl::shape_element>("right_brace", ']');
        auto underscore         = ngl_shape_cluster.add_element<ngl::shape_element>("underscore", '_');
        auto colon              = ngl_shape_cluster.add_element<ngl::shape_element>("colon", ':');
        auto left_curly_brace   = ngl_shape_cluster.add_element<ngl::shape_element>("left_curly_brace", '{');
        auto right_curly_brace  = ngl_shape_cluster.add_element<ngl::shape_element>("right_curly_brace", '}');
        auto comma              = ngl_shape_cluster.add_element<ngl::shape_element>("comma", ',');

        auto digit              = ngl_shape_cluster.add_fragment<ngl::shape_range>("digit", '0', '9');
        auto lower_letter       = ngl_shape_cluster.add_fragment<ngl::shape_range>("lower_letter", 'a', 'z');
        auto upper_letter       = ngl_shape_cluster.add_fragment<ngl::shape_range>("upper_letter", 'A', 'Z');

        auto letter             = ngl_shape_cluster.add_fragment<ngl::shape_or>("letter", lower_letter, upper_letter);

        auto number             = ngl_shape_cluster.add_element<ngl::shape_many>("number", digit);

        auto identifier_symbol  = ngl_shape_cluster.add_element<ngl::shape_or>("identifier_symbol", letter, digit, underscore);
        auto identifier_symbols = ngl_shape_cluster.add_element<ngl::shape_many>("identifier_symbols", identifier_symbol);
        auto raw_identifier     = ngl_shape_cluster.add_element<ngl::shape_sequence>("raw_identifier", letter, identifier_symbol);

        return ngl_shape_cluster;
    }
} // ngl

/*
<description> ::= <vector_description> | <scalar_description>
<vector_description> ::= <identifier> <space> <raw_identifier> "{" <description>* "}"
<scalar_description> ::= <identifier> <space> <raw_identifier>

<identifier> ::= <raw_identifier> | <path_identifier> | <parameterized_identifier>
<path_identifier> ::= <scalar_identifier> (<edge> <scalar_identifier>)+
<scalar_identifier> ::= <raw_identifier> | <parameterized_identifier>
<parameterized_identifier> ::= <raw_identifier> "<" <identifier> (" " <identifier>)* ">"
<raw_identifier> ::= <identifier_symbol> <identifier_symbol>*

<identifier_symbol> ::= <letter> | <digit> | <underscore>

<letter> ::= [a-z]
<digit> ::= [0-9]
<underscore> ::= "_"
<edge> ::= ":"
<space> ::= " "+
 */