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

        shape_cluster(const shape_cluster&) = delete;
        shape_cluster(shape_cluster&&) = default;

        [[nodiscard]] const std::string& name() const;
        [[nodiscard]] std::vector<ngl::shape_data>& datas();
        void display() const;

        ngl::shape_data add(ngl::shape_type, std::vector<uint64_t> data, const std::string& name = "shape");
        ngl::shape_data add(ngl::shape_type, char data, const std::string& name = "shape");
        ngl::shape_data add(ngl::shape_type, uint64_t data, const std::string& name = "shape");

        ngl::shape_data add(ngl::shape_element, const std::string& name = "shape_element");
        ngl::shape_data add(ngl::shape_element_vector, const std::string& name = "shape_element_vector");
        ngl::shape_data add(ngl::shape_many, const std::string& name = "shape_many");
        ngl::shape_data add(ngl::shape_not, const std::string& name = "shape_not");
        ngl::shape_data add(ngl::shape_or, const std::string& name = "shape_or");
        ngl::shape_data add(ngl::shape_range, const std::string& name = "shape_range");
        ngl::shape_data add(ngl::shape_sequence, const std::string& name = "shape_sequence");
        ngl::shape_data add(ngl::shape_space space, const std::string& name = "shape_space");

        uint64_t scalar_shapes_count() const;
        uint64_t vector_shapes_count() const;

    private:
        std::string name_;
        std::vector<ngl::shape_data> shape_datas_;
        std::vector<std::unique_ptr<std::vector<uint64_t>>> vector_datas_;
        uint64_t scalar_shapes_ = 0;
        uint64_t vector_shapes_ = 0;
        uint64_t shape_data_index_ = 0;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_SHAPE_CLUSTER_HPP_NGL
