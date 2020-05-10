#ifndef COMPILER_INCLUDE_NGL_PARSER_HPP_NGL
#define COMPILER_INCLUDE_NGL_PARSER_HPP_NGL

#include <ngl/lexer.hpp>
#include <ngl/log.hpp>

namespace ngl
{
    class parser
    {
    public:
        parser(ngl::lexer& lexer)
            : lexer_{ lexer }
        {
        }

    private:
        ngl::lexer& lexer_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_PARSER_HPP_NGL
