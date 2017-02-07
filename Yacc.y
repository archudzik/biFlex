/*
 HTML Parser by Artur@Chudzik.net.pl
 License: GPL
 Based on: xtree-c | XML Parser using Lex/Yacc 
 Source: https://code.google.com/p/xtree-c/
*/

%{
#include <stdio.h>
#include "lex.yy.c"
%}

%token START_TAG END_EMPTY_TAG END_TAG
%token ATTRIBUTE COMMENT CDATA REFERENCE XML_DECL PROC_INSTR
%token SYNTAX_ERROR

%%

document:
        prolog element misc
        ;

prolog:
        XML_DECL misc
        | misc
        ;

misc:
        COMMENT
        | PROC_INSTR
        |
        ;

element:
        START_TAG attList elementRemainder
        ;

attList:
        attList ATTRIBUTE
        | ATTRIBUTE
        | /* empty */
        ;

elementRemainder:
        END_EMPTY_TAG
        | '>' contentList END_TAG
        ;

content:
        element
        | COMMENT
        | CDATA
        | REFERENCE
        | PROC_INSTR
        ;

contentList:
        contentList content
        | content
        |
        ;
    

%%

main(int argc, char **argv) {
 htmlStackInit();
 yyparse(); 
 htmlStackFinish();
}

int yywrap(void) {
  return 1;
}

int yyerror(char *s) {
   setParseError(1);
   //printf("line %d: %s at %s\n", yylineno, s, yytext); 
}


