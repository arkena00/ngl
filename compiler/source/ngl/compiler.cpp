#include <ngl/compiler.hpp>

#include <fstream>
#include <iostream>

#include <ngl/cluster.hpp>
#include <ngl/lang.hpp>

namespace ngl
{
    compiler::compiler()
    {
        ngl::lang::identifier ngl{ "ngl" };
        ngl::lang::identifier alias{ "alias" };
        ngl::lang::identifier concept{ "concept" };

        process("ngl.ngl");
    }

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
        using namespace std::string_literals;

        file_path_ = std::move(file_path);
        std::ifstream file { file_path_ };
        if (!file)
        {
            std::cerr << "File not found : \"" + file_path_ + "\"";
            return;
        }

        std::string file_data { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

        ngl::cluster cluster{ std::move(file_data) };
    }
} // ngl