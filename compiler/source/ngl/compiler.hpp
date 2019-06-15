#ifndef COMPILER_SOURCE_NGL_COMPILER_HPP_NGL
#define COMPILER_SOURCE_NGL_COMPILER_HPP_NGL

#include <string>
#include <unordered_map>

namespace ngl
{
    class compiler
    {
    public:
        enum class flags { debug = 0, f = 2 };
        enum class params { output };

        compiler() = default;

        void add_flag(flags);
        void add_param(params, std::string value);

        void process();

        void set_file(std::string);

    private:
        std::string file_;
        flags flags_;
        std::unordered_map<params, std::string> params_;
    };
} // ngl

#endif // COMPILER_SOURCE_NGL_COMPILER_HPP_NGL
