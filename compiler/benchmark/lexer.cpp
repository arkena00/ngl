#include <ngl/lexer.hpp>
#include <benchmark/benchmark.h>

std::string data = "ngl::test zeta00";
std::string data2 = []{ std::string str; for(int i = 0; i < 100000; ++i) { str += data; }; return str; }();

auto lexer = [](benchmark::State& state)
{
    ngl::lexer lx{ data };

    for (auto _ : state)
    {
        lx.process();
    }
};

auto lexer2 = [](benchmark::State& state)
{
    ngl::lexer lx{ data2 };

    for (auto _ : state)
    {
        lx.process();
    }
};

int main(int argc, char** argv)
{
    auto unit = benchmark::kMicrosecond;

    benchmark::RegisterBenchmark("lexer", lexer)->Unit(unit);
    benchmark::RegisterBenchmark("lexer2", lexer2)->Unit(unit);

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    return 0;
}