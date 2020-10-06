#include "tokens.h"
#define INF 10000

//check for operators
int checkOperator(char *yytext)
{
    if(*yytext=='+')
        return PLUS_TOK;

    if(*yytext=='-')
        return MINUS_TOK;
    
    if(*yytext=='*')
        return MULTIPLY_TOK;

    if(*yytext=='/')
        return DIVIDE_TOK;

    if(*yytext=='%')
        return MODULO_TOK;

    if(*yytext=='!')
        return LNOT_TOK;

    if(*yytext=='&')
        return LAND_TOK;
    
    if(*yytext=='|')
        return LOR_TOK;

    if(*yytext=='^')
        return LXOR_TOK;
    
    return 0;
}

//check for Parenthesis
int checkParen(char *yytext)
{
    if(*yytext=='(')
        return LPAREN_TOK;

    if(*yytext==')')
        return RPAREN_TOK;

    if(*yytext=='{')
        return LCURL_TOK;

    if(*yytext=='}')
        return RCURL_TOK;

    if(*yytext=='[')
        return LSQUARE_TOK;

    if(*yytext==']')
        return RSQUARE_TOK;

    return 0;
}


//check for single ascii characters
int checkSingle(char *yytext)
{
    if(*yytext=='=')
        return EQUAL_TOK;

    if(*yytext==';')
        return SEMICOLON_TOK;

    if(*yytext==',')
        return COMA_TOK;

    if(*yytext==LT_TOK)
        return LT_TOK;

    if(*yytext==GT_TOK)
        return GT_TOK;

    if(*yytext==DOT_TOK)
        return DOT_TOK;

    if(*yytext==NEWLINE_TOK)
        return NEWLINE_TOK;

    return 0;   
}

// check for macro and headers
int checkMacro(char *yytext, FILE *yyin)
{
    char t[9];

    for(int i=0;i<8;i++)
    {
        if(i)
            t[i]=fgetc(yyin);
        else
        {
            t[i]=*yytext;
        }
    }

    if(t[1]=='d' && t[2]=='e' && t[3]=='f' && t[4]=='i' && t[5]=='n' && t[6]=='e' && t[7]==' ')
        return DEFINE_TOK;

    t[8]=fgetc(yyin);
    if(t[1]=='i' && t[2]=='n' && t[3]=='c' && t[4]=='l' && t[5]=='u' && t[6]=='d' && t[7]=='e' && t[8]==' ')
        return INCLUDE_TOK;

    return 0;
}

//checks for keywords
int checkType(char *yytext, FILE *yyin)
{
    
    fpos_t pos;
    char t[7];

    for(int i=0;i<2;i++)
    {
        if(i)
            t[i]=fgetc(yyin);
        else
        {
            t[i]=*yytext;
        }
    }

    if(t[0]=='i' && t[1]=='f')
        return IF_TOK;

    fgetpos(yyin,&pos);
    t[2]=fgetc(yyin);
    if(t[0]=='f' && t[1]=='o' && t[2]=='r' )
        return FOR_TOK;

    fgetpos(yyin,&pos);
    t[3]=fgetc(yyin);
    if(t[0]=='e' && t[1]=='l' && t[2]=='s' && t[3]=='e')
        return ELSE_TOK;

    if(t[0]=='i' && t[1]=='n' && t[2]=='t' && !(t[3]>='a' && t[3]<='z'))
    {
        fsetpos(yyin,&pos);
        return INT_TOK;
    }

    fgetpos(yyin,&pos);
    t[4]=fgetc(yyin);
    if(t[0]=='c' && t[1]=='h' && t[2]=='a' && t[3]=='r' && !(t[4]>='a' && t[4]<='z'))
    {
        fsetpos(yyin,&pos);
        return CHAR_TOK;
    }

    if(t[0]=='l' && t[1]=='o' && t[2]=='n' && t[3]=='g' && !(t[4]>='a' && t[4]<='z'))
    {
        fsetpos(yyin,&pos);
        return LONG_TOK;
    }
    if(t[0]=='w' && t[1]=='h' && t[2]=='i' && t[3]=='l' && t[4]=='e')
        return WHILE_TOK;

    fgetpos(yyin,&pos);
    t[5]=fgetc(yyin);
    if(t[0]=='f' && t[1]=='l' && t[2]=='o' && t[3]=='a' && t[4]=='t' && !(t[5]>='a' && t[5]<='z'))
    {
        fsetpos(yyin,&pos);
        return FLOAT_TOK;
    }

    fgetpos(yyin,&pos);
    t[6]=fgetc(yyin);
    if(t[0]=='d' && t[1]=='o' && t[2]=='u' && t[3]=='b' && t[4]=='l' && t[5]=='e' && !(t[6]>='a' && t[6]<='z'))
    {
        fsetpos(yyin,&pos);
        return DOUBLE_TOK;
    }
    return 0;
}

// check for constant value
int checkConst(char *yytext, FILE *yyin)
{
    // char buff[256];

    if(*yytext=='"')
    {
        char ch=0;
        while(ch!='"' && ch!=EOF)
        {
            ch=fgetc(yyin);
        }

        return STRINGCONST_TOK;
    }

    // 39 is the ASCII value of '
    if(*yytext==39)
    {
        char ch=0;
        while(ch!=39 && ch!=EOF)
        {
            ch=fgetc(yyin);
        }

        return CHARCONST_TOK;
    }

    fpos_t pos;
    
    if(*yytext>='0' && *yytext<='9')
    {
        char ch=*yytext;
        while((ch>='0' && ch<='9') && ch!=EOF)
        {
            fgetpos(yyin,&pos);
            ch=fgetc(yyin);
        }

        fsetpos(yyin, &pos);
        return INTCONST_TOK;
    }

    return 0;
}

//check for comment
int checkComment(char *yytext, FILE *yyin)
{
    fpos_t pos;
    fgetpos(yyin,&pos);

    if(fgetc(yyin)=='/')
    {
        char c=0;
        while(c!='\n' && c!=EOF)
        {
            c=fgetc(yyin);
        }

        return INF;
    }

    fsetpos(yyin,&pos);
    return 0;   
}