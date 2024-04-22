/* *************************************************
Filename:   trc.l
Author:     Duojie Chang
Student#:   100809247
************************************************** */

%{
  #include "trc.h"
%}

%union {
         char       string[MAXSTMTLENGTH];
         char       oracom[MAXSTMTLENGTH];
         SELECTSTMT *selectstmt;
       }

%token LEFT_BRACE
%token RIGHT_BRACE
%token PIPE
%token INVALID_CHAR
%token SEMI_COLON
%token HELP
%token NUMBER
%token FORALL
%token EXISTS
%token ASSIGN
%token ORTABLE 
%token DESCRIBE
%token ORDER
%token BY
%token IN
%token AS
%token <string> ASC
%token <string> DESC
%token <string> SIGN
%token <string> AND
%token <string> OR
%token <string> NOT
%token <string> RELATIONNAME
%token <string> VAR_ATTRIBUTE
%token <string> LEFT_PAR
%token <string> RIGHT_PAR
%token <string> RELOP
%token <string> COMMA
%token <string> DIGIT
%token <string> CONSTANT
%token <oracom> ORACOM
%type <selectstmt> Formula
//%type <selectstmt> And_Formula
//%type <selectstmt> Or_Formula
%type <selectstmt> Sub_Formula

%type <string> Aggregate
%token <string> MAX
%token <string> MIN
%token <string> SUM
%token <string> AVG
%token <string> COUNT

%type <selectstmt> expression
%type <selectstmt> Vars_Attrs

%type <selectstmt> Operand
%type <selectstmt> Equation
%type <selectstmt> Orders
%type <selectstmt> Condition
%type <selectstmt> Quantified_Form
%type <selectstmt> Quantifier
%type <selectstmt> existsVariables
%type <selectstmt> Order_by
%type <selectstmt> variables

%expect 3
%nonassoc UMINUS
%start query

%%
query	:	/*empty*/

		|	LEFT_BRACE expression RIGHT_BRACE SEMI_COLON 
			{ 
				//fprintf(stdout, "\nquery:            LEFT_BRACE expression RIGHT_BRACE SEMI_COLON \n"); 
				executesqlstmt(0, 0, 0);
				if (quantifier_error_flag == 1)
				{
					quantifier_error_flag = 0;
					fprintf(stdout, "\nTRC>");
				}
				exist_flag_count = 0;
        exist_flag=0;
				quantifier_error_flag = 0;
				quantifier_error_display_flag = 0;
				freevar_error_flag = 0;
				layers = 0;
				table_error_flag =0;
				not_exist_flag = 0;
				mult_exist_var_flag = 0;
			}
			query
		|	LEFT_BRACE expression RIGHT_BRACE Order_by SEMI_COLON
			{   
				//fprintf(stdout, "\nquery: | LEFT_BRACE expression RIGHT_BRACE Order_by SEMI_COLON\n");
				combine($4);
				executesqlstmt(0,0,0);
				if (quantifier_error_flag == 1)
				{
					quantifier_error_flag = 0;
				}
				exist_flag_count = 0;
                exist_flag=0;
				quantifier_error_flag = 0;
				quantifier_error_display_flag = 0;
				freevar_error_flag = 0;
				layers = 0;
				table_error_flag =0;
				not_exist_flag = 0;
				mult_exist_var_flag = 0;
			} 
			query
		|   ORACOM SEMI_COLON
			{
				//fprintf(stdout, "\nquery: | ORACOM SEMI_COLON\n");
				exeoracle($1);
			}
			query
		|   DESCRIBE RELATIONNAME SEMI_COLON
			{
				//fprintf(stdout, "\nquery: | ORACOM SEMI_COLON\n");
				describeTable($2);
			} 
			query
		|   DESC RELATIONNAME SEMI_COLON
			{
				//fprintf(stdout, "\nquery: | DESC RELATIONNAME SEMI_COLON\n");
				describeTable($2);
			} 
			query
		|   SEMI_COLON 					
			{
				//fprintf(stdout, "\nquery: | SEMI_COLON\n");
			}
			query
			
		|   HELP SEMI_COLON 
			{
        fprintf(stdout, "\n\nEnter a SQL statement or a PL/SQL block at the SQL> prompt.");
        fprintf(stdout, "Statements can be continued over several lines, except");
        fprintf(stdout, "within string literals.");
        fprintf(stdout, "Terminate a SQL statement with a semicolon.");
        fprintf(stdout, "Terminate a PL/SQL block (which can contain embedded semicolons)");
        fprintf(stdout, "with a slash (/).");
        fprintf(stdout, "Typing \"exit;\" or \"quit;\"  exits the program.");
        fprintf(stdout, "You typed \"?\" or \"help\" to get this message.\n\n");
			}
			query
		|   error SEMI_COLON
			{ 
				//fprintf(stdout, "\nquery: | error SEMI_COLON\n");
				yyerrok;
			}
			query
				
		|   RELATIONNAME SEMI_COLON
			{
				//fprintf(stdout, "\nquery: |RELATIONNAME SEMI_COLON\n");
				displayTable($1);
			}
			query
		|   RELATIONNAME ASSIGN temptable SEMI_COLON
			{
				//fprintf(stdout, "\nquery: |RELATIONNAME ASSIGN temptable SEMI_COLON\n");
				assignQuery($1);
				if (quantifier_error_flag == 1)
				{
					quantifier_error_flag = 0;
				}
				exist_flag_count = 0;
				quantifier_error_flag = 0;
				quantifier_error_display_flag = 0;
                exist_flag=0;
				freevar_error_flag = 0;
				layers = 0;
				table_error_flag =0;
				not_exist_flag = 0;
				mult_exist_var_flag = 0;
			}
			query
		|   RELATIONNAME LEFT_PAR variables RIGHT_PAR ASSIGN temptable SEMI_COLON
				{
                    //fprintf(stdout, "\nquery: |RELATIONNAME LEFT_PAR variables RIGHT_PAR ASSIGN temptable SEMI_COLON\n");
					renameattribute($1, $3);
					if (quantifier_error_flag == 1)
					{
						quantifier_error_flag = 0;
					}

					exist_flag_count = 0;
					quantifier_error_flag = 0;
					quantifier_error_display_flag = 0;
     exist_flag=0;
					freevar_error_flag = 0;
					layers = 0;
					table_error_flag =0;
					not_exist_flag = 0;
					mult_exist_var_flag = 0;
				} 
				query			
		;
variables	:   RELATIONNAME
				{
					//fprintf(stdout, "\nquery: | RELATIONNAME\n");
					$$=(SELECTSTMT*) addVarAttrs($1, NULL, NULL); 
				} 
			| 	RELATIONNAME COMMA variables
				{
					//fprintf(stdout, "\nquery: | RELATIONNAME COMMA variables\n");
					$$=(SELECTSTMT*) addVarAttrs($1, NULL, $3); 
			    }
		   ;
temptable	:   LEFT_BRACE expression RIGHT_BRACE
				{
				   //fprintf(stdout, "\nquery: | LEFT_BRACE expression RIGHT_BRACE\n");
				}
			|	LEFT_BRACE expression RIGHT_BRACE Order_by 
				{ 
					//fprintf(stdout, "\nquery: | LEFT_BRACE expression RIGHT_BRACE Order_by \n");
					combine($4);
				}
			;

Order_by	:	ORDER BY Orders
			{
				//fprintf(stdout, "\nOrder_by : ORDER BY Orders\n");
				$$ = $3; 
			};

Orders	:	VAR_ATTRIBUTE
			{
				//fprintf(stdout, "\nquery: | VAR_ATTRIBUTE\n");
				$$ =(SELECTSTMT*)addOrder($1,NULL,NULL,NULL);
			}
		|	Equation
			{
				 //fprintf(stdout, "\nquery: | Equation\n");
				 $$ = (SELECTSTMT*)addEqOrder($1,NULL,NULL);
			}
		|	Equation ASC
			{
				//fprintf(stdout, "\nquery: | Equation ASC\n");			  
			  $$ = (SELECTSTMT*)addEqOrder($1, $2, NULL);
			}
		|	Equation DESC
			{
				//fprintf(stdout, "\nquery: | Equation DESC\n");
				$$ = (SELECTSTMT*)addEqOrder($1, $2, NULL);
			}
	     
		|	Equation Orders
			{
				$$ = (SELECTSTMT*)addEqOrder($1, NULL, $2);
			}
			
		|	Equation ASC Orders
			{
				//fprintf(stdout, "\nquery: | Equation ASC Orders\n");
				$$ =(SELECTSTMT*)addEqOrder($1, $2, $3);
			}
		| 	Equation DESC Orders
			{
				//fprintf(stdout, "\nquery: | Equation DESC Orders\n");
				$$ =(SELECTSTMT*)addEqOrder($1, $2, $3);
			}
		|	VAR_ATTRIBUTE DESC
			{
				//fprintf(stdout, "\nquery: | VAR_ATTRIBUTE DESC\n");
				$$ =(SELECTSTMT*)addOrder($1,$2, NULL,NULL);
			}
		|	VAR_ATTRIBUTE COMMA Orders
			{
				//fprintf(stdout, "\nquery: | VAR_ATTRIBUTE COMMA Orders\n");
				$$=(SELECTSTMT*)addOrder($1,NULL,$3,NULL);
			}
		|	VAR_ATTRIBUTE ASC COMMA Orders
			{
				//fprintf(stdout, "\nquery: | VAR_ATTRIBUTE ASC COMMA Orders\n");
				$$=(SELECTSTMT*)addOrder($1, $2,$4,NULL);
			}
		|	VAR_ATTRIBUTE DESC COMMA Orders
			{
				//fprintf(stdout, "\nquery: | VAR_ATTRIBUTE DESC COMMA Orders\n");
				$$=(SELECTSTMT*)addOrder($1,$2,$4,NULL);
			}
		;
Equation	:   Operand SIGN Operand
				{
					//fprintf(stdout, "\nquery: | Operand SIGN Operand\n");
					$$=(SELECTSTMT*)addEquation($1,$2,$3,0);
				}
			|	Equation SIGN Operand
				{
					//fprintf(stdout, "\nquery: | Equation SIGN Operand\n");
					$$=(SELECTSTMT*)addEquation($1, $2,$3, 0);
				}
			|	Operand SIGN Equation
				{
					//fprintf(stdout, "\nquery: | Operand SIGN Equation\n");
					$$=(SELECTSTMT*)addEquation($1, $2, $3, 0);
				}
			|	LEFT_PAR Equation RIGHT_PAR SIGN Operand
				{
					//fprintf(stdout, "\nquery: | LEFT_PAR Equation RIGHT_PAR SIGN Operand\n");
					$$=(SELECTSTMT*)addEquation($2, $4, $5, 1);
				}
			|	Operand SIGN LEFT_PAR Equation RIGHT_PAR
				{
					//fprintf(stdout, "\nquery: | Operand SIGN LEFT_PAR Equation RIGHT_PAR\n");
					$$=(SELECTSTMT*)addEquation($1, $2, $4, 2);
				}
			;
	
expression	:   Vars_Attrs PIPE Formula
				{ 
					//fprintf(stdout, "\nquery: | Vars_Attrs PIPE Formula\n");
					buildexpression($1, $3);
				}			
			;

Formula    	:   Sub_Formula
					{ 
						//fprintf(stdout, "\nFormula:      Sub_Formula  \n");
						$$=$1;
					}
			|	Sub_Formula AND Formula
					{ 
						//fprintf(stdout, "\nFormula:      | Sub_Formula AND Formula\n");
						$$=(SELECTSTMT*) addAndFormula($1, $2, $3);
					}
			|	Sub_Formula OR Formula
					{
						//fprintf(stdout, "\nFormula    :     | Sub_Formula OR Formula \n");
						$$=(SELECTSTMT*) addOrFormula($1, $2, $3);
					}
			;

/*And_Formula :   Sub_Formula
					{ 
						//fprintf(stdout, "\nAnd_Formula:      Sub_Formula  \n");
						$$=$1;
					}
			|	Sub_Formula AND And_Formula
					{ 
						//fprintf(stdout, "\nAnd_Formula:      | Sub_Formula AND And_Formula\n");
						$$=(SELECTSTMT*) addAndFormula($1, $2, $3);
					}
			|	Sub_Formula OR And_Formula
					{
						//fprintf(stdout, "\nOr_Formula    :     | Sub_Formula OR And_Formula \n");
						$$=(SELECTSTMT*) addOrFormula($1, $2, $3);
					}
			;
			
Or_Formula  :  	Sub_Formula OR Sub_Formula
					{
						//fprintf(stdout, "\nOr_Formula    :     | Sub_Formula OR Sub_Formula \n");
						$$=(SELECTSTMT*) addOrFormula($1, $2, $3);
					}
			|	Sub_Formula OR Or_Formula
					{
						//fprintf(stdout, "\nOr_Formula    :     | Sub_Formula OR Sub_Formula \n");
						$$=(SELECTSTMT*) addOrFormula($1, $2, $3);
					}
			;*/

Sub_Formula	:   RELATIONNAME LEFT_PAR RELATIONNAME RIGHT_PAR
					{
						//fprintf(stdout, "\nSub_Formula:        RELATIONNAME LEFT_PAR RELATIONNAME RIGHT_PAR\n");
						$$=(SELECTSTMT*) addRelationname(NULL, $1, $3);
					}
			| 	NOT RELATIONNAME LEFT_PAR RELATIONNAME RIGHT_PAR
					{
						//fprintf(stdout, "\nSub_Formula:       | NOT RELATIONNAME LEFT_PAR RELATIONNAME RIGHT_PAR\n");
						$$=(SELECTSTMT*) addRelationname($1, $2, $4);
					}
		   
			| 	RELATIONNAME IN RELATIONNAME 
					{
						//fprintf(stdout, "\nSub_Formula:       | RELATIONNAME IN RELATIONNAME\n");
						$$=(SELECTSTMT*) addRelationname(NULL, $3, $1);
					}
			| 	RELATIONNAME NOT IN RELATIONNAME 
					{
						//fprintf(stdout, "\nSub_Formula:       | RELATIONNAME NOT IN RELATIONNAME\n");
						$$=(SELECTSTMT*) addRelationname($2, $4, $1);
					}
			| 	LEFT_PAR Formula RIGHT_PAR 
					{
						//fprintf(stdout, "\nSub_Formula:       | LEFT_PAR And_Formula RIGHT_PAR\n");                     
						$$=(SELECTSTMT*) addPar($1, $2, $3);
                    }
			
			| 	Condition
                    {
						$$ = $1;
                    }
			| 	Quantified_Form
					{
						$$ = $1; 
                    }			
			;			
Condition	:   Operand RELOP Operand 
				{
					$$=(SELECTSTMT*)addCondition($1, $2, $3, 0);
				}
			|	Equation RELOP Operand
				{
					$$ = (SELECTSTMT*)addCondition($1,$2,$3,0);
				}
			| 	LEFT_PAR NOT Operand RELOP Operand RIGHT_PAR
				{
					$$=(SELECTSTMT*)addCondition($3, $4, $5, 1);
				}
			| 	LEFT_PAR NOT Equation RELOP Operand RIGHT_PAR
				{
					$$=(SELECTSTMT*)addCondition($3, $4, $5, 1);
				}	
			;
				
Operand	:   VAR_ATTRIBUTE
			{
				$$=(SELECTSTMT*)addOperand($1, 'A');
			}
		| 	CONSTANT
			{
				$$=(SELECTSTMT*)addOperand($1, 'V');
			}
		| 	DIGIT
			{
				$$=(SELECTSTMT*)addOperand($1, 'V');
			}
		;
				
Quantified_Form	:   Quantifier LEFT_PAR Formula RIGHT_PAR /* quantifier (formula),not(exist)(formula) */
					{
						//fprintf(stdout, "\nQuantified_Form	:   Quantifier LEFT_PAR Formula RIGHT_PAR\n");
						buildexpression($1, $3);
						$$ = addQuantifierForm();	
						layers--;

						if(forall_flag != 0)
						{       
							forall_flag--;
						}
						if(layers == 0 && forall_flag != 0)
						{
							forall_flag = 0;
						}
					}  			
				| 	Quantifier Quantified_Form /* not(exist) not(exist) (formula) */
					{ 
						$$=addQuantifierForm();
						layers--;

						if(forall_flag != 0)
						{
							forall_flag--;
						}
						
						if(layers == 0 && forall_flag != 0)
						{
							forall_flag = 0;
						}
          }
				;
					
Quantifier	: 	LEFT_PAR EXISTS existsVariables RIGHT_PAR /*(exist)*/
				{
					///fprintf(stdout, "\nQuantifier:            | LEFT_PAR EXISTS existsVariables RIGHT_PAR\n");
					 layers++;
            exist_flag=0; /**/
           if(forall_flag == 1)
           {
            forall_flag = 2;
            not_exist_flag=0;
          }
					$$ = $3;
				}
			|	 LEFT_PAR FORALL existsVariables RIGHT_PAR
				{layers++;
					forall_flag = 1;
					$$ = $3;                          
				}
			| 	NOT LEFT_PAR EXISTS existsVariables RIGHT_PAR /*not (exist)*/
				{
					//fprintf(stdout, "\nQuantifier:            | NOT LEFT_PAR EXISTS existsVariables RIGHT_PAR\n");
					layers++;       
          not_exist_flag=1;
          /*exist_flag=1;*/
					if(forall_flag == 1)
          {
					forall_flag = 2;       
           }   

					if (mult_exist_var_flag == 0)
						{
							exist_flag = 1;
							exist_flag_count++;
						}
					else
						{
							exist_flag = 2;
							mult_exist_var_flag = 0;
						}
              
					$$ = $4; 
				}
			;
existsVariables:    RELATIONNAME 
					{ 
						$$=(SELECTSTMT*) addExistsVar($1, NULL); 
					}
				| 	RELATIONNAME IN RELATIONNAME
					{ 
						$$=(SELECTSTMT*) addRelationname(NULL, $3, $1); 
				   } 
				| 	RELATIONNAME COMMA existsVariables
					{
						mult_exist_var_flag = 1;                         
						$$=(SELECTSTMT*) addExistsVar($1, $3); 
					}
				| 	RELATIONNAME IN RELATIONNAME COMMA existsVariables
					{
						mult_exist_var_flag = 1;  
						$$=(SELECTSTMT*) addRelationname(NULL, $3, $1); 
						$$=(SELECTSTMT*) addExistsVar2($$, $5); 
					}
				;
Vars_Attrs	:   VAR_ATTRIBUTE 
				{
					$$=(SELECTSTMT*) addVarAttrs($1, NULL, NULL); 
			    }
			| 	SIGN
				{
					$$=(SELECTSTMT*) addVarAttrs($1, NULL, NULL); 
				}
			|	Equation
				{
					$$=(SELECTSTMT*)addEqAttrs($1,NULL);
				}
			|	Equation COMMA Vars_Attrs
				{
				   $$ = (SELECTSTMT*) addEqAttrs($1, $3);
				}
			| 	VAR_ATTRIBUTE COMMA Vars_Attrs 
				{
					$$=(SELECTSTMT*) addVarAttrs($1, NULL,$3);
				}
			| 	VAR_ATTRIBUTE AS RELATIONNAME COMMA Vars_Attrs 
				{
					$$=(SELECTSTMT*) addVarAttrs($1, $3,$5);
				}
			| 	VAR_ATTRIBUTE AS RELATIONNAME 
				{	
					$$=(SELECTSTMT*) addVarAttrs($1, $3, NULL);
				}
			|	Aggregate LEFT_PAR VAR_ATTRIBUTE  RIGHT_PAR 
				{
					$$ = (SELECTSTMT*)addVarAttrs2($1, $3, NULL, NULL, NULL);
				}
			|	Aggregate LEFT_PAR VAR_ATTRIBUTE  RIGHT_PAR AS RELATIONNAME
				{
					//fprintf(stdout, "\nVars_Attrs:           |Aggregate LEFT_PAR VAR_ATTRIBUTE  RIGHT_PAR AS RELATIONNAME \n");
					 $$ =(SELECTSTMT*)addVarAttrs2($1, $3, $6, NULL, NULL);
				}
			|	Aggregate LEFT_PAR SIGN RIGHT_PAR AS RELATIONNAME
				{
					//fprintf(stdout, "\nVars_Attrs:           |Aggregate LEFT_PAR SIGN RIGHT_PAR AS RELATIONNAME \n");
					$$ =(SELECTSTMT*)addVarAttrs2($1, $3, $6, NULL, NULL);
				}
			|	Aggregate LEFT_PAR VAR_ATTRIBUTE RIGHT_PAR AS RELATIONNAME COMMA Vars_Attrs
				{
				//fprintf(stdout, "\nVars_Attrs:           |  Aggregate LEFT_PAR VAR_ATTRIBUTE RIGHT_PAR AS RELATIONNAME COMMA Vars_Attrs\n");
					$$=(SELECTSTMT*) addVarAttrs2($1, $3, $6,$8, NULL);
				}
			| 	Aggregate LEFT_PAR SIGN RIGHT_PAR AS RELATIONNAME COMMA Vars_Attrs
				{
					//fprintf(stdout, "\nVars_Attrs:           | Aggregate LEFT_PAR SIGN RIGHT_PAR AS RELATIONNAME COMMA Vars_Attrs\n");
					$$=(SELECTSTMT*) addVarAttrs2($1, $3, $6,$8, NULL);
				}
			| 	Aggregate LEFT_PAR VAR_ATTRIBUTE RIGHT_PAR SIGN Vars_Attrs
				{
					//fprintf(stdout, "\nVars_Attrs:           | Aggregate LEFT_PAR VAR_ATTRIBUTE RIGHT_PAR SIGN Vars_Attrs\n");
					$$=(SELECTSTMT*) addVarAttrs2($1, $3, NULL,$6, $5);
				}
			| 	Aggregate LEFT_PAR SIGN RIGHT_PAR SIGN Vars_Attrs
				{
					//fprintf(stdout, "\nVars_Attrs:           | Aggregate LEFT_PAR SIGN RIGHT_PAR SIGN Vars_Attrs\n");
					$$=(SELECTSTMT*) addVarAttrs2($1, $3, NULL,$6, $5);
				}
			| 	Aggregate LEFT_PAR VAR_ATTRIBUTE RIGHT_PAR COMMA Vars_Attrs
				{
					//fprintf(stdout, "\nVars_Attrs:           | Aggregate LEFT_PAR VAR_ATTRIBUTE RIGHT_PAR COMMA Vars_Attrs\n");
					$$=(SELECTSTMT*) addVarAttrs2($1, $3, NULL,$6, NULL);
				}
			|	 Aggregate LEFT_PAR SIGN RIGHT_PAR COMMA Vars_Attrs
				{
					//fprintf(stdout, "\nVars_Attrs:           | Aggregate LEFT_PAR SIGN RIGHT_PAR COMMA Vars_Attrs\n");
					$$=(SELECTSTMT*) addVarAttrs2($1, $3, NULL,$6, NULL);
				}    
			;
			
Aggregate	:   AVG 
				{
					strcpy($$, $1);
				}
			|	MAX
				{
					strcpy($$, $1);
				}
			|	MIN
				{
					strcpy($$, $1);
				}
			|	SUM
				{
					strcpy($$, $1);
				}
			|	COUNT
				{
					strcpy($$, $1);
				};

%%

/* Offset in statement. */
int offset;

/* Flag if syntax error occures. */
char f_stmterror = 'N';
 
#include "lex.yy.c"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void yyerror(char* msg)
{
  fprintf(stdout, "%s\n", msg);
  fprintf(stdout, "unexpected %s at character offset %i in statement\n", yytext, offset);
	
  offset = 0;
  if (strcmp(yytext, ";") != 0)
    f_stmterror = 'Y';
   
  fprintf(stdout, "TRC>");  
}

/*int yywrap()
{
  exit(1);
}*/

/* -----------------------------------------------------------------------
Function name: main
Purpose:
	To connect to oracle, start the processr and disconnect from oracle
	when done
------------------------------------------------------------------------ */
int main(int argc, char **argv)
{
  char password[MAXLENGTH];
  char   user_id[MAXLENGTH];

  printf("%s", "Welcome To Tuple Calculus Interface!\n");

  char inFileName[] = "credentials.txt";

  FILE *inFile;

  /* open the input file */  
  inFile = fopen(inFileName, "r");
  fscanf(inFile, "%s %s", user_id, password);

  /*#printf("test");*/
   /*# printf("user_id:%s",user_id);*/
  /*#printf("password:%s",*password);*/

  /** Connect to the database. **/
  if (oracle_connect(user_id, password) != 0)
    exit(1);
  /*#system("clear\n");*/
  fprintf(stdout, "\n\t+------------------------------------------------------------+\n");
  fprintf(stdout, "\t|             Tuple Calculus Interface to Oracle             |\n");
  fprintf(stdout, "\t|                  Database Research Group                   |\n");
  fprintf(stdout, "\t|                 School of Computer Science                 |\n");
  fprintf(stdout, "\t|                    Carleton University                     |\n");
  fprintf(stdout, "\t|                   For help, type 'help;'                   |\n");
  fprintf(stdout, "\t|              To exit, type 'exit;' or 'quit;'              |\n");
  fprintf(stdout, "\t+------------------------------------------------------------+\n\n");
  fprintf(stdout, "TRC>");
  extern FILE* yyin;
  yyin = fopen(argv[1], "r");
  yyparse();
  fprintf(stdout, "\nThank you for using Tuple Relation Calculus interpreter!\n");
  oracle_disconnect();

  /*@@@@@@@@@@@@@@@@@@*/
  exist_flag_count = 0;
  quantifier_error_flag = 0;
  quantifier_error_display_flag = 0;
  freevar_error_flag = 0;
  layers = 0;
  table_error_flag =0;
  not_exist_flag = 0;
  forall_flag=0;
  mult_exist_var_flag = 0;
  exist_flag=0;
  return 0;
}
