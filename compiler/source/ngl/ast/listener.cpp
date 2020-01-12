#include <ngl/ast/listener.hpp>

#include <ngl/lang.hpp>
#include <ngl/cluster.hpp>
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

    void ast_listener::enterDescription(antlr4::nglParser::DescriptionContext * ctx)
    {
        //ngl::lang::identifier_descriptor idd{ ctx->identifier_descriptor() };

        //cluster_.process(ngl::lang::alias)


        //ngl::lang::identifier_path identifier_path{ ctx->identifier_descriptor()->identifier()-> };
        //ngl::lang::identifier identifier{ ctx->IDENTIFIER()->getText() };

        //std::cout << "\n__" << identifier_path.source() <<  identifier_path.target() ;

        /*if (identifier_descriptor == identifier_described)
        {
            std::cout << "ngl self description";
        }*/

        //if (ctx->description_block() != nullptr) std::cout << "\n__" <<  ctx->description_block()->getText();


        // add described identifier to the graph
        //auto identifier_node = cluster_.graph().add(std::move(identifier_path.name()));
        //cluster_.graph().connect(cluster_.root(), identifier_node);
    }

    void ast_listener::enterScalar_description(antlr4::nglParser::Scalar_descriptionContext* ctx)
    {
        std::cout << "\nscalar desc";
        ngl::lang::identifier descriptor{ ctx->identifier() };
        std::string described_identifier = ctx->RAW_IDENTIFIER()->getText();
        std::cout << " : " << descriptor.name();
        std::cout << " : " << described_identifier;
        std::cout << "\n";

        //cluster_.process()
        cluster_.graph().add(std::move(described_identifier), cluster_.root());
    }

    void ast_listener::enterVector_description(antlr4::nglParser::Vector_descriptionContext* ctx)
    {
        ngl::lang::identifier descriptor{ ctx->identifier(0) };
        std::string described_identifier = ctx->RAW_IDENTIFIER()->getText();
        if (descriptor.name() == described_identifier)
        {
            std::cout << "\nSELF DESC";
            auto self_node = cluster_.graph().add(descriptor.name(), cluster_.node());
            cluster_.set_node(self_node);

            for (int i = 1; i < ctx->identifier().size(); ++i)
            {
                ngl::lang::identifier id{ ctx->identifier(i) };
                std::cout << "\n_" << id.name();
                cluster_.graph().add(id.name(), cluster_.node());
            }

        }
    }
} // ngl
