#include <ngl/lexer.hpp>
#include <ngl/log.hpp>

#include <algorithm>
#include <array>
#include <bitset>
#include <numeric>

namespace ngl
{
    lexer::lexer()
    {}

    lexer::lexer(ngl::shape_cluster shape_cluster)
        : data_{}
    {
        shape_clusters_.emplace_back(std::move(shape_cluster));
        root_ = graph_.emplace("shape");
    }

    void lexer::process(std::string_view data)
    {
        data_ = data;
        process();
    }

    // todo : use 3 registers for scalar, vector and parser states
    void lexer::process()
    {
        reset();

        try
        {
            uint64_t vector_iterator = 0;
            std::bitset<64> shape_state;
            std::bitset<64> previous_state;
            std::bitset<64> sequence_state;

            bool finalize = false;

            uint64_t match_state = 0;
            uint64_t parser_state = 0;

            uint64_t vector_state = 0;
            uint64_t pvector_state = 0;
            shapes_.clear();
            shapes_.reserve(data_.size());

            size_t i = 0;
            size_t space = 0;

            if (shape_clusters_.empty()) ngl_error("Lexer requires at least 1 shape_cluster");
            auto& shape_cluster = shape_clusters_[0];
            auto& shape_data = shape_cluster.datas();
            auto scalar_shapes_count = shape_cluster.scalar_shapes_count();

            uint64_t fragment_state = shape_cluster.fragment_state();


            for (i = 0; i < data_.size(); ++i)
            {
                shape_state.reset();
                const auto& element = data_[i];
                //const auto& next_element = data_[i];

                std::cout << "\n" << element;

                for (size_t shape_it = 0; shape_it < shape_data.size(); ++shape_it)
                {
                    auto& shape = shape_data[shape_it];
                    bool match = false;

                    //std::cout << "\n" << shape_it << " " << shape_data[shape_it].name << " ";

                    switch (static_cast<shape_type>(shape.type))
                    {
                    case shape_type::space:
                        if (element == shape.data)
                        {
                            space++;
                            if (space == 1) { pvector_state = 0; vector_state = 0; }
                            goto jump;
                        }
                        break;

                    case shape_type::scalar_element:
                        match = (element == shape.data);
                        shape_state[shape.index] = match;
                        vector_state = 0;
                        //if (match) shape_it = scalar_shapes_count - 1;

                        break;

                    case shape_type::scalar_element_vector:
                        match = shape.data == (*reinterpret_cast<const uint64_t*>(&element) & shape.data);
                        shape_state[shape.index] = match;
                        vector_state = 0;
                        //if (match) shape_it = scalar_shapes_count - 1;

                        break;

                    case shape_type::scalar_range:
                        match = (element >= (shape.data >> 8u) && element <= ((shape.data << 56u) >> 56u));
                        shape_state[shape.index] = match;
                        vector_state = 0;
                        //if (match) shape_it = scalar_shapes_count - 1;

                        break;

                    case shape_type::logical_or:
                        match = shape_state.to_ullong() & shape.data;
                        shape_state[shape.index] = match;
                        vector_state = 0;

                        break;
                    case shape_type::logical_not:
                        match = !(shape_state.to_ullong() & shape.data);
                        shape_state[shape.index] = match;

                        break;

                    case shape_type::vector_sequence: {
                        auto ar = shape_cluster.vector_data(shape.data);
                        auto sequence_size = ar.size();

                        seq_match:

                        //shape_vector_index[];
                        //std::cout << " I: " << shape.vector_index;

                        // end of sequence
                        if (shape.vector_index == ~uint64_t(0))
                        {
                            shape.vector_index = 0;
                            match = false;
                            shape_state[shape.index] = false;
                            sequence_state[shape.index] = true;
                            //std::cout << "reset";
                            for (auto s : shape_data)
                            {
                                //if (s.type == (uint64_t) ngl::shape_type::vector_sequence) shape.vector_index = 0;
                            }
                        }


                        // current shape in the sequence
                        auto shape_id = ar[shape.vector_index];
                        auto shape_scalar = shape_cluster.is_scalar(shape_id);

                        bool index_match = shape_state.to_ullong() & shape_id;

                        // scalar current shape
                        // if matching shape is scalar, go to the next shape index in the sequence
                        if (shape_cluster.is_scalar(shape_id))
                        {
                            if (index_match)
                            {
                                shape.vector_index++;
                                // sequence end, finalise next iteration
                                if (shape.vector_index == sequence_size) shape.vector_index = ~uint64_t(0);
                            }
                        }
                        // vector current shape
                        else
                        {
                            // current index doesn t match
                            if (!index_match)
                            {
                                shape.vector_index++;
                                // end of sequence
                                if (shape.vector_index == sequence_size)
                                {
                                    shape.vector_index = ~uint64_t(0);
                                    goto seq_match;
                                }
                                else
                                {
                                    // try next index
                                    shape_id = ar[shape.vector_index];
                                    index_match = shape_state.to_ullong() & shape_id;

                                    if (shape_cluster.is_scalar(ar[shape.vector_index]))
                                    {
                                        goto seq_match;
                                    }
                                    else if (!index_match)
                                    {
                                        shape.vector_index = ~uint64_t(0);
                                    }
                                }
                            }
                        }


                        match = index_match;
                        shape_state[shape.index] = match;

                        if (match) vector_state |= shape.vector_id;
                        else shape.vector_index = 0;

                        //std::cout << " M: " << match;

                        break;
                    }

                    case shape_type::vector_many:
                        match = shape_state[shape.data];
                        shape_state[shape.index] = match;
                        if (match) vector_state |= shape.vector_id;
                        //std::cout << " [ _MANY " << shape.name << std::bitset<10>{ shape.vector_id } << ":" << match << " ]";

                        break;
                    } // switch

                    //std::cout << match;

                } // for shape

                //vector_state = vector_state & ~parser_state;
                //std::cout << "\n" << std::bitset<32>{ vector_state } << " " << std::bitset<24>{ vector_state & ~parser_state };

                match_state = shape_state.to_ullong() & ~fragment_state & ~shape_cluster.parser_state();
                vector_state = vector_state & ~shape_cluster.parser_state();
                parser_state = shape_state.to_ullong() & shape_cluster.parser_state();

                std::cout << " | S" << std::bitset<24>{ shape_state.to_ullong() };
                std::cout << " | V" << std::bitset<24>{ vector_state };
                //std::cout << " | Q" << std::bitset<24>{ sequence_state.to_ullong() };
                std::cout << " | M" << std::bitset<24>{ match_state };
                std::cout << " | P" << std::bitset<24>{ parser_state };

                //std::cout << " | " << std::bitset<24>{ parser_state & shape_state.to_ullong() };
                //std::cout << debug;

                if (!match_state)
                {
                    std::cout << "\n";
                    ngl_error("unexpected element: {}", element);
                    throw std::logic_error("lexer error : shape is a fragment");
                }
/*
                if (shape_state.to_ullong() == 0)
                {
                    ngl_error("unexpected element: {}", element);
                    break;
                }*/

                // analyse mode
                // check if vector_state has single bit when previous_vector_state != vector_state // bool has_single_bit = (-v ^ v) <  -v;


                // scalar finalization
                finalize = (-match_state ^ match_state) < -match_state && shape_cluster.is_scalar(match_state);
                // vector finalization
                finalize |= (vector_state & pvector_state) == 0;
                //
                finalize |= sequence_state.to_ullong();

                if (parser_state != 0)
                {
                    //graph_.add()
                    std::cout << "P::" << shape_cluster.name_of(parser_state);
                    //graph_.add()
                }

                if (i == 0) finalize = false;
                //if (shape_cluster.is_parser())

                // finalization
                if (finalize)
                {
                    add_shape(vector_state, std::to_string(pvector_state), { i - vector_iterator - space, vector_iterator });
                    vector_iterator = 0;
                    sequence_state = 0;
                    space = 0;
                    finalize = false;
                }

                previous_state = shape_state;
                pvector_state = vector_state;

                vector_iterator++;

                jump:;

                // std::cout << "\n" << element << " | " << " " << shape_state;
            } // for data

            // last shape
            add_shape(previous_state.to_ullong(), std::to_string(previous_state.to_ullong()), { i - vector_iterator - space, vector_iterator });
            vector_iterator = 0;

            // remove init shape
            //shapes_.erase(shapes_.begin());
        }
        catch (const std::exception& e)
        {
            std::cout << "ERROR: " << e.what();
        }
    }

    void lexer::process_v2(const std::string& data)
    {

    }

    void lexer::asm_process()
    {
        //uint64_t r = lexer_process(data_.data(), shape_datas_.data());
        //std::cout << r;
    }

    void lexer::add(ngl::shape_cluster& shape_cluster)
    {
        shape_clusters_.emplace_back(shape_cluster);
    }

    void lexer::add_shape(uint64_t shape_id, const std::string& name, ngl::location location)
    {
        ngl::shape shape;
        shape.id = shape_id;
        shape.name = name;
        shape.location = location;
        shapes_.emplace_back(std::move(shape));
        //parse();
    }

    std::string_view lexer::display(const ngl::shape& shape)
    {
        return data_.substr(shape.location.origin, shape.location.size);
    }

    void lexer::display()
    {
        for (const auto& shape : shapes_)
        {
            std::cout << shape.name << "(" << display(shape) << ") ";
        }
        std::cout << std::endl;
    }

    std::string lexer::to_string(const shape& shape) const
    {
        std::string str = shape.name + "(" + std::string(data_.substr(shape.location.origin, shape.location.size)) + ")";

        return str;
    }
    std::string lexer::to_string() const
    {
        std::string str;

        for (const auto& shape : shapes_)
        {
            str += to_string(shape) + " ";
        }

        return str;
    }
    const std::vector<shape>& lexer::shapes() const { return shapes_; }
    std::string_view lexer::shape_view(int index) const
    {
        return data_.substr(shapes_[index].location.origin, shapes_[index].location.size);
    }
    std::string_view lexer::data() const { return data_; }









    void lexer::parse()
    {
        return;
        /*
        auto& element = shapes_.back();
        auto& shape_datas = shape_clusters_[1].get().datas();

        std::cout << "\n__" << element.id << " " << display(element);

        uint64_t vector_iterator = 0;
        std::bitset<64> shape_state;
        std::bitset<64> previous_state;

        uint64_t vector_state = 0;
        uint64_t pvector_state = 0;




        for (size_t shape_it = 0; shape_it < shape_datas.size(); ++shape_it)
                {
                    auto& shape = shape_datas[shape_it];
                    bool match = false;

                    vector_state = vector_state

                    std::cout << "\n" << shape_it << " " << shape.name << " ";

                    switch (static_cast<shape_type>(shape.type))
                    {
                    case shape_type::vector_sequence: {
                        auto ar = reinterpret_cast<std::vector<uint64_t>*>(shape.data);
                        auto sequence_size = ar->size();

                        auto shape_index = ar->operator[](shape.vector_index);
                        auto next_shape_index = -1;
                        if (shape.vector_index + 1 < sequence_size) next_shape_index = reinterpret_cast<std::vector<uint64_t>*>(shape.data)->operator[](shape.vector_index + 1);

                        std::cout << "\nvector_sequence " << element.id << " " << shape_index;
                        bool pmatch = previous_state[shape.index];
                        bool index_match = shape_state[shape_index];

                        if (!index_match && pmatch && next_shape_index != -1)
                        {
                            index_match = shape_state[next_shape_index];
                            shape.vector_index += index_match;
                        }

                        match = index_match;
                        shape_state[shape.index] = match;

                        if (match) vector_state |= shape.vector_id;
                        else
                        {
                            shape.vector_index = 0;
                        }

                        shape.vector_index = (shape.vector_index + (!index_match & pmatch));

                        //std::cout << " I: " << shape.vector_index
                        //  << " PM: " << pmatch
                        //  << " IM: " << index_match
                        //  << " M: " << match;


                        break;
                    }

                    case shape_type::vector_many:
                        match = shape_state[shape.data];
                        shape_state[shape.index] = match;
                        if (match) vector_state |= shape.vector_id;
                        std::cout << "\nvector_many " << element.id << " " << shape.data;
                        //std::cout << " [ _MANY " << shape.name << std::bitset<10>{ shape.vector_id } << ":" << match << " ]";

                        break;

                    } // switch

                    std::cout << " | " << std::bitset<32>{ shape_state.to_ullong() };
                    std::cout << " | " << std::bitset<32>{ vector_state };

                    //std::cout << match;

                } // for shape
                */
    }

    const std::vector<ngl::shape_cluster>& lexer::shape_cluster() const
    {
        return shape_clusters_;
    }
    void lexer::reset()
    {

    }
} // ngl
