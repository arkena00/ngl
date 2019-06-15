package ngl;

import com.intellij.lexer.FlexLexer;
import com.intellij.psi.tree.IElementType;
import com.intellij.psi.TokenType;
import psi.ngl_types;

%%

%class ngl_lexer
%implements FlexLexer
%unicode
%function advance
%type IElementType
%eof{  return;
%eof}

CRLF=\R
SPACE=[\ \n\t\f ' ']
IDENTIFIER = [a-z]+
NGL = "ngl"
NGC = "ngc"
NGL_AXIOM = ({NGL} | {NGC})
SEMICOLON = ";"
EDGE = ":" | "::"
END_ = ([a-z]* | ':') (";" | "}")

%%

<YYINITIAL> {NGL_AXIOM} {END_}     *                           { yybegin(YYINITIAL); return ngl_types.NGL_AXIOM; }

[^]                                                         { return TokenType.BAD_CHARACTER; }