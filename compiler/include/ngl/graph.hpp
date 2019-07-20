#ifndef COMPILER_INCLUDE_NGL_GRAPH_HPP_NGL
#define COMPILER_INCLUDE_NGL_GRAPH_HPP_NGL

#include <nds/graph.hpp>

#include <string>

namespace ngl
{
    namespace lang { class identifier; }

    using graph = nds::graph<ngl::lang::identifier>;
} // ngl

#endif // COMPILER_INCLUDE_NGL_GRAPH_HPP_NGL
