#ifndef COMPILER_INCLUDE_NGL_LANG_HPP_NGL
#define COMPILER_INCLUDE_NGL_LANG_HPP_NGL

#include <ngl/assert.hpp>
#include <ngl/parser.hpp>
#include <ngl/lexer.hpp>

#include <optional>
#include <string>
#include <vector>

namespace ngl::lang
{
    struct scalar_identifier
    {
        using ast_node_type = antlr4::nglParser::Scalar_identifierContext;

        scalar_identifier(ast_node_type* ast_node);

        std::string name;
        std::optional<std::string> parameter;
    };

    class identifier
    {
        using ast_node_type = antlr4::nglParser::IdentifierContext;

    public:
        identifier(ast_node_type* ast_node)
        {
            if (ast_node->RAW_IDENTIFIER()) name_ = ast_node->RAW_IDENTIFIER()->getText();

            if (ast_node->path_identifier())
            {
                for (antlr4::nglParser::Scalar_identifierContext* scalar_id : ast_node->path_identifier()->scalar_identifier())
                {
                    parameters_->push_back( lang::scalar_identifier{ scalar_id } );
                    std::cout << "\ncheck " << parameters_->back().name;
                }
                name_ = parameters_->back().name;
            }
        }

        // is_scalar path

        const std::string& name() const
        {
            return name_;
        }

    private:
        std::string name_;
        std::optional<std::vector<lang::scalar_identifier>> parameters_;
    };

    /*
    class identifier_descriptor
    {
        using ast_node_type = antlr4::nglParser::Identifier_descriptorContext;

    public:
        identifier_descriptor(ast_node_type* ast_node)
        {
            if (ast_node->identifier_path())
            {
                //std::cout << "\n__path" << ast_node->identifier_path()->getText();
            }
            else if (ast_node->identifier_path())
            {
                //unit_.alias.get("concept")
                //std::cout << "\n__" << ast_node->IDENTIFIER()->getText();
            }

            // alias or identifier_path
        }
    };


    class identifier_path
    {
        using ast_node_type = antlr4::nglParser::Identifier_pathContext;
    public:
        identifier_path(ast_node_type* ast_node)
        {
            std::vector<antlr4::tree::TerminalNode*> identifiers;

            if (ast_node)
            {
                for (antlr4::tree::TerminalNode* item : ast_node->IDENTIFIER())
                {
                    identifiers_.push_back(item->getText());
                }

                for (auto i = 0; i != identifiers_.size() - 1; ++i)
                {
                    auto edge_type = ast_node->identifier_edge(i)->getStart()->getType();
                    std::cout << "\nsource: " << identifiers_[i] << " target: " << identifiers_[i + 1] << " " << edge_type;
                    if (edge_type == ngl::tokens::DOUBLE_COLON)
                    {
                        std::cout << " _deduction required";
                        // search from source until target
                    }
                }

                ngl_assert(identifiers_.size() > 0);
                name_ = identifiers_[0];
                for (auto i = 1; i < identifiers_.size(); ++i)
                {
                    name_ +=  ":" + identifiers_[i];
                }
            }
        }

        const std::string& name() const { return name_; }

        const std::string& source() const { return identifiers_[0]; }
        const std::string& target() const { return identifiers_[identifiers_.size() - 1]; }

    private:
        std::string name_;
        std::vector<std::string> identifiers_;
    };
     */
} // ngl

#endif // COMPILER_INCLUDE_NGL_LANG_HPP_NGL
