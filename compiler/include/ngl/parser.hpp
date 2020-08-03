#ifndef COMPILER_INCLUDE_NGL_PARSER_HPP_NGL
#define COMPILER_INCLUDE_NGL_PARSER_HPP_NGL

#include <ngl/lexer.hpp>
#include <ngl/log.hpp>

namespace ngl
{
    class parser
    {
    public:
        explicit parser(ngl::lexer& lexer)
            : lexer_{ lexer }
        {

        }

        void process(const std::string& source)
        {
            /*
            lexer_.set_source(source);

            while (lexer_.has_shapes())
            {
                auto shape = lexer_.next_shape();
                lexer_.display(shape);
            }*/
        }

    private:
        ngl::lexer& lexer_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_PARSER_HPP_NGL
