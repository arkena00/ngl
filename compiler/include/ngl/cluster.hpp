#ifndef COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL
#define COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL

#include <ngl/parser.hpp>
#include <ngl/lexer.hpp>
#include <ngl/graph.hpp>

namespace ngl
{
    class cluster
    {
    public:
        cluster(std::string name, std::string source);

        ngl::ast* ast();
        ngl::graph& graph();

        void build();

    private:
        std::string name_;
        std::string source_;
        ngl::graph graph_;
        ngl::lexer lexer_;
        ngl::parser parser_;
    };
} // namespace ngl

#endif // COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL
