%{
/* ***************************************************************************
Original Filename:   relalg.y
Current Filename:    alg.y
Revision Date:       Not Specified
Author:              Jaret Funk
Student#:            194-6-02491
Course:              CS 470-001
Date:                19 April 1999

Maintenance:
//First Set
  Maintainer: Sufang Hou
  Student#:   Not Specified
  Course:     Not Specified
  Date:       07 May 2004

//Second Set
  Maintainer: Duojie Chang
  Student#:   Not Specified
  Course:     Not Specified
  Date:       18 September 2012

//Third Set
  Maintainer: Mathieu Leblanc
  Student#:   101092676
  Course:     COMP4905A
  Date:       07 December 2020

Contents:   
  yacc translation rules for relational algebra grammar and their semantic 
  actions that perform the translation. Also contains syntax error handling 
  routing and main program of the interpreter.

  As per lex format, the expression are defined by writing their identifier
  followed by a colon. Any grammar rules associated with that expression are
  then defined and separated by vertical bars. Operations that must be 
  completed when a grammar rule occurs are defined inside of a block delimited
  by curly brackets '{', '}'.
  If debug mode is activated, the grammar rule that is execute will have its 
  pattern printed to the user.

  All usable tokens are defined at the beginning of the file. Tokens not 
  included in this section and found when parsing will most likely throw 
  an error, or be considered for another token (which would most likely result 
  in an erroneous result.
****************************************************************************** */

#include "alg.h"
%}

%union {
	char string[MAXLENGTH];
	char oracom[MAXSTMTLENGTH];
	SELECTSTMT* selectstmt;
	char* str_p; }

%token SEMI_COLON
%token LEFT_PAR
%token RIGHT_PAR
%token RENAME
%token SELECT
%token PROJECT
%token EQUIJOIN
%token JOIN
%token OR
%token TO
%token <string> AS
%token AND
%token <string> BINARYOP
%token <string> CONSTANT
%token <string> RELOP
%token COMMA
%token HELP
%token DEBUG
%token EXIT
%token QUIT
%token ASSIGN
%token <oracom> ORACOM 
%token DESCRIBE
%token <string> INVALID_CHAR
%token <string> SYMBOL
%token AGGREGATE
%token ORDER
%token BY
%token HAVING
%token <string> ASC
%token <string> DESC
%token <string> VARIABLE
%type <selectstmt> expression
%type <selectstmt> select_expr
%type <selectstmt> project_expr
%type <selectstmt> rename_expr
%type <selectstmt> join_expr
%type <selectstmt> aggregate_expr
%type <selectstmt> biop_expr
%type <selectstmt> condition
%type <selectstmt> and_condition
%type <selectstmt> rel_formula
%type <selectstmt> variables
%type <selectstmt> symbolSet 
%type <selectstmt> symbolSets
%type <selectstmt> symSetsWithoutVa
%type <selectstmt> operand
%type <selectstmt> operands
%type <selectstmt> havings
%type <selectstmt> havingvariables   
%type <selectstmt> orderbyvariables  
%type <selectstmt> orderby
 
%expect 39
%nonassoc UMINUS
%start statement
%%

statement:	
                /*nothing*/
                |	expression SEMI_COLON 
                  {
                    if(debug_mode) printf("statement: expression SEMI_COLON\n");
                    executesql($1);
                    delete_temp_tables();
                    delete_ren_tables();
                    YYACCEPT;
                  }
                
                |	expression BINARYOP expression SEMI_COLON
                  {
                    if(debug_mode) printf("statement: expression BINARYOP expression SEMI_COLON\n");
                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the first expression.
                    */
                    SELECTSTMT *nselect1 = NULL;
                    
                    /*
                      Pointer used to hold the statement representing the renamed
                      version of the second expression.
                    */
                    SELECTSTMT *nselect2 = NULL;
                    
                    /*
                      Pointer used to hold the statement representing the result 
                      of the binary operation.
                    */
                    SELECTSTMT *nselect3 = NULL;
                    
                    /*
                      Array used to store the generated name for the renamed version 
                      of the first expression.
                    */
                    char temp_str[MAXLENGTH];
                    
                    /*
                      Array used to store the generated name for the renamed version
                      of the second expression.
                    */
                    char temp_str2[MAXLENGTH];
                    
                    /*
                      Array used to store the generated name for the result of the 
                      binary operation.
                    */
                    char temp_str3[MAXLENGTH];
                    temp_str[0]='\0';
                    temp_str2[0]='\0';
                    temp_str3[0]='\0';
                    
                    //Integer variable used to iterate through rename table name candidates.
                    int i = 1;

                    /*
                      Generate table names by iterating through candidates until table names 
                      are created that cannot be correlated to an existing table.
                    */
                    do
                    {
                      snprintf(temp_str, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str) != 0);
                    do
                    {
                      snprintf(temp_str2, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str2[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str2) != 0);
                    do
                    {
                      snprintf(temp_str3, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str3[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str3) != 0);

                    //Create renamed versions of the first and second expressions.
                    assignQuery(temp_str, $1, 1, 0);
                    assignQuery(temp_str2, $3, 1, 0);

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the first 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect1 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect1->f_error='E';
                    }
                    else 
                    {
                      nselect1 = (SELECTSTMT* )addRelation(temp_str);
                      addToRenList(temp_str);
                    }

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the second 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str2, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect2 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect2->f_error='E';
                    }
                    else 
                    {
                      nselect2 = (SELECTSTMT* )addRelation(temp_str2);
                      addToRenList(temp_str2);
                    }

                    //If an error occurred in either of the operations, print them.
                    if(nselect1->f_error == 'E' || nselect2->f_error == 'E')
                    {
                      if(nselect1->f_error == 'E')
                      {
                        printf("%s\n", nselect1->errormsg);
                      }
                      if(nselect2->f_error == 'E')
                      {
                        printf("%s\n", nselect2->errormsg);
                      }
                      delete_temp_tables();
                      delete_ren_tables();
                      yyerrok;
                      YYABORT;
                    }
                    else
                    {
                      //Complete the binary operation and rename result.
                      assignQuery(temp_str3, binaryopstmt(nselect1, $2, nselect2), 1, 0);

                      /*
                        If an error occurred, raise error.
                        Otherwise, create a new statement for the renamed version of the result 
                        expression, and add the renamed table to the list managing the renamed 
                        tables.
                      */
                      if(strcmp(temp_str3, "0000000ERROR_OCCURED0000000") == 0)
                      {
                        if ((nselect3 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                        {
                          fprintf(stderr, "Not enough memory to allocate to list!");
                          exit(1);
                        }
                        nselect3->f_error='E';
                      }
                      else 
                      {
                        nselect3 = (SELECTSTMT* )addRelation(temp_str3);
                        addToRenList(temp_str3);
                      }
                      
                      //If an error occurred, print it and complete operation.
                      //Otherwise, execute resulting expression and complete operation.
                      if(nselect3->f_error == 'E')
                      {
                        printf("%s\n", nselect3->errormsg);
                        delete_temp_tables();
                        delete_ren_tables();
                        yyerrok;
                        YYABORT;
                      }
                      else
                      {
                        executesql(nselect3);
                        delete_temp_tables();
                        delete_ren_tables();
                        YYACCEPT;
                      }
                    }
                  }
                
                | expression BINARYOP expression BINARYOP expression SEMI_COLON
                  {
                    if(debug_mode) printf("statement: expression BINARYOP expression BINARYOP expression SEMI_COLON\n");

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the first expression.
                    */
                    SELECTSTMT *nselect1 = NULL;

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the second expression.
                    */
                    SELECTSTMT *nselect2 = NULL;

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the third expression.
                    */
                    SELECTSTMT* nselect3 = NULL;

                    /*
                      Pointer used to hold the statement representing the named 
                      version of the result of the first binary operation.
                    */
                    SELECTSTMT* nselect4 = NULL;

                    /*
                      Pointer used to hold the statement representing the named 
                      version of the result of the second binary operation.
                    */
                    SELECTSTMT* nselect5 = NULL;

                    /*
                      Array used to store the generated name for the renamed version 
                      of the first expression.
                    */
                    char temp_str[MAXLENGTH];
                    
                    /*
                      Array used to store the generated name for the renamed version 
                      of the second expression.
                    */
                    char temp_str2[MAXLENGTH];
                    
                    /*
                      Array used to store the generated name for the renamed version 
                      of the second expression.
                    */
                    char temp_str3[MAXLENGTH];
                    
                    /*
                      Array used to store the generated name for the named version 
                      of the result of the first binary operation.
                    */
                    char temp_str4[MAXLENGTH];
                    
                    /*
                      Array used to store the generated name for the renamed version 
                      of the result of the first binary operation.
                    */
                    char temp_str5[MAXLENGTH];
                    temp_str[0]='\0';
                    temp_str2[0]='\0';
                    temp_str3[0]='\0';
                    temp_str4[0]='\0';
                    temp_str5[0]='\0';

                    //Integer variable used to iterate through rename table name candidates.
                    int i = 1;

                    /*
                      Generate table names by iterating through candidates until table names 
                      are created that cannot be correlated to an existing table.
                    */
                    do
                    {
                      snprintf(temp_str, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str) != 0);
                    do
                    {
                      snprintf(temp_str2, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str2[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str2) != 0);
                    do
                    {
                      snprintf(temp_str3, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str3[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str3) != 0);
                    do
                    {
                      snprintf(temp_str4, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str4[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str4) != 0);
                    do
                    {
                      snprintf(temp_str5, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str5[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str5) != 0);

                    //Create renamed versions of the statement expressions.
                    assignQuery(temp_str, $1, 1, 0);
                    assignQuery(temp_str2, $3, 1, 0);
                    assignQuery(temp_str3, $5, 1, 0);

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the first 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect1 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect1->f_error='E';
                    }
                    else 
                    {
                      nselect1 = (SELECTSTMT* )addRelation(temp_str);
                      addToRenList(temp_str);
                    }

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the second 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str2, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect2 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect2->f_error='E';
                    }
                    else 
                    {
                      nselect2 = (SELECTSTMT* )addRelation(temp_str2);
                      addToRenList(temp_str2);
                    }

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the third 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str3, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect3 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect3->f_error='E';
                    }
                    else 
                    {
                      nselect3 = (SELECTSTMT* )addRelation(temp_str3);
                      addToRenList(temp_str3);
                    }

                    //If an error occurred in any of the operations, print them.
                    if(nselect1->f_error == 'E' || nselect2->f_error == 'E' || nselect3->f_error == 'E'){
                      if(nselect1->f_error == 'E'){
                        printf("%s\n", nselect1->errormsg);
                      }
                      if(nselect2->f_error == 'E'){
                        printf("%s\n", nselect2->errormsg);
                      }
                      if(nselect3->f_error == 'E'){
                        printf("%s\n", nselect3->errormsg);
                      }
                      delete_temp_tables();
                      delete_ren_tables();
                      yyerrok;
                      YYABORT;
                    }
                    else{
                      //Complete the first binary operation and rename result.
                      assignQuery(temp_str4, binaryopstmt(nselect1, $2, nselect2), 1, 0);

                      /*
                        If an error occurred, raise error.
                        Otherwise, create a new statement for the named version of the result 
                        of the first binary operation, and add the renamed table to the list 
                        managing the renamed tables.
                      */
                      if(strcmp(temp_str4, "0000000ERROR_OCCURED0000000") == 0)
                      {
                        if ((nselect4 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                        {
                          fprintf(stderr, "Not enough memory to allocate to list!");
                          exit(1);
                        }
                        nselect4->f_error='E';
                      }
                      else 
                      {
                        nselect4 = (SELECTSTMT* )addRelation(temp_str4);
                        addToRenList(temp_str4);
                      }
                      
                      //If an error occurred, print it and complete operation.
                      if(nselect4->f_error == 'E')
                      {
                        printf("%s\n", nselect4->errormsg);
                        delete_temp_tables();
                        delete_ren_tables();
                        yyerrok;
                        YYABORT;
                      }
                      else
                      {
                        //Complete the second binary operation and rename result.
                        assignQuery(temp_str5, binaryopstmt(nselect4, $4, nselect3), 1, 0);

                        /*
                          If an error occurred, raise error.
                          Otherwise, create a new statement for the named version of the result 
                          of the second binary operation, and add the renamed table to the list 
                          managing the renamed tables.
                        */
                        if(strcmp(temp_str5, "0000000ERROR_OCCURED0000000") == 0)
                        {
                          if ((nselect5 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                          {
                            fprintf(stderr, "Not enough memory to allocate to list!");
                            exit(1);
                          }
                          nselect5->f_error='E';
                        }
                        else 
                        {
                          nselect5 = (SELECTSTMT* )addRelation(temp_str5);
                          addToRenList(temp_str5);
                        }
                      
                        //If an error occurred, print it and complete operation.
                        //Otherwise, execute resulting expression and complete operation.
                        if(nselect5->f_error == 'E')
                        {
                          printf("%s\n", nselect5->errormsg);
                          delete_temp_tables();
                          delete_ren_tables();
                          yyerrok;
                          YYABORT;
                        }
                        else
                        {
                          executesql(nselect5);
                          delete_temp_tables();
                          delete_ren_tables();
                          YYACCEPT;
                        }
                      }
                    }
                  }
                
                |	VARIABLE ASSIGN expression SEMI_COLON
                  {
                    if(debug_mode) printf("statement: VARIABLE ASSIGN expression SEMI_COLON\n");

                    //Array used to store the table name for the new table.
                    char temp_str[MAXLENGTH];
                    temp_str[0]='\0';
                    strcpy(temp_str, $1);

                    //Create new table using the expression.
                    assignQuery(temp_str, $3, 1, 1);
                    delete_temp_tables();
                    delete_ren_tables();
                    YYACCEPT;
                  }
                
                | expression JOIN expression LEFT_PAR VARIABLE RELOP VARIABLE RIGHT_PAR SEMI_COLON		
                  {
                    if(debug_mode) printf("statement: expression JOIN expression LEFT_PAR VARIABLE RELOP VARIABLE RIGHT_PAR SEMI_COLON\n");
                    executesql(joinstmt($1, $3, $5, $6, $7)); 
                    delete_temp_tables();
                    delete_ren_tables();
                    YYACCEPT;
                  }
                
                |	VARIABLE ASSIGN expression BINARYOP expression SEMI_COLON
                  {
                    if(debug_mode) printf("statement: VARIABLE ASSIGN expression BINARYOP expression SEMI_COLON\n");

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the first expression.
                    */
                    SELECTSTMT *nselect1 = NULL;

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the second expression.
                    */
                    SELECTSTMT *nselect2 = NULL;

                    /*
                      Array used to store the generated name for the renamed version 
                      of the first expression.
                    */
                    char temp_str[MAXLENGTH];

                    /*
                      Array used to store the generated name for the renamed version 
                      of the second expression.
                    */
                    char temp_str2[MAXLENGTH];

                    /*
                      Array used to store the name of the renamed version of the result 
                      of the binary operation.
                    */
                    char temp_str3[MAXLENGTH];
                    temp_str[0]='\0';
                    temp_str2[0]='\0';
                    temp_str3[0]='\0';
                    strcpy(temp_str3, $1);

                    //Integer variable used to iterate through rename table name candidates.
                    int i = 1;

                    /*
                      Generate table names by iterating through candidates until table names 
                      are created that cannot be correlated to an existing table.
                    */
                    do
                    {
                      snprintf(temp_str, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str) != 0);
                    do
                    {
                      snprintf(temp_str2, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str2[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str2) != 0);

                    //Create renamed versions of the first and second expressions.
                    assignQuery(temp_str, $3, 1, 0);
                    assignQuery(temp_str2, $5, 1, 0);

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the first 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect1 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect1->f_error='E';
                    }
                    else 
                    {
                      nselect1 = (SELECTSTMT* )addRelation(temp_str);
                      addToRenList(temp_str);
                    }

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the second 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str2, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect2 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect2->f_error='E';
                    }
                    else 
                    {
                      nselect2 = (SELECTSTMT* )addRelation(temp_str2);
                      addToRenList(temp_str2);
                    }

                    //If an error occurred in either of the operations, print them.
                    if(nselect1->f_error == 'E' || nselect2->f_error == 'E'){
                      if(nselect1->f_error == 'E'){
                        printf("%s\n", nselect1->errormsg);
                      }
                      if(nselect2->f_error == 'E'){
                        printf("%s\n", nselect2->errormsg);
                      }
                      delete_temp_tables();
                      delete_ren_tables();
                      yyerrok;
                      YYABORT;
                    }
                    else{
                      //Otherwise complete the binary operation and the assign operation.
                      assignQuery(temp_str3, binaryopstmt(nselect1, $4, nselect2), 1, 1);
                      delete_temp_tables();
                      delete_ren_tables();
                      YYACCEPT;
                    }
                  }
                
                | VARIABLE LEFT_PAR variables RIGHT_PAR ASSIGN expression SEMI_COLON
                  {
                    if(debug_mode) printf("statement: VARIABLE LEFT_PAR variables RIGHT_PAR ASSIGN expression SEMI_COLON\n");
                    renameattribute($1, $3, $6, 1, 1);
                    delete_temp_tables();
                    delete_ren_tables();
                    YYACCEPT;
                  }
                
                | VARIABLE LEFT_PAR variables RIGHT_PAR ASSIGN expression BINARYOP expression SEMI_COLON
                  {
                    if(debug_mode) printf("statement: VARIABLE LEFT_PAR variables RIGHT_PAR ASSIGN expression BINARYOP expression SEMI_COLON\n");

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the first expression.
                    */
                    SELECTSTMT *nselect1 = NULL;

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the second expression.
                    */
                    SELECTSTMT *nselect2 = NULL;

                    /*
                      Array used to store the generated name for the renamed version 
                      of the first expression.
                    */
                    char temp_str[MAXLENGTH];

                    /*
                      Array used to store the generated name for the renamed version 
                      of the second expression.
                    */
                    char temp_str2[MAXLENGTH];

                    /*
                      Array used to store the name for the result of the binary operation.
                    */
                    char temp_str3[MAXLENGTH];
                    temp_str[0]='\0';
                    temp_str2[0]='\0';
                    temp_str3[0]='\0';
                    strcpy(temp_str3, $1);

                    //Integer variable used to iterate through rename table name candidates.
                    int i = 1;

                    /*
                      Generate table names by iterating through candidates until table names 
                      are created that cannot be correlated to an existing table.
                    */
                    do
                    {
                      snprintf(temp_str, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str) != 0);
                    do
                    {
                      snprintf(temp_str2, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str2[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str2) != 0);

                    //Create renamed versions of the first and second expressions.
                    assignQuery(temp_str, $6, 1, 0);
                    assignQuery(temp_str2, $8, 1, 0);

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the first 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect1 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect1->f_error='E';
                    }
                    else 
                    {
                      nselect1 = (SELECTSTMT* )addRelation(temp_str);
                      addToRenList(temp_str);
                    }

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the second 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str2, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect2 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect2->f_error='E';
                    }
                    else 
                    {
                      nselect2 = (SELECTSTMT* )addRelation(temp_str2);
                      addToRenList(temp_str2);
                    }

                    //If an error occurred in either of the operations, print them.
                    if(nselect1->f_error == 'E' || nselect2->f_error == 'E'){
                      if(nselect1->f_error == 'E'){
                        printf("%s\n", nselect1->errormsg);
                      }
                      if(nselect2->f_error == 'E'){
                        printf("%s\n", nselect2->errormsg);
                      }
                      delete_temp_tables();
                      delete_ren_tables();
                      yyerrok;
                      YYABORT;
                    }
                    else{
                      //Otherwise, complete the binary operation and the assign operation.
                      renameattribute(temp_str3, $3, binaryopstmt(nselect1, $7, nselect2), 1, 1);
                      delete_temp_tables();
                      delete_ren_tables();
                      YYACCEPT;
                    }
                  }
                
                |	ORACOM SEMI_COLON 
                  {
                    if(debug_mode) printf("statement: ORACOM SEMI_COLON\n");
                    executesqlstmt($1, 'Y', 0);
                    delete_temp_tables();
                    YYACCEPT;
                  }
                
                |	DESCRIBE VARIABLE SEMI_COLON
                  {
                    if(debug_mode) printf("statement: DESCRIBE VARIABLE SEMI_COLON\n");
                    describestatement($2);
                    YYACCEPT;
                  }
                
                |	SEMI_COLON 					
                  {
                    if(debug_mode) printf("statement: SEMI_COLON\n");
                    YYACCEPT;
                  }
                
                |	HELP SEMI_COLON
                  {
                    if(debug_mode) printf("statement: HELP SEMI_COLON\n");
                    system("cat ./alghelp.txt | less");
                    YYACCEPT;
                  }

                | DEBUG SEMI_COLON
                  {
                    debug_mode = (!debug_mode);
                    if(debug_mode) printf("statement: DEBUG SEMI_COLON\n");
                    YYACCEPT;
                  }
                
                |	error SEMI_COLON
                  {
                    if(debug_mode) printf("statement: error SEMI_COLON\n");
                    yyerrok;
                    YYABORT;
                  }

                | error
                  {
                    if(debug_mode) printf("statement: error\n");
                    yyerrok;
                    YYABORT;
                  }
                
                | havings expression orderby
                  {
                    if(debug_mode) printf("statement: havings expression orderby SEMI_COLON\n");
                    executesql(orderbyhavingstmt($2, $3, $1));
                    delete_temp_tables();
                    delete_ren_tables();
                    YYACCEPT;
                  }
                
                | expression orderby SEMI_COLON
                  {
                    if(debug_mode) printf("statement: expression orderby SEMI_COLON\n");
                    executesql(orderbyhavingstmt($1, $2, NULL));
                    delete_temp_tables();
                    delete_ren_tables();
                    YYACCEPT;
                  }
                ;


expression:     
                LEFT_PAR expression RIGHT_PAR
                  { 
                    if(debug_mode) printf("expression: LEFT_PAR expression RIGHT_PAR\n");
                    $$ = $2; 
                  }
                
                | VARIABLE
                  {
                    if(debug_mode) printf("expression: VARIABLE\n");
                    $$ = (SELECTSTMT* ) addRelation($1);
                  }
                
                | select_expr								
                  {
                    if(debug_mode) printf("expression: select_expr\n");
                    $$ = $1; 
                  }
                
                |	aggregate_expr								
                  {
                    if(debug_mode) printf("expression: aggregate_expr\n");
                    $$ = $1; 
                  }
                
                | join_expr
                  {
                    if(debug_mode) printf("expression: join_expr\n");
                    $$ = $1; 
                  }
                
                | biop_expr
                  {
                    if(debug_mode) printf("expression: biop_expr\n");
                    $$ = $1; 
                  }
                
                |	project_expr								
                  {
                    if(debug_mode) printf("expression: project_expr\n");
                    $$ = $1; 
                  }

                | rename_expr
                  {
                    if(debug_mode) printf("expression: rename_expr\n");
                    $$ = $1;
                  }
                
                | havings expression
                  {
                    if(debug_mode) printf("expression: havings expression\n");
                    $$ = orderbyhavingstmt($2, NULL, $1);
                    delete_temp_tables();
                  }
                ;
                
                
select_expr:    
                SELECT condition expression
                  {
                    if(debug_mode) printf("select_expr: SELECT condition expression\n");
                    $$ = (SELECTSTMT* )selectStmt($2, $3); 
                  }                       
                ;
                
                
project_expr:   
                PROJECT variables expression
                  {
                    if(debug_mode) printf("project_expr: PROJECT variables expression\n");
                    $$ = (SELECTSTMT* )projectstmt($2, $3); 
                  }
                ;

rename_expr:
                RENAME VARIABLE TO VARIABLE LEFT_PAR variables RIGHT_PAR
                  {
                    if(debug_mode) printf("rename_expr: RENAME VARIABLE TO VARIABLE LEFT_PAR variables RIGHT_PAR\n");

                    /*
                      Array used to store the table name to be used for the rename operation.
                    */
                    char temp_str[MAXLENGTH];
                    
                    /*
                      Array used to store the table name of the table to be renamed.
                    */
                    char temp_str2[MAXLENGTH];
                    temp_str[0]='\0';
                    temp_str2[0]='\0';
                    strcpy(temp_str, $4);
                    strcpy(temp_str2, $2);
                    
                    /*
                      Pointer for the statement containing the table to be renamed.
                    */
                    SELECTSTMT* temp_ptr = addRelation(temp_str2);

                    //Add renamed table name to renamed table list.
                    addToRenList(temp_str);
                    
                    //Complete rename operation.
                    renameattribute(temp_str, $6, temp_ptr, 1, 0);
                    
                    /*
                      Pointer to statement that will contain the renamed table.
                    */
                    SELECTSTMT *nselect = NULL;
                    
                    /*
                      If an error occurred, raise it.
                      Otherwise, create a new statement for the renamed table and return
                      its pointer.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect->f_error='E';
                    }
                    else 
                    {
                      nselect = (SELECTSTMT* )addRelation(temp_str);
                    }
                    $$ = nselect;
                  }

                /*Optional additional functionality for rename */
                | RENAME LEFT_PAR expression RIGHT_PAR TO VARIABLE LEFT_PAR variables RIGHT_PAR
                  {
                    if(debug_mode) printf("rename_expr: RENAME LEFT_PAR expression RIGHT_PAR TO VARIABLE LEFT_PAR variables RIGHT_PAR\n");

                    /*
                      Array used to store the table name to be used for the rename operation.
                    */
                    char temp_str[MAXLENGTH];
                    temp_str[0]='\0';
                    strcpy(temp_str, $6);
                    
                    //Add renamed table name to renamed table list.
                    addToRenList(temp_str);
                    
                    //Complete rename operation.
                    renameattribute(temp_str, $8, $3, 1, 0);
                    
                    /*
                      Pointer to statement that will contain the renamed table.
                    */
                    SELECTSTMT *nselect = NULL;
                    
                    /*
                      If an error occurred, raise it.
                      Otherwise, create a new statement for the renamed table and return
                      its pointer.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect->f_error='E';
                    }
                    else 
                    {
                      nselect = (SELECTSTMT* )addRelation(temp_str);
                    }
                    $$ = nselect;
                  }

                | RENAME LEFT_PAR expression RIGHT_PAR TO LEFT_PAR variables RIGHT_PAR
                  {
                    if(debug_mode) printf("rename_expr: RENAME LEFT_PAR expression RIGHT_PAR TO LEFT_PAR variables RIGHT_PAR\n");

                    /*
                      Array used to store the table name to be used for the rename operation.
                    */
                    char temp_str[MAXLENGTH];
                    temp_str[0]='\0';
                    
                    //Add renamed table name to renamed table list.
                    addToRenList(temp_str);
                    
                    //Complete rename operation.
                    renameattribute(temp_str, $7, $3, 1, 0);
                    
                    /*
                      Pointer to statement that will contain the renamed table.
                    */
                    SELECTSTMT *nselect = NULL;
                    
                    /*
                      If an error occurred, raise it.
                      Otherwise, create a new statement for the renamed table and return
                      its pointer.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect->f_error='E';
                    }
                    else 
                    {
                      nselect = (SELECTSTMT* )addRelation(temp_str);
                    }
                    $$ = nselect;
                  }

                | RENAME VARIABLE TO LEFT_PAR variables RIGHT_PAR
                  {
                    if(debug_mode) printf("rename_expr: RENAME VARIABLE TO LEFT_PAR variables RIGHT_PAR\n");

                    /*
                      Array used to store the table name to be used for the rename operation.
                      This rename operation will be anonymous since the result does not
                      have a table name provided by the user.
                    */
                    char temp_str[MAXLENGTH];
                    temp_str[0]='\0';
                    
                    //Add renamed table name to renamed table list.
                    addToRenList(temp_str);
                    
                    //Complete rename operation.
                    renameattribute(temp_str, $5, (SELECTSTMT*)addRelation($2), 1, 0);
                    
                    /*
                      Pointer to statement that will contain the renamed table.
                    */
                    SELECTSTMT *nselect = NULL;
                    
                    /*
                      If an error occurred, raise it.
                      Otherwise, create a new statement for the renamed table and return
                      its pointer.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect->f_error='E';
                    }
                    else 
                    {
                      nselect = (SELECTSTMT* )addRelation(temp_str);
                    }
                    $$ = nselect;
                  }
                
                | RENAME VARIABLE TO VARIABLE
                  {
                    if(debug_mode) printf("rename_expr: RENAME VARIABLE TO VARIABLE\n");
                    
                    /*
                      Array used to store the table name to be used for the rename operation.
                      This rename operation will be anonymous since the result does not
                      have a table name provided by the user.
                    */
                    char temp_str[MAXLENGTH];
                    temp_str[0]='\0';
                    strcpy(temp_str, $4);
                    
                    //Add renamed table name to renamed table list.
                    addToRenList(temp_str);
                    
                    //Complete rename operation.
                    assignQuery(temp_str, (SELECTSTMT* )addRelation($2), 1, 0);
                    
                    /*
                      Pointer to statement that will contain the renamed table.
                    */
                    SELECTSTMT *nselect = NULL;

                    /*
                      If an error occurred, raise it.
                      Otherwise, create a new statement for the renamed table and return
                      its pointer.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect->f_error='E';
                    }
                    else 
                    {
                      nselect = (SELECTSTMT* )addRelation(temp_str);
                    }
                    $$ = nselect;
                  }
                ;
                
                
join_expr:      
                expression EQUIJOIN expression LEFT_PAR VARIABLE COMMA VARIABLE RIGHT_PAR
                  {
                    if(debug_mode) printf("join_expr: expression EQUIJOIN expression LEFT_PAR VARIABLE COMMA VARIABLE RIGHT_PAR\n");
                    /*
                      Array used to store the equality operator used by EQUIJOIN operations.
                    */
                    char temp_str[MAXLENGTH];
                    temp_str[0] = '=';
                    temp_str[1] = '\0';
                    //Return pointer to a statement containing the EQUIJOIN operation.
                    $$ = (SELECTSTMT* )joinstmt($1, $3, $5, temp_str, $7); 
                  }

                | LEFT_PAR expression JOIN expression RIGHT_PAR LEFT_PAR VARIABLE RELOP VARIABLE RIGHT_PAR
                  {
                    if(debug_mode) printf("join_expr: LEFT_PAR expression JOIN expression RIGHT_PAR LEFT_PAR VARIABLE RELOP VARIABLE RIGHT_PAR\n");
                    $$ = (SELECTSTMT* )joinstmt($2, $4, $7, $8, $9); 
                  }
                
                | expression BINARYOP expression LEFT_PAR VARIABLE RIGHT_PAR
                  {
                    if(debug_mode) printf("join_expr: expression BINARYOP expression LEFT_PAR VARIABLE RIGHT_PAR\n");
                    $$ = (SELECTSTMT* )outerjoinstmt($1, $3, $2, $5); 
                  }

                | expression JOIN expression LEFT_PAR VARIABLE RELOP VARIABLE RIGHT_PAR
                  {
                    if(debug_mode) printf("join_expr: expression JOIN expression LEFT_PAR VARIABLE RELOP VARIABLE RIGHT_PAR\n");
                    $$ = (SELECTSTMT* )joinstmt($1, $3, $5, $6, $7); 
                    delete_temp_tables();
                  }
                ;
                
                
aggregate_expr: 
                AGGREGATE symbolSets expression
                  {
                    if(debug_mode) printf("aggregate_expr: AGGREGATE symbolSets expression\n");
                    $$ = (SELECTSTMT* )aggregatestmt($2, $3); 
                  }                
                ;
                
                
biop_expr:      
                expression BINARYOP expression
                  {
                    if(debug_mode) printf("biop_expr: expression BINARYOP expression\n");

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the first expression.
                    */
                    SELECTSTMT *nselect1 = NULL;

                    /*
                      Pointer used to hold the statement representing the renamed 
                      version of the second expression.
                    */
                    SELECTSTMT *nselect2 = NULL;

                    /*
                      Pointer used to hold the statement representing the result 
                      of the binary operation.
                    */
                    SELECTSTMT *nselect3 = NULL;

                    /*
                      Array used to store the generated name for the renamed version 
                      of the first expression.
                    */
                    char temp_str[MAXLENGTH];

                    /*
                      Array used to store the generated name for the renamed version 
                      of the second expression.
                    */
                    char temp_str2[MAXLENGTH];

                    /*
                      Array used to store the generated name for the renamed version 
                      of the result of the binary operation.
                    */
                    char temp_str3[MAXLENGTH];
                    temp_str[0]='\0';
                    temp_str2[0]='\0';
                    temp_str3[0]='\0';

                    //Integer variable used to iterate through rename table name candidates.
                    int i = 1;

                    /*
                      Generate table names by iterating through candidates until table names 
                      are created that cannot be correlated to an existing table.
                    */
                    do
                    {
                      snprintf(temp_str, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str) != 0);
                    do
                    {
                      snprintf(temp_str2, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str2[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str2) != 0);
                    do
                    {
                      snprintf(temp_str3, MAXLENGTH-1, "RENTAB%d", i);
                      temp_str3[MAXLENGTH-1]='\0';
                      ++i;
                    }while(temptable_test(temp_str3) != 0);

                    //Create renamed versions of the first and second expressions.
                    assignQuery(temp_str, $1, 1, 0);
                    assignQuery(temp_str2, $3, 1, 0);

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the first 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect1 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect1->f_error='E';
                    }
                    else 
                    {
                      nselect1 = (SELECTSTMT* )addRelation(temp_str);
                      addToRenList(temp_str);
                    }

                    /*
                      If an error occurred, raise error.
                      Otherwise, create a new statement for the renamed version of the second 
                      expression, and add the renamed table to the list managing the renamed 
                      tables.
                    */
                    if(strcmp(temp_str2, "0000000ERROR_OCCURED0000000") == 0)
                    {
                      if ((nselect2 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                      {
                        fprintf(stderr, "Not enough memory to allocate to list!");
                        exit(1);
                      }
                      nselect2->f_error='E';
                    }
                    else 
                    {
                      nselect2 = (SELECTSTMT* )addRelation(temp_str2);
                      addToRenList(temp_str2);
                    }

                    //If an error occurred in either of the operations, print them.
                    if(nselect1->f_error == 'E' || nselect2->f_error == 'E')
                    {
                      if(nselect1->f_error == 'E')
                      {
                        printf("%s\n", nselect1->errormsg);
                      }
                      if(nselect2->f_error == 'E')
                      {
                        printf("%s\n", nselect2->errormsg);
                      }
                      delete_temp_tables();
                      delete_ren_tables();
                      yyerrok;
                      YYABORT;
                    }
                    else
                    {
                      //Otherwise complete the binary operation and the assign operation.
                      assignQuery(temp_str3, binaryopstmt(nselect1, $2, nselect2), 1, 0);

                      /*
                        If an error occurred, raise error.
                        Otherwise, create a new statement for the renamed version of the result 
                        operation, and add the renamed table to the list managing the renamed 
                        tables.
                      */
                      if(strcmp(temp_str3, "0000000ERROR_OCCURED0000000") == 0)
                      {
                        if ((nselect3 = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
                        {
                          fprintf(stderr, "Not enough memory to allocate to list!");
                          exit(1);
                        }
                        nselect3->f_error='E';
                      }
                      else 
                      {
                        //Create statement for renamed result.
                        nselect3 = (SELECTSTMT* )addRelation(temp_str3);
                        //Add renamed table to list maintaining renamed tables.
                        addToRenList(temp_str3);
                      }
                      
                      /*
                        If an error occurred while creating the result of the binary 
                        operation, print an error message.
                        Otherwise, return generated statement.
                      */
                      if(nselect3->f_error == 'E')
                      {
                        printf("%s\n", nselect3->errormsg);
                        delete_temp_tables();
                        delete_ren_tables();
                        yyerrok;
                        YYABORT;
                      }
                      else
                      {
                        $$ = nselect3;
                      }
                    }
                  }
                ;
                
                
condition:      
                and_condition
                  {
                    if(debug_mode) printf("condition: and_condition\n");
                    $$ = condition_list($1, NULL); 
                  }
                | and_condition OR condition
                  {
                    if(debug_mode) printf("condition: and_condition OR condition\n");
                    $$ = condition_list($1, $3);
                  }
                ;
                
                
and_condition:  
                rel_formula
                  {
                    if(debug_mode) printf("and_condition: rel_formula\n");
                    $$ = andcond_list($1, NULL); 
                  }

                | rel_formula AND and_condition	
                  {
                    if(debug_mode) printf("and_condition: rel_formula AND and_condition	\n");
                    $$ = andcond_list($1, $3); 
                  }
                ;
                

rel_formula:    
                operands RELOP operand
                  {
                    if(debug_mode) printf("rel_formula: operands RELOP operand\n");
                    $$ = rel_formula1($1, $2, $3); 
                  }
                ;
                

variables:      
                VARIABLE
                  {
                    if(debug_mode) printf("variables: VARIABLE\n");
                    $$ = attribute_list($1, NULL); 
                  }

                | VARIABLE AS VARIABLE
                  {
                    if(debug_mode) printf("variables: VARIABLE AS VARIABLE\n");
                    $$ = attribute_list_asop($1, $2, $3, NULL);
                  }
                
                | VARIABLE INVALID_CHAR VARIABLE
                  {
                    if(debug_mode) printf("variables: VARIABLE INVALID_CHAR VARIABLE\n");
                    $$ = attribute_list_asop($1, $2, $3, NULL);
                  }

                |	VARIABLE COMMA variables
                  {
                    if(debug_mode) printf("variables: VARIABLE COMMA variables\n");
                    $$ = attribute_list($1, $3); 
                  }
                
                | VARIABLE AS VARIABLE COMMA variables
                  {
                    if(debug_mode) printf("variables: VARIABLE AS VARIABLE COMMA variables\n");
                    $$ = attribute_list_asop($1, $2, $3, $5);
                  }

                | VARIABLE INVALID_CHAR VARIABLE COMMA variables
                  {
                    if(debug_mode) printf("variables: VARIABLE INVALID_CHAR VARIABLE COMMA variables\n");
                    $$ = attribute_list_asop($1, $2, $3, $5);
                  }
                ;
                

symbolSet:      
                SYMBOL LEFT_PAR INVALID_CHAR RIGHT_PAR
                  {
                    if(debug_mode) printf("symbolSet: SYMBOL LEFT_PAR INVALID_CHAR RIGHT_PAR\n");
                    $$ = (SELECTSTMT*)getSymbSetString_agg($1, $3);
                  }

                | SYMBOL LEFT_PAR VARIABLE RIGHT_PAR
                  {
                    if(debug_mode) printf("symbolSet: SYMBOL LEFT_PAR VARIABLE RIGHT_PAR\n");
                    $$ = (SELECTSTMT*)getSymbSetString_agg($1, $3);
                  }
                ;
                

symbolSets:     
                symbolSet
                  {
                    if(debug_mode) printf("symbolSets: symbolSet\n");
                    $$ = (SELECTSTMT*)attribute_list_agg($1, NULL);
                  }
                
                | symbolSet AS VARIABLE
                  {
                    if(debug_mode) printf("symbolSets: symbolSet AS VARIABLE\n");
                    $$ = attribute_list_aggasop(($1)->info, $2, $3, NULL);
                  }
                
                | symbolSet INVALID_CHAR symbolSet
                  {
                    if(debug_mode) printf("symbolSets: symbolSet INVALID_CHAR symbolSet\n");
                    $$ = attribute_list_aggasop($1->info, $2, $3->info, NULL);
                  }

                | VARIABLE INVALID_CHAR symbolSet
                  {
                    if(debug_mode) printf("symbolSets: VARIABLE INVALID_CHAR symbolSet\n");
                    $$ = attribute_list_aggasop($1, $2, $3->info, NULL);
                  }

                | VARIABLE COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symbolSets: VARIABLE COMMA symSetsWithoutVa\n");
                    $$ = attribute_list($1, $3); 
                  }

                | VARIABLE AS VARIABLE COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symbolSets: VARIABLE AS VARIABLE COMMA symSetsWithoutVa\n");
                    $$ = attribute_list_aggasop($1, $2, $3, $5);
                  }


                | VARIABLE INVALID_CHAR symbolSet COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symbolSets: VARIABLE INVALID_CHAR symbolSet COMMA symSetsWithoutVa\n");
                    $$ = attribute_list_aggasop($1, $2, ($3)->info, $5);
                  }

                | symbolSet COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symbolSets: symbolSet COMMA symSetsWithoutVa\n");
                    $$ = (SELECTSTMT*)attribute_list_agg($1, $3); 
                  }

                | symbolSet AS VARIABLE COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symbolSets: symbolSet AS VARIABLE COMMA symSetsWithoutVa\n");
                    $$ = (SELECTSTMT*)attribute_list_aggasop($1->info, $2, $3, $5);
                  }

                | symbolSet INVALID_CHAR symbolSet COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symbolSets: symbolSet INVALID_CHAR symbolSet COMMA symSetsWithoutVa\n");
                    $$ = (SELECTSTMT*)attribute_list_aggasop($1->info, $2, $3->info, $5);
                  }
                ;      
                

symSetsWithoutVa:
                symbolSet
                  {
                    if(debug_mode) printf("symSetsWithoutVa: symbolSet\n");
                    $$ = (SELECTSTMT*)attribute_list_agg($1, NULL);
                  }

                | symbolSet AS VARIABLE
                  {
                    if(debug_mode) printf("symSetWithoutVa: symbolSet AS VARIABLE\n");
                    $$ = attribute_list_aggasop(($1)->info, $2, $3, NULL);
                  }

                | symbolSet INVALID_CHAR symbolSet
                  {
                    if(debug_mode) printf("symSetWithoutVa: symbolSet INVALID_CHAR symbolSet\n");
                    $$ = attribute_list_aggasop($1->info, $2, $3->info, NULL);
                  }

                | symbolSet COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symSetWithoutVa: symbolSet COMMA symSetsWithoutVa\n");
                    $$ = (SELECTSTMT*)attribute_list_agg($1, $3);
                  }

                | symbolSet AS VARIABLE COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symSetWithoutVa: symbolSet AS VARIABLE COMMA symSetsWithoutVa\n");
                    $$ = (SELECTSTMT*)attribute_list_aggasop($1->info, $2, $3, $5);
                  }

                | symbolSet INVALID_CHAR symbolSet COMMA symSetsWithoutVa
                  {
                    if(debug_mode) printf("symSetWithoutVa: symbolSet INVALID_CHAR symbolSet COMMA symSetsWithoutVa\n");
                    $$ = (SELECTSTMT*)attribute_list_aggasop($1->info, $2, $3->info, $5);
                  }
                ;
                

operands:       
                VARIABLE
                  { 
                    if(debug_mode) printf("operands: VARIABLE\n");
                    $$=(SELECTSTMT*)operand_list($1, 'I');
                  }

                | VARIABLE INVALID_CHAR operands
                  {
                    if(debug_mode) printf("operands: VARIABLE INVALID_CHAR operands\n");
                    $$ = (SELECTSTMT* )operand_list_agg($1, $2, $3);
                  }
                ;
                

operand:        
                CONSTANT
                  { 
                    if(debug_mode) printf("operand: CONSTANT\n");
                    $$=(SELECTSTMT*)operand_list($1, 'E');
                  }
                | VARIABLE
                  {
                    if(debug_mode) printf("operand: VARIABLE\n");
                    $$=(SELECTSTMT*)operand_list($1, 'I');
                  }
                ;
                

havings:        
                SELECT havingvariables RELOP CONSTANT
                  {  
                    if(debug_mode) printf("havings: SELECT havingvariables RELOP CONSTANT\n");
                    $$ = (SELECTSTMT* )havingstmt($2, $3, $4);
                  }
                ;
                

havingvariables: 
                symbolSet
                  {
                    if(debug_mode) printf("havingvariables\n");
                    $$ = (SELECTSTMT* )addhavinglist(($1)->info, NULL, NULL);
                  }

                | symbolSet INVALID_CHAR havingvariables
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )addhavinglist(($1)->info, $2, $3);
                  }

                | VARIABLE INVALID_CHAR havingvariables
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )addhavinglist($1, $2, $3);
                  }
                ;
                

orderby:        
                ORDER BY orderbyvariables ASC
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )orderbystmt($3, $4);
                  }

                | ORDER BY orderbyvariables DESC
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )orderbystmt($3, $4);
                  }
                ;


orderbyvariables:
                symbolSet
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )addorderbylist(($1)->info, NULL, NULL);
                  }

                | VARIABLE
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )addorderbylist($1, NULL, NULL);
                  }

                | symbolSet INVALID_CHAR orderbyvariables
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )addorderbylist(($1)->info, $2, $3);
                  }

                | VARIABLE INVALID_CHAR orderbyvariables
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )addorderbylist($1, $2, $3);
                  }

                | VARIABLE COMMA orderbyvariables
                  {
                    if(debug_mode) printf("SEMI_COLON\n");
                    $$ = (SELECTSTMT* )addorderbylist($1, ",", $3);
                  }
                ;
%%

/* Offset in statement. */
int offset;

/* Flag if syntax error occurs. */
char f_stmterror = 'N';
#include "lex.yy.c"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


/* -----------------------------------------------
Function Name: yyerror
Purpose:       
  To print out an error message whenever a syntax error occurs.
Parameters:
	message       the message to be displayed
Return Values:
	None
------------------------------------------------- */
void yyerror(char *message)
{	
  offset = 0;
  if (strcmp(yytext, ";") != 0)
    f_stmterror = 'Y';
  printf(message);
}

/* -----------------------------------------------
Function Name: main
Purpose:       
  To connect to oracle, start the parser and disconnect from oracle when done
Parameters:
  None
Return Values:
  0             execution completed successfully
  1             error occurred
------------------------------------------------- */
int main()
{
  	
  char   *password = NULL;	
  char   user_id[MAXLENGTH];
  debug_mode = false;
  divideby_flag = 0;

  system("clear");
  printf("\nPlease enter SQLPlus username: ");
  scanf("%s", user_id);
  getchar();

  password=getpass("Please enter the password: ");
  
  /* Connect to the database. */
  if (oracle_connect(user_id, password) != 0)
  {
    exit(1);
  }
  system("clear");
 
  fprintf(stdout, "\n\t+------------------------------------------------------------+\n");
  fprintf(stdout, "\t|           Relational Algebra Interface to Oracle           |\n");
  fprintf(stdout, "\t|                  mengchi@scs.carleton.ca                   |\n");
  fprintf(stdout, "\t|                   For help, type 'help;'                   |\n");
  fprintf(stdout, "\t|                    To exit, type 'exit;'                   |\n");
  fprintf(stdout, "\t+------------------------------------------------------------+\n");

  while(1){
    fprintf(stdout, "\nALG> ");
    YY_FLUSH_BUFFER;
    f_stmterror = 'N';
    yyparse();
  }

  oracle_disconnect();
  return 0;
}
