%{
/* *************************************************
Filename:   drc.y
Author:     Yan Li
Student#:   100679284
Class:      COMP 5305
************************************************** */

#include "drc.h"
/* Flag if syntax error occures. */
%}

%union {
	char *string;
	//char oracom[MAXSTMTLENGTH];
	SELECTSTMT *selectstmt;
}

%token DROP
%token DESCRIBE

%token AND
%token OR
%token NOT
%token EXISTS
%token FORALL
%token ORDER
%token BY
%token ASSIGN

%token EXIT
%token QUIT

%token SEMICOLON
%token LEFT_PAR
%right RIGHT_PAR
%token LEFT_CURVE
%token RIGHT_CURVE
%token VERTICLE_BAR
%token COMMA


%token <string> CONSTANT
%token <string> VARIABLE
%token <string> ADESC
%left <string> COMPARE
%left <string> OPERATION


%type <selectstmt> query
%type <selectstmt> ending_clause
%type <selectstmt> vars_cons
%type <selectstmt> D_Formula
%type <selectstmt> variables
%type <selectstmt> D_andFormula
%type <selectstmt> D_subFormula
%type <selectstmt> Precon
%type <selectstmt> cond
%type <selectstmt> Procon

%type <selectstmt> end
%type <selectstmt> AGG
%type <selectstmt> OPP

%type <selectstmt> table
%type <selectstmt> newElement
/*

*/
%nonassoc UMINUS
%start statement

%%

statement	:	/*nothing*/
			|	statement DROP VARIABLE SEMICOLON
				{
					fprintf(stdout, "\nstatement:      |   statement DROP VARIABLE SEMICOLON");
					dropTable($3);
					fprintf(yyout, "RQL> ");
				}
			| 	statement VARIABLE SEMICOLON
				{		
					fprintf(stdout, "\nstatement:      |   statement VARIABLE SEMICOLON");
					displayTable($2);
					fprintf(yyout, "RQL> ");
				}
			|	statement DESCRIBE VARIABLE SEMICOLON
				{ 
					fprintf(stdout, "\nstatement:      |   statement DESCRIBE VARIABLE SEMICOLON");
					describeTable($3);
					fprintf(yyout, "RQL> ");
				}
			|	statement query ending_clause 
				{ 
					fprintf(stdout, "\nstatement:      |   statement query ending_clause");
					executeSelectStruct($2, $3);
		        	}
			|	statement table ASSIGN query ending_clause
				{
					fprintf(stdout, "\nstatement:      |   statement table ASSIGN query ending_clause");
					createTable($2, $4, $5);
			};
table		:	VARIABLE
				{
					$$ = tempTable($1, NULL);
				}
			|	VARIABLE LEFT_PAR newElement RIGHT_PAR
				{
					$$ = tempTable($1, $3);
				}
			;
newElement	:	VARIABLE
				{
					$$ = newElements($1, NULL);
				}
			|	VARIABLE COMMA newElement  /* variable, variable , variable */
				{
					$$ = newElements($1, $3);
				}
			;/**/
query       :   LEFT_CURVE variables VERTICLE_BAR D_Formula RIGHT_CURVE /* {variaables | D_Formula } */
				{ 
					$$ = processQuery(NULL, $2, $4); 
				}
			;	/**/
variables   :   VARIABLE
				{
					$$ = variableList($1, NULL, NULL, NULL, NULL);
				}
			|	VARIABLE COMMA variables                           /* variable , variable */
				{
					$$ = variableList($1, NULL, NULL, $3, NULL);
				} 
			|	VARIABLE LEFT_PAR VARIABLE RIGHT_PAR                   /* variable (variable) µ¥ÁÐ±í */
				{
					$$ = variableList($3, $1, NULL, NULL, NULL);
				}	
			|	VARIABLE LEFT_PAR VARIABLE RIGHT_PAR COMMA variables /* variable (variable) , variables */
				{
					$$ = variableList($3, $1, NULL, $6, NULL);
				}
			|	VARIABLE OPERATION VARIABLE                          /* variable operation variable */
				{
					$$ = variableList($1, NULL, $2, NULL, $3);
				}
			|	VARIABLE OPERATION VARIABLE COMMA variables            /* variable operation variable , varianles */
				{
					$$ = variableList($1, NULL, $2, $5, $3);
				};
			|	VARIABLE LEFT_PAR OPERATION RIGHT_PAR                    /* variable (operation) */
				{
					$$ = variableList($3, $1, NULL, NULL, NULL);
				}
			|	VARIABLE LEFT_PAR OPERATION RIGHT_PAR COMMA variables     /* variable (operation) , variables */
				{
					$$ = variableList($3, $1, NULL, NULL, NULL);
				};
				
			|	VARIABLE LEFT_PAR VARIABLE RIGHT_PAR OPERATION VARIABLE LEFT_PAR VARIABLE RIGHT_PAR  /* variable (variable) operation (variable) */
				{
					$$ = doubleVariableList($1, $3, $5, $6, $8);
				}
				/**/
D_Formula		:	D_andFormula
				{ 
					fprintf(stdout, "\nD_Formula : D_andFormula\n");
					$$ = $1; 
				} 			
			|	Precon LEFT_PAR D_andFormula RIGHT_PAR AND D_Formula                
				{
					fprintf(stdout, "\nD_Formula : Precon LEFT_PAR D_andFormula RIGHT_PAR AND D_Formula\n");
					$$ = andConditionTreat($1, $3, $6);
				}
			|	Precon LEFT_PAR D_andFormula RIGHT_PAR OR D_Formula
				{
					fprintf(stdout, "\nD_Formula : Precon LEFT_PAR D_andFormula RIGHT_PAR OR D_Formula\n");
					$$ = orConditionTreat($1, $3, $6);
				} 
				;

D_andFormula	:	D_subFormula                                        /* processSubForm*/
				{ 
					fprintf(stdout, "\nD_andFormula : D_subFormula\n");
					$$ = $1; 
				}
			|	D_subFormula AND D_andFormula                                                       /* subf and andf */
				{ 
					fprintf(stdout, "\nD_andFormula : D_subFormula AND D_andFormula\n");
					$$ = processAndForm($1, $3); 
				}
			|	Precon LEFT_PAR D_andFormula RIGHT_PAR                                                /* precon (andf) */
				{
					fprintf(stdout, "\nD_andFormula : Precon LEFT_PAR D_andFormula RIGHT_PAR\n");
					$$ = conditionTreat($1, $3);
				}
			|	D_subFormula OR D_andFormula                                                                /* subf or andf */
				{
				fprintf(stdout, "\nD_andFormula : D_subFormula OR D_andFormula \n");
					$$ = processOrForm($1, $3); 
				}
			|	D_subFormula AND NOT D_andFormula                                                                /* subf and not andf */
				{
					fprintf(stdout, "\nD_andFormula : D_subFormula AND NOT D_andFormula\n");
					$$ = processAndNotForm($1, $4);
				}
			|	D_subFormula AND NOT LEFT_PAR D_andFormula RIGHT_PAR                                              /* subf and not (andf) */
				{
					fprintf(stdout, "\nD_andFormula : D_subFormula AND NOT LEFT_PAR D_andFormula RIGHT_PAR\n");
					$$ = processAndNotForm($1, $5);
				}
			|	D_subFormula AND LEFT_PAR Procon RIGHT_PAR                                                          /* subf and (procon) */
				{
					fprintf(stdout, "\nD_andFormula : D_subFormula AND LEFT_PAR Procon RIGHT_PAR\n");
					$$ = proCondition($1, $4);
				}
			|	D_subFormula AND Procon
				{
					fprintf(stdout, "\nD_andFormula : D_subFormula AND Procon\n");
					$$ = proCondition($1, $3);
				};
			
D_subFormula	:	VARIABLE LEFT_PAR vars_cons RIGHT_PAR
				{ 
					fprintf(stdout, "\nD_subFormula	: VARIABLE LEFT_PAR vars_cons RIGHT_PAR\n");
					$$ = processSubForm($1, $3); 
				}
        |  NOT VARIABLE LEFT_PAR vars_cons RIGHT_PAR                                        /* processNotSubForm*/
				{ 
					fprintf(stdout, "\nD_andFormula :NOT VARIABLE LEFT_PAR vars_cons RIGHT_PAR\n");
					$$ = processNotSubForm($2, $4); 
				}  
			;	
vars_cons	:	VARIABLE
				{ 
					$$ = varconList($1, NULL, 'V'); 
				}	
			|	VARIABLE COMMA vars_cons
				{ 
					$$ = varconList($1, $3, 'V'); 
				}
			|	CONSTANT
				{ 
					$$ = varconList($1, NULL, 'C'); 
				}
			|	CONSTANT COMMA vars_cons
				{ 
					$$ = varconList($1, $3, 'C'); 
				}
			;/**/			

Precon		:	LEFT_PAR EXISTS cond RIGHT_PAR          /* (exists cond) */
				{
					fprintf(stdout, "\n LEFT_PAR EXISTS cond RIGHT_PAR \n");
					$$ = $3;
				}
			|	LEFT_PAR FORALL cond RIGHT_PAR              /* (forall cond) */
				{
					fprintf(stdout, "\n LEFT_PAR FORALL cond RIGHT_PAR \n");
					$$ = preListForAll($3);
				}
			;
cond		:	VARIABLE      
				{
					fprintf(stdout, "\n VARIABLE \n");
					$$ = preList($1, NULL);
				}
			|	VARIABLE COMMA cond  /* variable , variable , variable */
				{
					fprintf(stdout, "\n VARIABLE COMMA cond \n");
					$$ = preList($1, $3);
				}
			;
Procon		:	VARIABLE COMPARE CONSTANT                                                 /* variable compare constant*/
				{
					fprintf(stdout, "\n VARIABLE COMPARE CONSTANT \n");  
					$$ = proList($1, NULL, NULL, $2, $3, NULL, NULL, 0);
				}
			|	VARIABLE COMPARE CONSTANT OR Procon                                            /* variable compare constant or procon */
				{
					fprintf(stdout, "\n VARIABLE COMPARE CONSTANT OR Procon \n");
					$$ = proList($1, NULL, NULL, $2, $3, NULL, $5, 2);
				}
			|	VARIABLE OPERATION VARIABLE COMPARE CONSTANT                                  /* variable operation variable compare constant */
				{
					fprintf(stdout, "\n VARIABLE OPERATION VARIABLE COMPARE CONSTANT \n");
					$$ = proList($1, $2, $3, $4, $5, NULL, NULL, 0);
				}
      |	VARIABLE COMPARE VARIABLE                                   
				{
					fprintf(stdout, "\n VARIABLE COMPARE VARIABLE  \n");
					$$ = proList($1,NULL, NULL, $2,  $3, NULL, NULL, 0);
				}
			/*
			|	AGG COMPARE CONSTANT
				{
					$$ = proList(NULL, NULL, NULL, $2, $3, $1, NULL);
				}*/
				/* no implement VARIABLE COMPARE CONSTANT AND Procon */
			;				


ending_clause   :   SEMICOLON
                    {
						$$ = processEnding(NULL);
					} ;                      
                |   ORDER BY end SEMICOLON
                    {
						$$ = processEnding($3);
					} 

end			:	VARIABLE
				{
					$$ = orderList($1, NULL, NULL, NULL);
				}
			|	VARIABLE ADESC
				{
					$$ = orderList($1, $2, NULL, NULL);
				}
			|	VARIABLE COMMA end
				{
					$$ = orderList($1, NULL, NULL, $3);
				}
			|	VARIABLE ADESC COMMA end
				{
					$$ = orderList($1, $2, NULL, $4);
				}
			|	AGG
				{
					$$ = orderList(NULL, NULL, NULL, $1);
				}
			|	AGG COMMA end
				{
					$$ = orderList(NULL, NULL, $3, $1);
				}
			|	OPP
				{
					$$ = orderList(NULL, NULL, NULL, $1);
				}
			|	OPP COMMA end
				{
					$$ = orderList(NULL, NULL, $3, $1);
				}
			;
AGG			:	VARIABLE LEFT_PAR VARIABLE RIGHT_PAR
				{
					$$ = stringList($1, NULL, $3, NULL);
				}
			|   VARIABLE LEFT_PAR VARIABLE RIGHT_PAR ADESC
				{
					$$ = stringList($1, NULL, $3, $5);
				}
			;
OPP			:	VARIABLE OPERATION VARIABLE
				{
					$$ = stringList($1, $2, $3, NULL);
				}
			|	VARIABLE OPERATION VARIABLE ADESC
				{
					$$ = stringList($1, $2, $3, $4);
				}
			;
			
%%

char syntaxError = 'N';
int offset;
#include "lex.yy.c"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


/* ----------------------------------------------------------------
Function name: yyerror
Purpose:
To print out an error message whenever a syntax error occurs.
Parameters:
message: the message to be displayed
Returns:
nothing
---------------------------------------------------------------- */
yyerror(char *message)
{
  printf("%d: %s at '%s'\n", yylineno, message, yytext);
  
  if (strcmp(yytext, ";") != 0)
    syntaxError = 'Y';
}

/* -----------------------------------------------
Function name: main
Purpose:       To connect to oracle, start the parser
		and disconnect from oracle when done
------------------------------------------------- */
//extern int yy_flex_debug;

int main()
{

  char   *password;	
  char   user_id[MAXLENGTH];

  system("clear");
  printf("\n%s", "Welcome To Domain Calculus Interface!\n");
  
  printf("\nEnter user-name: ");
  scanf("%s", user_id);
  getchar();
 
password=getpass("Enter password: ");
  //printf("%s,%s",user_id,*password);
  /* Connect to the database. */
  if (oracle_connect(user_id,password) != 0){
     printf("%s\n",user_id);
     printf("%s\n",password);
     exit(1);
  }
  system("clear");
  fprintf(stdout, "\n\t+------------------------------------------------------------+\n");
  fprintf(stdout, "\t|           Domain Calculus Interface to Oracle              |\n");
  fprintf(stdout, "\t|                 Author:     Yan Li                         |\n");
  fprintf(stdout, "\t|               Department of Computer Science               |\n");
  fprintf(stdout, "\t|                   Carleton University                      |\n");
  fprintf(stdout, "\t|                   To exit, type 'exit;'                    |\n");
  fprintf(stdout, "\t|                  mengchi@scs.carleton.ca                   |\n");
  fprintf(stdout, "\t+------------------------------------------------------------+\n\n");
  fprintf(stdout, "RQL> ");
  //yy_flex_debug = 1;
  yyparse();
  oracle_disconnect();
  //fprintf(yyout, "\nThank you for using Domain Relation Calculus interpreter!\n");
  return 0;
}
