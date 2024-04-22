%{
/* ***************************************************************************
Original Filename:   relalg.l
Current Filename:    alg.l
Revision Date:       Not Specified
Author:              Jaret Funk
Student#:            194-6-02491
Course:              CS 470-001
Date:                19 April 1999

Maintenance
//First Set
Maintainer: Haibo Wang
Student#:   Not Specified
Course:     Not Specified
Date:       28 January 2004

//Second Set
Maintainer: Mathieu Leblanc
Student#:   101092676
Course:     COMP4905A
Date:       07 December 2020

Contents:   
  Contains lex lexical anylizer rules for recognizing tokens and the 
  corresponding actions to be caried out when these tokens are recognized 
  and determines what token to return to the parser.

  The first part of the file contains the definitions for tokens.
  The second part of the file contains the rules for operations to be 
  carried out once a token has been encountered.
  The statements in the definitions and rules are self-explanatory.

  lineno keeps track of the number of lines within the user input.
****************************************************************************** */
#include <string.h>

int lineno = 1;
%}

/* INTERNAL ARRAY SIZE DEFINITIONS */
%a 10000
%p 10000
%o 10000
%e 10000
%n 10000
%k 60000

/* REGULAR DEFINITIONS */
update                       ((u|U)(p|P)(d|D)(a|A)(t|T)(e|E)" "([^;])*)
union                        ((u|U)(n|N)(i|I)(o|O)(n|N))
to                           ((t|T)(o|O))
times                        ((t|T)(i|I)(m|M)(e|E)(s|S))
sum                          ((s|S)(u|U)(m|M))
select                       ((s|S)(e|E)(l|L)(e|E)(c|C)(t|T))
rollback                     ((r|R)(o|O)(l|L)(l|L)(b|B)(a|A)(c|C)(k|K)([^;])*)
nrightjoin                   ((n|N)(r|R)(i|I)(g|G)(h|H)(t|T)(j|J)(o|O)(i|I)(n|N))
rightjoin                    ((r|R)(i|I)(g|G)(h|H)(t|T)(j|J)(o|O)(i|I)(n|N))
rename                       ((r|R)(e|E)(n|N)(a|A)(m|M)(e|E))
quit                         ((q|Q)(u|U)(i|I)(t|T))
project                      ((p|P)(r|R)(o|O)(j|J)(e|E)(c|C)(t|T))
product                      ((p|P)(r|R)(o|O)(d|D)(u|U)(c|C)(t|T))
order                        ((o|O)(r|R)(d|D)(e|E)(r|R))
or                           ((o|O)(r|R))
minus                        ((m|M)(i|I)(n|N)(u|U)(s|S))
min                          ((m|M)(i|I)(n|N))
max                          ((m|M)(a|A)(x|X))
nleftjoin                    ((n|N)(l|L)(e|E)(f|F)(t|T)(j|J)(o|O)(i|I)(n|N))
leftjoin                     ((l|L)(e|E)(f|F)(t|T)(j|J)(o|O)(i|I)(n|N))
njoin                        ((n|N)(j|J)(o|O)(i|I)(n|N))
equijoin                     ((e|E)(q|Q)(u|U)(i|I)(j|J)(o|O)(i|I)(n|N))
join                         ((j|J)(o|O)(i|I)(n|N))
intersect                    ((i|I)(n|N)(t|T)(e|E)(r|R)(s|S)(e|E)(c|C)(t|T))
insert                       ((i|I)(n|N)(s|S)(e|E)(r|R)(t|T)" "(i|I)(n|N)(t|T)(o|O)" "([^;])*)	
help                         ((h|H)(e|E)(l|L)(p|P))
nfulljoin                    ((n|N)(f|F)(u|U)(l|L)(l|L)(j|J)(o|O)(i|I)(n|N))
fulljoin                     ((f|F)(u|U)(l|L)(l|L)(j|J)(o|O)(i|I)(n|N))
exit                         ((e|E)(x|X)(i|I)(t|T))
droptable	                   ((d|D)(r|R)(o|O)(p|P)" "(t|T)(a|A)(b|B)(l|L)(e|E)" "([^;])*)
divideby                     ((d|D)(i|I)(v|V)(i|I)(d|D)(e|E)(b|B)(y|Y))
difference                   ((d|D)(i|I)(f|F)(f|F)(e|E)(r|R)(e|E)(n|N)(c|C)(e|E))
describe                     ((d|D)(e|E)(s|S)(c|C)(r|R)(i|I)(b|B)(e|E))
desc                         ((d|D)(e|E)(s|S)(c|C))
delete                       ((d|D)(e|E)(l|L)(e|E)(t|T)(e|E)" "(f|F)(r|R)(o|O)(m|M)" "([^;])*)
debug                        ((d|D)(e|E)(b|B)(u|U)(g|G))
createtable                  ((c|C)(r|R)(e|E)(a|A)(t|T)(e|E)" "(t|T)(a|A)(b|B)(l|L)(e|E)" "([^;])*)
count                        ((c|C)(o|O)(u|U)(n|N)(t|T))
commit                       ((c|C)(o|O)(m|M)(m|M)(i|I)(t|T)([^;])*)
by                           ((b|B)(y|Y))
avg                          ((a|A)(v|V)(g|G))
asc                          ((a|A)(s|S)(c|C))
as                           ((a|A)(s|S))
and                          ((a|A)(n|N)(d|D))
alter                        ((a|A)(l|L)(t|T)(e|E)(r|R)" "(t|T)(a|A)(b|B)(l|L)(e|E)" "([^;])*)
aggregate                    ((a|A)(g|G)(g|G)(r|R)(e|E)(g|G)(a|A)(t|T)(e|E))

comment                      (--(.)*\n)
delim                        [ \t]
digit                        [0-9]
invalidchar                  [~`!@\^&*{}\[\]:\"\.\?\/\\\|\+\-]
invalidchars                 {invalidchar}+
newlinechar                  [\n]
number                       {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
quote_string                 (\'([^'])*\')
semicolon                    ([;][ ]*[\n]|[;])
variable                     ([A-Za-z]([A-Za-z]|{digit}|\$|_|#)*)
whitespace                   {delim}*
%%

{to} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(TO);
}

{alter}       |
{createtable} |
{commit}      |
{delete}      |
{droptable}   |
{insert}      |
{rollback}    |
{update}      {
  offset += yyleng; 
	strncpy(yylval.oracom, yytext, MAXSTMTLENGTH); 
	return(ORACOM);
}

{difference} |
{divideby}   |
{fulljoin}   |
{nfulljoin}  |
{njoin}      |
{leftjoin}   |
{nleftjoin}  |
{product}    |
{nrightjoin} |
{rightjoin}  |
{minus}      |
{intersect}  |
{times}      |
{union}      {
  offset += yyleng; 
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(BINARYOP);
}

{avg}   |
{count} |
{min}   |
{max}   |
{sum}   {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(SYMBOL);
}

{select} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(SELECT);
}

{rename} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(RENAME);
}

{exit} |
{quit} {
  oracle_disconnect();
  fprintf(yyout, "\nLeaving relational algebra interpreter.\n");
  exit(1);
}

{project} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(PROJECT);
}

{order} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(ORDER);
}

{or} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(OR);
}

{equijoin} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(EQUIJOIN);
}

{join} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(JOIN);
}

{help} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(HELP);
}

{describe} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(DESCRIBE);
}

{desc} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(DESC);
}

{debug} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH); 
  return(DEBUG);
}

{by} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(BY);
}

{asc} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH); 
  return(ASC);
}

{as} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(AS);
} 

{and} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(AND);
}

{aggregate} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(AGGREGATE);
}

":=" {
  offset += yyleng; 
  strncpy(yylval.string, yytext, MAXLENGTH); 
  return(ASSIGN);
}
"," {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(COMMA);
}
"(" {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(LEFT_PAR);
}
")" {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(RIGHT_PAR);
}
"<>" |
"<=" |
"<"  |
"!="  |
"="  |
">=" |
">"  {
  offset += yyleng; 
  strncpy(yylval.string, yytext, MAXLENGTH); 
  return(RELOP);
}

{comment} {}

{invalidchars} {
  offset += yyleng;
  strncpy(yylval.string, yytext, MAXLENGTH); 
  return(INVALID_CHAR);
}

{newlinechar} {
  if(offset > 0)
  {
    if(++lineno > 1)
    {
      if (yyin == stdin)
      {
        fprintf(yyout, "%4d", lineno);
      }
    }
  }
  else
  {
    lineno = 1;
    if (yyin == stdin)
    {
      fprintf(yyout, "ALG> ");
    }
  }
}

{number} {
  offset += yyleng; 
	strncpy(yylval.string, yytext, MAXLENGTH); 
	return(CONSTANT);
}

{quote_string} {
  offset += yyleng; 
	strncpy(yylval.string, yytext, MAXLENGTH);
	return(CONSTANT);
}

{semicolon} {
  if (f_stmterror == 'N')
  {
    offset += yyleng;
  }
  else
  {
    f_stmterror = 'N';
  }
  lineno = 1;
  strncpy(yylval.string, yytext, MAXLENGTH);
  return(SEMI_COLON); 
}

{variable} {
  offset += yyleng;
  strncpy(yylval.string,yytext,MAXLENGTH);
  return(VARIABLE);
}

{whitespace} {}
%%
