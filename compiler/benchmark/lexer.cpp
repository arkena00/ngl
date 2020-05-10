#include <array>
#include <benchmark/benchmark.h>
#include <ngl/lexer.hpp>

#include "third_party/PEGTL/include/tao/pegtl.hpp"


void store(const std::string& id, const std::string& input, std::vector<ngl::shape>& output)
{
    ngl::shape s;
    s.name = id + "(" + input + ")";
    s.location.origin = 0;
    s.location.size = 10;
    output.emplace_back(std::move(s));
}

namespace
{
    using namespace tao::pegtl;

    struct identifier : sor< plus< ranges<'a', 'z', '0', '9'>>, plus<one<'_'>> > {};

    struct grammar : plus< identifier > {};

   template<typename Rule> struct action {};

   template<>
   struct action<identifier>
   {
       template<typename ParseInput>
       static void apply(const ParseInput& input, std::vector<ngl::shape>& output)
       {
           store("identifier", input.string(), output);
       }
   };
}



auto pegtl_lexer = [](benchmark::State& state, const std::string& data)
{
    int output_size = 0;

    for (auto _ : state)
    {
        std::vector<ngl::shape> output;
        memory_input input{data, "data"};
        parse< grammar, ::action >( input, output );
        output_size = output.size();
    }

    state.counters["code_size"] = data.size();
    state.counters["output_size"] = output_size;
};

auto lexer = [](benchmark::State& state, const std::string& data)
{
    int output_size = 0;

    for (auto _ : state)
    {
        ngl::lexer lx{ data };
        auto sh_letter = lx.add_shape_data(ngl::shape_type::scalar_range, uint64_t('a' << 8u | 'z') );
        auto sh_digit = lx.add_shape_data(ngl::shape_type::scalar_range, uint64_t('0' << 8u | '9'));
        auto sh__ = lx.add_shape_data(ngl::shape_type::scalar_element, '_');
        auto sh_identifier_symbol = lx.add_shape_data(ngl::shape_type::vector_or, sh_letter | sh_digit);
        auto sh_many_identifier_symbol = lx.add_shape_data(ngl::shape_type::vector_many, sh_identifier_symbol);

        auto sh_many_test = lx.add_shape_data(ngl::shape_type::vector_many, sh__);

        lx.process();
        output_size = lx.shapes_.size();
    }
    state.counters["code_size"] = data.size();
    state.counters["output_size"] = output_size;
};

auto lexer2 = [](benchmark::State& state, const std::string& data)
{
    int output_size = 0;

    for (auto _ : state)
    {
        ngl::lexer lx{ data };
        lx.process_v2();
        output_size = lx.shapes_.size();
    }

    state.counters["code_size"] = data.size();
    state.counters["output_size"] = output_size;
};

auto asm_lexer = [](benchmark::State& state, const std::string& data)
{
    int output_size = 0;

    for (auto _ : state)
    {
         ngl::lexer lx{ data };
         lx.asm_process();
        //output_size = lx.shapes_.size();
    }
    state.counters["code_size"] = data.size();
    state.counters["output_size"] = output_size;
};


int main(int argc, char** argv)
{
    //std::string data = "ngl test zeta00 ";
    std::string data = "ngl___00_";
    std::string data2 = [&data]{ std::string str; for(int i = 0; i < 1000000; ++i) { str += data; }; return str; }();


    benchmark::RegisterBenchmark("pegtl_lexer", pegtl_lexer, data)->Unit(benchmark::kMicrosecond);
    benchmark::RegisterBenchmark("pegtl_lexer", pegtl_lexer, data2)->Unit(benchmark::kMicrosecond);
    benchmark::RegisterBenchmark("lexer", lexer, data)->Unit(benchmark::kMicrosecond);
    benchmark::RegisterBenchmark("lexer", lexer, data2)->Unit(benchmark::kMicrosecond);
    //benchmark::RegisterBenchmark("asm_lexer", asm_lexer, data)->Unit(benchmark::kMicrosecond);
    //benchmark::RegisterBenchmark("asm_lexer", asm_lexer, data2)->Unit(benchmark::kMicrosecond);
    //benchmark::RegisterBenchmark("lexer2", lexer2, data)->Unit(benchmark::kMicrosecond);
    //benchmark::RegisterBenchmark("lexer2", lexer2, data2)->Unit(benchmark::kMicrosecond);

    //benchmark::RegisterBenchmark("test_array", test_array, data2)->Unit(benchmark::kMicrosecond);
    //benchmark::RegisterBenchmark("test_singleloop", test_singleloop, data2)->Unit(benchmark::kMicrosecond);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();


/*
    pegtl::memory_input input{data, "data"};
    std::string output;
    if (pegtl::parse< lx::grammar, lx::action >( input, output )) std::cout << "ok";
    else std::cout << "err";
    std::cout << pegtl_output.size();*/


    return 0;
}