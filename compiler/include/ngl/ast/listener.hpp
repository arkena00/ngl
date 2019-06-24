#ifndef COMPILER_INCLUDE_NGL_AST_LISTENER_HPP_NGL
#define COMPILER_INCLUDE_NGL_AST_LISTENER_HPP_NGL

#include <ngl/graph.hpp>

#include <antlr4-runtime.h>
#include <antlr4/nglBaseListener.h>
#include <antlr4/nglLexer.h>
#include <antlr4/nglParser.h>

#include <string>

namespace ngl
{
    class ast_listener : public antlr4::nglBaseListener
    {
    public:
        ast_listener(ngl::graph& graph);

    private:
        void enterStatement(antlr4::nglParser::StatementContext * ctx) override;
        void enterExpression_description(antlr4::nglParser::Expression_descriptionContext * ctx) override;

        ngl::graph& graph_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_AST_LISTENER_HPP_NGL
