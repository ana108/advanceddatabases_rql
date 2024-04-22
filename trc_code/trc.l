/* *************************************************
Filename:   trc.l
Author:     Duojie Chang
Student#:   100809247
************************************************** */
%option noyywrap yylineno case-insensitive

%{
	#include <string.h>
	int lineno = 1;	
  	#include "trc.h"

%}

semicolon                    [;][ ]*[\n]
delim                        [ \t]
newlinechar                  [\n]
whitespace                   {delim}*
invalidchar                  [~'@\^{}\[\]:\"\.\?\\\|]
invalidchars                 {invalidchar}+
 
digit                        [0-9]
comment                      (--(.)*\n)
quote_string                 (\'[^']*\')
number                       {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
describe                     ((d|D)(e|E)(s|S)(c|C)(r|R)(i|I)(b|B)(e|E))

var_attribute                [\*]|[A-Za-z][A-Za-z]*{digit}*\.[A-Za-z#\*]*
relationname		    	 ([A-Za-z]([A-Za-z]|{digit}|\$|_|#)*)

%%

"{"                          {offset+=yyleng;return(LEFT_BRACE);}
"}"                          {offset+=yyleng;return(RIGHT_BRACE);}
"("                          {offset+=yyleng;strncpy(yylval.string, yytext, MAXLENGTH);return(LEFT_PAR);}

")"                          {offset+=yyleng;strncpy(yylval.string, yytext, MAXLENGTH);return(RIGHT_PAR);}
"|"                          {offset+=yyleng;return(PIPE);}
"="                          |
"!="                         |
">"                          |
"<"                          |
"<>"                         |
">="                         |
"<="                         {offset+=yyleng;
                              strncpy(yylval.string, yytext, MAXLENGTH);
                              return(RELOP);} 
":="                         {
                               offset+=yyleng;
                               strncpy(yylval.string, yytext, MAXLENGTH);
                               return(ASSIGN);}
"+"                          |
"-"                          |
"*"                          |
"/"                          {
                               offset+=yyleng;
                               strcpy(yylval.string,yytext);
                               return(SIGN);
                             }
"and"                        {
                              offset+=yyleng;
                              strcpy(yylval.string, yytext); 
                              return(AND);
                             }
"as"                        {
                              offset+=yyleng;
                              strcpy(yylval.string, yytext); 
                              return(AS);
                             }

"in"                        {
                              offset+=yyleng;
                              strcpy(yylval.string, yytext); 
                              return(IN);
                             }		  
"or"                         {
                               offset+=yyleng;
                               strcpy(yylval.string, yytext); 
                               return(OR);
                             }
"not"                       {
                               offset+=yyleng;
                               strcpy(yylval.string, yytext); 
                               return(NOT);
                             }
","                          {
                               offset+=yyleng;
                               strncpy(yylval.string, yytext, MAXLENGTH);
                               return(COMMA);
                             }
{whitespace}                 {/*no action and no return*/}
{newlinechar}                { if(offset > 0)
                               {
                                 if( ++lineno > 1)
                                   if (yyin == stdin)
                                     fprintf(yyout, "%4d ", lineno);
                               }
                               else
                               {
                                 lineno = 1;
                                 if (yyin == stdin)
                                   fprintf(yyout, "TRC>");
                               }
                             }
{comment}                    {/*no action and no return*/}
{invalidchars}               {return(INVALID_CHAR);}
{semicolon}                  { if (f_stmterror == 'N')
                                 offset += yyleng;
                               else
                                 f_stmterror == 'N';
                 
                               lineno = 1;
                               return(SEMI_COLON);
                             }
"exists"                     {offset+=yyleng;return(EXISTS);}

"max"                        {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(MAX);
                              }
"min"                      {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(MIN);
                              }
"sum"                        {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(SUM);
                              }
"avg"                       {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(AVG);
                              }
"count"                        {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(COUNT);
                              }
"asc"                       {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(ASC); 
                              }
"desc"                        {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(DESC); 
                              }
"order"                       {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(ORDER); 
                              }
"by"                        {offset+=yyleng;
                              strcpy(yylval.string, yytext);
                              return(BY); 
                              }

{digit}                      {offset+=yyleng;
                              strcpy(yylval.string, yytext);
			      return(DIGIT);}
"forall"                     {offset+=yyleng;return(FORALL);}
"exit" 		             |
"quit"                       {
                               oracle_disconnect();
                               fprintf(yyout, "\nLeaving Tuple Relation Calculus interpreter!\n\n");
                               exit(1);
                             }
"help"                       {offset+=yyleng;return(HELP);}
{number}                     {offset+=yyleng;strncpy(yylval.string, yytext, MAXLENGTH); return(CONSTANT);}
{quote_string}               {offset+=yyleng;strncpy(yylval.string, yytext, MAXLENGTH); return(CONSTANT);}
"insert"                     |
"update"                     |
"delete"                     |
"alter"                      |
"droptable"                  |
"commit"                     |
"rollback"                   |
"createtable"                {
                               offset += yyleng; 
                               strncpy(yylval.oracom, yytext, MAXSTMTLENGTH); 
                               return(ORACOM);
                             }

"describe"     		     {offset += yyleng; return(DESCRIBE);}
{var_attribute}              {offset+=yyleng;strncpy(yylval.string,yytext,MAXLENGTH);return(VAR_ATTRIBUTE);}

{relationname}               {offset+=yyleng;strncpy(yylval.string,yytext,MAXLENGTH);return(RELATIONNAME);}

%%

