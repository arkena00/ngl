#ifndef COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL
#define COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL

#include <ngl/parser.hpp>
#include <ngl/lexer.hpp>
#include <ngl/graph.hpp>
#include "lang.hpp"

namespace ngl
{
    class cluster
    {
    public:
        cluster(std::string name, std::string source);

        void set_node(nds::node<std::string>*);

        ngl::ast* ast();
        ngl::graph& graph();
        nds::node<std::string>* root();
        nds::node<std::string>* node();

        void process(ngl::lang::identifier&);

    private:
        std::string name_;
        std::string source_;
        ngl::lexer lexer_;
        ngl::parser parser_;
        ngl::graph graph_;
        nds::node<std::string>* root_;
        nds::node<std::string>* node_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL
