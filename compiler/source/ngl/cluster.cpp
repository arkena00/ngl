#include <ngl/cluster.hpp>

#include <ngl/log.hpp>
#include <nds/encoder/graph.hpp>

namespace ngl
{
    cluster::cluster(std::string name, std::string source)
        : name_{ std::move(name) }
        , source_{ std::move(source) }
        , lexer_{ }
        , parser_{ lexer_ }
        , root_{ nullptr }
    {
        root_ = graph_.add(name_);
        node_ = root_;
    }

    void cluster::process()
    {
        ngl_info("Process cluster {}", name_);
        lexer_.process();
    }

    ngl::graph& cluster::graph()
    {
        return graph_;
    }


    nds::node_ptr<std::string> cluster::root()
    {
        return root_;
    }



    nds::node_ptr<std::string> cluster::node()
    {
        return node_;
    }
} // ngl