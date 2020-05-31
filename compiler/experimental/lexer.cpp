#include <ngl/lexer.hpp>
#include <ngl/shape_cluster.hpp>

#include <tao/pegtl.hpp>

void store(const std::string& id, const std::string& input, std::vector<ngl::shape>& output)
{
    ngl::shape s;
    s.name = id + "(" + input + ")";
    s.location.origin = 0;
    s.location.size = 10;
    output.emplace_back(std::move(s));
}

namespace
{
    using namespace tao::pegtl;

    //struct identifier : sor<plus<ranges<'a', 'z', '0', '9'>>, plus<one<'_'>>>{};
    struct identifier : seq< one<'_'>, plus<ranges<'a', 'z', '0', '9'>>, one<'_'> > {};
    struct number : ranges<'0', '9'> {};

    struct grammar : plus<sor<identifier, number>>{};

    template<typename Rule>
    struct action{};
/*
    template<>
    struct action<identifier>
    {
        template<typename ParseInput>
        static void apply(const ParseInput& input, std::vector<ngl::shape>& output)
        {
            store("identifier", input.string(), output);
        }
    };

    template<>
    struct action<number>
    {
        template<typename ParseInput>
        static void apply(const ParseInput& input, std::vector<ngl::shape>& output)
        {
            store("number", input.string(), output);
        }
    };*/
}

int main()
{
    try
    {
        std::string data = "1212struct12";

        ngl::shape_cluster shapes;
        /*
        auto letter = shapes.add(ngl::shape_range('a', 'z'));
        auto digit = shapes.add(ngl::shape_range('0', '9'));
        auto underscore = shapes.add(ngl::shape_element('_'));
        auto identifier_symbol = shapes.add(ngl::shape_or(letter, underscore));
        auto many_identifier_symbol = shapes.add(ngl::shape_many(identifier_symbol));
        auto identifier = shapes.add(ngl::shape_sequence(underscore, many_identifier_symbol, underscore));*/

        shapes.add(ngl::shape_element('1'));
        shapes.add(ngl::shape_element('2'));
        shapes.add(ngl::shape_element_vector("struct"));

        ngl::lexer lx{ shapes };

        shapes.display();

        //
        lx.process(data);
        std::cout << "\n\nCPP lexer\n";
        lx.display();

        //
        std::cout << "\nASM lexer\n";
        lx.asm_process();

        //
        std::cout << "\nPEGTL lexer\n";
        std::vector<ngl::shape> output;
        memory_input input{ data, "data" };
        if (!parse<grammar, ::action>(input, output)) std::cout << "err";
        for (const auto& shape : output)
        {
            std::cout << shape.name + " ";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}


/*
string = "ngl_00 "
// identifier = letter (letter | digit | '_')+
// number = sign?
// test = letter, #
1   00001 [az]      scalar letter
2   00010 [09]      scalar digit
4   00100 [_]       scalar _
8   01000 [00111]   id_symbol scalar_or<1 2 4>
16  10000 [[1 8]]  identifier sequence<1, 8>
32        [16]      many<id_symbol> // many<16>

vector_id
0000000001010100
0000000001010100
0000000001010100



 */

/*
auto letter = shapes.add(ngl::shape_range('a', 'z'));
auto digit = shapes.add(ngl::shape_range('0', '9'));
auto underscore = shapes.add(ngl::shape_element('_'));

auto identifier_symbol = shapes.add(ngl::shape_or(letter, underscore));
auto many_identifier_symbol = shapes.add(ngl::shape_many(identifier_symbol));
auto identifier = shapes.add(ngl::shape_sequence(identifier_symbol, many_identifier_symbol));




identifier: (letter | cap_letter) id_symbol* ^[a-zA-Z_][a-zA-Z0-9_\-?']*
operator: ^(\+|\-|\*|/|<=|>=|!=|<|>|@=|@|=|\^)
capture: ^&[a-zA-Z_][a-zA-Z0-9_\-?']*
getfield: ^\.[a-zA-Z_][a-zA-Z0-9_\-?']*
skip: ^[\s]+
comment: # any
shorthand: ^[']
 */




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


    */
