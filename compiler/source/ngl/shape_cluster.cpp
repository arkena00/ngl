#include <ngl/shape_cluster.hpp>

#include <bitset>
#include <iostream>

namespace ngl
{
    const std::string& shape_cluster::name() const { return name_; }
    std::vector<ngl::shape_data>& shape_cluster::datas() { return shape_datas_; }
    uint64_t shape_cluster::scalar_shapes_count() const { return scalar_shapes_; }

    void shape_cluster::display() const
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

    ngl::shape_data shape_cluster::add(ngl::shape_type shape_type, std::vector<uint64_t> data, const std::string& name)
    {
        vector_datas_.push_back(std::move(data));

        ngl::shape_data shape;

        shape.index = shape_data_index_++;
        shape.id = 1u << shape.index;
        shape.type = static_cast<uint64_t>(shape_type);
        shape.data = reinterpret_cast<uint64_t>(std::addressof(vector_datas_.back()));
        shape.name = name;

        //for (const auto& sh_id : vector_datas_.back()) shape.vector_id |= sh_id;
        //shape.vector_id |= shape.id;
        std::bitset<64> vector_state_mask{ ~uint64_t(0) << scalar_shapes_ };
        shape.vector_id = shape.id & vector_state_mask.to_ullong();

        shape_datas_.push_back(shape);

        return shape;
    }

    ngl::shape_data shape_cluster::add(ngl::shape_type shape_type, char data, const std::string& name)
    {
        return add(shape_type, static_cast<uint64_t>(data), name);
    }

    ngl::shape_data shape_cluster::add(ngl::shape_type shape_type, uint64_t data, const std::string& name)
    {
        ngl::shape_data shape;

        switch (shape_type)
        {
        case ngl::shape_type::scalar_element:
        case ngl::shape_type::scalar_element_vector:
        case ngl::shape_type::scalar_range:
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

    ngl::shape_data shape_cluster::add(ngl::shape_element element, const std::string& name)
    {
        return add(shape_type::scalar_element, element.data, name);
    }
    ngl::shape_data shape_cluster::add(ngl::shape_element_vector element, const std::string& name)
    {
        return add(shape_type::scalar_element_vector, element.data, name);
    }
    ngl::shape_data shape_cluster::add(ngl::shape_or or_, const std::string& name)
    {
        return add(shape_type::composite_or, or_.data, name);
    }
    ngl::shape_data shape_cluster::add(ngl::shape_range range, const std::string& name)
    {
        return add(shape_type::scalar_range, range.data, name);
    }
    ngl::shape_data shape_cluster::add(ngl::shape_many many, const std::string& name)
    {
        return add(shape_type::vector_many, many.data, name);
    }
    ngl::shape_data shape_cluster::add(ngl::shape_sequence sequence, const std::string& name)
    {
        return add(shape_type::vector_sequence, std::move(sequence.data), name);
    }
    ngl::shape_data shape_cluster::add(ngl::shape_space space, const std::string& name)
    {
        return add(shape_type::space, std::move(space.data), name);
    }
} // ngl