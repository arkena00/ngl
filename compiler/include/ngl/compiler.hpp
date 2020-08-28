#ifndef COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL
#define COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL

#include <ngl/concretizer.hpp>
#include <ngl/graph.hpp>

#include <llvm/Support/CommandLine.h>

#include <bitset>
#include <string>
#include <unordered_map>

#include <nds/encoder/graph.hpp>

namespace nds::encoders
{
    template<> template<>
    inline std::string dot<>::node_name<std::string>(const std::string& v)
    {
        return v;
    }
}

namespace ngl
{
    class compiler
    {
    public:
        enum class flags { none = 0, debug, graph, nongl, trace };
        enum class params { output };

        compiler();

        void init();

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

        std::unique_ptr<ngl::concretizer> concretizer_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL
