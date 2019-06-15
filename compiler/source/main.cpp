#include <ngl/cli.hpp>
#include <ngl/compiler.hpp>

int main(int argc, const char* argv[])
{
    ngl::compiler nglc;
    ngl::cli cli{ nglc, argv };

    nglc.process();

    return 0;
}