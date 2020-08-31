#include "../../lexer.hpp"

class lexer_sequence : public ::testing::Test
{
protected:
    void SetUp() override
    {
        letter = shapes.add_fragment<ngl::shape_range>('a', 'z');
        digit = shapes.add_fragment<ngl::shape_range>('0', '9');
        underscore = shapes.add_fragment('_');
    }
    ngl::shape_cluster shapes;
    ngl::shape_data digit;
    ngl::shape_data letter;
    ngl::shape_data underscore;
};

TEST_F(lexer_sequence, basic)
{
    auto seq = shapes.add_element<ngl::shape_sequence>(letter, underscore, digit);

    ngl::lexer lx{ shapes };
    std::string data{ "n_0" };
    lx.process(data);
    LX_EXPECT("n_0");
}

TEST_F(lexer_sequence, repeat)
{
    auto seq = shapes.add_element<ngl::shape_sequence>(letter, underscore, digit);

    ngl::lexer lx{ shapes };
    std::string data{ "n_0n_0" };
    lx.process(data);
    LX_EXPECT("n_0", "n_0");
}

TEST_F(lexer_sequence, circular)
{
    auto seq = shapes.add_element<ngl::shape_sequence>(letter, underscore, letter);

    ngl::lexer lx{ shapes };
    std::string data{ "n_nn_n" };
    lx.process(data);
    LX_EXPECT("n_n", "n_n");
}