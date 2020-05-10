# Compiler

interactive / incremental compilation

code stored in a database 1 bloc / entry
or : group concepts in files using path. ngl/concept/math/matrix ngl::matrix


> source code
    clusters
        code ast, ids graph, source 
> graph -> codegen


source_code -> AST -> program_graph -> program_IR


error types : 
programer error (logical)
program user error (human)

manage input error by program phase
set_index(int i)
set_index(5) // compilation phase, check index range
set_index(runtime_input) // run phase, value come from human input -> 



ngl
    alias
    function
    
ngl:program
    ngl:function
        ngl:instruction:add


SCALAR ELEMENT < > :
SCALAR RANGE A-Z 0-9
SCALAR ELEMENT_VECTOR :: == != struct
SHAPE OR 
[ < ]
[12 34 56]
[s t r u c t]

many<SCALAR>
vector<state>
loop<element>
{
    loop<shapes>
    {
        switch(ELEMENT)
        is ELEMENT_VECTOR
            state = shape_0
        is ELEMENT
            state = shape_1
        is RANGE
            state = shape_2
    }
}



ngl::test zeta0

    
    
ngl::element zeta00 { ngl:int a }

ngl : 0, 3
? : 4, 2
element : 4, 7
\space : skip
zeta00 : 

scalar range letter
scalar range digit
scalar element < > : !=
vector many<letter>
vector many one_of <letter digit>
vector sequence <letter digit>

[index] [range] [element] [seq]
[I] [L D] [_ : ! =] [:: ==] [rule]
 0   1 0   0 0 0 0
 1   1 0   0 0 0 0
 2   0 1   0 0 0 0
 3   0 0   0 0 0 0  1
 4   0 0   0 0 0 0  1
 5   1 0   0 0 0 0
 6   0 0   1 0 0 0
 7   0 0   0 0 1 0
 8   0 0   0 0 0 1

vector bidule one_of<L, D> [4][L, D] [110001]
vector test on_of<=, bidule>


[SAMPLE]
az8::z_ !=
0123456 78

ELEMENT_SCALAR < > : =
RANGE
ELEMENT_VECTOR == ::

// sequence
seqid 0 ::
seqid 1 ::=
1 [00 0100]
2 [00 0100]
3 [00 0001]
seqSH: [00 0101]
seqid 2 :L9
1 [00 0100]
2 [10 0000]
3 [01 0000]
seqSH: [11 0100]


// impl
bitset<64> scalar_results;
is_letter = ('a' <= E && E >= 'z')
scalar_results[letter_index] = is_letter

is_element('_') = E == '_'
scalar_results['_'_index] = is_element

id_digit = ('0' <= E && E >= '9')
scalar_results[digit_index] = is_digit

on first true // stop

bitset<64> rules = (111000); // letter, digit, _
is_identifier = scalar_results | rules

SEQ<L, D>

