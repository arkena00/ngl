grammar ngl;

root : (statement | HSPACE | VSPACE)*;

statement : expression_description /*| expression_specialisation*/;

identifier_descriptor: IDENTIFIER | identifier_path;

identifier_path: IDENTIFIER (identifier_edge IDENTIFIER)+;
identifier_edge: COLON | DOUBLE_COLON;

expression_description : identifier_descriptor IDENTIFIER (';' | description_block);

description_block :
'{'
    (expression_description
    | identifier_descriptor ';'
    )*
'}';


IDENTIFIER: LETTER+ (LETTER | DIGIT)*;

BRACKET_OPEN : '{';
BRACKET_CLOSE : '}';

COLON : ':';
DOUBLE_COLON : '::';
SEMI_COLON : ';';

DIGIT : [0-9];
LETTER : [a-zA-Z];

HSPACE : [ \t]+ -> skip;
VSPACE :  [\r\n]+ -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;
BLOCK_COMMENT : '/*' .*? '*/' -> skip;
