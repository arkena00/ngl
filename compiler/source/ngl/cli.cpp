#include <ngl/cli.hpp>
#include <ngl/compiler.hpp>

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
        cl::opt<bool> flag_debug("d", cl::desc("debug mode"));

        cl::opt<std::string> input_filename(cl::Positional, cl::Required, cl::desc("<input file>"));

        // parse cl
        cl::ParseCommandLineOptions(argc, argv);

        if (flag_debug) nglc_.add_flag(ngl::compiler::flags::debug);

        nglc_.process(input_filename);

        // post process

    }
} // ngl