#ifndef COMPILER_INCLUDE_NGL_PARSER_HPP_NGL
#define COMPILER_INCLUDE_NGL_PARSER_HPP_NGL

#include <ngl/lexer.hpp>
#include <ngl/ast/listener.hpp>
#include <ngl/log.hpp>

#include <antlr4-runtime.h>

namespace ngl
{
    class error_system : public antlr4::BaseErrorListener
    {
        void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
                         const std::string &msg, std::exception_ptr e) override
        {
            ngl_error("Parser error: {}", msg);
        }
    };

    using ast = antlr4::tree::ParseTree;

    class parser
    {
    public:
        parser(ngl::lexer& lexer)
            : lexer_{ lexer }
            , antlr_tokens_{ &lexer.antlr_lexer() }
            , antlr_parser_{ &antlr_tokens_ }
        {
            antlr_parser_.removeErrorListeners();
            antlr_parser_.addErrorListener(&err_);
        }

        ngl::ast* ast()
        {
            return antlr_parser_.root();
        }

    private:
        ngl::error_system err_;
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
