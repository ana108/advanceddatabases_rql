
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[7];
};
static struct sqlcxp sqlfpn =
{
    6,
    "drc.pc"
};


static unsigned int sqlctx = 4435;


static struct sqlexd {
   unsigned long  sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
            short *cud;
   unsigned char  *sqlest;
            char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
   unsigned char  **sqphsv;
   unsigned long  *sqphsl;
            int   *sqphss;
            short **sqpind;
            int   *sqpins;
   unsigned long  *sqparm;
   unsigned long  **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
            int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
   unsigned char  *sqhstv[4];
   unsigned long  sqhstl[4];
            int   sqhsts[4];
            short *sqindv[4];
            int   sqinds[4];
   unsigned long  sqharm[4];
   unsigned long  *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {12,4};

/* SQLLIB Prototypes */
extern sqlcxt ( void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * );
extern sqlcx2t( void **, unsigned int *,
                   struct sqlexd *, struct sqlcxp * );
extern sqlbuft( void **, char * );
extern sqlgs2t( void **, char * );
extern sqlorat( void **, unsigned int *, void * );

/* Forms Interface */
static int IAPSUCC = 0;
static int IAPFAIL = 1403;
static int IAPFTL  = 535;
extern void sqliem( unsigned char *, signed int * );

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

/* CUD (Compilation Unit Data) Array */
static short sqlcud0[] =
{12,4130,873,0,0,
5,0,0,1,0,0,17,849,0,0,1,1,0,1,0,1,5,0,0,
24,0,0,1,0,0,11,853,0,0,1,1,0,1,0,1,32,0,0,
43,0,0,1,0,0,20,900,0,0,1,1,0,1,0,3,32,0,0,
62,0,0,1,0,0,14,913,0,0,1,0,0,1,0,2,32,0,0,
81,0,0,2,0,0,31,2589,0,0,0,0,0,1,0,
96,0,0,1,0,0,15,2616,0,0,0,0,0,1,0,
111,0,0,3,0,0,30,2617,0,0,0,0,0,1,0,
126,0,0,0,0,0,27,2642,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
157,0,0,1,0,0,19,2704,0,0,1,1,0,1,0,3,32,0,0,
176,0,0,1,0,0,20,2742,0,0,1,1,0,1,0,3,32,0,0,
195,0,0,1,0,0,14,2809,0,0,1,0,0,1,0,2,32,0,0,
};


/* *************************************************
Filename:   drc.pc
Author:     Yan Li
Student#:   100679284
Class:      COMP 5305
************************************************** */
#include "drc.h"
#include <setjmp.h>
/* Maximum number of select-list items or variables. */
#define MAX_ITEMS 40
/* Maximum lengths of the _names_ of the
   select-list items or indicator variables. */
#define MAX_VNAME_LEN 30
#define MAX_INAME_LEN 30
#ifndef NULL
#define NULL 0
#endif
char *dml_commands[] = {"SELECT", "select", "INSERT", "insert","UPDATE", "update", "DELETE", "delete"}; 
/* exec sql begin declare section; */ 

	char sql_statement[1024] = {'\0'};
/* exec sql var sql_statement is string(1024); */ 

/* exec sql end declare section; */ 

/* exec sql include sqlca;
 */ 
/*
 * $Header: sqlca.h 24-apr-2003.12:50:58 mkandarp Exp $ sqlca.h 
 */

/* Copyright (c) 1985, 2003, Oracle Corporation.  All rights reserved.  */
 
/*
NAME
  SQLCA : SQL Communications Area.
FUNCTION
  Contains no code. Oracle fills in the SQLCA with status info
  during the execution of a SQL stmt.
NOTES
  **************************************************************
  ***                                                        ***
  *** This file is SOSD.  Porters must change the data types ***
  *** appropriately on their platform.  See notes/pcport.doc ***
  *** for more information.                                  ***
  ***                                                        ***
  **************************************************************

  If the symbol SQLCA_STORAGE_CLASS is defined, then the SQLCA
  will be defined to have this storage class. For example:
 
    #define SQLCA_STORAGE_CLASS extern
 
  will define the SQLCA as an extern.
 
  If the symbol SQLCA_INIT is defined, then the SQLCA will be
  statically initialized. Although this is not necessary in order
  to use the SQLCA, it is a good pgming practice not to have
  unitialized variables. However, some C compilers/OS's don't
  allow automatic variables to be init'd in this manner. Therefore,
  if you are INCLUDE'ing the SQLCA in a place where it would be
  an automatic AND your C compiler/OS doesn't allow this style
  of initialization, then SQLCA_INIT should be left undefined --
  all others can define SQLCA_INIT if they wish.

  If the symbol SQLCA_NONE is defined, then the SQLCA variable will
  not be defined at all.  The symbol SQLCA_NONE should not be defined
  in source modules that have embedded SQL.  However, source modules
  that have no embedded SQL, but need to manipulate a sqlca struct
  passed in as a parameter, can set the SQLCA_NONE symbol to avoid
  creation of an extraneous sqlca variable.
 
MODIFIED
    lvbcheng   07/31/98 -  long to int
    jbasu      12/12/94 -  Bug 217878: note this is an SOSD file
    losborne   08/11/92 -  No sqlca var if SQLCA_NONE macro set 
  Clare      12/06/84 - Ch SQLCA to not be an extern.
  Clare      10/21/85 - Add initialization.
  Bradbury   01/05/86 - Only initialize when SQLCA_INIT set
  Clare      06/12/86 - Add SQLCA_STORAGE_CLASS option.
*/
 
#ifndef SQLCA
#define SQLCA 1
 
struct   sqlca
         {
         /* ub1 */ char    sqlcaid[8];
         /* b4  */ int     sqlabc;
         /* b4  */ int     sqlcode;
         struct
           {
           /* ub2 */ unsigned short sqlerrml;
           /* ub1 */ char           sqlerrmc[70];
           } sqlerrm;
         /* ub1 */ char    sqlerrp[8];
         /* b4  */ int     sqlerrd[6];
         /* ub1 */ char    sqlwarn[8];
         /* ub1 */ char    sqlext[8];
         };

#ifndef SQLCA_NONE 
#ifdef   SQLCA_STORAGE_CLASS
SQLCA_STORAGE_CLASS struct sqlca sqlca
#else
         struct sqlca sqlca
#endif
 
#ifdef  SQLCA_INIT
         = {
         {'S', 'Q', 'L', 'C', 'A', ' ', ' ', ' '},
         sizeof(struct sqlca),
         0,
         { 0, {0}},
         {'N', 'O', 'T', ' ', 'S', 'E', 'T', ' '},
         {0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}
         }
#endif
         ;
#endif
 
#endif
 
/* end SQLCA */
/* exec sql include sqlda;
 */ 
/*
 * $Header: sqlda.h 08-may-2007.05:58:33 ardesai Exp $ sqlda.h 
 */

/***************************************************************
*      The SQLDA descriptor definition                         *
*--------------------------------------------------------------*
*      VAX/3B Version                                          *
*                                                              *
* Copyright (c) 1987, 2007, Oracle. All rights reserved.  *
***************************************************************/


/* NOTES
  **************************************************************
  ***                                                        ***
  *** This file is SOSD.  Porters must change the data types ***
  *** appropriately on their platform.  See notes/pcport.doc ***
  *** for more information.                                  ***
  ***                                                        ***
  **************************************************************
*/

/*  MODIFIED
    ardesai    05/08/07  - Bug[6037057] Undef Y
    apopat     05/08/02  - [2362423] MVS PE to make lines shorter than 79
    apopat     07/31/99 -  [707588] TAB to blanks for OCCS
    lvbcheng   10/27/98 -  change long to int for sqlda
    lvbcheng   08/15/97 -  Move sqlda protos to sqlcpr.h
    lvbcheng   06/25/97 -  Move sqlda protos to this file
    jbasu      01/29/95 -  correct typo
    jbasu      01/27/95 -  correct comment - ub2->sb2
    jbasu      12/12/94 - Bug 217878: note this is an SOSD file
    Morse      12/01/87 - undef L and S for v6 include files
    Richey     07/13/87 - change int defs to long 
    Clare      09/13/84 - Port: Ch types to match SQLLIB structs
    Clare      10/02/86 - Add ifndef SQLDA
*/

#ifndef SQLDA_
#define SQLDA_ 1
 
#ifdef T
# undef T
#endif
#ifdef F
# undef F
#endif

#ifdef S
# undef S
#endif
#ifdef L
# undef L
#endif

#ifdef Y
 # undef Y
#endif
 
struct SQLDA {
  /* ub4    */ int        N; /* Descriptor size in number of entries        */
  /* text** */ char     **V; /* Ptr to Arr of addresses of main variables   */
  /* ub4*   */ int       *L; /* Ptr to Arr of lengths of buffers            */
  /* sb2*   */ short     *T; /* Ptr to Arr of types of buffers              */
  /* sb2**  */ short    **I; /* Ptr to Arr of addresses of indicator vars   */
  /* sb4    */ int        F; /* Number of variables found by DESCRIBE       */
  /* text** */ char     **S; /* Ptr to Arr of variable name pointers        */
  /* ub2*   */ short     *M; /* Ptr to Arr of max lengths of var. names     */
  /* ub2*   */ short     *C; /* Ptr to Arr of current lengths of var. names */
  /* text** */ char     **X; /* Ptr to Arr of ind. var. name pointers       */
  /* ub2*   */ short     *Y; /* Ptr to Arr of max lengths of ind. var. names*/
  /* ub2*   */ short     *Z; /* Ptr to Arr of cur lengths of ind. var. names*/
  };
 
typedef struct SQLDA SQLDA;
 
#endif

/* ----------------- */
/* defines for sqlda */
/* ----------------- */

#define SQLSQLDAAlloc(arg1, arg2, arg3, arg4) sqlaldt(arg1, arg2, arg3, arg4) 

#define SQLSQLDAFree(arg1, arg2) sqlclut(arg1, arg2) 




SQLDA *bind_dp;
SQLDA *select_dp;
extern SQLDA *sqlald();
extern void sqlnul();
/* File pointers to be used for input and output to the interpreter. */
//extern FILE *yyin, *yyout;  

/* Define a buffer to hold longjmp state info. */
jmp_buf jmp_continue;
/* A global flag for the error routine. */
int  parse_flag = 0;
char f_oracle_error = 'F';
LIST *temp_table_list = NULL; 

/* --------------------------------------------------------------Begin-------------------------------------------------------------------------- */
/*					Statement function
	1. displayTable
	2. dropTable
	3. describeTable
	4. 

*/
/* ------------------------------------------------------------------------------------------------
Function name: displayTable
Purpose: To display the info of the specified table.
Parameters (tablename): name of the table
Display: information in table (= select * from tablename)
Returns: nothing
-------------------------------------------------------------------------------------------------*/
void displayTable(char *tablename)
{	
	if (retrieveColumnNames(tablename) != NULL)
	{
		char sqlStmt[MAXSTMTLENGTH] = {'\0'};
		char temp[] = "select * from ";
		strncpy(sqlStmt, temp, strlen(temp));
		uppercase(tablename);
		strncat(sqlStmt, tablename, strlen(tablename));
		executeSql(sqlStmt, 'Y', 0);
	}
	else
	{
		fprintf(stdout, "Table %s does not exists in the database\n", tablename);
	}
}

/* ------------------------------------------------------------------------------------------------
Function name: dropTable
Purpose:	drop created table 
Parameters (tablename): name of the table
Returns:	none
-------------------------------------------------------------------------------------------------*/
void dropTable(char* tablename)
{
	if (retrieveColumnNames(tablename) != NULL)
	{
		char sqlStmt[MAXSTMTLENGTH] = {'\0'};
		char temp[] = "drop table ";
		strncpy(sqlStmt, temp, strlen(temp));
		uppercase(tablename);
		strncat(sqlStmt, tablename, strlen(tablename));
		executeSql(sqlStmt, 'Y', 0);
		fprintf(stderr, "Table is dropped.\n");
	}
	else
	{
		fprintf(stdout, "Table %s does not exists in the database\n", tablename);
	}
}

/* ------------------------------------------------------------------------------------------------
Function name: describeTable
Purpose: To display the schema of the specified table.
Parameters: tablename: name of the table
Returns: nothing
-------------------------------------------------------------------------------------------------*/
void describeTable(char *tablename)
{
	if (retrieveColumnNames(tablename) != NULL)
	{
		char sqlStmt[MAXSTMTLENGTH] = {'\0'};
		char temp[] = "select column_name, nullable, data_type, data_length, data_precision, data_scale from user_tab_columns where table_name = '";
		strncpy(sqlStmt, temp, strlen(temp));
		uppercase(tablename);
		strcat(sqlStmt, tablename);
		strcat(sqlStmt, "'\n");
		executeSql(sqlStmt, 'Y', 0);
	}
	else
	{
		fprintf(stdout, "Table %s does not exists in the database\n", tablename);
	}
}

/* --------------------------------------------------------------------------------------------------------------------
Function name: executeSelectStruct
Purpose:	Execute a select structure by translating it to a SQL statement
Parameters: selectStruct: the query to be executed endingStruct: the ending structure to be combined with query
Returns:	nothing
----------------------------------------------------------------------------------------------------------------------*/
void executeSelectStruct(SELECTSTMT *selectStruct, SELECTSTMT * endingStruct)
{
	char sqlStmt[MAXSTMTLENGTH] = {'\0'};
	if (selectStruct == NULL) 
	{
   		fprintf(stdout, "Empty query\n");
		fprintf(stdout, "\nDRC> ");
		freeexpr(selectStruct);
		//free(selectStruct);
		freeexpr(endingStruct);
		if (endingStruct != NULL)
		{
			free(endingStruct);
		}
   		return;
 	}
	if(selectStruct ->f_error == 'E') 
	{
		fprintf(stdout, "\n%s\n", selectStruct->errormsg);
		fprintf(stdout, "\nDRC> ");
		freeexpr(selectStruct);
		freeexpr(endingStruct);
		if (endingStruct != NULL)
		{
			free(endingStruct);
		}
		return;
	}
	if(endingStruct == NULL)
	{
		if (selectStruct->forall !=10)
		{
			buildSqlStmt(sqlStmt, selectStruct);
		}
		else
		{
			buildSqlStmtwithForall(sqlStmt,selectStruct);
		}
		executeSql(sqlStmt, 'Y', 0);
	}
	else if(endingStruct ->f_error == 'E')
	{
		fprintf(stdout, "\n%s\n", endingStruct->errormsg);
		fprintf(stdout, "\nDRC> ");
		freeexpr(selectStruct);
		free(selectStruct);
		freeexpr(endingStruct);
		free(endingStruct);
		return;
	}
	else
	{
        LIST_ITEM* orderby =  endingStruct->orderby->front;
		LIST_ITEM* foratt;
		LIST_ITEM* foragg;
		LIST_ITEM* foropp;
		int check = 0;
		while (orderby != NULL) {
			check = 0;
			foratt = selectStruct->attributes->front;
			if (selectStruct->aggregates != NULL) {
				foragg = selectStruct->aggregates->front;
			}
			else {
				foragg = NULL;
			}
			if (selectStruct->opattributes != NULL) {
				foropp = selectStruct->opattributes->front;
			}
			else {
				foropp = NULL;
			}			
			char *pch;
			pch = (char*) calloc(20, sizeof(char));
			if (pch == NULL) {
				fprintf(stderr, "Not enough memory to allocate this time, please rerun program again!\n");
				exit(1);
			}
			char temp[64] = {'\0'};
			strncpy(temp, orderby->id, strlen(orderby->id));
			pch = strtok(temp, " ");
			char end[64] = {'\0'};
			while (foratt != NULL) {
				
				if (pch == NULL) {
					fprintf(stderr, "1\n");
					exit(1);
				}
				
				if (strncmp(pch, foratt->alias, strlen(pch)) == 0 && strncmp(pch, foratt->alias, strlen(foratt->alias)) == 0) { 
					strncpy(end, foratt->id, strlen(foratt->id));
					strncat(end, " ", 1);
					pch = strtok(NULL, " ");
					
					if (pch == NULL) {
					fprintf(stderr, "1\n");
					exit(1);
					}
					
					strncat(end, pch, strlen(pch));
					strncpy(orderby->id, end, strlen(end));
					(orderby->id)[strlen(end)] = '\0';
					break;
				}
				foratt= foratt->next;
			}
			/*
			if (pch != NULL) {
				free(pch);
			}
			*/
			//if (check == 0)
			//{
				char *pch_agg;
				pch_agg = (char*) calloc(20, sizeof(char));
				if (pch_agg == NULL) {
					fprintf(stderr, "Not enough memory to allocate this time, please rerun program again!\n");
					exit(1);
				}
				char tempagg[64] = {'\0'};
				char lastagg[64] = {'\0'};
				strncpy(tempagg, orderby->id, strlen(orderby->id));
				pch_agg = strtok(tempagg, " ");
				while (foragg != NULL) {
					if (strncmp(pch_agg, foragg->alias, strlen(pch_agg)) == 0 && strncmp(pch_agg, foragg->alias, strlen(foragg->alias)) == 0) {
						strncpy(lastagg, foragg->id, strlen(foragg->id));
						strncat(lastagg, " ", 1);
						pch_agg = strtok(NULL, " ");
						strncat(lastagg, pch_agg, strlen(pch_agg));
						strncpy(orderby->id, lastagg, strlen(lastagg));
						(orderby->id)[strlen(lastagg)] = '\0';
						//check = 1;
						break;
					}
					foragg = foragg->next;
				}
				/*
				if (pch_agg != NULL) {
					free(pch_agg);
				}
				*/
			//}
			//if (check == 0)
			//{
				char *pch_opp;
				pch_opp = (char*) calloc(20, sizeof(char));
				if (pch_opp == NULL) {
					fprintf(stderr, "Not enough memory to allocate this time, please rerun program again!\n");
					exit(1);
				}
				char tempopp[64] = {'\0'};
				char lastopp[64] = {'\0'};
				strncpy(tempopp, orderby->id, strlen(orderby->id));
				pch_opp = strtok(tempopp, " ");
				while (foropp != NULL) {				
					if (strncmp(pch_opp, foropp->alias, strlen(pch_opp)) == 0 && strncmp(pch_opp, foropp->alias, strlen(foropp->alias)) == 0) {
						strncpy(lastopp, foropp->id, strlen(foropp->id));
						strncat(lastopp, " ", 1);
						pch_opp = strtok(NULL, " ");
						
						if (pch_opp == NULL) {
							fprintf(stderr, "3\n");
							exit(1);
						}
						
						strncat(lastopp, pch_opp, strlen(pch_opp));
						strncpy(orderby->id, lastopp, strlen(lastopp));
						(orderby->id)[strlen(lastopp)] = '\0';
						check = 1;
						break;
					}
					foropp = foropp->next;
				}
				/*
				if (pch_opp != NULL) {
					free(pch_opp);
				}
				*/
			//}
			if (check == 0) {
				char opp[3] = {'\0'};
				char order[5] = {'\0'};
				char current[64] = {'\0'};
				char final[64] = {'\0'};
				strncpy(current, orderby->id, strlen(orderby->id));
				char *pch_curr;
				pch_curr = (char*) calloc(20, sizeof(char));
				if (pch_curr == NULL) {
					fprintf(stderr, "Not enough memory to allocate this time, please rerun program again!\n");
					exit(1);
				}
				pch_curr = strtok(current, " ");
				char result[48] = {'\0'};
				
				strncpy(result, pch_curr, strlen(pch_curr));
				if(strstr(result, "+") != NULL) {
					opp[0] = '+';
				}
				else if (strstr(result, "-") != NULL) {
					opp[0] = '-';
				}
				else if (strstr(result, "*") != NULL) {
					opp[0] = '*';
				}
				else if (strstr(result, "/") != NULL){
					opp[0] = '/';
				}
				
				if (opp[0] != '\0') {
				
					pch_curr = strtok(NULL, " ");	
					strncpy(order, pch_curr, strlen(pch_curr));
					char *pch_result;
					pch_result = (char*) calloc(20, sizeof(char));
					if (pch_result == NULL) {
						fprintf(stderr, "Not enough memory to allocate this time, please rerun program again!\n");
						exit(1);
					}
					pch_result = strtok(result, "+-*/");
					foratt = selectStruct->attributes->front;
					while(foratt != NULL) {
						if (strncmp(pch_result, foratt->alias, strlen(pch_result)) == 0 && strncmp(pch_result, foratt->alias, strlen(foratt->alias)) == 0) { 
							strncat(final, foratt->id, strlen(foratt->id));
							strncat(final, opp, 1);
							break;
						}
						foratt= foratt->next;
					}
					pch_result = strtok(NULL, "+-*/");
					foratt = selectStruct->attributes->front;
					while(foratt != NULL) {					
						if (strncmp(pch_result, foratt->alias, strlen(pch_result)) == 0 && strncmp(pch_result, foratt->alias, strlen(foratt->alias)) == 0) { 
							strncat(final, foratt->id, strlen(foratt->id));
							break;
						}
						foratt= foratt->next;
					}
					strncat(final, " ", 1);
					strncat(final, order, strlen(order));
					strncpy(orderby->id, final, strlen(final));
					(orderby->id)[strlen(final)] = '\0';
					/*
					if (pch_result != NULL) {
						free(pch_result);
					}
					if (pch_curr != NULL) {
						free(pch_curr);
					}
					*/
				//check = 1;
				}
			}		
			
			orderby = orderby->next;
		}
		
		selectStruct->orderby = endingStruct->orderby;
		if (selectStruct->forall !=10)
		{
			buildSqlStmt(sqlStmt, selectStruct);
		}
		
		else
		{
			buildSqlStmtwithForall(sqlStmt,selectStruct);
		}
		/**/
		executeSql(sqlStmt, 'Y', 0);
	}
  	fprintf(stdout, "\nDRC> ");
	freeexpr(selectStruct);
	free(selectStruct);
	freeexpr(endingStruct);
	free(endingStruct);
	
}

/*-------------------------------------------------------------
Function name: buildSqlStmt
Purpose: To build the select statement string for the select statement in the select structure.
Parameters: sqlStmt: string the sql statement is to be put in
	         SELECTSTMT: structure containing the select statement
Returns: nothing
------------------------------------------------------------- */
void buildSqlStmt(char *sqlStmt, SELECTSTMT *selectStruct)
{
	//printf("*buildsqlstmt\n");
	if (selectStruct == NULL)
	{
		return;
	}
	if (selectStruct->unionCase == 0 && selectStruct->minusCase == 0)
	{
		strcpy(sqlStmt, "SELECT DISTINCT ");
		if (selectStruct->attributes != NULL) 
		{
			createString(sqlStmt, selectStruct->attributes->front, 0);
			if (selectStruct->aggregates != NULL) {
				strcat(sqlStmt, " , ");
				createString(sqlStmt, selectStruct->aggregates->front, 0);
				selectStruct->groupby = selectStruct->attributes;
				if (selectStruct->opattributes != NULL){
					selectStruct->opattributes->count = 1;
				}
			}
			if (selectStruct->opattributes != NULL) {
				strcat(sqlStmt, " , ");
				createString(sqlStmt, selectStruct->opattributes->front, 0);
				if (selectStruct->opattributes->count == -1)
				{
					selectStruct->groupby = selectStruct->attributes;
				}
			}		
		}
		else {
			if (selectStruct->aggregates != NULL && selectStruct->opattributes != NULL) {
				createString(sqlStmt, selectStruct->aggregates->front, 0);
				strcat(sqlStmt, " , ");
				createString(sqlStmt, selectStruct->opattributes->front, 0);
			} 
			else {
				if (selectStruct->aggregates != NULL)
					createString(sqlStmt, selectStruct->aggregates->front, 0);
				else {
					if (selectStruct->opattributes != NULL)
						createString(sqlStmt, selectStruct->opattributes->front, 0);
					else 
						strcat(sqlStmt, "*");
				}
			}
		}
		strcat(sqlStmt, "\n  FROM ");
		if (selectStruct->tables == NULL)
		{
			return;
		}
		createString(sqlStmt, selectStruct->tables->front, 0);
		if (selectStruct->conditions != NULL)
		{
			strcat(sqlStmt, "\n WHERE ");
			createString(sqlStmt, selectStruct->conditions->front, 1);
		}
		
		/*
		if (selectStruct->orConditions != NULL)
		{
			strcat(sqlStmt, "\n OR ");
			createOrString(sqlStmt, selectStruct->orConditions->front, 1);
		}
		*/
	
		if (selectStruct->groupby != NULL)
		{
			strcat(sqlStmt, "\n GROUP BY ");
			createString(sqlStmt, selectStruct->groupby->front, 0);
		}
		if (selectStruct->having != NULL)
		{
			if (selectStruct->groupby == NULL)
			{
				selectStruct->groupby = selectStruct->attributes;
				strcat(sqlStmt, "\n GROUP BY ");
				createString(sqlStmt, selectStruct->groupby->front, 0);
				strcat(sqlStmt, "\nHAVING ");
				createString(sqlStmt, selectStruct->having->front, 0);
			}
			else
			{
				strcat(sqlStmt, "\nHAVING ");
				createString(sqlStmt, selectStruct->having->front, 0);
			}
		}
		if (selectStruct->orderby != NULL)
		{
			strcat(sqlStmt, "\n ORDER BY ");
			createString(sqlStmt, selectStruct->orderby->front, 0);
		}
	}
	else
	{
		char tmpStmt[MAXSTMTLENGTH] = {'\0'};
		char *pch;
		strcpy(tmpStmt, "SELECT DISTINCT ");
		pch = strstr(selectStruct->attributes->front->id, ".");
		int len = strlen(pch);
		int index;
		char tmpString[100] = {'\0'};
		for (index = 1; index < len; index++)
		{
			tmpString[index-1] = pch[index];
		}
		strncat(tmpStmt, tmpString, strlen(tmpString));
		strcat(tmpStmt, "\n  FROM ");
		
		if (selectStruct->minusCase != 10) //only union
		{
			LIST_ITEM *current = selectStruct->tables->front;
			while (current != NULL)
			{
				strncat(sqlStmt, tmpStmt, strlen(tmpStmt));
				strncat(sqlStmt, current->id, strlen(current->id));
				if (current->next != NULL)
				{
					strncat(sqlStmt, " UNION ", 7);
				}
				current = current->next;			
			}
		}
		else
		{
			if (selectStruct->unionCase == 10) //minus + union
			{
				LIST_ITEM *current = selectStruct->tables->front;
				strncat(sqlStmt, tmpStmt, strlen(tmpStmt));
				strncat(sqlStmt, current->id, strlen(current->id));
				current = current->next;
				strncat(sqlStmt, " MINUS ", 7);
				strncat(sqlStmt, "(", 1);
				while (current != NULL)
				{
					strncat(sqlStmt, tmpStmt, strlen(tmpStmt));
					strncat(sqlStmt, current->id, strlen(current->id));
					if (current->next != NULL)
					{
						strncat(sqlStmt, " UNION ", 7);
					}
					current = current->next;
				}
				strncat(sqlStmt, ")", 1);
			}
			else //only minus
			{
				//not good solution, if more time, do some improvement 
				//for case such that {SNAME, JNAME | (exists S#,J#) (Supp(S#, SNAME, _, _) and Pro(J#,JNAME,_) and not (SPJ(S#, P#, J#, QTY)))};
				if (selectStruct->conditions != NULL)
				{
					strcpy(sqlStmt, "SELECT DISTINCT ");
					createString(sqlStmt, selectStruct->attributes->front, 0);
					strcat(sqlStmt, "\n  FROM ");
					createString(sqlStmt, selectStruct->tables->front, 0);
					strncat(sqlStmt, " MINUS ", 7);
					strcat(sqlStmt, "SELECT DISTINCT ");
					createString(sqlStmt, selectStruct->attributes->front, 0);
					strcat(sqlStmt, "\n  FROM ");
					createString(sqlStmt, selectStruct->tables->front, 0);
					strcat(sqlStmt, "\n WHERE ");
					createString(sqlStmt, selectStruct->conditions->front, 1);
				}
				else // for case such that {CITY | t1(city) AND NOT t2(city)};
				{
					LIST_ITEM *current = selectStruct->tables->front;
					strncat(sqlStmt, tmpStmt, strlen(tmpStmt));
					strncat(sqlStmt, current->id, strlen(current->id));
					current = current->next;
					strncat(sqlStmt, " MINUS ", 7);
					strncat(sqlStmt, tmpStmt, strlen(tmpStmt));
					strncat(sqlStmt, current->id, strlen(current->id));
				}
			}
		}
	}
}

/*-------------------------------------------------------------
Function name: buildSqlStmtwithForall
Purpose: To build the select statement string for the select statement in the select structure.
Parameters: sqlStmt: string the sql statement is to be put in
	         SELECTSTMT: structure containing the select statement
Returns: nothing
------------------------------------------------------------- */
void buildSqlStmtwithForall(char *sqlStmt, SELECTSTMT *selectStruct)
{
	if (selectStruct->unionCase == 0 && selectStruct->minusCase == 0)
	{
		strcpy(sqlStmt, "SELECT DISTINCT ");
		createString(sqlStmt, selectStruct->attributes->front, 0);
		strcat(sqlStmt, "\n  FROM ");
   
		LIST_ITEM *current = selectStruct->tables->front;
		strncat(sqlStmt, current->id, strlen(current->id));
   if(current->not_flag == 1)
		strcat(sqlStmt, "\n WHERE EXISTS ");
   else 
    strcat(sqlStmt, "\n WHERE NOT EXISTS ");
		strcat(sqlStmt, "(select * from ");
		current = current->next;
		strncat(sqlStmt, current->id, strlen(current->id));
  if(current->not_flag == 1)
		strcat(sqlStmt, "\n WHERE EXISTS ");
   else 
    strcat(sqlStmt, "\n WHERE NOT EXISTS ");
    
    
		strcat(sqlStmt, "(select * from ");
		current = current->next;
		strncat(sqlStmt, current->id, strlen(current->id));
		strcat(sqlStmt, "\n WHERE ");
		createString(sqlStmt, selectStruct->conditions->front, 1);
		strcat(sqlStmt, "))");		
	}
	
	//strcpy(sqlStmt, "select * from t");
}

/* -----------------------------------------------
Function name: createstring
Purpose:       To loop through all of the elements in a linked list and concatenate them into the string sqlstring.
Parameters: sqlstring	the string to place the elements into
			front		the front of the list containing the elements
Returns:        nothing
------------------------------------------------- */
void createString(char *sqlstring, LIST_ITEM *front, int type)
{
	//printf("*createstring\n");
	LIST_ITEM *current = front;
	while (current != NULL)
	{
		//if ((current->type == 'I') || (current->type == 'N') || (current->type == 'T') || (current->type == 'E'))
		strcat(sqlstring, current->id);
		if(current->next != NULL && type == 0)
			strcat(sqlstring, ", ");
		if(current->next != NULL && type == 1)
			strcat(sqlstring, " AND ");
 		if(current->next != NULL && type == 1)
			strcat(sqlstring, " OR ");
		current = current->next;

	}
}

/* ------------------------------------------------------
Function name: andConditionTreat
Purpose:	to deal with the format: (exist att1, ...) (tablename_1(att1,...) and procondion_1) AND (exist attr1, ...) (tablename_2(attr1,...) and procondion_2) 
		if there are same attributes name in previous and next part, here we need to add T1.sth = T2.sth
Parameters: assembled prelist, assembled formula1 and formula2
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* andConditionTreat(SELECTSTMT* precondition, SELECTSTMT* andFormula1, SELECTSTMT* andFormula2)
{
	SELECTSTMT* result = conditionTreat(precondition, andFormula1);
	result->tables = mergeList(result->tables, andFormula2->tables);
	result->attributes = mergeList(result->attributes, andFormula2->attributes);
	result->conditions = mergeList(result->conditions, andFormula2->conditions);
	result->having = mergeList(result->having, andFormula2->having);
	
	LIST_ITEM* temp = andFormula1->attributes->front;
	char condition[MAXLENGTH] = {'\0'};
	int index = 0; 
	while (temp != NULL ) 
	{
		LIST_ITEM* att =  andFormula2->attributes->front;
		while (att != NULL)
		{
			if(strstr(temp->id, strstr(att->id, "."))!= NULL)
			{
				strncpy(condition, temp->id, strlen(temp->id));
				strncat(condition, "=", 1);
				strncat(condition, att->id, strlen(att->id));	
				index = 1;
			}
			if (index == 1)
				break;
			att = att->next;
		}
		if (index == 1)
			result->conditions = (LIST*) addToFront(condition, result->conditions,'Z');
		temp = temp->next;
		for(index = 0; index < 256; index++)
		{
			condition[index] = '\0';
		}
		index = 0;
	}
	andFormula2->conditions = NULL;
	andFormula2->having = NULL;
	andFormula2->attributes = NULL;
	andFormula2->tables = NULL;
	freeexpr(andFormula2);
	result->preCase = 0;
	return result;
}
/* ------------------------------------------------------
Function name: orConditionTreat
Purpose:	same as andCondition, but it has no more checks and result is saved in orConditions  
Parameters: assembled prelist, assembled formula1 and formula2
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* orConditionTreat(SELECTSTMT* precondition, SELECTSTMT* andFormula1, SELECTSTMT* andFormula2)
{
	SELECTSTMT* result = conditionTreat(precondition, andFormula1);
	result->tables = mergeList(result->tables, andFormula2->tables);
	andFormula2->tables = NULL;
	result->attributes = mergeList(result->attributes, andFormula2->attributes);
	andFormula2->attributes = NULL;
	result->orConditions = mergeList(result->conditions, andFormula2->conditions);
	andFormula2->conditions = NULL;
	result->having = mergeList(result->having, andFormula2->having);
	andFormula2->having = NULL;
	freeexpr(andFormula2);
	result->preCase = 0;
	return result;
}

/* ---------------------------------------------------------------end--------------------------------------------------------------------------- */

/* --------------------------------------------------------------Begin-------------------------------------------------------------------------- */
/*				Basic function
	1. uppercase
	2. freeexpr
	3. freelist
*/
/* --------------------------------------------------------------------------------------------------
Function name: uppercase
Purpose:       To change a string into uppercase.
Parameters: 	string		the string to change to uppercase
Returns:  	nothing
---------------------------------------------------------------------------------------------------*/
void uppercase(char *string)
{
	//printf("uppercase\n");
	int i, length;
	length = strlen(string);
    for (i = 0; i < length; i++)
	{
		string[i] = toupper(string[i]);
	}
}

/* -------------------------------------------------------------------------------
Function name: freeexpr
Purpose:       To deallocate the memory allocated to a select statement structure.

Parameters (expr):	the select statement to deallocate memory
Returns: 	nothing
--------------------------------------------------------------------------------*/
void freeexpr(SELECTSTMT *expr)
{
  if (expr != NULL)
  {
    freelist(expr->attributes);
    freelist(expr->tables);
    freelist(expr->conditions);
    freelist(expr->groupby);
	freelist(expr->having);
	freelist(expr->orderby);
	freelist(expr->aggregates);
	freelist(expr->opattributes);
	freelist(expr->pre);
  }
}


/* ------------------------------------------------------------------------
Function name: freelist
Purpose:       To deallocate the memory allocated to an entire linked list.
Parameters:	list	the list to dealocate memory 
Returns:	nothing
-------------------------------------------------------------------------*/
void freelist(LIST *list)
{	
	LIST_ITEM *old, *current;
	if (list != NULL)
	{
		current = list->front;
		while (current != NULL)
		{
           	old = current;
			current = current->next;
           	free(old);
		}
		free(list);
    }
}

/*---------------------------------------------------------------------end basic function------------------------------------------------------------------*/

/*----------------------------------------------------------------------Begin important function-----------------------------------------------------------*/
/*				Important function
	1. retrieveColumnNames
	2. executeSql
	3. addToBack
	4. addToBack
*/

/* -----------------------------------------------------------------------------------------------
Function name: retrieve_column_names
Purpose:       To retrieve all of the columns in tablename and return them in a linked list.
Parameters (tablename):	the name of the table to retrieve the columns 
Returns:       linked list containing the attributes of the table
------------------------------------------------------------------------------------------------*/
LIST *retrieveColumnNames(char *tablename)
{
	char sqlstmt[MAXSTMTLENGTH] = {'\0'};
	LIST *columns = NULL;
	uppercase(tablename);
	char temp[] = "select column_name from user_tab_columns where table_name = '";
	strncpy(sqlstmt, temp, strlen(temp));
	strcat(sqlstmt, tablename);
	strcat(sqlstmt, "'");
	columns = executeSql(sqlstmt, 'N', 0);
	return columns;
}

/* ----------------------------------------------------------------------------------------------------------------------------------
Function name: executeSql
Purpose: To execute a sql statement and display or return the results if so desired.
Parameters: sqlstmt: The statement to be executed.
			displayFlag: Flag that signals the results to be displayed if equal to Y else the results are returned in a linked list.
			create_flag: print message for build temp table(1 for print) 
Returns:    A linked list of the results of query if displayFlag = 'N', NULL otherwise.
-----------------------------------------------------------------------------------------------------------------------------------*/
LIST *executeSql(char *sqlstmt, char displayFlag, int create_flag)
{
  printf("%s\n", sqlstmt);
	int i;
    LIST *columns = NULL;
    i = setjmp(jmp_continue); 
	if (f_oracle_error == 'F') 
	{
      	memset (sql_statement, '\0', 1024);
		strncpy(sql_statement, sqlstmt, strlen(sqlstmt)); //MAXSTMTLENGTH
		sql_statement[strlen(sqlstmt)] = '\0';
        /* exec sql whenever sqlerror do sql_error(); */ 

        parse_flag = 1;     /* Set a flag for sqlError(). */
        /* exec sql prepare s from :sql_statement; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 1;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )5;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqhstv[0] = (unsigned char  *)sql_statement;
        sqlstm.sqhstl[0] = (unsigned long )1024;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error();
}


        parse_flag = 0;     /* Unset the flag. */
		/* exec sql declare c cursor for s; */ 

		set_bind_variables();
        /* exec sql open c using descriptor bind_dp; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 1;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.stmt = "";
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )24;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqcmod = (unsigned int )0;
        sqlstm.sqhstv[0] = (unsigned char  *)bind_dp;
        sqlstm.sqhstl[0] = (unsigned long )0;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode < 0) sql_error();
}


		if (displayFlag == 'Y') 
		{
            
			/*printf("%s\n", sqlstmt);*/
			
			
			if(create_flag == 1)
            {
                fprintf(stdout, "\nTable created.\n");
                fprintf(stdout, "\nDRC> ");
            }
			process_select_list();
			for (i = 0; i < 8; i++)
			{
				if (strncmp(sql_statement, dml_commands[i], 6) == 0) 
				{
					fprintf(stdout, "\n%d row%c processed.\n\n",
					sqlca.sqlerrd[2],
					sqlca.sqlerrd[2] == 1 ? '\0' : 's');
					break;
				}
			}
		} 
		else 
		{
			columns = retrieveColumns();
		}
	} 
	else 
	{
	    f_oracle_error = 'F';
	}
	return columns;
}

/* ----------------------------------------------------------------------------------------------------------------------------------
Function name: retrieve_columns
Purpose:       To place the retrieved column names into a linked list and return the list.
Parameters:	   none
Returns:	   List 	Linked list containing the retrieved column names.
-----------------------------------------------------------------------------------------------------------------------------------*/
LIST *retrieveColumns()
{
	int nullOk = 0;
    LIST *columns = NULL;
	select_dp->N = MAX_ITEMS;
	/* exec sql describe select list for s into select_dp; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 1;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )43;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlstm.sqhstv[0] = (unsigned char  *)select_dp;
 sqlstm.sqhstl[0] = (unsigned long )0;
 sqlstm.sqhsts[0] = (         int  )0;
 sqlstm.sqindv[0] = (         short *)0;
 sqlstm.sqinds[0] = (         int  )0;
 sqlstm.sqharm[0] = (unsigned long )0;
 sqlstm.sqadto[0] = (unsigned short )0;
 sqlstm.sqtdso[0] = (unsigned short )0;
 sqlstm.sqphsv = sqlstm.sqhstv;
 sqlstm.sqphsl = sqlstm.sqhstl;
 sqlstm.sqphss = sqlstm.sqhsts;
 sqlstm.sqpind = sqlstm.sqindv;
 sqlstm.sqpins = sqlstm.sqinds;
 sqlstm.sqparm = sqlstm.sqharm;
 sqlstm.sqparc = sqlstm.sqharc;
 sqlstm.sqpadto = sqlstm.sqadto;
 sqlstm.sqptdso = sqlstm.sqtdso;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
 if (sqlca.sqlcode < 0) sql_error();
}


	if (select_dp->F < 0) 
	{
	    fprintf (stdout, "\nToo many select-list items (%d), maximum is %d\n", (select_dp->F), MAX_ITEMS);
	    return NULL;
	}
	select_dp->N = select_dp->F;
	sqlnul (&(select_dp->T[0]), &(select_dp->T[0]), &nullOk);
	select_dp->V[0] = (char *) realloc(select_dp->V[0], select_dp->L[0] + 1);
	select_dp->T[0] = 1;
   	/* exec sql whenever not found goto endSelectLoop; */ 

   	for (;;) 
	{
    	/* exec sql fetch c using descriptor select_dp; */ 

{
     struct sqlexd sqlstm;
     sqlstm.sqlvsn = 12;
     sqlstm.arrsiz = 1;
     sqlstm.sqladtp = &sqladt;
     sqlstm.sqltdsp = &sqltds;
     sqlstm.iters = (unsigned int  )1;
     sqlstm.offset = (unsigned int  )62;
     sqlstm.selerr = (unsigned short)1;
     sqlstm.cud = sqlcud0;
     sqlstm.sqlest = (unsigned char  *)&sqlca;
     sqlstm.sqlety = (unsigned short)4352;
     sqlstm.occurs = (unsigned int  )0;
     sqlstm.sqfoff = (         int )0;
     sqlstm.sqfmod = (unsigned int )2;
     sqlstm.sqhstv[0] = (unsigned char  *)select_dp;
     sqlstm.sqhstl[0] = (unsigned long )0;
     sqlstm.sqhsts[0] = (         int  )0;
     sqlstm.sqindv[0] = (         short *)0;
     sqlstm.sqinds[0] = (         int  )0;
     sqlstm.sqharm[0] = (unsigned long )0;
     sqlstm.sqadto[0] = (unsigned short )0;
     sqlstm.sqtdso[0] = (unsigned short )0;
     sqlstm.sqphsv = sqlstm.sqhstv;
     sqlstm.sqphsl = sqlstm.sqhstl;
     sqlstm.sqphss = sqlstm.sqhsts;
     sqlstm.sqpind = sqlstm.sqindv;
     sqlstm.sqpins = sqlstm.sqinds;
     sqlstm.sqparm = sqlstm.sqharm;
     sqlstm.sqparc = sqlstm.sqharc;
     sqlstm.sqpadto = sqlstm.sqadto;
     sqlstm.sqptdso = sqlstm.sqtdso;
     sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
     if (sqlca.sqlcode == 1403) goto endSelectLoop;
     if (sqlca.sqlcode < 0) sql_error();
}


		*( select_dp->V[0] + (int)select_dp->L[0])= '\0';
		columns = addToBack(select_dp->V[0], columns, 'C'); 
   	}
endSelectLoop:
   	return columns;
}

/* -----------------------------------------------------------------------------------------------------------------------------------
Function name: addToBack 
Purpose: To add an entry to the back of a linked list.
Parameters:	newelement	string to be added to the linked list
			list 		Pointer to the linked list structure
		    idFlag		flag that specifies whether the new element is to be added as an id or an element
Returns:	The new list
------------------------------------------------------------------------------------------------------------------------------------*/
LIST *addToBack(char *newelement, LIST *list, char idFlag)
{
	LIST_ITEM *entry = NULL;
	if (list == NULL) 
	{
		if ((list = (LIST*) calloc(1, sizeof(LIST))) == NULL) 
		{
			fprintf(stderr, "Not enough memory to allocate to list!");
			exit(1);
		}
	}
	if ((entry = (LIST_ITEM *)malloc (sizeof (LIST_ITEM))) == NULL) 
	{
		fprintf(stderr, "Not enough memory to add item to list!\n");
		exit(1);
	}
	
	if (list->back == NULL) 
	{
		list->front = entry;
	}
	
	strncpy(entry->id, newelement, strlen(newelement));
	entry->id[strlen(newelement)] = '\0';
	if (idFlag == 'V' || idFlag == 'U' || idFlag == 'C' || idFlag == 'A' || idFlag == 'T' || idFlag == 't' || idFlag == 'N')
	{
		++list->count;
	}
	
	entry->type = idFlag;
	entry->prev = list->back;
	entry->next = NULL;
	
	if (list->back !=NULL)
	{
		list->back->next = entry;
	}
	
	list->back = entry;
	return list;
}

/* -----------------------------------------------------------------------------------------------------------------------------------
Function name: addToBack 
Purpose: To add an entry to the back of a linked list.
Parameters:	newelement	string to be added to the linked list
			secondelement
			list 		Pointer to the linked list structure
		    idFlag		flag that specifies whether the new element is to be added as an id or an element
Returns:	The new list
------------------------------------------------------------------------------------------------------------------------------------*/
LIST *addTwoToBack(char *newelement, char *secondelement, LIST *list, char idFlag)
{
	LIST_ITEM *entry = NULL;
	if (list == NULL) 
	{
		if ((list = (LIST*) calloc(1, sizeof(LIST))) == NULL) 
		{
			fprintf(stderr, "Not enough memory to allocate to list!");
			exit(1);
		}
	}
	if ((entry = (LIST_ITEM *)malloc (sizeof (LIST_ITEM))) == NULL) 
	{
		fprintf(stderr, "Not enough memory to add item to list!\n");
		exit(1);
	}
	
	if (list->back == NULL) 
	{
		list->front = entry;
	}
	
	strncpy(entry->id, newelement, strlen(newelement));
	entry->id[strlen(newelement)] = '\0';
	
	strncpy(entry->alias, secondelement, strlen(secondelement));
	entry->alias[strlen(secondelement)] = '\0';
	
	if (idFlag == 'V' || idFlag == 'U' || idFlag == 'C' || idFlag == 'A' || idFlag == 'T' || idFlag == 't' || idFlag == 'N')
	{
		++list->count;
	}
	
	entry->type = idFlag;
	entry->prev = list->back;
	entry->next = NULL;
	
	if (list->back !=NULL)
	{
		list->back->next = entry;
	}
	
	list->back = entry;
	return list;
}

/* ---------------------------------------------------------------------------------------------------------------------------------
Function name: addToFront 
Purpose: To add an entry to the front of a linked list.
Parameters: newelement	string to be added to the linked list
		list	Pointer to the linked list structure
		idFlag flag that specifies whether the new element is to be added as an id or an element
Returns: 	The new list
-----------------------------------------------------------------------------------------------------------------------------------*/
LIST *addToFront(char *newelement, LIST *list, char idFlag)
{
	char clear[MAXLENGTH] = {'\0'};
	LIST_ITEM *entry = NULL;
	if (list == NULL) 
	{	
		if ((list = (LIST*) calloc(1, sizeof(LIST))) == NULL) 
		{
			fprintf(stderr, "Not enough memory to allocate to list!");
			exit(1);
		}
	}
	if ((entry = (LIST_ITEM *)malloc (sizeof (LIST_ITEM))) == NULL) 
	{
		fprintf(stderr, "Not enough memory to add item to list!\n");
		exit(1);
	}
	if(list->front == NULL)
	{
		list->back  = entry;
	}
	strncpy(entry->id, clear, strlen(clear));	
	strncpy(entry->id, newelement, strlen(newelement));
	entry->id[strlen(newelement)] = '\0';
	if (idFlag == 'V' || idFlag == 'U' || idFlag == 'C' || idFlag == 'A' || idFlag == 'T' || idFlag == 't' || idFlag == 'N')
	{
		++list->count;
	}
	entry->type = idFlag;
	entry->next = list->front;
	entry->prev = NULL;
	if (list->front !=NULL)
		list->front->prev = entry;
	list->front = entry;
	return list;
}

/*-------------------------------------------------------End important function----------------------------------------------------------*/

/*------------------------------------------------------Begin Query Function-------------------------------------------------------------*/
/*
		Query Function
		1. variableList
		2. varconList
		3. 
		
		Ending Function
		1. processEnding
*/
/* ------------------------------------------------------
Function name: variableList
Purpose: To add a variable to a variable list
Parameters: variable, keyword, variables and operand details look at gramma definition at drc.y
Returns: Pointer to a struct contains a list of variables
------------------------------------------------------ */
SELECTSTMT* variableList(char *variable, char *keyword, char* opperate, SELECTSTMT *variables, char *v2)
{
	//code review: memory menagement pending	3/23
	SELECTSTMT* result = NULL;
	char tempstr[MAXLENGTH] = {'\0'};
	char t1[MAXLENGTH] = {'\0'};
	char agg[6] = {'\0'}; //aggregates
	char opp[1] = {'\0'};
	//LIST_ITEM* current = NULL;
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate to list!");
    	exit(1);
  	}
	if(variables != NULL && variables->f_error == 'E')
	{
		return variables;
	}
 	/*case 1, there are only variable or variable with order*/
	if (keyword == NULL && opperate == NULL)
	{
		strncpy(tempstr, variable, strlen(variable));
		uppercase(tempstr);
  		if (variables != NULL) 
		{
			//result->attributes = variables->attributes;
			result = variables;
			switch(variables->Lcase)
			{
				case 1: result->Lcase = 3; break;
				case 2: result->Lcase = 4; break;
				case 5: result->Lcase = 6; break;
				default: break;
			}
		} /*
		else 
		{
			result->Lcase = 0; //complete basic case: such as {S#,P#,QTY|SP(S#,P#,QTY)} 
		} */
		result->attributes = (LIST*) addToFront(tempstr, result->attributes, 'V');		
	}	
	//case 2, there are aggregates
	else
	{	
		if (opperate == NULL) {
			strncpy(agg, keyword, strlen(keyword));
			uppercase(agg);
			if((strncmp(agg,"COUNT", 5) == 0 && strlen(agg) == 5) || (strlen(agg) == 3 && (strncmp(agg,"SUM", 3) == 0 || strncmp(agg,"AVG", 3) == 0 
				||strncmp(agg,"MAX", 3) == 0 ||strncmp(agg,"MIN", 3) == 0)))
			{
				if (variables != NULL) 
				{
					result = variables;
					switch(variables->Lcase)
					{
						case 0: result->Lcase = 3; break;
						case 2: result->Lcase = 5; break;
						case 4: result->Lcase = 6; break;
						default: break;
					}
				}
				else {
					result->Lcase = 1;
				}
				if(variable != NULL)
				{
					strncpy(tempstr, agg, strlen(agg));
					strncat(tempstr, "(", 1);
					uppercase(variable);
					strncat(tempstr, variable, strlen(variable));
					strncat(tempstr, ")", 1);
					if(strncmp(agg,"COUNT", 5) != 0 && strncmp(variable,"*", 1) == 0)
					{
						result->f_error = 'E';
						strncpy(result->errormsg, keyword , strlen(keyword));
						strcat(result->errormsg, " is not COUNT, but wiht variable *");
					}
					else {
						result->aggregates = addToFront(tempstr, result->aggregates, 'G');	
					}
					//pending, if time allowed,  followed would be prepared for error check, see notes.
				}
				else {
					result->f_error = 'E';
					strncpy(result->errormsg, keyword , strlen(keyword));
					strncat(result->errormsg, " without variable", 18);
				}
			}
			else
			{
				result->f_error = 'E';
				strncpy(result->errormsg, "Invalid keyword ", 20);
				strncat(result->errormsg, keyword,  strlen(keyword));
			}
		}
		else {
			if (keyword == NULL) {
				strncpy(opp, opperate, strlen(opperate));
				uppercase(opp);
				if(strncmp(opp,"+",1) == 0 || strncmp(opp,"-", 1) == 0 || strncmp(opp,"*", 1) == 0 ||strncmp(opp,"/", 1) == 0)
				{
					if (variables != NULL) 
					{
						result = variables;
						switch(variables->Lcase)
						{
							case 0: result->Lcase = 4; break;
							case 1: result->Lcase = 5; break;
							case 3: result->Lcase = 6; break;
							default: break;
						}
					}
					else{
						result->Lcase = 2;
					}
					if(variable != NULL && v2 != NULL )
					{
						uppercase(variable);
						uppercase(v2);
						strncpy(tempstr, variable, strlen(variable));
						strncat(tempstr, opp, 1);
						strncat(tempstr, v2, strlen(v2));
						result->opattributes = addToFront(tempstr, result->opattributes, 'G');	
						//pending, if time allowed,  followed would be prepared for error check, see notes.
						//result->aggregates = addElement(variable, result->aggregates);
					}
					else {
						result->f_error = 'E';
						strncpy(result->errormsg, opperate , strlen(keyword));
						strncat(result->errormsg, " miss variable(s)", 18);
					}
				}
				else
				{
					result->f_error = 'E';
					strncpy(result->errormsg, "Invalid opperator ", 20);
					strncat(result->errormsg, keyword,  strlen(keyword));
				}
			}
			else {
				// this part for later improvement such as a + b, sum(c);
			}
		}
	}
 	return result;
}

/* ----------------------------------------------------------------------------------------------------------------
Function name: varconList
Purpose: To add a variable or a constant to a vars_cons list
Parameters: varcon: 	The element to be added
			varscons: 	The list to add to
			varconType: Variable, Constant or Underscore ***
Returns:	Pointer to a structure contains the list of variables & constants
------------------------------------------------------------------------------------------------------------------*/
SELECTSTMT *varconList(char *varcon, SELECTSTMT *varscons, char varconType) /*varcon = _ ,varscons = N,A */
{
	SELECTSTMT *result = NULL;
	char	tempstr[MAXLENGTH] = {'\0'};
	int len = 0;
    strncpy(tempstr, varcon, strlen(varcon));    
	if( (len = strspn(tempstr, "'")) > 0)                  /* varcon 不以 ‘ 开头 */
		;   
	else
		uppercase(tempstr);
	if ((result=(SELECTSTMT*)calloc(1, sizeof(SELECTSTMT)))==NULL) 
	{
		fprintf(stderr, "Not enough memory to allocate to list!");
		exit(1);
	}
	if (varscons != NULL)         
	{
		result->attributes = varscons->attributes;
		varscons->attributes = NULL;
	}
	result->attributes = (LIST*) addToFront(tempstr, result->attributes, varconType); 
	freeexpr(varscons);
	return result;
}

/* ---------------------------------------------------------------------------------------------------------------------
Function name: processSubForm
Purpose: To process formula relationName(list of variables & constants)
Parameters: relName: String of relation name
	        varscons: list of variables & constants
Returns: Pointer to the select struct of that formula
-----------------------------------------------------------------------------------------------------------------------*/
SELECTSTMT *processSubForm(char *relName, SELECTSTMT *varscons)
{                                                                          /* realname:tablename varscons:variable/constant   */
	SELECTSTMT *result;
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL){
		fprintf(stderr, "Not enough memory to allocate to list!\n");
		exit(1);
	}
	LIST_ITEM *currentVarCon = NULL; 
	LIST_ITEM *currentColumn = NULL;
	LIST_ITEM *columnTest = NULL;
	LIST *columnNames = NULL;
	char attribute[MAXLENGTH] = {'\0'};
	char id[MAXLENGTH] = {'\0'};
	char cond[MAXLENGTH] = {'\0'};
	
	int len = 0;
	if ((columnNames = retrieveColumnNames(relName)) != NULL) {
		if (varscons == NULL || columnNames->count != varscons->attributes->count) //报错
		{
			result->f_error = 'E';
			char temp[] = "Wrong number of attributes in table ";
			strncpy(result->errormsg, temp, strlen(temp));
			strcat(result->errormsg, relName);
		} else //here we need add a function to check if column name in table is correct or not
		{
			//07-03-16 adding and 10-03-09 modify
			
			/*columnTest = varscons->attributes->front;
			while(columnTest != NULL) {
				//strncpy(id, columnTest->id, strlen(columnTest->id));
				if(strncmp(columnTest->id, "_", 1) != 0 && columnTest->type != 'C')
				{
					if(searchList(columnTest->id, columnNames) == NULL) //报错
					{
						result->f_error = 'E';
						char temp[] = "Wrong attributes name in table ";
						strncpy(result->errormsg, temp, strlen(temp));
						strcat(result->errormsg, relName);
					}
				}
				columnTest = columnTest->next;
			}*/
			currentVarCon = varscons->attributes->front;  
			currentColumn = columnNames->front;
			result->tables = (LIST*) addToBack(relName, result->tables, 'T');
			//****************************************************************************************************
			while (currentVarCon != NULL && currentColumn !=NULL) 
			{
				
				if (strncmp(currentVarCon->id, "_", 1) != 0) /* variable != '_' */
				{
					if (currentVarCon->type != 'C')            /* variable != constant */
					{
						strcpy(attribute,relName);
						strcat(attribute, ".");
						len = strcspn(currentColumn->id, " ");
						strncat(attribute, currentColumn->id, len);                                                       /* attribute : realname.colunmname */
						//result->conditions = (LIST*) addToBack(attribute, result->conditions,'A');
						result->attributes = (LIST*) addTwoToBack(attribute, currentVarCon->id, result->attributes, 'A'); /**/
					}
					if(currentVarCon->type == 'C')               /* attribute = constant */
					{
						strcpy(attribute,relName);
						strcat(attribute, ".");
						len = strcspn(currentColumn->id, " ");
						strncat(attribute, currentColumn->id, len);
						strncpy(cond, attribute, strlen(attribute));
						strncat(cond, "=", 1);                              
						strncat(cond, currentVarCon->id, strlen(currentVarCon->id));                  /* cond : realname.variable = constant    */
						result->conditions = (LIST*) addToBack(cond, result->conditions,'Z');          /* 把cond添加到result->conditions 中*/
					}
					for(len = 0; len < MAXLENGTH; len++)
					{
						attribute[len] = '\0';
						cond[len] = '\0';
					}
				}
				currentVarCon = currentVarCon->next;
				currentColumn = currentColumn->next;
			}
		}
	} 
	else 
	{
		result->f_error = 'E';
		strncpy(result->errormsg, "Table ", MAXERRMSGLENGTH);
		strcat(result->errormsg, relName);
		strcat(result->errormsg, " does not exist in database.");
	}
	freelist(columnNames);
	freeexpr(varscons);
	result->preCase = 10;
	return result;
}
/* ---------------------------------------------------------------------------------------------------------------------
Function name: processNotSubForm
Purpose: To process formula relationName(list of variables & constants)
Parameters: relName: String of relation name
	        varscons: list of variables & constants
Returns: Pointer to the select struct of that formula
-----------------------------------------------------------------------------------------------------------------------*/
SELECTSTMT *processNotSubForm(char *relName, SELECTSTMT *varscons)
{                                                                          /* realname:student varscons:s,n,a   */
	SELECTSTMT *result;
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL){
		fprintf(stderr, "Not enough memory to allocate to list!\n");
		exit(1);
	}
	LIST_ITEM *currentVarCon = NULL; 
	LIST_ITEM *currentColumn = NULL;
	LIST_ITEM *columnTest = NULL;
	LIST *columnNames = NULL;
	char attribute[MAXLENGTH] = {'\0'};
	char id[MAXLENGTH] = {'\0'};
	char cond[MAXLENGTH] = {'\0'};
	
	int len = 0;
	if ((columnNames = retrieveColumnNames(relName)) != NULL) {
		if (varscons == NULL || columnNames->count != varscons->attributes->count) //报错
		{
			result->f_error = 'E';
			char temp[] = "Wrong number of attributes in table ";
			strncpy(result->errormsg, temp, strlen(temp));
			strcat(result->errormsg, relName);
		} else //here we need add a function to check if column name in table is correct or not
		{
			//07-03-16 adding and 10-03-09 modify
			
			/*columnTest = varscons->attributes->front;
			while(columnTest != NULL) {
				//strncpy(id, columnTest->id, strlen(columnTest->id));
				if(strncmp(columnTest->id, "_", 1) != 0 && columnTest->type != 'C')
				{
					if(searchList(columnTest->id, columnNames) == NULL) //报错
					{
						result->f_error = 'E';
						char temp[] = "Wrong attributes name in table ";
						strncpy(result->errormsg, temp, strlen(temp));
						strcat(result->errormsg, relName);
					}
				}
				columnTest = columnTest->next;
			}*/
			currentVarCon = varscons->attributes->front;  
			currentColumn = columnNames->front;
			result->tables = (LIST*) addToBack(relName, result->tables, 'T');
      
      result->tables->back->not_flag = 1 ;
      
			//****************************************************************************************************
			while (currentVarCon != NULL && currentColumn !=NULL) 
			{
				
				if (strncmp(currentVarCon->id, "_", 1) != 0) /* variable != '_' */
				{
					if (currentVarCon->type != 'C')            /* variable != constant */
					{
						strcpy(attribute,relName);
						strcat(attribute, ".");
						len = strcspn(currentColumn->id, " ");
						strncat(attribute, currentColumn->id, len);                                                       /* attribute : realname.colunmname */
						//result->conditions = (LIST*) addToBack(attribute, result->conditions,'A');
						result->attributes = (LIST*) addTwoToBack(attribute, currentVarCon->id, result->attributes, 'A'); /**/
					}
					for(len = 0; len < MAXLENGTH; len++)
					{
						attribute[len] = '\0';
						cond[len] = '\0';
					}
				}
				currentVarCon = currentVarCon->next;
				currentColumn = currentColumn->next;
			}
		}
	} 
	else 
	{
		result->f_error = 'E';
		strncpy(result->errormsg, "Table ", MAXERRMSGLENGTH);
		strcat(result->errormsg, relName);
		strcat(result->errormsg, " does not exist in database.");
	}
	freelist(columnNames);
	freeexpr(varscons);
	result->preCase = 10;
	return result;
}
/*-------------------------------------------------------
Function name: processAndForm
Purpose:
	Process the conjunction formulas
Parameters:
	formula1, formula2: two sub formulas connected by 'and'
Returns:
	Pointer to the structure of the conjunction
	
------------------------------------------------------ */
SELECTSTMT *processAndForm(SELECTSTMT *formula1, SELECTSTMT *formula2)
{
	SELECTSTMT *result;
	if ((result=(SELECTSTMT*)calloc(1,sizeof(SELECTSTMT)))==NULL) {
		fprintf(stderr, "Not enough memory to allocate to list!");
		exit(1);
	}
	if (formula1 == NULL) {
		result->f_error = 'E';
		strncpy(result->errormsg, "Missing one side of and formula", MAXERRMSGLENGTH);
		return result;
	}
	if (formula2 == NULL) {
		result->f_error = 'E';
		strncpy(result->errormsg, "Missing one side of and formula", MAXERRMSGLENGTH);
		return result;
	}
	if (formula1->f_error == 'E') {
		freeexpr(result);
		return formula1;
	}
	if (formula2->f_error == 'E') {
		freeexpr(result);
		return formula2;
	}
	//result->conditions = addToFront(" and ", formula2->conditions, 'E');
	result->attributes = mergeList(result->attributes, formula1->attributes);
	result->attributes = mergeList(result->attributes, formula2->attributes);
	result->tables = mergeList(result->tables, formula1->tables);
	result->tables = mergeList(result->tables, formula2->tables);
	if (formula2->conditions != NULL)
	{
		result->conditions = mergeList(result->conditions, formula2->conditions);
		formula2->conditions = NULL;
	}
	formula1->attributes = NULL;
	formula2->attributes = NULL;
	formula1->tables = NULL;
	formula2->tables = NULL;
	result->minusCase = formula2->minusCase;
	result->unionCase = formula2->unionCase;
	result->forall = formula2->forall;
	freeexpr(formula1);
	freeexpr(formula2);
	result->preCase = 10;
	return result;
}

/* ---------------------------------------------------------
Function name: mergeList
Purpose: To merge two linked lists.
Parameters: list1: The list to be at the front of the merge list
		list2: The list to be at the back of the merged list
Returns: The merged list
---------------------------------------------------------- */
LIST *mergeList(LIST *list1, LIST *list2)
{
	LIST *newList = NULL;
	if (list1 == NULL)
		newList = list2;
	else if (list2 == NULL)
		newList = list1;
	else {
		newList = list1;
		list2->front->prev = newList->back;
		newList->back->next = list2->front;
		newList->back = list2->back;
	}
	return newList;
}

/* ------------------------------------------------------
Function name: processQuery
Purpose: To bind the variables with the actual relation attributes.
Parameters: variables: pointer to a struct containing the list of domain variables
	         formula: the formula part of the query
Returns:     Pointer to a struct contains the select statement
------------------------------------------------------ */
SELECTSTMT *processQuery(char * star, SELECTSTMT *headvars, SELECTSTMT *formula)
{
	if (headvars->f_error == 'E')
		return headvars;
	if (formula->f_error == 'E')
		return formula;
	
	
	if (formula->preCase == 10)
	{
		LIST_ITEM* temp = NULL;
		if (headvars->attributes != NULL)
		{
			temp = headvars->attributes->front;
		}
		char condition[MAXLENGTH] = {'\0'};
		int index = 0;
		while (temp != NULL ) 
		{
			LIST_ITEM* att =  formula->attributes->front;
			while (att != NULL)
			{
				//uppercase(temp->id);
				//uppercase(att->alias);
				//if(strstr(strstr(att->id, "."), temp->id)!= NULL)
				if (strncmp(att->alias, temp->id, strlen(temp->id)) == 0 && strncmp(att->alias, temp->id, strlen(att->alias)) == 0)
				{
					strncat(condition, att->id, strlen(att->id));
					att->quantified = 10;
					index++;
					if (index == 1)
					{
						strncat(condition, "=", 1);
					}
				}
				if(index == 2)
					break;
				att = att->next;
			}
			temp = temp->next;
			if (index == 2)
			{
				formula->conditions = (LIST*) addToFront(condition, formula->conditions,'Z');
			}
			for(index = 0; index < 32; index++)
			{
				condition[index] = '\0';
			}
			index = 0;
		}
	}
	else
	{
		LIST_ITEM* temp = NULL;
		if (headvars->attributes != NULL)
		{
			temp = headvars->attributes->front;
		}
		while (temp != NULL ) 
		{
			LIST_ITEM* att =  formula->attributes->front;
			while (att != NULL)
			{
				//uppercase(temp->id);
				//uppercase(att->alias);
				//if(strstr(strstr(att->id, "."), temp->id)!= NULL)
				if (strncmp(att->alias, temp->id, strlen(temp->id)) == 0 && strncmp(att->alias, temp->id, strlen(att->alias)) == 0)
				{
					att->quantified = 10;
				}
				att = att->next;
			}
			temp = temp->next;
		}
	}
	
	//if (headvars->aggregates != NULL)
	
	
	// do quantified test
	LIST_ITEM* foratt =  formula->attributes->front;

	LIST_ITEM* agg = NULL;
	LIST_ITEM* opp = NULL;
	while (foratt != NULL)
	{
		if (headvars->aggregates != NULL)
		{
			agg = headvars->aggregates->front;
			char *token = " ()";
			char *word;
			char tempStr[32];
			while (agg != NULL)
			{
				strncpy(tempStr, agg->id, strlen(agg->id));
				word = strtok(tempStr, token);
				word = strtok(NULL, token);
				if(strncmp(word, foratt->alias, strlen(word)) == 0 && strncmp(word, foratt->alias, strlen(foratt->alias)) == 0)
				{
					agg->quantified = 10;
					foratt->quantified = 10;  /********important********/
				}
				agg = agg->next;
			}
		}
		foratt = foratt->next;		
	}
	
	if (headvars->opattributes != NULL)
	{
		opp = headvars->opattributes->front;
		char *token_1 = "+-*/() ";
		char *token_2 = "+-*/";
		char *word;
		char tempStr[32];
		while (opp != NULL)
		{
			strncpy(tempStr, opp->id, strlen(opp->id));
			if (strstr(tempStr, "SUM") != NULL || strstr(tempStr, "MIN") != NULL || strstr(tempStr, "MAX") != NULL || strstr(tempStr, "AVG") != NULL) 
			{
				word = strtok(tempStr, token_1);
				word = strtok(NULL, token_1);
				foratt =  formula->attributes->front;
				opp->quantified = 0;
				while (foratt != NULL)
				{
					if(strncmp(word, foratt->alias, strlen(word)) == 0 && strncmp(word, foratt->alias, strlen(foratt->alias)) == 0)
					{
						opp->quantified = 5;
						foratt->quantified = 10;
					}
					foratt = foratt->next;	
				}
				word = strtok(NULL, token_1);
				word = strtok(NULL, token_1);
				foratt =  formula->attributes->front;
				while (foratt != NULL)
				{
					if(strncmp(word, foratt->alias, strlen(word)) == 0 && strncmp(word, foratt->alias, strlen(foratt->alias)) == 0)
					{
						opp->quantified = opp->quantified + 5;
						foratt->quantified = 10;
					}
					foratt = foratt->next;	
				}
				printf("%d\n", opp->quantified);
			}
			else {			
				word = strtok(tempStr, token_2);
				foratt =  formula->attributes->front;
				opp->quantified = 0;
				while (foratt != NULL)
				{
					if(strncmp(word, foratt->alias, strlen(word)) == 0 && strncmp(word, foratt->alias, strlen(foratt->alias)) == 0)
					{
						opp->quantified = 5;
						foratt->quantified = 10;
					}
					foratt = foratt->next;	
				}
				word = strtok(NULL, token_2);
				foratt =  formula->attributes->front;
				while (foratt != NULL)
				{
					if(strncmp(word, foratt->alias, strlen(word)) == 0 && strncmp(word, foratt->alias, strlen(foratt->alias)) == 0)
					{
						opp->quantified = opp->quantified + 5;
						foratt->quantified = 10;
					}
					foratt = foratt->next;	
				}
			}
			opp = opp->next;
		}
	}
		
	foratt = formula->attributes->front;
	while (foratt != NULL)
	{
		if (foratt->quantified != 10)
		{
			headvars->f_error = 'E';
			strcpy(headvars->errormsg, "quantified issue: ");
			strncat(headvars->errormsg, foratt->id, strlen(foratt->id));
			break;
		}
		foratt = foratt->next;
	}
	
	if (headvars->aggregates != NULL)
	{
		agg = headvars->aggregates->front;
	}
	while (agg != NULL)
	{
		if (agg->quantified != 10)
		{
			headvars->f_error = 'E';
			strcpy(headvars->errormsg, "quantified issue: ");
			strncat(headvars->errormsg, agg->id, strlen(agg->id));
			break;
		}
		agg = agg->next;
	}
	
	if (headvars->opattributes != NULL)
	{
		opp = headvars->opattributes->front;
	}
	while (opp != NULL)
	{
		if (opp->quantified != 10)
		{
			headvars->f_error = 'E';
			strcpy(headvars->errormsg, "quantified issue: ");
			strncat(headvars->errormsg, opp->id, strlen(opp->id));
			break;
		}
		opp = opp->next;
	}
	
	if(headvars->attributes != NULL)
	{
		LIST_ITEM* temp = NULL;
		temp = headvars->attributes->front;
		while (temp != NULL ) 
		{
			//uppercase(temp->alias);
			LIST_ITEM* att =  formula->attributes->front;
			while (att != NULL)
			{
				//uppercase(att->id);
				//if(strstr(strstr(att->id, "."), temp->id)!= NULL && (strlen(strstr(att->id, ".")) - strlen(temp->id)) == 1)
				if (strncmp(att->alias, temp->id, strlen(temp->id)) == 0 && strncmp(att->alias, temp->id, strlen(att->alias)) == 0)
				{
					strncpy(temp->alias, temp->id, strlen(temp->id));
					strncpy(temp->id, att->id, strlen(att->id));
					temp->id[strlen(att->id)] = '\0';					
				}
				att = att->next;
			}
			temp = temp->next;
		}
	}
	
	if(headvars->aggregates != NULL)
	{
		agg = headvars->aggregates->front;
		char *token = " .()";
		while (agg != NULL ) 
		{
			//uppercase(agg->id);
			strncpy(agg->alias, agg->id, strlen(agg->id));
			LIST_ITEM* att =  formula->attributes->front;
			while (att != NULL)
			{
				//uppercase(att->id);
				//if(strstr(strstr(att->id, "."), temp->id)!= NULL && (strlen(strstr(att->id, ".")) - strlen(temp->id)) == 1)
				//strncpy(tempStr, agg->id, strlen(agg->id));
				char *wordatt;
				char tempagg[32];
				strncpy(tempagg, agg->id, strlen(agg->id));
				wordatt = strtok(tempagg, token);
				wordatt = strtok(NULL, token);
				if (strncmp(att->alias, wordatt, strlen(att->alias)) == 0 && strncmp(att->alias, wordatt, strlen(wordatt)) == 0)
				{
					strtok(agg->id, token);
					strncat(agg->id, "(", 1);
					char tempStr[32];
					char *wordagg;
					strncpy(tempStr, att->id, strlen(att->id));
					wordagg = strtok(tempStr, token);
					wordagg = strtok(NULL, token);
					strncat(agg->id, wordagg, strlen(wordagg));
					strncat(agg->id, ")", 1);
					strncat(agg->id, "\0", 1);
				}
				att = att->next;
			}
			agg = agg->next;
		}
	}
	
	if(headvars->opattributes != NULL)
	{
		opp = headvars->opattributes->front;
		char *token = "+-*/.";
		char *token_2 = "()";
		char special[32] = {'\0'};
		int check;
		while (opp != NULL ) 
		{
			//uppercase(opp->id);
			check = 0;
			strncpy(opp->alias, opp->id, strlen(opp->id));
			LIST_ITEM* att;
			char *word;
			char *specialword;
			char tempopp[32] = {'\0'};
			char tempStr[64] = {'\0'};
			strncpy(tempopp, opp->id, strlen(opp->id));
			word = strtok(tempopp, token);
			att =  formula->attributes->front;
			memset(special, '\0', 32);
			strncpy(special, word, strlen(word));
			specialword = strtok(special, token_2);
			while (att != NULL)
			{
				if (strncmp(specialword, "SUM", 3) == 0 || strncmp(specialword, "MIN", 3) == 0 || strncmp(specialword, "MAX", 3) == 0 || strncmp(specialword, "AVG", 3) == 0) 
				{
					strncpy(tempStr, specialword, strlen(specialword));
					strncat(tempStr, "(", 1);
					specialword = strtok(NULL, token_2);
					check = 1;
				}
								
				if(strncmp(specialword, att->alias, strlen(specialword)) == 0 && strncmp(specialword, att->alias, strlen(att->alias)) == 0)
				{
					char temp[32];
					char *wordatt;
					strncpy(temp, att->id, strlen(att->id));
					wordatt = strtok(temp, token);
					wordatt = strtok(NULL, token);
					strncat(tempStr, wordatt, strlen(wordatt));
					if (check == 1)
					{
						strncat(tempStr, ")", 1);
					}
				}
				att = att->next;	
			}
			
			if (strstr(opp->id, "+") != NULL)
			{
				strncat(tempStr, "+", 1);
			}
			else if (strstr(opp->id, "-") != NULL)
			{
				strncat(tempStr, "-", 1);
			}
			else if (strstr(opp->id, "*") != NULL)
			{
				strncat(tempStr, "*", 1);
			}
			else
			{
				strncat(tempStr, "/", 1);
			}
			
			check = 0;
			
			strncpy(tempopp, opp->id, strlen(opp->id));
			word = strtok(tempopp, token);
			word = strtok(NULL, token);
			att =  formula->attributes->front;
			memset(special, '\0', 32);
			check = 0;
			strncpy(special, word, strlen(word));
			specialword = strtok(special, token_2);
			while (att != NULL)
			{
				
				/*
				if(strncmp(word, att->alias, strlen(word)) == 0 && strncmp(word, att->alias, strlen(att->alias)) == 0)
				{
					char temp[32];
					char *wordatt;
					strncpy(temp, att->id, strlen(att->id));
					wordatt = strtok(temp, token);
					wordatt = strtok(NULL, token);
					strncat(tempStr, wordatt, strlen(wordatt));
				}
				att = att->next;	*/
				
				if (strncmp(specialword, "SUM", 3) == 0 || strncmp(specialword, "MIN", 3) == 0 || strncmp(specialword, "MAX", 3) == 0 || strncmp(specialword, "AVG", 3) == 0) 
				{
					strncat(tempStr, specialword, strlen(specialword));
					strncat(tempStr, "(", 1);
					specialword = strtok(NULL, token_2);
					check = 1;
				}
								
				if(strncmp(specialword, att->alias, strlen(specialword)) == 0 && strncmp(specialword, att->alias, strlen(att->alias)) == 0)
				{
					char temp[32];
					char *wordatt;
					strncpy(temp, att->id, strlen(att->id));
					wordatt = strtok(temp, token);
					wordatt = strtok(NULL, token);
					strncat(tempStr, wordatt, strlen(wordatt));
					if (check == 1)
					{
						strncat(tempStr, ")", 1);
					}
				}
				att = att->next;	
				
			}
			strncpy(opp->id, tempStr, strlen(tempStr));
			opp = opp->next;
		}
	}

	SELECTSTMT *result = NULL;
	result = headvars;
	result->tables = formula->tables;
	result->unionCase = formula->unionCase;
	result->minusCase = formula->minusCase;
	result->forall = formula->forall;
	result->conditions = formula->conditions;
	result->orConditions = formula->orConditions;
	result->having = formula->having;
	formula->tables = NULL;
	formula->conditions = NULL;
	formula->having = NULL;
	freeexpr(formula);
	return result;
}

/* ------------------------------------------------------------------
Function name: searchList
Purpose: To search a list for a item contains a given id
Parameters: item: The item to search for
		list: The list to search on
Return: Pointer to the first item satisfied
------------------------------------------------------------------*/
LIST_ITEM *searchList(char *item, LIST *list)
{
	LIST_ITEM *current = NULL;
 	if (list == NULL) 
	{
		fprintf(stderr, "In searchList: list == NULL\n");
		exit(1);
	}
	current = list->front;
	while (current != NULL) 
	{
		if (strncmp(current->id, item, strlen(item)) == 0)
			return current;
		else
			current = current->next;
	}
	return current;
}

/*-------------------------------------------------------
Function name: processEnding
Purpose: to process ending stucture, f.g. if there is a order by clause.
Parameters (endingStruct): ending struct
Return: the pointer to the select struct
 
--------------------------------------------------------*/
SELECTSTMT *processEnding(SELECTSTMT *endingStruct)
{
	if(endingStruct == NULL)
	{ 
		freeexpr(endingStruct);
		return NULL;
	}
	return endingStruct;
}

/*-------------------------------------------------------
Function name: processOrForm
Purpose:
	Process the conjunction formulas
Parameters:
	formula1, formula2: two sub formulas connected by 'or'
Returns:
	Pointer to the structure of the conjunction
	
------------------------------------------------------ */
SELECTSTMT *processOrForm(SELECTSTMT *formula1, SELECTSTMT *formula2)
{
	SELECTSTMT *result;
	if ((result=(SELECTSTMT*)calloc(1,sizeof(SELECTSTMT)))==NULL) {
		fprintf(stderr, "Not enough memory to allocate to list!");
		exit(1);
	}
	if (formula1 == NULL) {
		result->f_error = 'E';
		strncpy(result->errormsg, "Missing one side of and formula", MAXERRMSGLENGTH);
		return result;
	}
	if (formula2 == NULL) {
		result->f_error = 'E';
		strncpy(result->errormsg, "Missing one side of and formula", MAXERRMSGLENGTH);
		return result;
	}
	if (formula1->f_error == 'E') {
		freeexpr(result);
		return formula1;
	}
	if (formula2->f_error == 'E') {
		freeexpr(result);
		return formula2;
	}
	
	result->attributes = formula1->attributes;
	formula1->attributes = NULL;
	formula2->attributes = NULL;
	result->tables = mergeList(result->tables, formula1->tables);
	result->tables = mergeList(result->tables, formula2->tables);
	formula1->tables = NULL;
	formula2->tables = NULL;
	
	result->unionCase = 10;
	result->preCase = 10;
	
	freeexpr(formula1);
	free(formula1);
	freeexpr(formula2);
	free(formula2);
	return result;
}

/*-------------------------------------------------------
Function name: processAndNotForm
Purpose:
	Process the conjunction formulas
Parameters:
	formula1, formula2: two sub formulas connected by 'And Not'
Returns:
	Pointer to the structure of the conjunction
	
------------------------------------------------------ */
SELECTSTMT *processAndNotForm(SELECTSTMT *formula1, SELECTSTMT *formula2)
{
	SELECTSTMT *result;
	if ((result=(SELECTSTMT*)calloc(1,sizeof(SELECTSTMT)))==NULL) {
		fprintf(stderr, "Not enough memory to allocate to list!");
		exit(1);
	}
	if (formula1 == NULL) {
		result->f_error = 'E';
		strncpy(result->errormsg, "Missing one side of and formula", MAXERRMSGLENGTH);
		return result;
	}
	if (formula2 == NULL) {
		result->f_error = 'E';
		strncpy(result->errormsg, "Missing one side of and formula", MAXERRMSGLENGTH);
		return result;
	}
	if (formula1->f_error == 'E') {
		freeexpr(result);
		return formula1;
	}
	if (formula2->f_error == 'E') {
		freeexpr(result);
		return formula2;
	}
	
	result->attributes = mergeList(result->attributes, formula1->attributes);
	result->attributes = mergeList(result->attributes, formula2->attributes);
	formula1->attributes = NULL;
	formula2->attributes = NULL;
	result->tables = mergeList(result->tables, formula1->tables);
	result->tables = mergeList(result->tables, formula2->tables);
	formula1->tables = NULL;
	formula2->tables = NULL;
	
	result->minusCase = 10;
	result->unionCase = formula2->unionCase;
	result->preCase = 10;
	
	freeexpr(formula1);
	freeexpr(formula2);
	
	return result;
}

/* ------------------------------------------------------
Function name: preList
Purpose: 	to merge the attributes listed in format of (exist att1, att2, ...)
Parameters: attribute name, and list
Returns:	new list with addtional attribute name
------------------------------------------------------ */
SELECTSTMT* preList(char* cond, SELECTSTMT* list)
{
	SELECTSTMT* result;
	if (list == NULL)
	{
		if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL){
			fprintf(stderr, "Not enough memory to allocate to list!\n");
			exit(1);
		}
		if (cond == NULL)
		{
			result->f_error = 'E';
		    strcpy(result->errormsg, "syntax error after keyword EXISTS ");
		}
		else {
			result->pre = addToFront(cond, result->pre, 'Z');
		}
	
	}
	else {
		result = list;
		if (cond == NULL)
		{
			result->f_error = 'E';
		    strcpy(result->errormsg, "syntax error after keyword EXISTS ");
		}
		else {
			result->pre = addToFront(cond, result->pre, 'Z');
		}
	}
	return result;

}


/* ------------------------------------------------------
Function name: preListForAll
Purpose: 	to mark forall case
Parameters: list and mark
Returns:	new list with mark
------------------------------------------------------ */
SELECTSTMT* preListForAll(SELECTSTMT* list)
{
	list->forall = 10;
	/*
	LIST_ITEM* temp = list->tables->front;
	while (temp != NULL)
	{
		temp->forall = 10;
		temp = temp->next;
	}
	*/
	return list;
}

/* ------------------------------------------------------
Function name: conditionTreat
Purpose:	to check if there are two same attributes name in two table. If found, it shoud set condition such as T1.name = T2.name
Parameters: the list of attributes in (exist att1, ...) and the list of attributes with table name
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* conditionTreat(SELECTSTMT* cond, SELECTSTMT* list)
{
	if (cond->f_error == 'E')
		return cond;
  	if (list->f_error == 'E')
    	return list;
	LIST_ITEM* temp = cond->pre->front;
	char condition[MAXLENGTH] = {'\0'};
	int index = 0;
	while (temp != NULL ) 
	{
		LIST_ITEM* att =  list->attributes->front;
		while (att != NULL)
		{
			uppercase(temp->id);
			//if(strstr(strstr(att->id, "."), temp->id)!= NULL)
			if(strncmp(att->alias, temp->id, strlen(att->alias)) == 0 && strncmp(att->alias, temp->id, strlen(temp->id)) == 0)
			{
				strncat(condition, att->id, strlen(att->id));
				index++;
				att->quantified = 10;
				if (index == 1)
				{
					strncat(condition, "=", 1);
				}
			}
			if(index == 2)
				break;
			att = att->next;
		}
		temp = temp->next;
		if (index == 2)
		{
			list->conditions = (LIST*) addToFront(condition, list->conditions,'Z');
		}
		for(index = 0; index < 16; index++)
		{
			condition[index] = '\0';
		}
		index = 0;
	}
	if (cond->forall == 10)
	{
		list->forall = 10;
	}
	freeexpr(cond);
	list->preCase = 0; /*roll back*/
	return list;
}

/* ------------------------------------------------------
Function name: proList
Purpose:	the string read from query in procodition defination and save them in conditions of SELECTSTMT
Parameters: the strings of prolist read from query 
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* proList(char* v1, char* opp, char* v2, char* comp, char* v3, SELECTSTMT* havings, SELECTSTMT* list, int Case)
{
	//if time allowed, modify this function to do more check /*comp=compare*/
 printf(comp);
	SELECTSTMT* result;
	char temp[MAXLENGTH] = {'\0'};
	char* pch;
	if (list != NULL)
	{
		result = list;
	}
	else {
		if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL)
		{
			fprintf(stderr, "Not enough memory to allocate to list!\n");
			exit(1);
		}
	}
	//case 1
	if (havings == NULL)
	{
		if (opp == NULL) 
		{
			strncpy(temp, v1, strlen(v1));
			strcat(temp, comp);
			strncat(temp, v3, strlen(v3));              /* v1 comp v3 */
			if (Case == 0)
			{
				result->conditions = addToFront(temp, result->conditions, 'Z');
			}
			if (Case == 2) /*id = " or " id*/
			{
				strncat(temp, " or ", 4);
				strncat(temp, result->conditions->front->id, strlen(result->conditions->front->id));
				strncpy(result->conditions->front->id, temp, strlen(temp));
			}
		}
		else {//case 2
			strncpy(temp, v1, strlen(v1));
			strncat(temp, opp, strlen(opp));
			strncat(temp, v2, strlen(v2));
			strncat(temp, comp, strlen(comp));
			strncat(temp, v3, strlen(v3));
			result->conditions = addToFront(temp, result->conditions, 'Z'); /* v1 opp v2 compare v3 */
		}
	}
	else
	{
		strncpy(temp, havings->orderby->front->id, strlen(havings->orderby->front->id));
		pch = strstr(temp,"ASC");
		strncpy(pch,"\0\0\0",3);
		strncat(temp, comp, strlen(comp));
		strncat(temp, v3, strlen(v3));
		result->having = addToFront(temp, result->having, 'H'); 
	}
	freeexpr(havings);
	return result;

}

/* ------------------------------------------------------
Function name: proCondition
Purpose:	to deal with the condition in such format (exist att1...) (table_name(att1, ....) and procondition )).  Here procondition is: attributes > sth or sum(attribute) = sth or etc. 
Parameters:  assembled proconditon
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* proCondition(SELECTSTMT* list, SELECTSTMT* cond)  /* list = relation , cond = variable compare constant =condition */
{
	char pch[1024] = {'\0'};
	char clear[3] = {'\0'};
	int index;
	LIST_ITEM* temp = NULL;
	LIST_ITEM* condition = cond->conditions->front;
	LIST_ITEM* listatt = NULL;
	int checked;
	while (condition != NULL)
	{
		char str[1024];
		strncpy(str, condition->id, strlen(condition->id));
		char end[1024] = {'\0'};
		char* pch_str;
		//change input such as A >= 3 and B = 4 into A>=3 and B=4 /*去掉input空格*/
		pch_str = strtok (str," ");
		strncpy(end, pch_str, strlen(pch_str));                        /* str = condition ,end = variable = pch_str */
		while (pch_str != NULL)
		{
			pch_str = strtok (NULL, " ");                                /* end = condition */
			if (pch_str != NULL) {
				if (strncmp(pch_str, "and", 3) == 0 || strncmp(pch_str, "or", 2) == 0) {
					strncat(end, " ", 1);
					strncat(end, pch_str, strlen(pch_str));
					strncat(end, " ", 1);
				}
				else {
					strncat(end, pch_str, strlen(pch_str));
				}			
			}	
		}
		//
		char* pch_end;
		char final[10][32] = {"\0"};
		pch_end = strtok (end, " ");
		int index = 0;
		char last[1024] = {"\0"};
		strncat(last, "(", 1);
		while (pch_end != NULL)
		{
			strncpy(final[index], pch_end, strlen(pch_end));
			pch_end = strtok (NULL, " ");
			index++;                                          /* index = 3 , final = {"variable","compare",""}*/
		}
		//
		int a = 0;
		for (; a < index; a++)
		{
			char temp[32] = {"\0"};
			strncpy(temp, final[a], strlen(final[a]));
			char *pch_temp;
			if (strstr(temp, ">=") != NULL) {
				pch_temp = strtok (temp, ">=");
				listatt = list->attributes->front;
				while(listatt != NULL) {
					if(strncmp(listatt->alias, pch_temp, strlen(pch_temp)) == 0 && strncmp(listatt->alias, pch_temp, strlen(listatt->alias)) == 0)
					{
						strncat(last, listatt->id, strlen(listatt->id));
						strncat(last, ">=", 2);
						pch_temp = strtok (NULL, ">=");
						strncat(last, pch_temp, strlen(pch_temp));
						checked = 1;
						break;
					}
					listatt= listatt -> next;
				}
			}
			else if (strstr(temp, "<>") != NULL) {
				pch_temp = strtok (temp, "<>");
				listatt = list->attributes->front;
				while(listatt != NULL) {
					if(strncmp(listatt->alias, pch_temp, strlen(pch_temp)) == 0 && strncmp(listatt->alias, pch_temp, strlen(listatt->alias)) == 0)
					{
						strncat(last, listatt->id, strlen(listatt->id));
						strncat(last, "<>", 2);
						pch_temp = strtok (NULL, "<>");
						strncat(last, pch_temp, strlen(pch_temp));
						checked = 1;
						break;
					}
					listatt= listatt -> next;
				}
			}
      else if (strstr(temp, "!=") != NULL) {
				pch_temp = strtok (temp, "!=");
				listatt = list->attributes->front;
				while(listatt != NULL) {
					if(strncmp(listatt->alias, pch_temp, strlen(pch_temp)) == 0 && strncmp(listatt->alias, pch_temp, strlen(listatt->alias)) == 0)
					{
						strncat(last, listatt->id, strlen(listatt->id));
						strncat(last, "!=", 2);
						pch_temp = strtok (NULL, "!=");
						strncat(last, pch_temp, strlen(pch_temp));
						checked = 1;
						break;
					}
					listatt= listatt -> next;
				}
			}
			else if (strstr(temp, "<=") != NULL) {
				pch_temp = strtok (temp, "<=");
				listatt = list->attributes->front;
				while(listatt != NULL) {
					if(strncmp(listatt->alias, pch_temp, strlen(pch_temp)) == 0 && strncmp(listatt->alias, pch_temp, strlen(listatt->alias)) == 0)
					{
						strncat(last, listatt->id, strlen(listatt->id));
						strncat(last, "<=", 2);
						pch_temp = strtok (NULL, "<=");
						strncat(last, pch_temp, strlen(pch_temp));
						checked = 1;
						break;
					}
					listatt= listatt -> next;
				}
			}
			else if (strstr(temp, "=") != NULL) {
				pch_temp = strtok (temp, "=");
				listatt = list->attributes->front;
				while(listatt != NULL) {
					if(strncmp(listatt->alias, pch_temp, strlen(pch_temp)) == 0 && strncmp(listatt->alias, pch_temp, strlen(listatt->alias)) == 0)
					{
						strncat(last, listatt->id, strlen(listatt->id));
						strncat(last, "=", 1);
						pch_temp = strtok (NULL, "=");
						strncat(last, pch_temp, strlen(pch_temp));
						checked = 1;
						break;
					}
					listatt= listatt -> next;
				}
			}
			else if (strstr(temp, "<") != NULL) {
				pch_temp = strtok (temp, "<");
				listatt = list->attributes->front;
				while(listatt != NULL) {
					if(strncmp(listatt->alias, pch_temp, strlen(pch_temp)) == 0 && strncmp(listatt->alias, pch_temp, strlen(listatt->alias)) == 0)
					{
						strncat(last, listatt->id, strlen(listatt->id));
						strncat(last, "<", 1);
						pch_temp = strtok (NULL, "<");
						strncat(last, pch_temp, strlen(pch_temp));
						checked = 1;
						break;
					}
					listatt= listatt -> next;
				}
			}
			else if (strstr(temp, ">") != NULL) {
				pch_temp = strtok (temp, ">");
				listatt = list->attributes->front;
				while(listatt != NULL) {
					if(strncmp(listatt->alias, pch_temp, strlen(pch_temp)) == 0 && strncmp(listatt->alias, pch_temp, strlen(listatt->alias)) == 0)
					{
						strncat(last, listatt->id, strlen(listatt->id));
						strncat(last, ">", 1);
						pch_temp = strtok (NULL, ">");
						strncat(last, pch_temp, strlen(pch_temp));
						checked = 1;
						break;
					}
					listatt= listatt->next;
				}
			}
			else {
				if (checked == 1) {
					strncat(last, " ", 1);
					strncat(last, temp, strlen(temp));
					strncat(last, " ", 1);
					checked = 0;
				}
			}
		}
		strncat(last, ")", 1);
		if (checked == 1)
		{
			strncpy(condition->id, last, strlen(last));
			(condition->id)[strlen(last)] = '\0';
		}
		condition = condition -> next;
	}	
	list->conditions = cond->conditions;
	list->having = cond->having;
	cond->having = NULL;
	cond->conditions = NULL;
	freeexpr(cond);
	list->preCase = 10;
	return list;
}

/* ------------------------------------------------------
Function name: doubleVariableList
Purpose:	deal with the format sum(sth) + / -  count(sth)
Parameters: operator: sum, count, max ... , operation +-/ 
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* doubleVariableList(char* keyword1, char* v1, char* opp, char* keyword2, char* v2)
{
	char agg1[6] = {'\0'};
	char agg2[6] = {'\0'};
	char temp1[MAXLENGTH] = {'\0'};
	char temp2[MAXLENGTH] = {'\0'};
	SELECTSTMT*	result;
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate to list!\n");
		exit(1);
	}
	strncpy(agg1, keyword1, strlen(keyword1));
	strncpy(agg2, keyword2, strlen(keyword2));
	uppercase(agg1);
	uppercase(agg2);
	
	if((strncmp(agg1,"COUNT", 5) == 0 && strlen(agg1) == 5) || (strlen(agg1) == 3 && (strncmp(agg1,"SUM", 3) == 0 || strncmp(agg1,"AVG", 3) == 0 
		||strncmp(agg1,"MAX", 3) == 0 ||strncmp(agg1,"MIN", 3) == 0)))
	{
		strncpy(temp1, agg1, strlen(agg1));
		strncat(temp1, "(", 1);
		uppercase(v1);
		strncat(temp1, v1, strlen(v1));
		strncat(temp1, ")", 1);
	}
	else
	{
		result->f_error = 'E';
		strncpy(result->errormsg, "Invalid keyword ", 20);
		strncat(result->errormsg, keyword1,  strlen(keyword1));
		return result;
	}
	
	if((strncmp(agg2,"COUNT", 5) == 0 && strlen(agg2) == 5) || (strlen(agg2) == 3 && (strncmp(agg2,"SUM", 3) == 0 || strncmp(agg2,"AVG", 3) == 0 
		||strncmp(agg2,"MAX", 3) == 0 ||strncmp(agg2,"MIN", 3) == 0)))
	{
		strncpy(temp2, agg2, strlen(agg2));
		strncat(temp2, "(", 1);
		uppercase(v2);
		strncat(temp2, v2, strlen(v2));
		strncat(temp2, ")", 1);
	}
	else
	{
		result->f_error = 'E';
		strncpy(result->errormsg, "Invalid keyword ", 20);
		strncat(result->errormsg, keyword2,  strlen(keyword2));
		return result;
	}
	freeexpr(result);
	SELECTSTMT*	finalresult = variableList(temp1, NULL, opp, NULL, temp2);
	finalresult->opattributes->count = -1;
	return finalresult;
}


/*--------------------------------------------------------------end Query Function-------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*													Oracle function
						1. sql_error
						2. oracle_disconnect
						3. oracle_connect
						4. alloc_descriptors
						5. set_bind_variables
						6. process_select_list
*/
			
/* -----------------------------------------------------------------------------
Function name: sqlError
Purpose: To handle any sql errors that arise from executing the sql statement.
Parameters: none
Returns: nothing
------------------------------------------------------------------------------*/
void sql_error()
{
    int i;
    f_oracle_error = 'T';
    fprintf (stdout, "\n\n%.70s\n",sqlca.sqlerrm.sqlerrmc);
    if (parse_flag)
        fprintf (stdout, "Parse error at character offset %d in SQL statement.\n", sqlca.sqlerrd[4]);
    /* exec sql whenever sqlerror continue; */ 

    /* exec sql rollback work; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 1;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )81;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


    longjmp(jmp_continue, 1);
}

/* -----------------------------------------------------------------------------
Function name: oracle_disconnect
Purpose:       To disconnect from Oracle
Parameters: none
Returns: nothing
------------------------------------------------------------------------------*/
void oracle_disconnect()
{
	//printf("oracle_disconnect\n");
	int i;
	for (i = 0; i < MAX_ITEMS; i++)
	{    
		if (bind_dp->V[i] != (char *) 0)
			free(bind_dp->V[i]);
		free(bind_dp->I[i]);   /* MAX_ITEMS were allocated. */
		if (select_dp->V[i] != (char *) 0)
			free(select_dp->V[i]);
		free(select_dp->I[i]); /* MAX_ITEMS were allocated. */
	}
	sqlclu(bind_dp);
	sqlclu(select_dp);
	/* exec sql whenever sqlerror continue; */ 

	/* Close the cursor. */
	/* exec sql close c; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 1;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )96;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	/* exec sql commit work release; */ 

{
 struct sqlexd sqlstm;
 sqlstm.sqlvsn = 12;
 sqlstm.arrsiz = 1;
 sqlstm.sqladtp = &sqladt;
 sqlstm.sqltdsp = &sqltds;
 sqlstm.iters = (unsigned int  )1;
 sqlstm.offset = (unsigned int  )111;
 sqlstm.cud = sqlcud0;
 sqlstm.sqlest = (unsigned char  *)&sqlca;
 sqlstm.sqlety = (unsigned short)4352;
 sqlstm.occurs = (unsigned int  )0;
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


	fprintf(stdout, "\nHave a good day!\n");
	/* exec sql whenever sqlerror do sql_error(); */ 

	return;
}

/* ------------------------------------------------------------------------------
Function name: oracle_connect
Purpose:       To connect to Oracle
Parameters: none
Returns: 0      if connects to Oracle successfully
	   -1     if unsuccessful
---------------------------------------------------------------------------------*/
int oracle_connect(char * p_userid, char * p_passwd)
{
    /* exec sql begin declare section; */ 

  char    myid[120];
/* exec sql end declare section; */ 


  strcpy(myid, p_userid);
  strcat(myid, "/");
  strcat(myid, p_passwd);
    
    /* exec sql whenever sqlerror goto connect_error; */ 


    /* exec sql connect :myid; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )10;
    sqlstm.offset = (unsigned int  )126;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)myid;
    sqlstm.sqhstl[0] = (unsigned long )120;
    sqlstm.sqhsts[0] = (         int  )120;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlstm.sqlcmax = (unsigned int )100;
    sqlstm.sqlcmin = (unsigned int )2;
    sqlstm.sqlcincr = (unsigned int )1;
    sqlstm.sqlctimeout = (unsigned int )0;
    sqlstm.sqlcnowait = (unsigned int )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) goto connect_error;
}


 
  /*  fprintf(yyout, "\nConnected to ORACLE\n");*/

    /* Allocate memory for the select and bind descriptors. */
    if (alloc_descriptors(MAX_ITEMS, MAX_VNAME_LEN, MAX_INAME_LEN) != 0)
        exit(1);

    return 0;

  connect_error:
    fprintf(stderr, "Cannot connect to ORACLE\n");
    return -1;
}

/* -----------------------------------------------------------------------------------
Function name: alloc_descriptors
Purpose:    	To allocate the BIND and SELECT descriptors using sqlald(). Also 
			allocate the pointers to indicator variables in each descriptor.  The
			pointers to the actual bind variables and the select-list items are
			realloc'ed in the set_bind_variables() or process_select_list() routines.  
			This routine allocates 1 byte for select_dp->V[i] and bind_dp->V[i], so 
			the realloc will work correctly.
Returns:	0	success
			-1	failure
------------------------------------------------------------------------------------*/
int alloc_descriptors(int size, int max_vname_len, int max_iname_len)
{
	//printf("alloc_descriptors\n");
	int i;
    if ((bind_dp = sqlald(size, max_vname_len, max_iname_len)) == (SQLDA *) 0)
    {
        fprintf(stderr, "Cannot allocate memory for bind descriptor.");
        return -1;  /* Have to exit in this case. */
    }
    if ((select_dp = sqlald (size, max_vname_len, max_iname_len)) == (SQLDA *) 0)
    {
        fprintf(stderr, "Cannot allocate memory for select descriptor.");
        return -1;
    }
    select_dp->N = MAX_ITEMS;
    for (i = 0; i < MAX_ITEMS; i++) {
        bind_dp->I[i] = (short *) malloc(sizeof (short));
        select_dp->I[i] = (short *) malloc(sizeof(short));
        bind_dp->V[i] = (char *) malloc(1);
        select_dp->V[i] = (char *) malloc(1);
    }  
    return 0;
}

/* ------------------------------------------------------------------------------------------------
Function name: set_bind_variables
Purpose:       To realloc the pointers to the actual bind variables and the select-list items.
Parameters:	none
Returns: nothing
-------------------------------------------------------------------------------------------------*/
void set_bind_variables()
{
    int i, n;
    char bindVar[64] = {'\0'};
    /* exec sql whenever sqlerror do sql_error(); */ 

    bind_dp->N = MAX_ITEMS;  /* Initialize count of array elements. */
    /* exec sql describe bind variables for s into bind_dp; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )157;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)bind_dp;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error();
}


    if (bind_dp->F < 0) {
        fprintf (stdout, "\nToo many bind variables (%d), maximum is %d\n.", bind_dp->F, MAX_ITEMS);
        return;
    }
    bind_dp->N = bind_dp->F;
    for (i = 0; i < bind_dp->F; i++) {
        fprintf (stdout, "\nEnter value for bind variable %.*s:  ", (int)bind_dp->C[i], bind_dp->S[i]);
        fgets(bindVar, sizeof bindVar, stdin);
        n = strlen(bindVar) - 1;
        bind_dp->L[i] = n;
        bind_dp->V[i] = (char *) realloc(bind_dp->V[i], (bind_dp->L[i] + 1));            
        strncpy(bind_dp->V[i], bindVar, n);
        if ((strncmp(bind_dp->V[i], "NULL", 4) == 0) || (strncmp(bind_dp->V[i], "null", 4) == 0))
            *bind_dp->I[i] = -1;
        else
            *bind_dp->I[i] = 0;
        bind_dp->T[i] = 1;
    }  
}

/* -----------------------------------------------
Function name: process_select_list
Purpose:       To realloc the pointers to the actual bind variables and the select-list items and display the results of the query to stdout.
Parameters:	none
Returns: nothing
------------------------------------------------- */
void process_select_list()
{
	//printf("process_select_list\n");
    int i, null_ok, precision, scale;
    if ((strncmp(sql_statement, "SELECT", 6) != 0) && (strncmp(sql_statement, "select", 6) != 0))
    {
        select_dp->F = 0;
        return;
    }
    select_dp->N = MAX_ITEMS;
    
    /* exec sql describe select list for s into select_dp; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )176;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlstm.sqhstv[0] = (unsigned char  *)select_dp;
    sqlstm.sqhstl[0] = (unsigned long )0;
    sqlstm.sqhsts[0] = (         int  )0;
    sqlstm.sqindv[0] = (         short *)0;
    sqlstm.sqinds[0] = (         int  )0;
    sqlstm.sqharm[0] = (unsigned long )0;
    sqlstm.sqadto[0] = (unsigned short )0;
    sqlstm.sqtdso[0] = (unsigned short )0;
    sqlstm.sqphsv = sqlstm.sqhstv;
    sqlstm.sqphsl = sqlstm.sqhstl;
    sqlstm.sqphss = sqlstm.sqhsts;
    sqlstm.sqpind = sqlstm.sqindv;
    sqlstm.sqpins = sqlstm.sqinds;
    sqlstm.sqparm = sqlstm.sqharm;
    sqlstm.sqparc = sqlstm.sqharc;
    sqlstm.sqpadto = sqlstm.sqadto;
    sqlstm.sqptdso = sqlstm.sqtdso;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
    if (sqlca.sqlcode < 0) sql_error();
}



    if (select_dp->F < 0)
    {
        fprintf (stdout, "Too many select-list items (%d), maximum is %d\n", (select_dp->F), MAX_ITEMS);
        return;
    }
    select_dp->N = select_dp->F;
   
    fprintf (stdout, "\n");
    for (i = 0; i < select_dp->F; i++)
    {
        sqlnul (&(select_dp->T[i]), &(select_dp->T[i]), &null_ok);

        switch (select_dp->T[i])
        {
            case  1 : 
					break;
            case  2 : 
                sqlprc (&(select_dp->L[i]), &precision, &scale);              
                if (precision == 0) precision = 40;                    
                if (scale > 0)
                    select_dp->L[i] = sizeof(float);
                else
                    select_dp->L[i] = sizeof(int);
                break;
            case  8 : /* LONG datatype */
                select_dp->L[i] = 240;
                break;
            case 11 : /* ROWID datatype */
                select_dp->L[i] = 18;
                break;
            case 12 : /* DATE datatype */
                select_dp->L[i] = 9;
                break;
            case 23 : /* RAW datatype */
                break;
            case 24 : /* LONG RAW datatype */
                select_dp->L[i] = 240;
                break;
        }
         if (select_dp->T[i] != 2)
            select_dp->V[i] = (char *) realloc(select_dp->V[i],
                                    select_dp->L[i] + 1);  
         else
            select_dp->V[i] = (char *) realloc(select_dp->V[i],
                                    select_dp->L[i]);  
        if (select_dp->T[i] == 2)
			if (scale > 0)
				fprintf (stdout, "%.*s ", select_dp->L[i]+3, select_dp->S[i]);
	        else
				fprintf (stdout, "%.*s ", select_dp->L[i], select_dp->S[i]);
        else
            fprintf (stdout, "%-.*s ", select_dp->L[i], select_dp->S[i]);
        if (select_dp->T[i] != 24 && select_dp->T[i] != 2)
			select_dp->T[i] = 1;
        if (select_dp->T[i] == 2)
			if (scale > 0)
				select_dp->T[i] = 4;  /* float */
			else
				select_dp->T[i] = 3;  /* int */
    }
    fprintf (stdout, "\n");
    /* exec sql whenever not found goto end_select_loop; */ 


    for (;;)
    {
        /* exec sql fetch c using descriptor select_dp; */ 

{
        struct sqlexd sqlstm;
        sqlstm.sqlvsn = 12;
        sqlstm.arrsiz = 4;
        sqlstm.sqladtp = &sqladt;
        sqlstm.sqltdsp = &sqltds;
        sqlstm.iters = (unsigned int  )1;
        sqlstm.offset = (unsigned int  )195;
        sqlstm.selerr = (unsigned short)1;
        sqlstm.cud = sqlcud0;
        sqlstm.sqlest = (unsigned char  *)&sqlca;
        sqlstm.sqlety = (unsigned short)4352;
        sqlstm.occurs = (unsigned int  )0;
        sqlstm.sqfoff = (         int )0;
        sqlstm.sqfmod = (unsigned int )2;
        sqlstm.sqhstv[0] = (unsigned char  *)select_dp;
        sqlstm.sqhstl[0] = (unsigned long )0;
        sqlstm.sqhsts[0] = (         int  )0;
        sqlstm.sqindv[0] = (         short *)0;
        sqlstm.sqinds[0] = (         int  )0;
        sqlstm.sqharm[0] = (unsigned long )0;
        sqlstm.sqadto[0] = (unsigned short )0;
        sqlstm.sqtdso[0] = (unsigned short )0;
        sqlstm.sqphsv = sqlstm.sqhstv;
        sqlstm.sqphsl = sqlstm.sqhstl;
        sqlstm.sqphss = sqlstm.sqhsts;
        sqlstm.sqpind = sqlstm.sqindv;
        sqlstm.sqpins = sqlstm.sqinds;
        sqlstm.sqparm = sqlstm.sqharm;
        sqlstm.sqparc = sqlstm.sqharc;
        sqlstm.sqpadto = sqlstm.sqadto;
        sqlstm.sqptdso = sqlstm.sqtdso;
        sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
        if (sqlca.sqlcode == 1403) goto end_select_loop;
        if (sqlca.sqlcode < 0) sql_error();
}


        for (i = 0; i < select_dp->F; i++)
        {

            if (*select_dp->I[i] < 0)
                if (select_dp->T[i] == 4) 
                  fprintf (stdout, "%-*c ",(int)select_dp->L[i]+3, ' ');
                else
                  fprintf (stdout, "%-*c ",(int)select_dp->L[i], ' ');
            else
                if (select_dp->T[i] == 3)     /* int datatype */
                  fprintf (stdout, "%*d ", (int)select_dp->L[i], *(int *)select_dp->V[i]);
                else if (select_dp->T[i] == 4)     /* float datatype */
                  fprintf (stdout, "%*.2f ", (int)select_dp->L[i], *(float *)select_dp->V[i]);
                else                          /* character string */
				{ 
					*( select_dp->V[i] + select_dp->L[i])= '\0'; 
					fprintf (stdout, "%-*s ", (int)select_dp->L[i], select_dp->V[i]);
				}
        }
	fprintf (stdout, "\n");
    }
  end_select_loop:
  return;
}
/****************************************************************************************************************************************************************/


/****************************************************************Order By***************************************************************************************/
/* --------------------------------------------------
Function name: orderList
Purpose:
Parameters: 
Returns: 
---------------------------------------------------- */
SELECTSTMT* orderList(char *variable, char *keyword, SELECTSTMT *source, SELECTSTMT *variables)
{
	//code review: memory menagement pending	3/23
	SELECTSTMT* result = NULL;
	char tempstr[MAXLENGTH] = {'\0'};
	char order[5] = {'\0'};
	//LIST_ITEM* current = NULL;
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate to list!");
    	exit(1);
  	}
	//this is for two sepaical cases
	if (variable == NULL && source == NULL)
	{
		result = variables;
		return result;
	}
	
	if (variable == NULL && source != NULL)
	{
		result->orderby = mergeList(source->orderby, variables->orderby);
		return result;
	}
		
	
	if(variables != NULL && variables->f_error == 'E')
	{
		return variables;
	}
 	/*case 1: pending */
	if (keyword == NULL )
	{
		strncpy(tempstr, variable, strlen(variable));
		uppercase(tempstr);
		strncat(tempstr, " ASC", 4);
		if (variables != NULL) 
		{
			//result->attributes = variables->attributes;
			result = variables;
		}
		result->orderby = (LIST*) addToFront(tempstr, result->orderby, 'V');		
	}	
	//case 2, 
	else
	{
		strncpy(order, keyword, strlen(keyword));
		uppercase(order);
		if((strncmp(order,"ASC",3) == 0 && strlen(order) == 3) || (strlen(order) == 4 && (strncmp(order,"DESC", 4) == 0)))
		{
			strncpy(tempstr, variable, strlen(variable));
			uppercase(tempstr);
			strncat(tempstr, " ", 1);
			strncat(tempstr, order, strlen(order));
			if (variables != NULL) 
			{
				//result->attributes = variables->attributes;
				result = variables;
			}
			result->orderby = (LIST*) addToFront(tempstr, result->orderby, 'V');		
		}
		else
		{
			result->f_error = 'E';
			strncpy(result->errormsg, keyword , strlen(keyword));
			strncat(result->errormsg, " not ASC or DESC", 16);
		}
	}
 	return result;
}


/* --------------------------------------------------
Function name: stringList
Purpose: 
Parameters: 
Returns: 
---------------------------------------------------- */
SELECTSTMT* stringList(char* v1, char* v2, char* v3, char* v4)
{
	//3-18: here, pending v1--v4 necessary empty string check, if time allowed, it would be added	
	SELECTSTMT* result = NULL;
	char tempstr[MAXLENGTH] = {'\0'};
	char agg[6] = {'\0'}; //aggregates
	char opp[1] = {'\0'};
	char order[5] = {'\0'};
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate to list!");
    	exit(1);
  	}
	if (v2 == NULL)
	{
		strncpy(agg, v1, strlen(v1));
		uppercase(agg);
		if((strncmp(agg,"COUNT", 5) == 0 && strlen(agg) == 5) || (strlen(agg) == 3 && (strncmp(agg,"SUM", 3) == 0 || strncmp(agg,"AVG", 3) == 0 
				||strncmp(agg,"MAX", 3) == 0 ||strncmp(agg,"MIN", 3) == 0)))
		{
			strncpy(tempstr, agg, strlen(agg));
			strncat(tempstr, "(", 1);
			uppercase(v3);
			strncat(tempstr, v3, strlen(v3));
			strncat(tempstr, ")", 1);
			if (v4 != NULL)
			{
				strncpy(order, v4, strlen(v4));
				uppercase(order);
				if((strncmp(order,"ASC",3) == 0 && strlen(order) == 3) || (strlen(order) == 4 && (strncmp(order,"DESC", 4) == 0)))
				{
					strncat(tempstr, " ", 1);
					strncat(tempstr, order, strlen(order));
				}
				else
				{
					result->f_error = 'E';
					strncpy(result->errormsg, v4 , strlen(v4));
					strncat(result->errormsg, " not ASC or DESC", 16);
				}
				
			}
			else
			{
				strncat(tempstr, " ASC", 4);				
			}
			result->orderby = addToFront(tempstr, result->orderby, 'G');	
			//pending, if time allowed,  followed would be prepared for error check, see notes.
			
		}
		else
		{
			result->f_error = 'E';
			strncpy(result->errormsg, "Invalid keyword ", 20);
			strncat(result->errormsg, v4, strlen(v4));
		}
	}
	else
	{
		strncpy(opp, v2, strlen(v2));
		uppercase(opp);
		if(strncmp(opp,"+",1) == 0 || strncmp(opp,"-", 1) == 0 || strncmp(opp,"*", 1) == 0 ||strncmp(opp,"/", 1) == 0)
		{
			uppercase(v1);
			strncpy(tempstr, v1, strlen(v1));
			strncat(tempstr, opp, strlen(opp));
			uppercase(v3);
			strncat(tempstr, v3, strlen(v3));
			if (v4 != NULL)
			{
				strncpy(order, v4, strlen(v4));
				uppercase(order);
				if((strncmp(order,"ASC",3) == 0 && strlen(order) == 3) || (strlen(order) == 4 && (strncmp(order,"DESC", 4) == 0)))
				{
					strncat(tempstr, " ", 1);
					strncat(tempstr, order, strlen(order));
				}
				else
				{
					result->f_error = 'E';
					strncpy(result->errormsg, v4 , strlen(v4));
					strncat(result->errormsg, " not ASC or DESC", 16);
				}
				
			}
			else
			{
				strncat(tempstr, " ASC", 4);				
			}
			result->orderby = addToFront(tempstr, result->orderby, 'G');	
			//pending, if time allowed,  followed would be prepared for error check, see notes.
		}
		else
		{
			result->f_error = 'E';
			strncpy(result->errormsg, "Invalid opperator ", 20);
			strncat(result->errormsg, v2,  strlen(v2));
		}
	}
 	return result;
}

/**************************************************************End Order By***************************************************************************************/

/**************************************************************Create Table***************************************************************************************/

/* ------------------------------------------------------
Function name: newElements
Purpose: assemble the attributes in the created table 	
Parameters: attribute, and assembled list
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* newElements(char* v1, SELECTSTMT* list)
{
	SELECTSTMT*	result;
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate to list!\n");
		exit(1);
	}
	if(list != NULL)
	{
		result->attributes = addToFront(v1, list->attributes, 'V');
		list->attributes = NULL;
		list->tables = NULL; //strange issue: system allocate unreadable memory to it, so set null. what happens? 
		list->aggregates = NULL;
		list->opattributes = NULL;
		//freeexpr(list);
	}
	else
	{
		result->attributes = addToFront(v1, result->attributes, 'V');
	}
	return result;
}

/* ------------------------------------------------------
Function name: tempTable
Purpose:	create temp table (format: t1 := {S#,P#|(EXISTS QTY) (SP(S#,P#,QTY) and QTY > 1000)};)
Parameters: table name and assembled list of attributes in table 
Returns:	SELECTSTMT
------------------------------------------------------ */
SELECTSTMT* tempTable(char* v1, SELECTSTMT* list)
{
	SELECTSTMT*	result;
	if ((result = (SELECTSTMT*)calloc(1, sizeof(SELECTSTMT))) == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate to list!\n");
		exit(1);
	}
	result->tables = addToFront(v1, result->tables, 'T');
	if(list != NULL)
	{
		result->attributes = list->attributes;
		list->attributes = NULL;
		freeexpr(list);
	}
	return result;
}

/* ------------------------------------------------------
Function name: createTable
Purpose:	Execute a select structure by translating it to a SQL statement
Parameters: selectStruct: the query to be executed endingStruct: the ending structure to be combined with query
Returns:	nothing
------------------------------------------------------ */
void createTable(SELECTSTMT * newTable, SELECTSTMT * selectStruct, SELECTSTMT *endingStruct)
{
	char sqlStmt[MAXSTMTLENGTH] = {'\0'};
	if (selectStruct == NULL) 
	{
   		fprintf(yyout, "Empty query\n");
		fprintf(yyout, "\nDRC> ");
		freeexpr(selectStruct);
		freeexpr(endingStruct);
   		return;
 	}
	if(selectStruct ->f_error == 'E') 
	{
		fprintf(yyout, "\n%s\n", selectStruct->errormsg);
		fprintf(yyout, "\nDRC> ");
		freeexpr(selectStruct);
		freeexpr(endingStruct);
		return;
	}
	//we do not care endingStruct unless it has problme.
	if(endingStruct != NULL)
	{
		if(endingStruct ->f_error == 'E')
		{
			fprintf(yyout, "\n%s\n", endingStruct->errormsg);
			fprintf(yyout, "\nDRC> ");
			freeexpr(selectStruct);
			freeexpr(endingStruct);
			return;
		}
	}
	else
	{
        //selectStruct->orderby = endingStruct->orderby;
		createSqlStmt(sqlStmt, newTable, selectStruct);
		executeSql(sqlStmt, 'Y', 0);
	}
  	fprintf(yyout, "\nDRC> ");
	freeexpr(selectStruct);
	freeexpr(endingStruct);
	freeexpr(newTable);
}
/* ------------------------------------------------------
Function name: createSqlStmt
Purpose: implement sql query string for creating table  	
Parameters:  table name and sql query info
Returns: none.
------------------------------------------------------ */
void createSqlStmt(char *sqlStmt, SELECTSTMT * Table, SELECTSTMT *selectStruct)
{
	if (selectStruct == NULL)
	{
		return;
	}
	//in this case, we do not support * notation
	if (selectStruct->attributes == NULL || strncmp(selectStruct->attributes->front->id, "*", 1) == 0)  
	{
		return;
	}
	
	strcpy(sqlStmt, "CREATE TABLE ");
	strncat(sqlStmt, Table->tables->front->id,  strlen(Table->tables->front->id));
	strcat(sqlStmt, " AS SELECT");
	
	//suppose variables have the same number, if time allowed, I will add necessary check for it 
	if(selectStruct->aggregates != NULL)
	{

		selectStruct->groupby = addToFront(selectStruct->attributes->front->id, selectStruct->groupby, 'G');
		selectStruct->attributes = mergeList(selectStruct->attributes, selectStruct->aggregates);
		selectStruct->aggregates = NULL;
	}
	if(selectStruct->opattributes != NULL)
	{
		selectStruct->attributes = mergeList(selectStruct->attributes, selectStruct->opattributes);
		selectStruct->opattributes = NULL;
	}
	
	if(Table->attributes != NULL)
	{
		LIST_ITEM* temp1 = selectStruct->attributes->front;
		LIST_ITEM* temp2 = Table->attributes->front;
		while(temp1 != NULL)
		{
			strncat(temp1->id, " AS ", 4);
			strncat(temp1->id, temp2->id, strlen(temp2->id));
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
	
	strcat(sqlStmt, " DISTINCT ");
	createString(sqlStmt, selectStruct->attributes->front, 0);
	
	strcat(sqlStmt, "\n  FROM ");
	if (selectStruct->tables == NULL)
	{
		return;
	}
	createString(sqlStmt, selectStruct->tables->front, 0);
	if (selectStruct->conditions != NULL)
	{
		strcat(sqlStmt, "\n WHERE ");
		createString(sqlStmt, selectStruct->conditions->front, 1);
	}
	if (selectStruct->groupby != NULL)
	{
		strcat(sqlStmt, "\n GROUP BY ");
		createString(sqlStmt, selectStruct->groupby->front, 0);
	}
	if (selectStruct->having != NULL)
	{
		strcat(sqlStmt, "\nHAVING ");
		createString(sqlStmt, selectStruct->having->front, 0);
	}
	if (selectStruct->orderby != NULL)
	{
		strcat(sqlStmt, "\n ORDER BY ");
		createString(sqlStmt, selectStruct->orderby->front, 0);
	}
}

/**************************************************************End Create Table***********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*										unused function
				1. lowercase
				2. parseTableName

*/

/* --------------------------------------------------------------------
Function name: lowercase
Purpose:       To change a string into uppercase.
Parameters:	string		the string to change to uppercase
Returns:  	nothing
---------------------------------------------------------------------*/
void lowercase(char *string)
{
	//printf("lowercase\n");
	int i, length;
	length = strlen(string);
	for (i = 0; i < length; i++)
		string[i] = tolower(string[i]);
}

/*-------------------------------------------------------------------- 
Function name: parseTableName
Purpose: parse the table name from table.attribute
Parameters: attribute: attribute in the form table.attribute
Returns: the string contains table name
---------------------------------------------------------------------*/
void parseTableName(char *attribute, char *tableName)
{
	int i;
	for (i = 0; i < strlen(attribute); i++)
	{
		if (attribute[i] == '.')
		break;
		tableName[i] = attribute[i];
	}
	tableName[i] = '\0';
}

/*-------------------------------------------------------------
Function name: copyList
Purpose: To copy a list to a new list
Parameters: The list to be copy
Returns: The new list;
-------------------------------------------------------------*/
LIST *copyList(LIST *list)
{
	LIST *newList = NULL;
	LIST_ITEM *current = NULL;
	if (list == NULL) 
		return NULL;
	if ((newList = (LIST*) calloc(1, sizeof(LIST))) == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate to list!");
		exit(1);
	}
	current = list->front;
	while (current != NULL)
	{
		addToBack(current->id, newList, current->type);
		current = current->next;
	}
	return newList;
}
/* -------------------- ------------------------------------------------------------------------END ALL---------------------------------------------------------------------------------------------- */
