#include "../lexer.hpp"

TEST(lexer_ngl_shape, ngl_identifier)
{
    // identifier
    {
        ngl::lexer lx{ ngl::get_shape_cluster() };
        std::string data { "test_id00 _test2 _id3" };
        lx.process(data);
        LX_EXPECT("test_id00", "_test2", "_id3");
    }
}

TEST(lexer_ngl_shape, ngl_identifier_path)
{
    // identifier
    {/*
        ngl::lexer lx{ ngl::get_shape_cluster() };
        std::string data { "ngl:concept:container" };
        lx.process(data);
        LX_EXPECT("test_id00", "_test2", "_id3");*/
    }
}

TEST(lexer_ngl_shape, ngl_identifier_error)
{
    {
        ngl::lexer lx{ ngl::get_shape_cluster() };
        std::string data { "0test" };
        //EXPECT_ANY_THROW( lx.process(data) );
    }
}
