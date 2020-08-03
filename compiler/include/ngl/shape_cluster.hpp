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

        ngl::shape_data add(ngl::shape_type, std::vector<uint64_t> data, const std::string& name = "shape", bool is_parser = false);
        ngl::shape_data add(ngl::shape_type, char data, const std::string& name = "shape", bool is_parser = false);
        ngl::shape_data add(ngl::shape_type, uint64_t data, const std::string& name = "shape", bool is_parser = false);

        ngl::shape_data add(ngl::shape_element, const std::string& name = "shape_element", bool is_parser = false);
        ngl::shape_data add(ngl::shape_element_vector, const std::string& name = "shape_element_vector", bool is_parser = false);
        ngl::shape_data add(ngl::shape_many, const std::string& name = "shape_many", bool is_parser = false);
        ngl::shape_data add(ngl::shape_not, const std::string& name = "shape_not", bool is_parser = false);
        ngl::shape_data add(ngl::shape_or, const std::string& name = "shape_or", bool is_parser = false);
        ngl::shape_data add(ngl::shape_range, const std::string& name = "shape_range", bool is_parser = false);
        ngl::shape_data add(ngl::shape_sequence, const std::string& name = "shape_sequence", bool is_parser = false);
        ngl::shape_data add(ngl::shape_space space, const std::string& name = "shape_space", bool is_parser = false);

        uint64_t scalar_shapes_count() const;
        uint64_t vector_shapes_count() const;

        uint64_t parser_index = 0;
        uint64_t parser_shape_state_ = 0;

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
