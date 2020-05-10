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
        size_t vector_sequence_index = 0;
        size_t vector_many_index = 0;
        uint64_t vector_iterator = 0;
        std::bitset<64> shape_state;
        std::bitset<64> previous_state;

        std::bitset<64> vector_state_mask { ~uint64_t(0) << scalar_shapes_ };
        std::bitset<64> scalar_state_mask { ~vector_state_mask };

        //std::cout << scalar_state_mask;

        auto shape_count = 0;
        size_t i = 0;

        for (i = 0; i < data_.size(); ++i)
        {
            shape_state.reset();


            for (size_t shape_it = 0; shape_it < shape_datas_.size(); ++shape_it)
            {
                const auto& shape = shape_datas_[shape_it];
                bool match = false;

                switch (static_cast<shape_type>(shape.type))
                {
                    case shape_type::scalar_element:
                        match = (data_[i] == shape.data);
                        shape_state[shape.id - 1] = match;

                        if (match) shape_it += scalar_shapes_ - 1;
                        break;

                    case shape_type::scalar_range:
                        match = (data_[i] >= (shape.data >> 8u) && data_[i] <= ((shape.data << 56u) >> 56u));
                        shape_state[shape.id - 1] = match;

                        if (match) shape_it += scalar_shapes_ - 1;
                        break;

                    case shape_type::vector_or:
                        match = shape_state.to_ullong() & shape.data;
                        shape_state[shape.id - 1] = match;

                        //shape_it += scalar_shapes_ - 1;
                        break;

                    case shape_type::vector_sequence:
                    {
                        if (vector_sequence_index == 2)
                        {
                            //add_shape("seq", { i - vector_sequence_index + 1, vector_sequence_index });
                            shape_state[shape.id - 1] = true;
                            vector_sequence_index = 0; break;
                        }
                        auto shape_id = reinterpret_cast<std::array<uint64_t, 2>*>(shape.data)->operator[](vector_sequence_index);
                        shape_state[shape.id - 1] = shape_state[shape_id - 1];
                        //std::cout << "__" << shape_state[shape_id - 1] << "__";
                        vector_sequence_index++;

                        break;
                    }

                    case shape_type::vector_many:
                        match = shape_state[shape.data - 1];
                        shape_state[shape.id - 1] = match;

                        break;
                } // switch

                //std::cout << "\n" << data_[i] << " | " << " " << shape_state << " SHC " << shape_count;
            } // for shape

            //std::cout << "\n" << data_[i] << " | " << " " << shape_state;

            // vector finalisation
            if (shape_state.to_ullong() != previous_state.to_ullong())
            {
                add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator, vector_iterator });
                vector_iterator = 0;
            }


            previous_state = shape_state;
            vector_iterator++;
            //std::cout << "\n" << data_[i] << " | " << " " << shape_state;
        } // for data

        // last shape
        add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator, vector_iterator });
        vector_iterator = 0;

        // remove init shape
        shapes_.erase(shapes_.begin());
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

    uint64_t lexer::add_shape_data(ngl::shape_type shape_type, std::vector<uint64_t> data)
    {
        return add_shape_data(shape_type, reinterpret_cast<uint64_t>(data.data()));
    }

    uint64_t lexer::add_shape_data(ngl::shape_type shape_type, char data)
    {
        return add_shape_data(shape_type, static_cast<uint64_t>(data));
    }

    uint64_t lexer::add_shape_data(ngl::shape_type shape_type, uint64_t data)
    {
        switch (shape_type)
        {
        case ngl::shape_type::scalar_element:
        case ngl::shape_type::scalar_element_vector:
        case ngl::shape_type::scalar_range:
            scalar_shapes_++;
        default:;
        }

        ngl::shape_data shape;
        shape.id = shape_data_index_++;
        shape.type = static_cast<uint64_t>(shape_type);
        shape.data = data;

        shape_datas_.push_back(shape);
        return shape.id;
    }

    void lexer::display()
    {
        std::string_view data_view{ data_ };
        for (const auto& shape : shapes_)
        {
            std::cout << shape.name << "(" << data_view.substr(shape.location.origin, shape.location.size) << ") ";
        }
        std::cout << std::endl;
    }

    std::string lexer::to_string(shape shape)
    {
        std::string str;
        std::cout << shape.name;

        return str;
    }
    std::string lexer::to_string(std::vector<shape> shapes)
    {
        std::string str;

        for (const auto& shape : shapes)
        {
            std::cout << shape.name;
        }
        std::cout << std::endl;

        return str;
    }
    const std::vector<shape>& lexer::shapes() const { return shapes_; }
} // ngl