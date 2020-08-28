#include <nds/graph.hpp>
#include <ngl/cluster.hpp>
#include <nds/encoder/graph.hpp>

namespace nds::encoders
{
    template<> template<>
    inline std::string dot<>::node_name<std::string>(const std::string& v)
    {
        return v;
    }
}

using namespace std::string_literals;

int main()
{
    ngl::cluster cluster{ "cluster", "" };
    auto& g = cluster.graph();
    auto n0 = g.add("ngl"s);
    auto ngc = g.add("concept"s, n0);
    auto ngi = g.add("instruction"s, n0);
    auto ngs = g.add("shape"s, n0);

    auto ngc_add = g.add("ngc:add"s, ngc);
    auto ngi_add = g.add("ngi:add"s, ngi);
    auto ngs_add = g.add("ngs:add(id + id)"s, ngs);

    auto id1 = g.add("id_1"s, ngs_add);
    auto id2 = g.add("id_2"s, ngs_add);


    g.add_arc(ngc_add, ngi_add);

    g.add_arc(ngs_add, ngc_add);
    g.add_arc(ngc_add, ngs_add);

    cluster.process();

    nds::encoders::dot<>::encode<nds::console>(cluster.graph());

    return 0;
}
