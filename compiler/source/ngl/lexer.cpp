#include <algorithm>
#include <array>
#include <bitset>
#include <ngl/lexer.hpp>

namespace ngl
{
    lexer::lexer(const std::string& data)
        : cursor_{ 0 }
        , data_{ data }
    {

    }

    void lexer::process()
    {
    try
    {
        size_t vector_sequence_index = 0;
        size_t vector_many_index = 0;
        uint64_t vector_iterator = 0;
        std::bitset<64> shape_state;
        std::bitset<64> previous_state;

        uint64_t vector_state;

        std::bitset<64> vector_state_mask{ ~uint64_t(0) << scalar_shapes_ };
        std::bitset<64> scalar_state_mask{ ~vector_state_mask };
        shapes_.reserve(data_.size());

        auto shape_count = 0;
        auto shape_end = false;
        size_t i = 0;
        size_t space = 0;

        for (i = 0; i < data_.size(); ++i)
        {
            shape_state.reset();

            std::cout << "\n" << data_[i];

            for (size_t shape_it = 0; shape_it < shape_datas_.size(); ++shape_it)
            {
                auto& shape = shape_datas_[shape_it];
                bool match = false;
                shape_end = false;
                vector_state = 0;

                switch (static_cast<shape_type>(shape.type))
                {
                case shape_type::space:
                    if (data_[i] == shape.data)
                    {
                        space++;
                        goto jump;
                    }
                    break;

                case shape_type::scalar_element:
                    match = (data_[i] == shape.data);
                    shape_state[shape.index] = match;
                    vector_state = 0;

                    // if (match) shape_it = scalar_shapes_ - 1;
                    break;

                case shape_type::scalar_range:
                    match = (data_[i] >= (shape.data >> 8u) && data_[i] <= ((shape.data << 56u) >> 56u));
                    shape_state[shape.index] = match;
                    vector_state = 0;

                    // if (match) shape_it = scalar_shapes_ - 1;
                    break;

                case shape_type::scalar_or:
                    match = shape_state.to_ullong() & shape.data;
                    shape_state[shape.index] = match;
                    vector_state = 0;

                    // shape_it += scalar_shapes_ - 1;
                    break;

                case shape_type::vector_sequence: {
                    auto sequence_size = 3u;

                    auto shape_index = reinterpret_cast<std::vector<uint64_t>*>(shape.data)->operator[](shape.vector_index);
                    auto next_shape_index = -1;
                    if (shape.vector_index + 1 < sequence_size) next_shape_index = reinterpret_cast<std::vector<uint64_t>*>(shape.data)->operator[](shape.vector_index + 1);

                    bool index_match = shape_state[shape_index];
                    bool next_match = false;
                    if (next_shape_index != -1) next_match = shape_state[next_shape_index];
                    bool pmatch = previous_state[shape.index];


                    match = (bool)shape.vector_index | index_match;
                    shape_state[shape.index] = match;


                    //if (index_match && !pmatch) std::cout << "INIT";

                    if (match) vector_state = shape.vector_id;

                    std::cout << " I: " << shape.vector_index
                              << " NM: " << next_match
                              << " PM: " << pmatch
                              << " IM: " << index_match
                              << " M: " << match << " | " << std::bitset<10>{ shape_state.to_ullong() };
                    //std::cout << "\n" << (vector_state_mask & shape_state) << " " <<  std::bitset<10>{ shape.vector_id };

                    //if (sequence_size - 1 == shape.vector_index) shape.vector_index = 0;

                    shape.vector_index = (shape.vector_index + (!index_match & pmatch));

                    break;
                }

                case shape_type::vector_many:
                    match = shape_state[shape.data];
                    shape_state[shape.index] = match;
                    vector_state = 0; // vector_state_mask & shape_state;
                    //std::cout << " _MANY" << match;

                    break;
                } // switch

            } // for shape

            /*
            std::cout << "\n"
                      << data_[i]
                      << " | " << std::bitset<10>{ shape_state.to_ullong() }
                      << " | " << std::bitset<10>{ vector_state };*/

            if (shape_state.to_ullong() == 0)
            {
                std::cout << "\nunexpected token\n";
                break;
            }

            // analyse mode
            // check if vector_state has single bit when previous_vector_state != vector_state // bool has_single_bit = (~v + 1u) ^ v <  ~v + 1u;

            // scalar finalisation
            if ((previous_state.to_ullong() & vector_state_mask.to_ullong()) == 0)
            {
                add_shape(std::to_string(previous_state.to_ullong()), { i - 1 - space, 1 });
                vector_iterator = 0;
                space = 0;
            }
            // vector finalisation
            else if ((shape_state.to_ullong() & vector_state_mask.to_ullong()) != (previous_state.to_ullong() & vector_state_mask.to_ullong()))
            {
                add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator - space, vector_iterator });
                vector_iterator = 0;
                space = 0;
                vector_state = 0;
            }


            previous_state = shape_state;

            vector_iterator++;
        jump:;
            // std::cout << "\n" << data_[i] << " | " << " " << shape_state;
        } // for data

        // last shape
        add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator, vector_iterator });
        vector_iterator = 0;

        // remove init shape
        shapes_.erase(shapes_.begin());
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what();
    }
    }

    void lexer::process_v2()
    {

    }

    void lexer::asm_process()
    {
        //uint64_t r = lexer_process(data_.data(), shape_datas_.data());
        //std::cout << r;
    }

    void lexer::add_shape(const std::string& name, ngl::location location)
    {
        ngl::shape shape;
        shape.name = name;
        shape.location = location;
        shapes_.push_back(shape);
    }

    ngl::shape_data lexer::add_shape_data(ngl::shape_type shape_type, std::vector<uint64_t> data, const std::string& name)
    {
        vec_datas_.push_back(std::move(data));

        ngl::shape_data shape;

        shape.index = shape_data_index_++;
        shape.id = 1u << shape.index;
        shape.type = static_cast<uint64_t>(shape_type);
        shape.data = reinterpret_cast<uint64_t>(std::addressof(vec_datas_.back()));
        shape.name = name;

        for (const auto& sh_id : vec_datas_.back()) shape.vector_id |= sh_id;
        shape.vector_id |= shape.id;

        shape_datas_.push_back(shape);

        return shape;
    }

    ngl::shape_data lexer::add_shape_data(ngl::shape_type shape_type, char data, const std::string& name)
    {
        return add_shape_data(shape_type, static_cast<uint64_t>(data), name);
    }

    ngl::shape_data lexer::add_shape_data(ngl::shape_type shape_type, uint64_t data, const std::string& name)
    {
        ngl::shape_data shape;

        switch (shape_type)
        {
        case ngl::shape_type::scalar_element:
        case ngl::shape_type::scalar_element_vector:
        case ngl::shape_type::scalar_range:
        case ngl::shape_type::scalar_or:
            scalar_shapes_++;
            break;
        [[fallthrough]]; default:;
        }

        shape.index = shape_data_index_++;
        shape.id = 1u << shape.index;
        std::bitset<64> vector_state_mask{ ~uint64_t(0) << scalar_shapes_ };
        shape.vector_id = shape.id & vector_state_mask.to_ullong();
        shape.type = static_cast<uint64_t>(shape_type);
        shape.data = data;
        shape.name = name;

        shape_datas_.push_back(shape);
        return shape;
    }

    ngl::shape_data lexer::add_shape_data(ngl::shape_element element, const std::string& name)
    {
        return add_shape_data(shape_type::scalar_element, element.data, name);
    }
    ngl::shape_data lexer::add_shape_data(ngl::shape_or or_, const std::string& name)
    {
        return add_shape_data(shape_type::scalar_or, or_.data, name);
    }
    ngl::shape_data lexer::add_shape_data(ngl::shape_range range, const std::string& name)
    {
        return add_shape_data(shape_type::scalar_range, range.data, name);
    }
    ngl::shape_data lexer::add_shape_data(ngl::shape_many many, const std::string& name)
    {
        return add_shape_data(shape_type::vector_many, many.data, name);
    }

    void lexer::display()
    {
        for (const auto& shape : shapes_)
        {
            std::cout << shape.name << "(" << data_.substr(shape.location.origin, shape.location.size) << ") ";
        }
        std::cout << std::endl;
    }
    void lexer::display_shapes_description()
    {
        for (int i = 0; i < shape_datas_.size(); ++i)
        {
            std::cout << "index " << shape_datas_[i].index
                      << " | id " << std::bitset<16>{ shape_datas_[i].id }
                      << " | vector_id " << std::bitset<16>{ shape_datas_[i].vector_id }
                      << " | data " << std::bitset<16>{ shape_datas_[i].data }
                      << " | " << shape_datas_[i].name << "\n";
        }
        std::cout << std::endl;
    }
    std::string lexer::to_string(const shape& shape)
    {
        std::string str;
        str += "TK(" + shape.name + ")";

        return str;
    }
    std::string lexer::to_string(const std::vector<shape>& shapes)
    {
        std::string str;

        for (const auto& shape : shapes)
        {
            str += to_string(shape);
        }

        return str;
    }
    const std::vector<shape>& lexer::shapes() const { return shapes_; }
    std::string_view lexer::shape_view(int index) const
    {
        return data_.substr(shapes_[index].location.origin, shapes_[index].location.size);
    }
    std::string_view lexer::data() const { return data_; }
} // ngl