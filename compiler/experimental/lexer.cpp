#include <ngl/lexer.hpp>
#include <ngl/shape_cluster.hpp>

/*
// sequence loop
(A B C) (A B C)
ex:
ngl (: zeta) (: test)


// partial sequence
sequence : (A B C)
matching (A B Z) : no match, reset the sequence

// nested sequence
test<zeta<test>>

// recursive rules
id : raw_id | param_id
scalar_id : raw_id | param_id
param_id : raw_id < id >

 */

int main()
{
    try
    {
        ngl::shape_cluster cpp;
        {
            auto letter = cpp.add(ngl::shape_range('a', 'z'));
            auto letters = cpp.add(ngl::shape_many(letter));
            auto S = cpp.add(ngl::shape_element('s'));
            auto T = cpp.add(ngl::shape_element('t'));
            auto R = cpp.add(ngl::shape_element('r'));
            auto U = cpp.add(ngl::shape_element('u'));
            auto C = cpp.add(ngl::shape_element('c'));
            cpp.add(ngl::shape_sequence(S, T, R, U, C, T));
        }

        ngl::shape_cluster seq;
        ngl::shape_cluster shapes;
        auto letter = shapes.add(ngl::shape_range('a', 'z'));
        auto digit = shapes.add_element<ngl::shape_range>("digit", '0', '9');
        auto underscore = shapes.add(ngl::shape_element('_'));
        auto underscores = shapes.add(ngl::shape_many(underscore));

        auto letters = shapes.add(ngl::shape_many(letter));
        auto digits = shapes.add(ngl::shape_many(digit));

        auto A = seq.add(ngl::shape_element('a'));
        auto B = seq.add(ngl::shape_element('b'));
        auto C = seq.add(ngl::shape_element('c'));
        auto zero = seq.add(ngl::shape_element('0'));
        auto us = seq.add(ngl::shape_element('_'));

        auto abc = seq.add(ngl::shape_sequence(A, B, C));
        seq.add(ngl::shape_sequence(zero, abc, zero));

        ngl::lexer lx{ seq };
        seq.display();

        std::string data = "0abc0_";

        /*
        seq< "abcd", "0">

        <a, b, c, d>
        101000
        100100
        100010
        0000001
        abc0

        (abcd) a b c 0

        0 001000
        0 000100
        0 000010
        0 000001
        1 0000001
        abcd*/


        lx.process(data);


        std::cout << "\n\nCPP lexer\n";
        std::cout << lx.to_string();

        //
        std::cout << "\nASM lexer\n";
        lx.asm_process();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}

/*
    I: index
    IM: index_match
    NM: next IM
    LI: last index
    LS: last shape
    VID: vector id

    # seq<_ ng _>
    _ I: 0 IM: 1 PM: 0 NM: 0 M: 1
        n I: 0 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 1 IM = 1 M = 1
    n I: 1 IM: 1 PM: 1 NM: 0 M: 1
    g I: 1 IM: 1 PM: 1 NM: 0 M: 1
        _ I: 1 IM: 0 PM: 1 NM: 1 M: 0 -> if !IM && PM -> I = 2 IM = 1 M = 1
    _ I: 2 IM: 1 PM: 1 NM: 0 M: 1

    #end1 I == LI && is_scalar<LS>               -> I = 0 VID = ~VID
    #end2 I == LI && !is_scalar<LS> && NM == 0   -> I = 0 VID = ~VID


    Size S
    False F
    True T
    Index I

    I = I + (((TF & 1u) ^ 1u) & ((TF & 2u) >> 1)) % S;




G (100)

ngl
    add_shape (101)
00
    add_shape (101)

NGL
    add_shape (110)
00
    add_shape (110)

100 : desc = ngl::description
001 : sd = ngl::scalar_description

101 : sd = ngl::scalar_description
        .add(ngl)
        .add(00)
desc.add(sc)

110 : vd = ngl::vector_description
        .add(ngl)
        .add(00)
desc.add(sc)
 ...


   desc
   /  \
  SC  VD
/  \  /  \
ID  ID ID ID

*/
