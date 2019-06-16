#include <ngl/cli.hpp>

#include <ngl/compiler.hpp>

#include <argh.h>
#include <iostream>

namespace ngl
{
    cli::cli()
    {}

    void cli::process(const char** argv)
    {
        argh::parser cmdl(argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

        // 0 args
        if (cmdl[{ "-v", "--version" }])
        {
            std::cout << "ngl compiler 0.1\n";
            return;
        }

        // 1 args
        if (cmdl[{ "-d", "--debug" }]) nglc_.add_flag(ngl::compiler::flags::debug);

        std::string output;
        if (cmdl({ "-o", "--output" }) >> output) nglc_.add_param(ngl::compiler::params::output, output);

        if (cmdl.pos_args().size() < 2) std::cerr << "File argument missing";

        nglc_.process(cmdl[1]);
    }
} // ngl