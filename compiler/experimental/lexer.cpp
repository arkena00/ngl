#include <ngl/lexer.hpp>

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

    struct identifier : sor< plus< ranges<'a', 'z', '0', '9'>>, plus<one<'_'>> > {};

    struct grammar : plus< identifier > {};

   template<typename Rule> struct action {};

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
    std::string data = "ngl___00_";
    ngl::lexer lx{ data };

    auto sh_letter = lx.add_shape_data(ngl::shape_type::scalar_range, uint64_t('a' << 8u | 'z') );
    auto sh_digit = lx.add_shape_data(ngl::shape_type::scalar_range, uint64_t('0' << 8u | '9'));
    auto sh__ = lx.add_shape_data(ngl::shape_type::scalar_element, '_');
    auto sh_identifier_symbol = lx.add_shape_data(ngl::shape_type::vector_or, sh_letter | sh_digit);
    auto sh_many_identifier_symbol = lx.add_shape_data(ngl::shape_type::vector_many, sh_identifier_symbol);

    auto sh_many_test = lx.add_shape_data(ngl::shape_type::vector_many, sh__);



    lx.process();
    std::cout << "CPP lexer\n";
    lx.display();

    std::cout << "\nASM lexer\n";
    lx.asm_process();

    std::cout << "\nPEGTL lexer\n";
    std::vector<ngl::shape> output;
    memory_input input{data, "data"};
    if (!parse< grammar, ::action >( input, output )) std::cout << "err";
    for (const auto& shape : output)
    {
        std::cout << ngl::lexer::to_string(shape);
    }

    return 0;
}


/*
string = "n#gl_00 "
// identifier = letter (letter | digit | '_')+
// test = letter, #
1   00001 [az]      scalar letter
2   00010 [09]      scalar digit
4   00100 [_]       scalar _
8   01000 [00111]   id_symbol scalar_or<1 2 4>
16  10000 [[1 32]]  identifier sequence<1, 32>
32        [16]      many<id_symbol> // many<16>

shape[1] = true
shape[2] = false
shape[8] = true
shape[16] = shape[8]
shape[32] = shape[16]

many<or< letter
many<or< digit
11001
11010
 */