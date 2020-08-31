#include "lexer.hpp"

//! scalar shapes : resolved in a single loop iteration
//! range, element, element_vector, or
//! [az], '_', 'struct', (shape_0 | shape_1)

TEST(lexer, scalar_range)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add_element<ngl::shape_range>('a', 'z');
    auto digit = shapes.add_element<ngl::shape_range>('0', '9');
    //shapes.add(ngl::shape_or(letter, digit));

    ngl::lexer lx{ shapes };

    std::string data { "ngl012" };
    lx.process(data);
    LX_EXPECT("n", "g", "l", "0", "1", "2");
}

TEST(lexer, scalar_element)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add_element('n');
    auto digit = shapes.add_element('0');
    auto underscore = shapes.add_element('_');

    ngl::lexer lx{ shapes };

    std::string data { "n_0" };
    lx.process(data);
    LX_EXPECT("n", "_", "0");
}

TEST(lexer, composite_or)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add_element<ngl::shape_range>('a', 'z');
    auto digit = shapes.add_element<ngl::shape_range>('0', '9');
    auto underscore = shapes.add_element('_');
    shapes.add_element<ngl::shape_or>(letter, digit);

    ngl::lexer lx{ shapes };

    std::string data { "ng0_" };
    lx.process(data);
    LX_EXPECT("n", "g", "0", "_");
}


TEST(lexer, vector_many)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add_element<ngl::shape_range>('a', 'z');
    auto digit = shapes.add_element<ngl::shape_range>('0', '9');
    auto underscore = shapes.add_element('_');
    shapes.add_element<ngl::shape_many>(letter);
    shapes.add_element<ngl::shape_many>(digit);

    ngl::lexer lx{ shapes };

    std::string data { "ngl00_" };
    lx.process(data);
    LX_EXPECT("ngl", "00", "_");
}





TEST(lexer, composite_multishape)
{
    //! multiple shapes true at same time
    ngl::shape_cluster shapes;
    auto underscore = shapes.add_element('_');
    auto letter = shapes.add<ngl::shape_range>("letter", 'a', 'z');
    auto digit = shapes.add_element<ngl::shape_range>("digit", '0', '9');

    auto letter_or_digit = shapes.add_element<ngl::shape_or>(letter, digit);

    shapes.add_element<ngl::shape_many>(digit);
    shapes.add_element<ngl::shape_many>(letter_or_digit);

    ngl::lexer lx{ shapes };

    std::string data { "ngl00_00_" };
    lx.process(data);
    LX_EXPECT("ngl00", "_", "00", "_");
}