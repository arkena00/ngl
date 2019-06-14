
#include <iostream>

#include "antlr4-runtime.h"
#include "gen/ngl/nglLexer.h"
#include "gen/ngl/nglParser.h"

#include "gen/ngl/nglBaseListener.h"

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
    }

        void enterIdentifier_edge(ngl::nglParser::Identifier_edgeContext * ctx) override
    {
          std::cout << "\nenterIdentifier_edge: " << ctx->getText();
    }

       void enterIdentifier(ngl::nglParser::IdentifierContext * ctx) override
       {
            std::cout << "\nenterIdentifier: " << ctx->getText();
       }

       void enterIdentifier_path(ngl::nglParser::Identifier_pathContext * ctx) override
       {
            std::cout << "\nenterIdentifier_path: " << ctx->getText();
       }

};

int main(int argc, const char * argv[]) {

  ANTLRInputStream input(" ngl:concept     domain; "
                         "ngl::domain math; "
                         "  ");
  ngl::nglLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  ngl::nglParser parser(&tokens);
  tree::ParseTree *tree = parser.root();

  TreeShapeListener listener;
  tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";


  std::wcout << "\n\nParse Tree: " << s << std::endl; //Unicode output in the console is very limited.

  return 0;
}