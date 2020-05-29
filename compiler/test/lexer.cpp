#include "lexer.hpp"

//! scalar shapes : resolved in a single loop iteration
//! range, element, element_vector, or
//! [az], '_', 'struct', (shape_0 | shape_1)

TEST(lexer, scalar_range)
{
    LX_TEST("abz089");

    LX_SHAPE(letter, ngl::shape_range('a', 'z')); // ngl::shape_or(R1, R2, R3)
    LX_SHAPE(digit, ngl::shape_range('0', '9'));

    LX_EXPECT("a", "b", "z", "0", "8", "9");
}

TEST(lexer, scalar_element)
{
    LX_TEST("z_0");

    LX_SHAPE(letter, ngl::shape_element('z'));
    LX_SHAPE(underscore, ngl::shape_element('_'));
    LX_SHAPE(digit, ngl::shape_range('0', '9'));

    LX_EXPECT("z", "_", "0");
}

TEST(lexer, scalar_or)
{
    LX_TEST("a_z00");

    LX_SHAPE(letter, ngl::shape_range('a', 'z'));
    LX_SHAPE(underscore, ngl::shape_element('_'));
    LX_SHAPE(digit, ngl::shape_range('0', '9'));
    LX_SHAPE(or_LU, ngl::shape_or(letter, digit));

    LX_EXPECT("a_z", "00");
}


TEST(lexer, vector_many)
{
    //! S1: LETTER+
    //! S2: DIGIT+
    LX_TEST("abcd0123");

    LX_SHAPE(letter, ngl::shape_range('a', 'z'));
    LX_SHAPE(digit, ngl::shape_range('0', '9'));
    LX_SHAPE(many_letter, ngl::shape_many(letter));
    LX_SHAPE(many_digit, ngl::shape_many(digit));

    auto sh_letter = lx.add_shape_data(ngl::shape_range('a', 'z'));
    auto sh_digit = lx.add_shape_data(ngl::shape_range('0', '9'));
    auto sh__ = lx.add_shape_data(ngl::shape_type::scalar_element, '_');
    auto sh_identifier_symbol = lx.add_shape_data(ngl::shape_type::scalar_or, sh_letter | sh_digit);
    auto sh_many_identifier_symbol = lx.add_shape_data(ngl::shape_type::vector_many, sh_identifier_symbol);

    auto sh_many_test = lx.add_shape_data(ngl::shape_type::vector_many, sh__);

    lx.process();

    ASSERT_TRUE(lx.shapes().size() == 4);

    ASSERT_TRUE(lx.shape_view(0) == "ngl");
    ASSERT_TRUE(lx.shape_view(1) == "___");
    ASSERT_TRUE(lx.shape_view(2) == "00");
    ASSERT_TRUE(lx.shape_view(3) == "_");

}