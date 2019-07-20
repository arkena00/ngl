#ifndef COMPILER_INCLUDE_NGL_PARSER_HPP_NGL
#define COMPILER_INCLUDE_NGL_PARSER_HPP_NGL

#include <ngl/lexer.hpp>
#include <ngl/ast/listener.hpp>

namespace ngl
{
    using ast = antlr4::tree::ParseTree;

    class parser
    {
    public:
        parser(ngl::lexer& lexer)
            : lexer_{ lexer }
            , antlr_tokens_{ &lexer.antlr_lexer() }
            , antlr_parser_{ &antlr_tokens_ }
        {}

        ngl::ast* ast()
        {
            return antlr_parser_.root();
        }

    private:
        antlr4::nglParser antlr_parser_;
        antlr4::CommonTokenStream antlr_tokens_;
        ngl::lexer& lexer_;
    };

    inline void traverse(ngl::ast* ast, ngl::ast_listener& listener)
    {
        antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, ast);
    }
} // ngl

#endif // COMPILER_INCLUDE_NGL_PARSER_HPP_NGL
