#ifndef COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
#define COMPILER_INCLUDE_NGL_LEXER_HPP_NGL

#include <antlr4/nglLexer.h>
#include <antlr4/nglParser.h>
#include <ANTLRInputStream.h>

namespace ngl
{
    // temporary alias to access tokens enum
    struct tokens : antlr4::nglParser {};

    class lexer
    {
    public:
        lexer(const std::string& data)
            : antlr_input_{ data }
            , antlr_lexer_{ &antlr_input_ }
        {}

        antlr4::nglLexer& antlr_lexer() { return antlr_lexer_; }

    private:
        antlr4::ANTLRInputStream antlr_input_;
        antlr4::nglLexer antlr_lexer_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_LEXER_HPP_NGL
