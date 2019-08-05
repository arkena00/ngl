#ifndef COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL
#define COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL

#include <ngl/graph.hpp>

#include <llvm/Support/CommandLine.h>

#include <bitset>
#include <string>
#include <unordered_map>

namespace ngl
{
    class compiler
    {
    public:
        enum class flags { none = 0, debug, trace, graph };
        enum class params { output };

        compiler();

        void add_flag(flags);
        void set_flags(unsigned int);
        bool has_flag(flags flag);

        void add_param(params, std::string value);

        void process(std::string file_path);

        void set_file(std::string);

    private:
        std::string file_path_;
        std::bitset<64> flags_;
        std::unordered_map<params, std::string> params_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL
