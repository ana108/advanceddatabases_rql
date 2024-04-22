%option noyywrap case-insensitive
%{
/* *************************************************
Filename:   drc.l
Author:     Yan Li
Student#:   100679284
Class:      COMP 5305
************************************************** */
#include <string.h>
//#include "drc.tab.h"
int lineno = 1;
%}



letter		[A-Za-z]		
digit		[0-9]
variable	({letter}({letter}|{digit}|\$|_|#)*)|_

semicolon   [;][ ]*[\n]
delim		[ \t]
verticlebar	[\|]
whitespace	{delim}+

invalidchar 	[~`@\^&\[\]:\"\.\?\\]
invalidchars	{invalidchar}+

quote_string	(\'([^'(;\n)])*\')
number		{digit}+(\.{digit}+)?(E[+\-]?{digit}+)?


%%

DESCRIBE {return DESCRIBE;}
DROP	{return DROP;}
AND {return AND;}
OR {return OR;}
NOT {return NOT;}
EXISTS {return EXISTS;}
FORALL {return FORALL;}
ORDER {return ORDER;}
BY {return BY;}


{whitespace}	{}
{semicolon}		{return SEMICOLON;}
"("		{return LEFT_PAR;}
")"		{return RIGHT_PAR;}
"{"		{return LEFT_CURVE;}
"}"		{return RIGHT_CURVE;}
","		{return COMMA;}
{verticlebar}	{return VERTICLE_BAR;}



ASC		|
DESC	{ 
			yylval.string = strdup(yytext);
			return ADESC;
		}

EXIT	|
QUIT	{
            oracle_disconnect();
            fprintf(yyout, "\nThank you for using Domain Relation Calculus interpreter!\n");
			exit(1);
        }

":="	{
			return ASSIGN;
		}
		
"<"		|
"!="  |
"<="	|
"="		|
"<>"	|
">"		|
">="	{
	        yylval.string = strdup(yytext);
			return COMPARE;
		}
		
"+"  	| 
"-"     |       
"*"  	|        
"/"     {
			yylval.string = strdup(yytext);
            return OPERATION;       /*关系运算符 operation 逻辑运算符 compare*/
		}
		
[\n]	{
			if (yyin == stdin)
			{
				fprintf(yyout, "RQL> ");
			}
		}

{variable} {
				yylval.string = strdup(yytext);
				return VARIABLE;
			}

{number}	{
				yylval.string = strdup(yytext);
				return CONSTANT;
			}
{quote_string}	{
					yylval.string = strdup(yytext);
					return CONSTANT;
				}
%%