#ifndef COMPILER_INCLUDE_NGL_LANG_HPP_NGL
#define COMPILER_INCLUDE_NGL_LANG_HPP_NGL

#include <ngl/assert.hpp>
#include <ngl/parser.hpp>
#include <ngl/lexer.hpp>

#include <string>

namespace ngl::lang
{
    class identifier
    {
    public:
        identifier(std::string name) : name_{ std::move(name) } {}

        const std::string& name() const { return name_; }

    private:
        std::string name_;
    };

    class identifier_descriptor
    {
        using ast_node_type = antlr4::nglParser::Identifier_descriptorContext;

    public:
        identifier_descriptor(ast_node_type* ast_node)
        {
            if (ast_node->identifier_path())
            {
                std::cout << "\n__path" << ast_node->identifier_path()->getText();
            }
            else if (ast_node->IDENTIFIER())
            {
                //unit_.alias.get("concept")
                std::cout << "\n__" << ast_node->IDENTIFIER()->getText();
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

            std::cout << ast_node->getText();
/*
            for (antlr4::tree::TerminalNode* item : ast_node->IDENTIFIER())
            {
                identifiers_.push_back(item->getText());
                std::cout << "\nID : " << item->getText();
            }
            if (identifiers_.size() > 0) std::cout << "error";

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

            name_ = ":" + identifiers_[0];
            for (auto i = 1; i < identifiers_.size(); ++i)
            {
                name_ +=  ":" + identifiers_[i];
            }*/
        }

        const std::string& name() const { return name_; }

        const std::string& source() const { return identifiers_[0]; }
        const std::string& target() const { return identifiers_[identifiers_.size() - 1]; }

    private:
        std::string name_;
        std::vector<std::string> identifiers_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_LANG_HPP_NGL
