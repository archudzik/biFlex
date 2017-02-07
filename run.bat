bison -d Yacc.y
flex Lex.l
gcc -o parser Yacc_tab.c
pause