%{

#include"lex.yy.c"

void yyerror(char *);
int scope=0;
extern int yylineno;

typedef struct Symbol{
        char* name;
        int scope;
        int dtype; // 0 for int, 1 for float, 2 for char

} Symbol;

typedef struct SymbolNode{
        Symbol node;
        struct SymbolNode *next;

}SymbolNode;

SymbolNode *head = NULL;

void addToTable(Symbol snode);
void showSymbol(Symbol s);
void createSymbol(char *sname, int sdtype);
void showTable();
int checkSymbol(char *sname);

void showSymbol(Symbol s)
{
        printf("Name: %s\nScope: %d\nDatatype: %d\n\n",s.name,s.scope,s.dtype);
}

void createSymbol(char *sname, int sdtype)
{
        Symbol *st = (Symbol *)malloc(sizeof(Symbol));
        
        st->name=sname;
        st->dtype=sdtype;
        st->scope=scope;

        addToTable(*st);
        // showSymbol(*st);
}

void addToTable(Symbol snode)
{
        SymbolNode *ptr=head;

        if(ptr==NULL)
        {
                ptr=(SymbolNode*)malloc(sizeof(SymbolNode));
                ptr->node=snode;
                ptr->next=NULL;
                head=ptr; 
        }

        else
        {
                while(ptr->next!=NULL)
                {
                        ptr=ptr->next;
                }

                ptr->next=(SymbolNode*)malloc(sizeof(SymbolNode));
                ptr=ptr->next;
                ptr->node=snode;
                ptr->next=NULL;
        }
}

void showTable()
{
        SymbolNode *ptr=head;

        if(ptr==NULL)
                printf("Symbol Table Empty.\n");
        else
                printf("\nSYMBOL TABLE:\n");

        while(ptr!=NULL)
        {
                showSymbol(ptr->node);
                ptr=ptr->next;
        }
}

int checkSymbol(char *sname)
{
        SymbolNode *ptr=head;

        while(ptr!=NULL)
        {
                if(!strcmp(ptr->node.name,sname))
                {
                        if(ptr->node.scope<=scope)
                                return 1;
                        else 
                                return 0;

                        break;
                }

                ptr=ptr->next;
        }

        return 0;
}

%}
%token LPAREN_TOK
%token RPAREN_TOK 
%token LCURL_TOK 
%token RCURL_TOK 
%token LSQUARE_TOK 
%token RSQUARE_TOK 

%token PLUS_TOK 
%token MINUS_TOK 
%token MULTIPLY_TOK 
%token DIVIDE_TOK 
%token MODULO_TOK 
%token LNOT_TOK 
%token LAND_TOK 
%token LOR_TOK 
%token LXOR_TOK  

%token SEMICOLON_TOK 
%token EQUAL_TOK 
%token COMA_TOK 
%token GT_TOK 
%token LT_TOK 
%token DOT_TOK 
%token NEWLINE_TOK 
%token GTEQ_TOK        
%token LTEQ_TOK        
%token NOTEQ_TOK        
%token PLUSEQ_TOK       
%token MINEQ_TOK        
%token MULEQ_TOK        
%token DIVEQ_TOK        
%token INCR_TOK        
%token DECR_TOK
%token EQEQ_TOK 

%token DEFINE_TOK 
%token INCLUDE_TOK 

%token INT_TOK 
%token FLOAT_TOK 
%token DOUBLE_TOK 
%token LONG_TOK 
%token CHAR_TOK 

%token IF_TOK 
%token ELSE_TOK 
%token FOR_TOK 
%token WHILE_TOK 

%token INTCONST_TOK 
%token CHARCONST_TOK 
%token STRINGCONST_TOK 
%token FLOATCONST_TOK 

%token ID_TOK 
%token MAIN_TOK
%token RETURN_TOK 
%token DELIM_TOK 

%start S

%union{
        char* string;
        int dtype;
}

%type<string> id_token ID_TOK
%type<dtype> datatype INT_TOK FLOAT_TOK DOUBLE_TOK CHAR_TOK LONG_TOK;

%%
S    : headers  userfunc datatype  MAIN_TOK LPAREN_TOK RPAREN_TOK BLOCK      {printf("Syntax for Main Function is Ok....\n"); showTable();}
     ;

headers: headers INCLUDE_TOK LT_TOK ID_TOK DOT_TOK ID_TOK GT_TOK
        | INCLUDE_TOK LT_TOK ID_TOK DOT_TOK ID_TOK GT_TOK   {printf("Syntax for include is Ok....\n");}
        ;

BLOCK: LCURL_TOK { scope++; printf("Scope: %d\n",scope);}  STATEMENTS  BLOCKS  RCURL_TOK { scope--; printf("Scope: %d\n",scope);}
     ;

BLOCKS: BLOCK STATEMENTS BLOCKS                                {}
      |
      ;

STATEMENTS:STATEMENTS  stmt
          | 
          ;

stmt:     DECLARATION SEMICOLON_TOK
        | ID_TOK { if(!checkSymbol($1)) {yyerror("Used Variable either not declared or not in scope"); return 1;}} startop value operation SEMICOLON_TOK {printf("Non- declaration statement correct.....\n"); }
        | forloop {printf("forloop syntax correct.....detected at %d\n",yylineno);}
        | if_tok  {printf("If block detected at %d\n",yylineno);} 
        | else_tok {printf("Else block detected at %d\n",yylineno);}
        | FUNCTION SEMICOLON_TOK     
          ;


DECLARATION:datatype id_token {printf("Syntax of The Declaration Statement is Correct.....\n"); createSymbol($2,$1);}
           ;

datatype:INT_TOK {$$ = 0;}
        | FLOAT_TOK {$$ = 1;}
        | CHAR_TOK {$$ = 2;}
        | DOUBLE_TOK {$$ = 3;}
        | LONG_TOK {$$ = 4;}
        ;

id_token: id_token COMA_TOK ID_TOK 
        | ID_TOK EQUAL_TOK value     {}
        | ID_TOK                     {}
        ;

constant: INTCONST_TOK 
        | FLOATCONST_TOK 
        | CHARCONST_TOK 
        | STRINGCONST_TOK
        ;

operation: operation operator value
        | operator value
        ;

operator:  PLUS_TOK | MINUS_TOK | DIVIDE_TOK | MULTIPLY_TOK | MODULO_TOK;

comp: GT_TOK | LT_TOK | GTEQ_TOK | LTEQ_TOK | NOTEQ_TOK | EQEQ_TOK;

value: ID_TOK{ if(!checkSymbol($1)) {yyerror("Used Variable either not declared or not in scope"); return 1;}} | constant | LPAREN_TOK datatype RPAREN_TOK ID_TOK{ if(!checkSymbol($4)) {yyerror("Used Variable either not declared or not in scope"); return 1;}} | FUNCTION;

startop: EQUAL_TOK | PLUSEQ_TOK | MINEQ_TOK | MULEQ_TOK | DIVEQ_TOK ;

forloop: FOR_TOK LPAREN_TOK DECLARATION SEMICOLON_TOK compstatement SEMICOLON_TOK forinc RPAREN_TOK BLOCK;

compstatement: ID_TOK comp value;

forinc: ID_TOK startop value | ID_TOK inc;

inc: INCR_TOK | DECR_TOK;

if_tok: IF_TOK LPAREN_TOK compstatement RPAREN_TOK stmt | IF_TOK LPAREN_TOK compstatement RPAREN_TOK BLOCK;

else_tok: ELSE_TOK stmt | ELSE_TOK BLOCK;

args:   args COMA_TOK value
        | value;

FUNCTION: ID_TOK LPAREN_TOK args RPAREN_TOK {printf("Function Call detected at %d\n",yylineno);} 
        ;

userfunc: datatype ID_TOK LPAREN_TOK userargs RPAREN_TOK FUNCBLOCK {printf("User defined function detected at %d\n",yylineno);}

FUNCBLOCK: LCURL_TOK  STATEMENTS  BLOCKS  returnstmt RCURL_TOK;

returnstmt: RETURN_TOK value operation SEMICOLON_TOK;

userargs: userargs COMA_TOK datatype ID_TOK {createSymbol($4,$3);}| datatype ID_TOK {createSymbol($2,$1);} 

%%

int main()
{
        extern FILE *yyin;
        yyin=fopen("sample.c","r");
        if(yyparse()==0) 
                printf("Parsed Successfully\n");
        else 
                printf("\nParsing Error at Line No %d\n", yylineno);


        fclose(yyin);
        return 0;	

}

void yyerror(char *s)
{
	printf("yyerror: %s\n",s);
}
