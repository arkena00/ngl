grammar ngl;

root : ngl_file EOF ;

ngl_file : (ngl_statement | HSPACE | VSPACE)* ;



identifier: LETTER+ (LETTER | DIGIT)* ;
identifier_edge: ':' | '::' ;
identifier_path: identifier (identifier_edge identifier)+ ;

ngl_statement : expression_description ;

expression_description : identifier_path HSPACE identifier SEMI_COLON ;



HSPACE : [ \t]+ ;
VSPACE :  [\r\n]+  ;
// SPACE : (' ' | '\r\n' | '\n')+ ;
DIGIT :  [0-9] ;
LETTER : [a-zA-Z] ;

SEMI_COLON : ';' ;
