#include <ngl/cli.hpp>

#include <ngl/compiler.hpp>

#include <argh.h>
#include <iostream>

namespace ngl
{
    cli::cli(ngl::compiler& nglc, const char** argv)
        : nglc_{ nglc }
    {
        argh::parser cmdl(argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

        if (cmdl[{ "-d", "--debug" }]) nglc_.add_flag(ngl::compiler::flags::debug);

        std::string output;
        if (cmdl({ "-o", "--output" }) >> output) nglc_.add_param(ngl::compiler::params::output, output);

        if (cmdl.pos_args().size() < 2) std::cerr << "File argument missing";
        else nglc.set_file(cmdl[1]);
    }
} // ngl