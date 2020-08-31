#include "../../lexer.hpp"

class lexer_sequence_vector : public ::testing::Test
{
protected:
    void SetUp() override
    {
        letter = shapes.add_fragment<ngl::shape_range>('a', 'z');
        digit = shapes.add_element<ngl::shape_range>('0', '9');
        underscore = shapes.add_fragment('_');
        letters = shapes.add_fragment<ngl::shape_many>(letter);
    }
    ngl::shape_cluster shapes;
    ngl::shape_data digit;
    ngl::shape_data letter;
    ngl::shape_data letters;
    ngl::shape_data underscore;
};

TEST_F(lexer_sequence_vector, basic)
{
    auto seq = shapes.add_element<ngl::shape_sequence>(underscore, letters, underscore);

    {
        ngl::lexer lx{ shapes };
        std::string data{ "_ngl_" };
        lx.process(data);
        LX_EXPECT("_ngl_");
    }

    {
        ngl::lexer lx{ shapes };
        std::string data{ "9_ngl_" };
        lx.process(data);
        LX_EXPECT("9", "_ngl_");
    }

    {
        ngl::lexer lx{ shapes };
        std::string data{ "_ngl_9" };
        lx.process(data);
        LX_EXPECT("_ngl_", "9");
    }
}

TEST_F(lexer_sequence_vector, repeat)
{
    auto seq = shapes.add_element<ngl::shape_sequence>(underscore, letters);
    {
        ngl::lexer lx{ shapes };
        std::string data { "_ngl_ngl" };
        lx.process(data);
        LX_EXPECT("_ngl", "_ngl");
    }
}
TEST_F(lexer_sequence_vector, circular)
{
    auto seq = shapes.add_element<ngl::shape_sequence>(underscore, letters, underscore);
    {
        ngl::lexer lx{ shapes };
        std::string data { "_ngl__ngl_" };
        lx.process(data);
        LX_EXPECT("_ngl_", "_ngl_");
    }
}