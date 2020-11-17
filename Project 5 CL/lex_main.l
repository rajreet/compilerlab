%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "tokens.h"
#include "yacc_main.tab.h"

extern int yylineno;
%}

%%

;                                {return(SEMICOLON_TOK);}
,                                {return (COMA_TOK);}
=                                {return (EQUAL_TOK);}
[>]                                {return (GT_TOK);}
[<]                                {return (LT_TOK);}
[.]                               {return (DOT_TOK);}
\+                                {return (PLUS_TOK);}
-                                {return (MINUS_TOK);}
\*                                {return (MULTIPLY_TOK);}
[/]                                {return (DIVIDE_TOK);}
%                                {return (MODULO_TOK);}
!                                {return (LNOT_TOK);}
[|]                                {return (LOR_TOK);}
&                                {return (LAND_TOK);}

\{                               {return(LCURL_TOK);}
\}                               {return(RCURL_TOK);}
\(				                 {return(LPAREN_TOK);}
\)				                 {return(RPAREN_TOK);}
\]				                 {return(RSQUARE_TOK);}
\[			                     {return(LSQUARE_TOK);}

"<="                               {return (LTEQ_TOK);}
">="                               {return (GTEQ_TOK);}
"!="                               {return (NOTEQ_TOK);}
"+="                               {return (PLUSEQ_TOK);}
"-="                               {return (MINEQ_TOK);}
"*="                               {return (MULEQ_TOK);}
"/="                               {return (DIVEQ_TOK);}
"++"                               {return (INCR_TOK);}
"--"                               {return (DECR_TOK);}
"=="                                {return (EQEQ_TOK);}

int                              {return(INT_TOK);}
float                            {return(FLOAT_TOK);}
double                            {return(DOUBLE_TOK);}
long                            {return(LONG_TOK);}
char                            {return(CHAR_TOK);}

if                              {return(IF_TOK);}
else                            {return(ELSE_TOK);}
for                            {return(FOR_TOK);}
while                            {return(WHILE_TOK);}

main                             {return(MAIN_TOK);}
"return"                            {return (RETURN_TOK);}
#include                         {return (INCLUDE_TOK);}
([a-z]|[A-Z])([a-z]|[A-Z]|[0-9])* { yylval.string=strdup(yytext); return (ID_TOK);}

([0-9])+                         {return (INTCONST_TOK);}
([0-9])+(".")([0-9])+               {return (FLOATCONST_TOK);}

\"([^"])+\"                               {return (STRINGCONST_TOK);}
'(.)'                                   {return (CHARCONST_TOK);}

(["/"])(["/"])([^\n])*                         {/* Do Nothing for comment*/}
[ \t\n]+                         {/* Do Nothing for newline*/}
%%

int yywrap(void)
{
   return 1;
}

// int main(int argc,char *argv[])
// {
//     extern FILE *yyin;
//     yyin=fopen("sample.c","r");
//     int val;
//     while((val = yylex()) > 0)
//     {
//         if(val!=DELIM_TOK)
//             printf("Token : %s \t\t Token ID : %d\n", yytext, val);
        
//     }
    
//     fclose(yyin);
// }


 
