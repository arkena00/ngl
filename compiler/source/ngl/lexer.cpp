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

    lexer::lexer(ngl::shape_cluster& shape_cluster)
        : data_{}
    {
        shape_clusters_.emplace_back(shape_cluster);
    }

    void lexer::process(const std::string& data)
    {
        data_ = data;
        process();
    }

    void lexer::process()
    {
        try
        {
            uint64_t vector_iterator = 0;
            std::bitset<64> shape_state;
            std::bitset<64> previous_state;

            uint64_t vector_state = 0;
            uint64_t pvector_state = 0;
            shapes_.clear();
            shapes_.reserve(data_.size());

            size_t i = 0;
            size_t space = 0;

            if (shape_clusters_.empty()) ngl_error("Lexer requires at least 1 shape_cluster");
            auto& shape_data = shape_clusters_[0].get().datas();
            auto scalar_shapes_count = shape_clusters_[0].get().scalar_shapes_count();

            for (i = 0; i < data_.size(); ++i)
            {
                shape_state.reset();
                const auto& element = data_[i];
                //const auto& next_element = data_[i];

                //std::cout << "\n" << element;

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

                        //!     # seq<_ ng _>
                        //!    _ I: 0 IM: 1 PM: 0 NM: 0 M: 1
                        //!        n I: 0 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 1 IM = 1 M = 1
                        //!    n I: 1 IM: 1 PM: 1 NM: 0 M: 1
                        //!    g I: 1 IM: 1 PM: 1 NM: 0 M: 1
                        //!        _ I: 1 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 2 IM = 1 M = 1
                        //!    _ I: 2 IM: 1 PM: 1 NM: 0 M: 1
                        //!
                        //!    #end1 I == LI && is_scalar<LS>               -> I = 0 VID = ~VID
                        //!    #end2 I == LI && !is_scalar<LS> && NM == 0   -> I = 0 VID = ~VID
                    case shape_type::vector_sequence: {
                        auto ar = reinterpret_cast<std::vector<uint64_t>*>(shape.data);
                        auto sequence_size = ar->size();

                        auto shape_index = ar->operator[](shape.vector_index);
                        auto next_shape_index = -1;
                        if (shape.vector_index + 1 < sequence_size) next_shape_index = reinterpret_cast<std::vector<uint64_t>*>(shape.data)->operator[](shape.vector_index + 1);

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
                        //std::cout << " [ _MANY " << shape.name << std::bitset<10>{ shape.vector_id } << ":" << match << " ]";

                        break;
                    } // switch

                    //std::cout << match;

                } // for shape


                //std::cout << " | " << std::bitset<32>{ shape_state.to_ullong() };
                //std::cout << " | " << std::bitset<32>{ vector_state };

                //std::cout << debug;

                if (shape_state.to_ullong() == 0)
                {
                    ngl_error("unexpected element: {}", element);
                    break;
                }

                // analyse mode
                // check if vector_state has single bit when previous_vector_state != vector_state // bool has_single_bit = (-v ^ v) <  -v;

                // scalar finalisation
                /*
                if ((previous_state.to_ullong() & vector_state_mask.to_ullong()) == 0)
                {
                    add_shape(std::to_string(previous_state.to_ullong()), { i - 1 - space, 1 });
                    vector_iterator = 0;
                    space = 0;
                }*/

                // vector finalisation
                if ((vector_state & pvector_state) == 0)
                {
                    //std::cout << "__" << (i - vector_iterator - space) << "__" << vector_iterator;
                    add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator - space, vector_iterator });
                    vector_iterator = 0;
                    space = 0;
                }

                previous_state = shape_state;
                pvector_state = vector_state;

                vector_iterator++;

                jump:;

                // std::cout << "\n" << element << " | " << " " << shape_state;
            } // for data

            // last shape
            add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator - space, vector_iterator });
            vector_iterator = 0;

            // remove init shape
            shapes_.erase(shapes_.begin());
        }
        catch (const std::exception& e)
        {
            std::cout << "ERROR: " << e.what();
        }
    }

    void lexer::process_v2(const std::string& data)
    {
        data_ = data;
        try
        {
            uint64_t vector_iterator = 0;
            std::bitset<64> shape_state;
            std::bitset<64> previous_state;

            uint64_t vector_state = 0;
            uint64_t pvector_state = 0;
            shapes_.clear();
            shapes_.reserve(data_.size());

            size_t i = 0;
            size_t space = 0;

            if (shape_clusters_.empty()) ngl_error("Lexer requires at least 1 shape_cluster");
            auto& shape_data = shape_clusters_[0].get().datas();
            auto scalar_shapes_count = shape_clusters_[0].get().scalar_shapes_count();

            for (i = 0; i < data_.size(); ++i)
            {
                shape_state.reset();
                const auto& element = data_[i];
                //const auto& next_element = data_[i];

                //std::cout << "\n" << element;

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
                        if (match) shape_it = scalar_shapes_count;

                        break;

                    case shape_type::scalar_element_vector:
                        match = shape.data == (*reinterpret_cast<const uint64_t*>(&element) & shape.data);
                        shape_state[shape.index] = match;
                        vector_state = 0;
                        if (match) shape_it = scalar_shapes_count;

                        break;

                    case shape_type::scalar_range:
                        match = (element >= (shape.data >> 8u) && element <= ((shape.data << 56u) >> 56u));
                        shape_state[shape.index] = match;
                        vector_state = 0;
                        if (match) shape_it = scalar_shapes_count;

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

                        //!     # seq<_ ng _>
                        //!    _ I: 0 IM: 1 PM: 0 NM: 0 M: 1
                        //!        n I: 0 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 1 IM = 1 M = 1
                        //!    n I: 1 IM: 1 PM: 1 NM: 0 M: 1
                        //!    g I: 1 IM: 1 PM: 1 NM: 0 M: 1
                        //!        _ I: 1 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 2 IM = 1 M = 1
                        //!    _ I: 2 IM: 1 PM: 1 NM: 0 M: 1
                        //!
                        //!    #end1 I == LI && is_scalar<LS>               -> I = 0 VID = ~VID
                        //!    #end2 I == LI && !is_scalar<LS> && NM == 0   -> I = 0 VID = ~VID
                    case shape_type::vector_sequence: {
                        auto ar = reinterpret_cast<std::vector<uint64_t>*>(shape.data);
                        auto sequence_size = ar->size();

                        auto shape_index = ar->operator[](shape.vector_index);
                        auto next_shape_index = -1;
                        if (shape.vector_index + 1 < sequence_size) next_shape_index = reinterpret_cast<std::vector<uint64_t>*>(shape.data)->operator[](shape.vector_index + 1);

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
                        if (match) vector_state = (vector_state | shape.vector_id) ; // vector_state_mask & shape_state;
                        //std::cout << " [ _MANY " << shape.name << std::bitset<10>{ shape.vector_id } << ":" << match << " ]";

                        break;
                    } // switch

                    //std::cout << match;

                } // for shape


                //std::cout << " | " << std::bitset<32>{ shape_state.to_ullong() };
                //std::cout << " | " << std::bitset<32>{ vector_state };

                //std::cout << debug;

                if (shape_state.to_ullong() == 0)
                {
                    ngl_error("unexpected element: {}", element);
                    break;
                }

                // analyse mode
                // check if vector_state has single bit when previous_vector_state != vector_state // bool has_single_bit = (~v + 1u) ^ v <  ~v + 1u;

                // scalar finalisation
                /*
                if ((previous_state.to_ullong() & vector_state_mask.to_ullong()) == 0)
                {
                    add_shape(std::to_string(previous_state.to_ullong()), { i - 1 - space, 1 });
                    vector_iterator = 0;
                    space = 0;
                }*/

                // vector finalisation
                if ((vector_state & pvector_state) == 0)
                {
                    //std::cout << "__" << (i - vector_iterator - space) << "__" << vector_iterator;
                    add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator - space, vector_iterator });
                    vector_iterator = 0;
                    space = 0;
                }

                previous_state = shape_state;
                pvector_state = vector_state;

                vector_iterator++;

                jump:;

                // std::cout << "\n" << element << " | " << " " << shape_state;
            } // for data

            // last shape
            add_shape(std::to_string(previous_state.to_ullong()), { i - vector_iterator - space, vector_iterator });
            vector_iterator = 0;

            // remove init shape
            shapes_.erase(shapes_.begin());
        }
        catch (const std::exception& e)
        {
            std::cout << "ERROR: " << e.what();
        }
    }

    void lexer::asm_process()
    {
        //uint64_t r = lexer_process(data_.data(), shape_datas_.data());
        //std::cout << r;
    }

    void lexer::add(ngl::shape_cluster& shape_cluster)
    {
        shape_clusters_.push_back(shape_cluster);
    }

    void lexer::add_shape(const std::string& name, ngl::location location)
    {
        ngl::shape shape;
        shape.name = name;
        shape.location = location;
        shapes_.push_back(shape);
    }

    void lexer::display()
    {
        for (const auto& shape : shapes_)
        {
            std::cout << shape.name << "(" << data_.substr(shape.location.origin, shape.location.size) << ") ";
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
} // ngl


//!     # seq<_ ng _>
//!    _ I: 0 IM: 1 PM: 0 NM: 0 M: 1
//!        n I: 0 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 1 IM = 1 M = 1
//!    n I: 1 IM: 1 PM: 1 NM: 0 M: 1
//!    g I: 1 IM: 1 PM: 1 NM: 0 M: 1
//!        _ I: 1 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 2 IM = 1 M = 1
//!    _ I: 2 IM: 1 PM: 1 NM: 0 M: 1
//!
//!    #end1 I == LI && is_scalar<LS>               -> I = 0 VID = ~VID
//!    #end2 I == LI && !is_scalar<LS> && NM == 0   -> I = 0 VID = ~VID