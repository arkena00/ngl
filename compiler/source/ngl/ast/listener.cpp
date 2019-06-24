#include <ngl/ast/listener.hpp>

#include <ngl/lang.hpp>
#include <ngl/graph.hpp>

#include <vector>

namespace ngl
{
    ast_listener::ast_listener(ngl::graph& graph)
        : graph_{ graph }
    {}

    void ast_listener::enterStatement(antlr4::nglParser::StatementContext * ctx)
    {
          std::cout << "\nStatementContext: " << ctx->getText();
    }

    void ast_listener::enterExpression_description(antlr4::nglParser::Expression_descriptionContext * ctx)
    {
        ngl::lang::identifier_path identifier_path{ ctx->identifier_path() };

        // add described identifier to the graph
        graph_ += "\n" +identifier_path.name();
    }
} // ngl
