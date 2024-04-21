#ifndef ALG_H
#define ALG_H

/* ***************************************************************************
Original Filename:   relalg.h
Current Filename:    alg.h
Revision Date:       Not Specified
Author:              Jaret Funk
Student#:            194-6-02491
Course:              CS 470-001
Date:                19 April 1999

Maintenance:
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

Purpose:
  Relational algebra converter header file containing protypes for functions 
  used by the converter and definitions of data structures used by the 
  converter.
****************************************************************************** */

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/* Max table.attribute length */
#define MAXLENGTH 60

/* Max sql statement length */
#define MAXSTMTLENGTH 1024

/*Max error message length */
#define MAXERRMSGLENGTH 255

//Global flag used to indicate that a DIVIDEBY operation will be conducted.
int divideby_flag;

//DEPRECATED.
//Global flag used to indicate that a select statement be constructed in a 
//set operation.
int sql_flag;

//Global flag used to indicate whether debug mode is active.
bool debug_mode;

/* 
  Linked list generic item.
  
  next: Pointer to next list item.
  prev: Pointer to previous list item.
  type:
	  'I'	attribute
	  'T'	table
	  'E'	element
  id: Array used to hold the value of the element.
*/
typedef struct listitem LIST_ITEM;
struct listitem
{
  LIST_ITEM* next;
  LIST_ITEM* prev;
  char type;
  char id[MAXLENGTH];
};

/*
  Structure for linked lists.

  count: Used to hold the number of elements in the list.
  front: Pointer to the element at the front of the list.
  back: Pointer to the leement at the back of the list.
*/
typedef struct condlist LIST;
struct condlist
{
  int count;
  LIST_ITEM* front;
  LIST_ITEM* back;
};

/*
  Structure for token attribute.

  attributes: Pointer to structure holding information about attributes 
              involved in the statement.
  tables:     Pointer to structure holding information about tables 
              involved in the statement.
  conditions: Pointer to structure holding information about conditions 
              involved in the statement.
  groupby:    Pointer to structure holding information about the groupby 
              portion of the statement.
  having:     Pointer to structure holding information about the having 
              portion of the statement.
  orderby:    Pointer to structure holding information about the orderby 
              portion of the statement.
  f_error:    Character used to flag whether an error occurred during the 
              processing or formation of the statement.
  errormsg:   Array used to store the error message relevant to an error 
              that occurred during the processing or formation of the 
              statement.
  info:       Array used to store various types of information useful to 
              the processing or formation of the statement.
*/
typedef struct select SELECTSTMT;
struct select
{
  LIST* attributes;
  LIST* tables;
  LIST* conditions;
  LIST* groupby;
  LIST* having;
  LIST* orderby;
  char f_error;
  char errormsg[MAXERRMSGLENGTH];
  char info[MAXLENGTH];
};

/* Function prototypes */
/* See alg.pc for function descriptions. */
void        addattributes(char *, SELECTSTMT *);
void        add_outerjoin_stmt(SELECTSTMT*, char*);
void        assignQuery(char*, SELECTSTMT*, int, int);
void        buildselectstmt(char *, SELECTSTMT *);
void        buildSqlStmt(char *, SELECTSTMT *);
void        createstring(char *, LIST_ITEM *);
void        createString(char *, LIST_ITEM *);
void        describestatement(char *);
void        dropTmpTables(char *);
void        executesql(SELECTSTMT*);
void        executesqltable(SELECTSTMT *, char *, char );
void        freeexpr(SELECTSTMT *expr);
void        lowercase(char *);
void        oracle_disconnect();
void        parse_attribute(char *, char *);
void        removeFromBack(char*, LIST*);
void        renameattribute(char*, SELECTSTMT*, SELECTSTMT*, int, int);
void        set_bind_variables();
void        uppercase(char *); 
void        yyerror(char *);
SELECTSTMT* addOperand(char* , char);
SELECTSTMT* addRelation(char*);
SELECTSTMT* aggregatestmt(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* andcond_list(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* attribute_list(char *, SELECTSTMT *);
SELECTSTMT* binaryopstmt(SELECTSTMT *, char* , SELECTSTMT *);
SELECTSTMT* condition_list(SELECTSTMT *andcondlist, SELECTSTMT *condlist);
SELECTSTMT* dividebystmt(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* findattribute(char* , char* );
SELECTSTMT* joinstmt(SELECTSTMT *, SELECTSTMT *, char *, char *, char *);
SELECTSTMT* njoinstmt(SELECTSTMT*, SELECTSTMT*, char*);
SELECTSTMT* operand_list(char *, char );
SELECTSTMT* productstmt(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* projectstmt(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* rel_formula1(SELECTSTMT *, char *, SELECTSTMT *);
SELECTSTMT* rel_formula2(SELECTSTMT *);
SELECTSTMT* retrieveattribute(char* );
SELECTSTMT* selectstmt(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* setopstmt(SELECTSTMT *, char* , SELECTSTMT *);
LIST*       common_join_att(LIST_ITEM *, LIST_ITEM *, char *);
LIST*       executesqlstmt(char*, char, int);
LIST*       retrieve_columns();
LIST*       retrieve_column_names(char *);
int         alloc_descriptors();
int         compare_attribute(char*, char*);
int         oracle_connect(char*, char*);
int         process_select_list();
int         strsearch(char*, char);
int         temptable_test(char* );
char        duplicate_att(LIST_ITEM *, LIST_ITEM *, char *);

/* Methods for LIST manipulation */
void        addToRenBack(char*);
void        freelist(LIST *);
void        printList_i(LIST *);
void        remove_attribute(LIST*, LIST_ITEM*);
LIST*       addtoback(char *, LIST *, char );
LIST*       addtolist(char *, LIST *, char );
LIST*       mergelist(LIST *, LIST *);
LIST*       ordered_lists(LIST *, LIST *);
int         find_duplicated_column(SELECTSTMT*);
int         remove_duplicated_column(SELECTSTMT*);
int         searchlist(char *, LIST_ITEM *);
char        addtablename(char *, LIST_ITEM *, char *);
char        addptablename(LIST_ITEM *, LIST_ITEM *, char *);
char        compare_lists(LIST *, LIST *, char *);

/* Methods to deal with the temporary tables */
void        addToRenList(char*);
void        delete_temp_tables();
void        generate_temp_table_name(char*);
void        delete_ren_tables();

/* Methods to deal with the aggregate */
SELECTSTMT* addhavinglist(char*, char*, SELECTSTMT*);
SELECTSTMT* addorderbylist(char*, char*, SELECTSTMT*);
SELECTSTMT* attribute_list_agg(SELECTSTMT *, SELECTSTMT *);
SELECTSTMT* attribute_list_aggasop(char*, char*, char*, SELECTSTMT*);
SELECTSTMT* attribute_list_asop(char*, char*, char*, SELECTSTMT*);
SELECTSTMT* getSymbSetString_agg(char *, char *);
SELECTSTMT* havingstmt(SELECTSTMT*, char*, char*);
SELECTSTMT* orderbyhavingstmt(SELECTSTMT*, SELECTSTMT*, SELECTSTMT*);
SELECTSTMT* orderbystmt(SELECTSTMT*, char*);
char        addtablename_agg(char *, LIST_ITEM *, char *);
char        addptablename_agg(LIST_ITEM *, LIST_ITEM *, char *);
#endif
