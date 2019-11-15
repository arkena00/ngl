grammar ngl;

root : LINE* statements;

statements: statement | statements statement;

statement : description (LINE+ | EOF) /*| expression_specialisation*/;

// description
description
    : scalar_description
    | scalar_description_required
    | vector_description
    | post_description
    ;

scalar_description: identifier RAW_IDENTIFIER;
scalar_description_required: required_identifier RAW_IDENTIFIER;

vector_description: identifier RAW_IDENTIFIER
    '{'
        (description
        | required_identifier
        | identifier
        | LINE
        )*
    '}';

post_description: identifier LINE?
    '{'
        (description
        | required_identifier
        | identifier
        | '\n'
        )*
    '}';

// identifier
identifier: RAW_IDENTIFIER | parameterized_identifier | path_identifier;

parameterized_identifier: RAW_IDENTIFIER '<' identifier_parameters '>';
identifier_parameters: identifier | identifier_parameters ',' identifier;

path_identifier:
    (RAW_IDENTIFIER | parameterized_identifier)
    (identifier_edge (RAW_IDENTIFIER | parameterized_identifier))+
    ;

identifier_edge: COLON | DOUBLE_COLON;

required_identifier: '<' identifier '>';

RAW_IDENTIFIER: LETTER+ (LETTER | DIGIT)*;

LESS: '<';
GREATER: '>';


COLON : ':';
DOUBLE_COLON : '::';
SEMI_COLON : ';';

DIGIT : [0-9];
LETTER : [a-zA-Z];

LINE: '\n';
HSPACE : [ \t]+ -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;
BLOCK_COMMENT : '/*' .*? '*/' -> skip;
