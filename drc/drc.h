/* *************************************************
Filename:   drc.h
Author:     Yan Li
Student#:   100679284
Class:      COMP 5305
************************************************** */

#ifndef _DRC_H
#define _DRC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/* Max table.attribute length */
#define MAXLENGTH 5120

/* Max sql statement length */
#define MAXSTMTLENGTH 10240

/*Max error message length */
#define MAXERRMSGLENGTH 255

#define TEMP_LOGIN_INFORMAYTION_FILE_NAME ".temp01192004"
#define REMOVE_COMMAND "rm -f "

extern int yylineno;
//void yyerror(char *s, ...);
extern FILE *yyin, *yyout;		

/* Linked list generic item
 Type can be:
	'A'	table.attribute
	'V'	variable
	'N' variable(not)
	'T'	table
	't'	temporary table
	'U'	underscore
	'C'	constant
	'E'	element
	'O'	operator
	'Q' quantifier
*/
typedef struct listitem LIST_ITEM;
struct listitem
{
	LIST_ITEM *next;
	LIST_ITEM *prev;
	char type;
	char id[MAXLENGTH];
	char element[MAXLENGTH]; 
	char alias[MAXLENGTH];
	int	forall;
	int quantified;
   int not_flag;
};

/* Structure for linked lists */
typedef struct condlist LIST;
struct condlist
{
	int        count;
	LIST_ITEM* front;
	LIST_ITEM* back;
};
/* Structure for token attribute */
//typedef struct select SELECTSTMT;
//struct select
typedef struct select SELECTSTMT;
struct select
{
	LIST *attributes;
	LIST *tables;
	LIST *conditions;
	LIST *orConditions;
	LIST *groupby;
	LIST *having;
	LIST *orderby;
	char f_error;
	char errormsg[MAXERRMSGLENGTH];
	char info[MAXLENGTH];

    LIST *opattributes;     /*select clause with only variables*/
	LIST *aggregates;		/* select clause */
	LIST *pre;
	int  Lcase; 
	
	int unionCase;			/*for union case*/
	int minusCase;			/*for minus case*/
	int forall;				/*for forall case*/
	int preCase;			/*no pre-condition in formular if it is 10*/
	
};
/* case define
Lcase: 0 basic
            1 aggregates
	 2 opperation
	 3 basic + aggregates
	 4 basic + opperation 
	 5 aggregates + opperation
	 6 all

Rcase:
*/

/* Function prototypes */
SELECTSTMT* andConditionTreat(SELECTSTMT*, SELECTSTMT*, SELECTSTMT*);
SELECTSTMT* conditionTreat(SELECTSTMT*, SELECTSTMT*);
SELECTSTMT* doubleVariableList(char *, char *, char *, char *, char *);
SELECTSTMT* newElements(char*, SELECTSTMT*);
SELECTSTMT* operandList(char *, char );
SELECTSTMT* orConditionTreat(SELECTSTMT*, SELECTSTMT*, SELECTSTMT*);
SELECTSTMT* orderList(char *, char *, SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* preList(char*, SELECTSTMT*);
SELECTSTMT* preListForAll(SELECTSTMT*);
SELECTSTMT* processAndForm(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* processAndNotForm(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* processOrForm(SELECTSTMT*, SELECTSTMT*); 
SELECTSTMT* processEnding(SELECTSTMT *);
SELECTSTMT* processQuery(char *, SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* processSubForm(char *, SELECTSTMT*);
SELECTSTMT* proCondition(SELECTSTMT*, SELECTSTMT*);
SELECTSTMT* proList(char*, char*, char*, char*, char*, SELECTSTMT*, SELECTSTMT*, int);
SELECTSTMT*	stringList(char*, char*, char*, char*);
SELECTSTMT* tempTable(char*, SELECTSTMT*);
SELECTSTMT* variableList(char *, char *, char *, SELECTSTMT *, char *);
SELECTSTMT* varconList(char *, SELECTSTMT*, char );

LIST_ITEM*	searchList(char *, LIST *);

LIST*   addToBack(char *, LIST *, char );
LIST*	addTwoToBack(char *, char *, LIST *, char);
LIST*	addToFront(char *, LIST *, char );
LIST*   addToList(char *, LIST *, char );
LIST*	retrieveColumns();
LIST*	retrieveColumnNames(char *);
LIST*	copyList(LIST *);
LIST*	mergeList(LIST *, LIST *);
LIST*	executeSql(char*, char, int);



void    buildSqlStmt(char *, SELECTSTMT *);
void 	buildSqlStmtwithForall(char *, SELECTSTMT *);
void	createOrString(char *, LIST_ITEM *, int);
void	createSqlStmt(char *, SELECTSTMT *, SELECTSTMT *);
void    createString(char *, LIST_ITEM *, int);
void 	createTable(SELECTSTMT *, SELECTSTMT *, SELECTSTMT *);
void 	describeTable(char *);
void 	displayTable(char *);
void 	dropTable(char *);
void	executesql(SELECTSTMT*);
void 	executeSelectStruct(SELECTSTMT *, SELECTSTMT *);
void    freeexpr(SELECTSTMT *expr);
void    freelist(LIST *);
void    lowercase(char *);
void   	process_select_list();
void   	set_bind_variables();
void    uppercase(char *); 
void 	parseTableName(char *, char *);
void   	oracle_disconnect();
void	sql_error();

int    	alloc_descriptors();
int    	oracle_connect(char*, char*);

//int 	variableBinding(LIST *, LIST *, LIST *);
//void 	tableBinding(SELECTSTMT *, LIST *);
//void 	conditionBinding(SELECTSTMT *, LIST *, LIST *);
//void 	generate_temp_table_name(char* );
//void 	delete_temp_tables();
//void          dropTmpTables(char *);
//void	caseSet(SELECTSTMT *, int, int)
//void 	attributeBinding(SELECTSTMT *, LIST *, LIST *);
//LIST*   executesqlstmt(char*, char, int);
//LIST*   retrieve_columns();
//LIST*   retrieve_column_names(char *);
//SELECTSTMT* attribute_list(char *, SELECTSTMT *);
//LIST*   addElement(char *, LIST *);
#endif

