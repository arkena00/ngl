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
    //identifier: ^[a-zA-Z_][a-zA-Z0-9_\-?']*

    struct letter : sor<ranges<'a', 'z'>, ranges<'A', 'Z'>> {};
    struct underscore : one<'_'> {};
    struct dash : one<'-'> {};
    struct qmark : one<'?'> {};
    struct squote : one<'\''> {};
    struct number : ranges<'0', '9'> {};
    struct identifier : seq<letter, plus<sor<underscore, dash, qmark, squote, letter, number>>> {};
    struct space : plus<one<' '>> {};

    struct grammar : plus<sor<identifier, plus<one<' '>>>>{};

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
    };*/
/*
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
        ngl::shape_cluster shapes;
        ngl::shape_cluster parser_shapes;

        auto colon = shapes.add(ngl::shape_element(':'), "element_:");
        auto digit = shapes.add(ngl::shape_range('0', '9'), "range_09");

        shapes.add(ngl::shape_many(colon), "");
        shapes.add(ngl::shape_many(digit), "");

        /*
        auto space = shapes.add(ngl::shape_space(' '));

        auto min_letter = shapes.add(ngl::shape_range('a', 'z'), "range_az");
        auto max_letter = shapes.add(ngl::shape_range('A', 'Z'), "range_AZ");
        auto digit = shapes.add(ngl::shape_range('0', '9'), "range_09");
        auto underscore = shapes.add(ngl::shape_element('_'), "element__");
        auto colon = shapes.add(ngl::shape_element(':'), "element_:");
        auto dot_colon = shapes.add(ngl::shape_element(';'), "element_;");
        auto bracket_open = shapes.add(ngl::shape_element('['), "element_[");
        auto bracket_close = shapes.add(ngl::shape_element(']'), "element_]");
        //auto chevron_open = shapes.add(ngl::shape_element('<'), "element_<");
        //auto chevron_close = shapes.add(ngl::shape_element('>'), "element_>");

        auto letter = shapes.add(ngl::shape_or(min_letter, max_letter), "letter");

        auto letters = shapes.add(ngl::shape_many(letter), "letters");
        //auto digits = shapes.add(ngl::shape_many(digit), "digits");


        //auto path_end = shapes.add(ngl::shape_sequence(colon, letter));
        //auto many_path_end = shapes.add(ngl::shape_many(path_end));

        auto path_identifier = shapes.add(ngl::shape_sequence(letters, colon, digit));
         */

        //std::string data = "aa:0bb:1";
        std::string data = ":::000";

        shapes.display();

        ngl::lexer lx{ shapes };
        //lx.add(parser_shapes);

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
