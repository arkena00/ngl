#include <ngl/lexer.hpp>
#include <ngl/shape_cluster.hpp>
#include <nds/graph.hpp>
#include <ngl/cluster.hpp>

using namespace std::string_literals;

int main()
{
    try
    {
        ngl::shape_cluster shapes;
        auto letter = shapes.add_element<ngl::shape_range>("letter", 'a', 'z');
        auto plus = shapes.add_fragment<ngl::shape_element>("plus", '+');

        auto add = shapes.add<ngl::shape_sequence>("add", letter, plus, letter);

        ngl::lexer lx{ shapes };

        std::string data{ "a+b" };
        lx.process(data);

        std::vector<std::string> v;
        lx.graph().targets(lx.root(), [&](auto&& n) { v.push_back(*n); });

        std::cout << "\n" << lx.to_string();

    } catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

}