#include "lexer.hpp"

//! scalar shapes : resolved in a single loop iteration
//! range, element, element_vector, or
//! [az], '_', 'struct', (shape_0 | shape_1)

TEST(lexer, scalar_range)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add(ngl::shape_range('a', 'z'));
    auto digit = shapes.add(ngl::shape_range('0', '9'));
    shapes.add(ngl::shape_or(letter, digit));

    ngl::lexer lx{ shapes };

    lx.process("ngl012");
    LX_EXPECT("n", "g", "l", "0", "1", "2");
}

TEST(lexer, scalar_element)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add(ngl::shape_element('n'));
    auto digit = shapes.add(ngl::shape_element('0'));
    auto underscore = shapes.add(ngl::shape_element('_'));

    ngl::lexer lx{ shapes };

    lx.process("n_0");
    LX_EXPECT("n", "_", "0");
}

TEST(lexer, composite_or)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add(ngl::shape_range('a', 'z'));
    auto digit = shapes.add(ngl::shape_range('0', '9'));
    auto underscore = shapes.add(ngl::shape_element('_'));
    shapes.add(ngl::shape_or(letter, digit));

    ngl::lexer lx{ shapes };

    lx.process("ng0_");
    LX_EXPECT("n", "g", "0", "_");
}


TEST(lexer, vector_many)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add(ngl::shape_range('a', 'z'));
    auto digit = shapes.add(ngl::shape_range('0', '9'));
    auto underscore = shapes.add(ngl::shape_element('_'));
    shapes.add(ngl::shape_many(letter));
    shapes.add(ngl::shape_many(digit));

    ngl::lexer lx{ shapes };

    lx.process("ngl00_");
    LX_EXPECT("ngl", "00", "_");
}

TEST(lexer, vector_sequence)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add(ngl::shape_range('a', 'z'));
    auto digit = shapes.add(ngl::shape_range('0', '9'));
    auto underscore = shapes.add(ngl::shape_element('_'));
    auto identifier_symbol = shapes.add(ngl::shape_or(letter, underscore));
    auto many_identifier_symbol = shapes.add(ngl::shape_many(identifier_symbol));
    auto identifier = shapes.add(ngl::shape_sequence(underscore, many_identifier_symbol, underscore));

    ngl::lexer lx{ shapes };

    lx.process("9_ngl_");
    LX_EXPECT("9", "_ngl_");

    lx.process("_ngl_9");
    LX_EXPECT("_ngl_", "9");

    lx.process("_ngl_");
    LX_EXPECT("_ngl_");
}

TEST(lexer, composite_multishape)
{
    //! multiple shapes true at same time
    ngl::shape_cluster shapes;
    auto underscore = shapes.add(ngl::shape_element('_'));
    auto letter = shapes.add(ngl::shape_range('a', 'z'));
    auto digit = shapes.add(ngl::shape_range('0', '9'));

    auto letter_or_digit = shapes.add(ngl::shape_or(letter, digit));

    shapes.add(ngl::shape_many(digit));
    shapes.add(ngl::shape_many(letter_or_digit));

    ngl::lexer lx{ shapes };

    lx.process("ngl00_00_");
    LX_EXPECT("ngl00", "_", "00", "_");
}