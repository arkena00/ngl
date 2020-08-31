#include <array>
#include <benchmark/benchmark.h>
#include <ngl/lexer.hpp>

#include <tao/pegtl.hpp>

namespace ngl_shapes
{
    static ngl::shape_cluster shapes;
    namespace
    {
        /*
        static auto letter = identifier.add(ngl::shape_range('a', 'z'));
        static auto digit = identifier.add(ngl::shape_range('0', '9'));
        static auto underscore = identifier.add(ngl::shape_element('_'));
        static auto identifier_symbol = identifier.add(ngl::shape_or(letter, underscore));
        static auto many_identifier_symbol = identifier.add(ngl::shape_many(identifier_symbol));
        static auto cluster = identifier.add(ngl::shape_sequence(underscore, many_identifier_symbol, underscore));
         */

        auto space = shapes.add(ngl::shape_space(' '));

        auto min_letter = shapes.add(ngl::shape_range('a', 'z'));
        auto max_letter = shapes.add(ngl::shape_range('A', 'Z'));
        auto digit = shapes.add_element<ngl::shape_range>("digit", '0', '9');
        auto underscore = shapes.add(ngl::shape_element('_'));
        auto dash = shapes.add(ngl::shape_element('-'));
        auto qmark = shapes.add(ngl::shape_element('?'));
        auto single_quote = shapes.add(ngl::shape_element('\''));

        auto letter = shapes.add(ngl::shape_or(min_letter, max_letter));


        auto identifier_symbol = shapes.add(ngl::shape_or(letter, digit, underscore, dash, qmark, single_quote));
        auto many_identifier_symbol = shapes.add(ngl::shape_many(identifier_symbol));
        auto identifier = shapes.add(ngl::shape_sequence(letter, many_identifier_symbol));
    }
}


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

    struct letter : sor<ranges<'a', 'z'>, ranges<'A', 'Z'>> {};
    struct underscore : one<'_'> {};
    struct dash : one<'-'> {};
    struct qmark : one<'?'> {};
    struct squote : one<'\''> {};
    struct number : ranges<'0', '9'> {};
    struct identifier : seq<letter, plus<sor<underscore, dash, qmark, squote, letter, number>>> {};
    struct space : plus<one<' '>> {};

    struct grammar : plus<sor<identifier, space>>{};

    template<typename Rule>
    struct action{};

    template<>
    struct action<identifier>
    {
        template<typename ParseInput>
        static void apply(const ParseInput& input, std::vector<ngl::shape>& output)
        {
            store("identifier", input.string(), output);
        }
    };

/*
    template<>
    struct action<number>
    {
        template<typename ParseInput>
        static void apply(const ParseInput& input, std::vector<ngl::shape>& output)
        {
            store("number", input.string(), output);
        }
    };*/
}



auto pegtl_lexer = [](benchmark::State& state, const std::string& data)
{
    int output_size = 0;

    for (auto _ : state)
    {
        std::vector<ngl::shape> output;
        output.reserve(data.size());
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
        ngl::lexer lx{ ngl_shapes::shapes };

        lx.process(data);
        output_size = lx.shapes().size();
    }
    state.counters["code_size"] = data.size();
    state.counters["output_size"] = output_size;
};

auto lexer2 = [](benchmark::State& state, const std::string& data)
{
    int output_size = 0;

    for (auto _ : state)
    {
        ngl::lexer lx{ ngl_shapes::shapes };

        lx.process_v2(data);
        output_size = lx.shapes().size();
    }
    state.counters["code_size"] = data.size();
    state.counters["output_size"] = output_size;
};

auto asm_lexer = [](benchmark::State& state, const std::string& data)
{
    int output_size = 0;

    for (auto _ : state)
    {
         ngl::lexer lx{ ngl_shapes::shapes };
         lx.asm_process();
        //output_size = lx.shapes().size();
    }
    state.counters["code_size"] = data.size();
    state.counters["output_size"] = output_size;
};


int main(int argc, char** argv)
{
    //std::string data = "ngl test zeta00 ";
    std::string data = "ngl-00? zeta_0' ";
    std::string data2 = [&data]{ std::string str; for(int i = 0; i < 100000; ++i) { str += data; }; return str; }();


    benchmark::RegisterBenchmark("pegtl_lexer", pegtl_lexer, data)->Unit(benchmark::kMicrosecond);
    benchmark::RegisterBenchmark("pegtl_lexer", pegtl_lexer, data2)->Unit(benchmark::kMicrosecond);
    benchmark::RegisterBenchmark("lexer", lexer, data)->Unit(benchmark::kMicrosecond);
    benchmark::RegisterBenchmark("lexer", lexer, data2)->Unit(benchmark::kMicrosecond);

    benchmark::RegisterBenchmark("lexer2", lexer2, data)->Unit(benchmark::kMicrosecond);
    benchmark::RegisterBenchmark("lexer2", lexer2, data2)->Unit(benchmark::kMicrosecond);


    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();


    return 0;
}