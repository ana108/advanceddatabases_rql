/* *************************************************
Filename:   trc.l
Author:     Duojie Chang
Student#:   100809247
************************************************** */

#ifndef _TRC_H
#define _TRC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/*Max table.attribute length*/
#define  MAXLENGTH 60

/*Max sql statement length*/
#define  MAXSTMTLENGTH 1024

/*Max error message length */
#define MAXERRMSGLENGTH 255

#define TEMP_LOGIN_INFORMAYTION_FILE_NAME ".temp01192004"
#define REMOVE_COMMAND "rm -f "

int exist_flag, forall_flag, mult_exist_var_flag, or_flag;
int exist_flag_count;

int quantifier_error_flag;
int quantifier_error_display_flag;
int freevar_error_flag;
int layers;
int table_error_flag;
int not_exist_flag;


/* Linked list generic item
   Type can be:
	'A'	table.attribute
        'J'     join conditions like OR, AND, AND NOT.
	'V'	variable
	'T'	table
	't'	temporary table
	'U'	underscore
	'C'	constant
	'E'	element
	'O'	operator
	'X'	exist attribute
        'Q'     equation
*/

/*Linked list generic item*/

typedef struct listitem LIST_ITEM;
struct listitem
{
 char id[MAXSTMTLENGTH];
 char type;
 char aggregate[MAXSTMTLENGTH];
 char as[MAXSTMTLENGTH];
 LIST_ITEM *next;
 LIST_ITEM *prev;
 };


/*Structure for token attribute*/
typedef struct condlist LIST;
struct condlist
{
 LIST_ITEM *front;
 LIST_ITEM *back;
 int count;
 };

/*Structure for token attribute*/
typedef struct select SELECTSTMT;
struct select
{
   LIST *attributes;
   LIST *tables;
   LIST *conditions;
   LIST *orderby;

   LIST *freevars;

   char f_error;
   char errormsg[MAXERRMSGLENGTH];
};

void yyerror(char *message);

void  freeList(LIST*);
void  freeExpr(SELECTSTMT*);
void  printList(LIST*);
LIST* retrieve_columns();
LIST* retrieve_column_names(char*);
LIST* executesqlstmt(int, int, int);
void  oracle_disconnect();
int   oracle_connect(char*, char*);
int   alloc_descriptors(int, int, int);
int   set_bind_variables();
int   process_select_list();
void  help();
void  sql_error();
LIST* addToFront(char*, LIST*, char);
LIST* addtoback(char*, LIST*, char);
SELECTSTMT* addVarAttrs(char*, char*,SELECTSTMT*);
SELECTSTMT* addEqAttrs(SELECTSTMT*, SELECTSTMT*);
SELECTSTMT* addExistsVar(char*, SELECTSTMT *);
SELECTSTMT* addExistsVar2(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* addPar(char*, SELECTSTMT*, char*);
SELECTSTMT* addCondition(SELECTSTMT*, char*, SELECTSTMT*, int);
SELECTSTMT* addOperand(char*, char);
void dropTmpTables(char *);
LIST *mergeList(LIST*, LIST*);
SELECTSTMT* addAndFormula(SELECTSTMT*, char*, SELECTSTMT*);
SELECTSTMT* addRelationname(char*, char*, char*);
SELECTSTMT* addOrFormula(SELECTSTMT*, char*, SELECTSTMT*);
SELECTSTMT* join_relations(SELECTSTMT*, char*, SELECTSTMT*);
void buildexpression(SELECTSTMT*, SELECTSTMT*);
char* uppercase(char *);
void describeTable(char*);
void displayTable(char*);
void exeoracle(char*);
SELECTSTMT* addQuantifierForm();
int temptable_test(char*);
void assignQuery(char*);
void buildJoinSQLStmt(SELECTSTMT*, SELECTSTMT*);
int  table_test(char*);
int  searchlist(char *, LIST_ITEM *);
void parse_attribute(char *, char *);
int join_test(SELECTSTMT*, SELECTSTMT*);
void renameattribute(char*, SELECTSTMT*);
SELECTSTMT* addVarAttrs2(char *, char *, char *, SELECTSTMT *, char *);
LIST* addAggToFront(char *, char *, char *, LIST *, char);
SELECTSTMT* addHaving(char *, SELECTSTMT *, char *, SELECTSTMT *);
SELECTSTMT* addOrder(char *, char *, SELECTSTMT *,char *);
SELECTSTMT* addEqOrder(SELECTSTMT*,char*,SELECTSTMT *);
void combine(SELECTSTMT *);
SELECTSTMT* addEquation(SELECTSTMT*,char*,SELECTSTMT*,int);
#endif
