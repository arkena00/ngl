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
    class cluster;

    class ast_listener : public antlr4::nglBaseListener
    {
    public:
        ast_listener(ngl::cluster&);

    private:
        void enterStatement(antlr4::nglParser::StatementContext * ctx) override;
        void enterDescription(antlr4::nglParser::DescriptionContext * ctx) override;
        void enterScalar_description(antlr4::nglParser::Scalar_descriptionContext * ctx) override;
        void enterVector_description(antlr4::nglParser::Vector_descriptionContext * ctx) override;

        ngl::cluster& cluster_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_AST_LISTENER_HPP_NGL
