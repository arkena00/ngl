#include <ngl/ast/listener.hpp>

#include <ngl/lang.hpp>
#include <ngl/graph.hpp>

#include <vector>

namespace ngl
{
    ast_listener::ast_listener(ngl::cluster& cluster)
        : cluster_{ cluster }
    {}

    void ast_listener::enterStatement(antlr4::nglParser::StatementContext * ctx)
    {
          //std::cout << "\nStatementContext: " << ctx->getText();
    }

    void ast_listener::enterExpression_description(antlr4::nglParser::Expression_descriptionContext * ctx)
    {
       // compilation_unit. .add<ngl::lang::identifier_descriptor>()
        ngl::lang::identifier_descriptor idd{ ctx->identifier_descriptor() };

        //cluster_.process(ngl::lang::alias)

        return;
        ngl::lang::identifier_path identifier_path{ ctx->identifier_descriptor()->identifier_path() };
        //ngl::lang::identifier identifier{ ctx->IDENTIFIER()->getText() };

        //std::cout << "\n__" << identifier_path.source() <<  identifier_path.target() ;

        /*if (identifier_descriptor == identifier_described)
        {
            std::cout << "ngl self description";
        }*/

        if (ctx->description_block() != nullptr) std::cout << "\n__" <<  ctx->description_block()->getText();


        // add described identifier to the graph
        //auto identifier_node = graph_.add(std::move(identifier));
        //graph_.connect(std::get<0>(graph_.roots()), identifier_node);
    }
} // ngl
