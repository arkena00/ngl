#include <ngl/lexer.hpp>
#include <ngl/parser.hpp>
#include <ngl/shape_cluster.hpp>
#include <nds/graph.hpp>
#include <ngl/cluster.hpp>

using namespace std::string_literals;

int main()
{
    try
    {
        ngl::ngl_shape_cluster ngl_shapes;
        ngl::lexer lexer {ngl_shapes};
        std::string source_code = R"(
ngl:concept function
{
    ngl:data result
}

ngl:concept:function add
{
    ngl::int <a>
    ngl::int <b>
    ngl:concept:function:result ngl::instruction_add<a, b>
}
)";

        lexer.process(source_code);

        // Parsing algorithm
//
//        auto& shapes = lexer.shapes();
//        ngl::cluster cluster {"main", ""};
//        auto& graph = cluster.graph();
//
//        for (const auto& shape : shapes)
//        {
//            std::cout << shape.name << std::endl;
//        }

        ngl::parser parser {lexer};

    } catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}

//int main()
//{
//    try
//    {
//        ngl::ngl_shape_cluster ngl_shape;
//
//        ngl::lexer lx{ ngl_shape };
//
//        std::string data = R"(
//ngl:shape scalar_description
//{
//    ngc:sequence<ngs:identifier ngs:identifier>
//}
//)";
//
//
//ngl_shape.add(ngl::shape_sequence());
//
//
//
//    lx.process(data);
//    std::cout << lx.to_string();
//
//    }
//    catch (const std::exception& e)
//    {
//        std::cout << e.what();
//    }
//
//    return 0;
//}