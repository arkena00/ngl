#include <ngl/compiler.hpp>

#include <ngl/ast/listener.hpp>
#include <ngl/graph.hpp>
#include <ngl/lexer.hpp>
#include <ngl/parser.hpp>

#include <llvm/ADT/APInt.h>

#include <iostream>
#include <fstream>

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

    void compiler::process(std::string file_path)
    {
        file_path_ = std::move(file_path);
        std::ifstream file { file_path_ };
        if (!file)
        {
            std::cerr << "File not found : \"" + file_path_ + "\"";
            return;
        }
        std::string file_data { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

        ngl::lexer lexer{ std::move(file_data) };
        ngl::parser parser{ lexer };

        ngl::graph graph;
        ngl::ast_listener listener{ graph };
        ngl::traverse(parser.ast(), listener);

        std::cout << "\n" << graph;
    }
} // ngl
