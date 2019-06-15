#include <iostream>
#include <ngl/compiler.hpp>


#include "antlr4-runtime.h"
#include "gen/ngl/nglLexer.h"
#include "gen/ngl/nglParser.h"

#include "gen/ngl/nglBaseListener.h"

#include "argh.h"
#include <Windows.h>

#pragma execution_character_set("utf-8")

using namespace antlr4;

class TreeShapeListener : public ngl::nglBaseListener
{
public:
    void enterNgl_statement(ngl::nglParser::Ngl_statementContext * ctx) override
    {
          std::cout << "\nenterNgl_statement: " << ctx->getText();
    }

    void enterExpression_description(ngl::nglParser::Expression_descriptionContext * ctx) override
    {
          std::cout << "\nenterExpression_description: " << ctx->getText();
          std::cout << "\nsource : " << ctx->identifier_path()->getText();
          std::cout << "\nadd : " << ctx->identifier()->getText();
          for (ngl::nglParser::Identifier_edgeContext* item : ctx->identifier_path()->identifier_edge())
          {
              std::cout << "\nedge : " << item->getText();
          }
    }
};

namespace ngl
{
    void compiler::add_flag(compiler::flags flag)
    {
        flags_ = static_cast<compiler::flags>((uint32_t)flags_ | (uint32_t)flag);
    }

    void compiler::add_param(compiler::params param, std::string value)
    {
        params_.emplace(param, std::move(value));
    }

    void compiler::process()
    {
        std::ifstream file { file_ };
        if (!file)
        {
            std::cerr << "File not found : \"" + file_ + "\"";
            return;
        }
        std::string file_data { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

        ANTLRInputStream input(file_data);
        ngl::nglLexer lexer(&input);
        CommonTokenStream tokens(&lexer);

        ngl::nglParser parser(&tokens);
        tree::ParseTree* tree = parser.root();

        TreeShapeListener listener;
        tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

        std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";

        std::wcout << "\n\nParse Tree: " << s << std::endl; // Unicode output in the console is very limited.

    }

    void compiler::set_file(std::string file)
    {
        file_ = std::move(file);
    }
} // namespace ngl
