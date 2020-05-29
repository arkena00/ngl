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
    struct number : plus<ranges<'0', '9'>> {};

    struct grammar : plus<sor<identifier, number>>{};

    template<typename Rule>
    struct action{};

    template<>
    struct action<identifier>
    {
        template<typename ParseInput>
        static void apply(const ParseInput& input, std::vector<ngl::shape>& output)
        {
            store("identifier", input.string(), output);
        }
    };
}

int main()
{
    try
    {
        std::string data = "9_ng_0_ng_9";

        ngl::shape_cluster shapes;
        auto letter = shapes.add(ngl::shape_range('a', 'z'));
        auto digit = shapes.add(ngl::shape_range('0', '9'));
        auto underscore = shapes.add(ngl::shape_element('_'));
        auto identifier_symbol = shapes.add(ngl::shape_or(letter, underscore));
        auto many_identifier_symbol = shapes.add(ngl::shape_many(identifier_symbol));
        auto identifier = shapes.add(ngl::shape_sequence(underscore, many_identifier_symbol, underscore));

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
letter: az
cap_letter: AZ

underscore: _
dbl_quote: "
plus: +
minus: -
dot: .

id_symbol: letter | cap_letter | underscore


string: dbl_quote ( !dbl_quote ) dbl_quote
number:  (plus | minus)? digit+ (dot digit+)?

operator: ^(\+|\-|\*|/|<=|>=|!=|<|>|@=|@|=|\^)

identifier: (letter | cap_letter) id_symbol* ^[a-zA-Z_][a-zA-Z0-9_\-?']*
capture: ^&[a-zA-Z_][a-zA-Z0-9_\-?']*
getfield: ^\.[a-zA-Z_][a-zA-Z0-9_\-?']*
skip: ^[\s]+
comment: # any
shorthand: ^[']
 */




/*
    state 0100
    seq<_ ng _> 0
    E  _ I: 0 C: 0 R: 1
    E  n I: 0 C: 1 R: 0        0 & 1 -> I++
    ML n I: 1 C: 0 R: 1
    ML g I: 1 C: 1 R: 1
    ML _ I: 1 C: 2 R: 0        0 & 1 -> I++
    E  _ I: 2 C: 0 R: 1
    E  0 I: 2 C: 1 R: 0        0 & 1 -> end

    Size S
    False F
    True T
    Index I

    I = I + (((TF & 1u) ^ 1u) & ((TF & 2u) >> 1)) % S;


    */

    /*
    _  000001
    L  000010
    D  000100
    ML 001000
    S  010000
    S  100000

    S<_, ML, D>
    S<_ D>
    // _  a b 0 1
    _  010001
    a  011000
    b  011000
    0  010100
    1  000100

    scalar   000111
    vector   001000
    sequence 010000


    //auto sh_many_test = lx.add_shape_data("NAME", ngl::shape_type::vector_many, sh__);
*/