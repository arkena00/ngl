grammar ngl;

root : file EOF;

file : (statement | HSPACE | VSPACE)*;

statement : expression_description;

identifier_path: IDENTIFIER (identifier_edge IDENTIFIER)+;
identifier_edge: COLON | DOUBLE_COLON;

expression_description : identifier_path HSPACE IDENTIFIER SEMI_COLON;


IDENTIFIER: LETTER+ (LETTER | DIGIT)*;


COLON : ':';
DOUBLE_COLON : '::';
SEMI_COLON : ';';

DIGIT : [0-9];
LETTER : [a-zA-Z];

HSPACE : [ \t]+;
VSPACE :  [\r\n]+ -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;
