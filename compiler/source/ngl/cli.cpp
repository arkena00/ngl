#include <ngl/cli.hpp>
#include <ngl/compiler.hpp>

#include <iostream>
#include <llvm/Support/CommandLine.h>

namespace ngl
{
    cli::cli()
    {}

    void cli::process(int argc, const char** argv)
    {
        using namespace llvm;

        cl::SetVersionPrinter([](raw_ostream& os){ os << "ngl compiler 0.1"; });
        cl::opt<std::string> OutputFilename("o", cl::desc("Specify output filename"), cl::value_desc("filename"));

        cl::opt<std::string> input_filename(cl::Positional, cl::Required, cl::desc("<input file>"));

        // flags
        cl::bits<ngl::compiler::flags> compiler_flags( cl::desc("Compiler flags"),
            cl::values
            (
                cl::OptionEnumValue{ "d", int(ngl::compiler::flags::debug), "Debug" }
                , cl::OptionEnumValue{ "t", int(ngl::compiler::flags::trace), "Trace" }
                , cl::OptionEnumValue{ "g", int(ngl::compiler::flags::graph), "Show program graph" }
                , cl::OptionEnumValue{ "nongl", int(ngl::compiler::flags::nongl), "Do not process ngl.ngl" }
            )
        );

        // parse cl
        cl::ParseCommandLineOptions(argc, argv);

        nc_.set_flags(compiler_flags.getBits());

        nc_.init();
        nc_.process(input_filename.c_str());

        // post process

    }
} // ngl