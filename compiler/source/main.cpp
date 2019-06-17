#include <ngl/cli.hpp>
#include <ngl/compiler.hpp>

int main(int argc, const char* argv[])
{
    ngl::cli cli;

    cli.process(argc, argv);

    return 0;
}