#include <gtest/gtest.h>
#include <ngl/lexer.hpp>

#define LX_EXPECT(...) EXPECT_TRUE(test_tokens(lx, __VA_ARGS__))

template<std::size_t... Is, class... Ts>
::testing::AssertionResult has_tokens(const ngl::lexer& lx, std::index_sequence<Is...>, Ts&&... ts)
{
    bool match_size = lx.shapes().size() == sizeof...(ts);
    if (!match_size) return ::testing::AssertionFailure() << "input size : " << lx.shapes().size() << " expected size : " << sizeof...(ts) << "\nOutput: " << lx.to_string();

    bool match_tokens = ((lx.shape_view(Is) == ts) && ...);
    if (match_tokens) return ::testing::AssertionSuccess();
    else
    {
        return ::testing::AssertionFailure() << "tokens : " << lx.to_string();
    }
}

template<class... Ts>
auto test_tokens(const ngl::lexer& lx, Ts&&... ts)
{
    return has_tokens(lx, std::make_index_sequence<sizeof...(Ts)>{}, std::forward<Ts>(ts)...);
}