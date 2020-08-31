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
            : name_{ std::move(name) }
        {}

        void display() const;

        template<class Shape, class... Ts>
        ngl::shape_data add_fragment(const char* name, Ts&&... vs)
        {
            Shape sh(std::forward<Ts>(vs)...);
            return add(Shape::type, std::move(sh.data), name, true, false);
        }

        template<class Shape = ngl::shape_element, class... Ts>
        ngl::shape_data add_fragment(Ts&&... vs)
        {
            Shape sh(std::forward<Ts>(vs)...);
            return add(Shape::type, std::move(sh.data), Shape::name, true, false);
        }


        template<class Shape = ngl::shape_element, class... Ts>
        ngl::shape_data add_element(const char* name, Ts&&... vs)
        {
            Shape sh(std::forward<Ts>(vs)...);
            return add(Shape::type, std::move(sh.data), name, false, false);
        }

        template<class Shape, class... Ts>
        ngl::shape_data add_element(Ts&&... vs)
        {
            Shape sh(std::forward<Ts>(vs)...);
            return add(Shape::type, std::move(sh.data), Shape::name, false, false);
        }

        ngl::shape_data add_element(char v)
        {
            ngl::shape_element sh(v);
            return add(ngl::shape_element::type, sh.data, std::string(1, v), false, false);
        }

        template<class Shape, class... Ts>
        ngl::shape_data add(const std::string& name, Ts&&... vs)
        {
            Shape sh(std::forward<Ts>(vs)...);
            return add(Shape::type, std::move(sh.data), name, false, true);
        }

        ngl::shape_data add(ngl::shape_type, std::vector<uint64_t> data, const std::string& name = "shape", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_type, char data, const std::string& name = "shape", bool is_fragment = false, bool is_parser = false);
        ngl::shape_data add(ngl::shape_type, uint64_t data, const std::string& name = "shape", bool is_fragment = false, bool is_parser = false);

        [[nodiscard]] bool is_fragment(uint64_t shape_id) const;
        [[nodiscard]] bool is_parser(uint64_t shape_id) const;
        [[nodiscard]] bool is_scalar(uint64_t shape_index) const;

        [[nodiscard]] const std::string& name_of(uint64_t shape_id) const;

        [[nodiscard]] const std::string& name() const;
        [[nodiscard]] std::vector<ngl::shape_data>& datas();

        [[nodiscard]] uint64_t scalar_shapes_count() const;
        [[nodiscard]] uint64_t vector_shapes_count() const;
        std::vector<uint64_t>& vector_data(unsigned int index) { return vector_datas_[index]; }

        [[nodiscard]] uint64_t fragment_state() const { return fragment_state_; }
        [[nodiscard]] uint64_t parser_state() const { return parser_state_; }

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

    ngl::shape_cluster& get_shape_cluster();
} // ngl

#endif // COMPILER_INCLUDE_NGL_SHAPE_CLUSTER_HPP_NGL
