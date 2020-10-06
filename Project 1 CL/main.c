#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "checks.h"

#define INF 10000
int prev=1;
int yylex(char *yytext, FILE *yyin)
{
    fpos_t position;
    fgetpos(yyin,&position);

    //strip comments
    if(*yytext=='/')
    {
        if(checkComment(yytext,yyin))
        {
            fsetpos(yyin,&position);
            return checkComment(yytext,yyin);
        }
    }

    if(checkOperator(yytext))
        return checkOperator(yytext);

    if(checkParen(yytext))
        return checkParen(yytext);

    if(checkSingle(yytext))
        return checkSingle(yytext);

    //check macro
    if(*yytext=='#')
    {
        if(checkMacro(yytext,yyin))
        {
            fsetpos(yyin,&position);
            return checkMacro(yytext,yyin);
        }
    }

    //check constant values
    if(*yytext=='"' || *yytext==39 || (*yytext>='0' && *yytext<='9' && prev))
    {
        if(checkConst(yytext,yyin))
        {
            fsetpos(yyin,&position);
            return checkConst(yytext,yyin);
        }
    }

    if(checkType(yytext,yyin))
    {
        fsetpos(yyin,&position);
        return checkType(yytext,yyin);
    }


    fsetpos(yyin,&position);
    if(prev)
    {
        prev=0;
        return ID_TOK;
    }
    else
        return 0;  
}

int main(int argc, char *argv[])
{
    FILE *yyin;
    char *yytext;

    if(argc!=2)
    {
        printf("Invalid Input Format.\n");
    }

    else
    {
        
        yyin = fopen(argv[1],"r");

        if(yyin==NULL)
        {
            printf("Couldn't open file.\n");
            return 1;
        }

        while(1)
        {
            /* I am iterating character by character. Checkout "checks.h" for the functions*/
            *yytext=fgetc(yyin);

            if(*yytext==EOF)
                break;

            if(*yytext==' ')
                continue;

            /* This following line generates token. The further lines are just to pretty print*/
            int ch=yylex(yytext,yyin);

            if(ch==INF)
                continue;
            if((char)ch=='\n')
                 printf("NEWLINE_TOK \tASCII / Value: %d\n",ch);
            else if(ch==600)
            {
                printf("ID_TOK \t\tASCII / Value: %d\n",ch);
            }

            else if(ch>=500)
            {
                if(ch==500)
                {
                    printf("INTCONST_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==501)
                {
                    printf("CHARCONST_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==502)
                {
                    printf("STRINGCONST_TOK ASCII / Value: %d\n",ch);
                }
            }

            else if(ch>=400)
            {
                if(ch==400)
                {
                     printf("INT_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==401)
                {
                     printf("FLOAT_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==402)
                {
                     printf("DOUBLE_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==403)
                {
                     printf("LONG_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==404)
                {
                     printf("CHAR_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==IF_TOK)
                {
                     printf("IF_TOK \t\tASCII / Value: %d\n",ch);
                }

                if(ch==ELSE_TOK)
                {
                     printf("ELSE_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==FOR_TOK)
                {
                     printf("FOR_TOK \tASCII / Value: %d\n",ch);
                }

                if(ch==WHILE_TOK)
                {
                     printf("WHILE_TOK \tASCII / Value: %d\n",ch);
                }
            }

            else if(ch>=300)
            {
                if(ch==300)
                {
                     printf("DEFINE_TOK \t\tASCII / Value: %d\n",ch);
                }

                if(ch==301)
                {
                     printf("INCLUDE_TOK \tASCII / Value: %d\n",ch);
                }
            }
            else if(ch)
            {
                printf("%c \t\tASCII / Value: %d\n",(char)ch,ch);
            }

            prev=ch;
            if(prev==ID_TOK)
                prev=0;
       
        }
    }
    
}
