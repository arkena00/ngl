#include <ngl/compiler.hpp>

#include <fstream>
#include <iostream>

#include <ngl/cluster.hpp>
#include <ngl/lang.hpp>

#include <spdlog/spdlog.h>
#include <ngl/log.hpp>

namespace ngl
{
    compiler::compiler()
         : flags_{}
         , concretizer_{ std::make_unique<ngl::llvm_concretizer>() }
    {
        spdlog::set_level(spdlog::level::info);
    }

    void compiler::init()
    {
        if (!has_flag(flags::nongl)) process("ngl.ngl");

        concretizer_ = std::make_unique<ngl::llvm_concretizer>();
    }

    void compiler::add_flag(compiler::flags flag)
    {
        flags_.set(static_cast<unsigned int>(flag));
    }

    void compiler::set_flags(unsigned int flags)
    {
        flags_ = flags;

        if (has_flag(flags::trace)) spdlog::set_level(spdlog::level::trace);
    }

    bool compiler::has_flag(compiler::flags flag)
    {
        return flags_.test(static_cast<unsigned int>(flag));
    }

    void compiler::add_param(compiler::params param, std::string value)
    {
        params_.emplace(param, std::move(value));
    }

    void compiler::process(std::string file_path)
    {
        using namespace std::string_literals;
        ngl_trace("compiler process {}", file_path);

        file_path_ = std::move(file_path);
        std::ifstream file { file_path_ };
        if (!file)
        {
            std::cerr << "File not found : \"" + file_path_ + "\"\n";
            return;
        }

        std::string file_data { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

        try
        {
            ngl::cluster cluster{ file_path_, std::move(file_data) };
            cluster.process();
            concretizer_->process(cluster);

            // post flags
            if (has_flag(flags::graph))
            {
                std::cout << "\n\nGraph\n";
                nds::encoders::dot<>::encode<nds::console>(cluster.graph());
            }
        }
        catch(...) { ngl_error("parser error"); }
    }
} // ngl