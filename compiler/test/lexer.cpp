#include <gtest/gtest.h>

#include <ngl/lexer.hpp>

TEST(lexer, static_rule)
{
    //! R1: (LETTER | DIGIT)+
    //! R2: '_'+

    std::string data = "ngl___00_";
    ngl::lexer lx{ data };

    auto sh_letter = lx.add_shape_data(ngl::shape_type::scalar_range, uint64_t('a' << 8u | 'z') );
    auto sh_digit = lx.add_shape_data(ngl::shape_type::scalar_range, uint64_t('0' << 8u | '9'));
    auto sh__ = lx.add_shape_data(ngl::shape_type::scalar_element, '_');
    auto sh_identifier_symbol = lx.add_shape_data(ngl::shape_type::vector_or, sh_letter | sh_digit);
    auto sh_many_identifier_symbol = lx.add_shape_data(ngl::shape_type::vector_many, sh_identifier_symbol);

    auto sh_many_test = lx.add_shape_data(ngl::shape_type::vector_many, sh__);

    lx.process();

    ASSERT_TRUE(lx.shapes().size() == 4);
}