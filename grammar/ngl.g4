grammar ngl;

root
    : LINE* statements
    ;

statements
    : statement
    | statements statement
    ;

statement
    : description (LINE+ | EOF) /*| expression_specialisation*/
    ;

// description
description
    : scalar_description
    | scalar_description_required
    | vector_description
    | post_description
    ;

scalar_description
    : identifier RAW_IDENTIFIER
    ;
scalar_description_required
    : required_identifier RAW_IDENTIFIER
    ;

vector_description
    : identifier RAW_IDENTIFIER LINE?
    '{'
        (description
        | required_identifier
        | identifier
        | LINE
        )*
    '}'
    ;

post_description
    : identifier LINE?
    '{'
        (description
        | required_identifier
        | identifier
        | LINE
        )*
    '}'
    ;

// identifier
identifier
    : RAW_IDENTIFIER
    | parameterized_identifier
    | path_identifier
    ;

scalar_identifier
    : RAW_IDENTIFIER
    | parameterized_identifier
    ;

parameterized_identifier
    : RAW_IDENTIFIER '<' identifier (',' identifier)* '>'
    ;

path_identifier:
    scalar_identifier (identifier_edge scalar_identifier)+
    ;

identifier_edge
    : COLON
    | DOUBLE_COLON
    ;

required_identifier
    : '<' identifier '>'
    ;

BRACKET_OPEN: '{';
BRACKET_CLOSE: '}';

LINE: '\n';


COLON: ':';
DOUBLE_COLON: '::';
SEMI_COLON: ';';

fragment DIGIT: [0-9];
fragment LETTER: [a-zA-Z];

RAW_IDENTIFIER: LETTER (LETTER | DIGIT)*;

HSPACE: [ \t]+ -> skip;
LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
