
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
    "trc.pc"
};


static unsigned int sqlctx = 4947;


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
5,0,0,1,0,0,17,186,0,0,1,1,0,1,0,1,5,0,0,
24,0,0,1,0,0,11,202,0,0,1,1,0,1,0,1,32,0,0,
43,0,0,1,0,0,20,276,0,0,1,1,0,1,0,3,32,0,0,
62,0,0,1,0,0,14,315,0,0,1,0,0,1,0,2,32,0,0,
81,0,0,1,0,0,15,361,0,0,0,0,0,1,0,
96,0,0,2,0,0,30,363,0,0,0,0,0,1,0,
111,0,0,0,0,0,27,397,0,0,4,4,0,1,0,1,97,0,0,1,10,0,0,1,10,0,0,1,10,0,0,
142,0,0,1,0,0,19,482,0,0,1,1,0,1,0,3,32,0,0,
161,0,0,1,0,0,20,582,0,0,1,1,0,1,0,3,32,0,0,
180,0,0,1,0,0,14,720,0,0,1,0,0,1,0,2,32,0,0,
199,0,0,4,0,0,31,781,0,0,0,0,0,1,0,
};


/* *************************************************
Filename:   trc.l
Author:     Duojie Chang
Student#:   100809247
************************************************** */

#include "trc.h"
#include <string.h>
#include <setjmp.h>

/* Maximum number of select-list items or bind variables. */
#define MAX_ITEMS         40
/* Maximum lengths of the _names_ of the
   select-list items or indicator variables. */
#define MAX_VNAME_LEN     30
#define MAX_INAME_LEN     30

#ifndef NULL
#define NULL  0
#endif

char *dml_commands[] = {"SELECT", "select", "INSERT", "insert",
                        "UPDATE", "update", "DELETE", "delete"};

/* exec sql begin declare section; */ 

   char    sql_statement[1024];
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

/* File pointers to be used for input and output
   to the interpreter. */
extern FILE *yyin, *yyout; 

/* Define a buffer to hold longjmp state info. */
jmp_buf jmp_continue;

/* A global flag for the error routine. */
int parse_flag = 0;
char f_oracle_error = 'F';
char sqlstmt[MAXSTMTLENGTH];
/************************************************************/

/* -----------------------------------------------
Function name: freeList
Purpose:
	To deallocate the memory allocated to
	an entire linked list.
Parameters:
	list: the list to dealocate memory for
Returns:
	nothing
------------------------------------------------- */
void freeList(LIST *list)
{
  LIST_ITEM *old, *current;
	
  if (list != NULL)
  {
    /* Loop through the linked list deallocating memory
       for each element and then the linked list
       structure itself. */
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

/* -----------------------------------------------
Function name: freeExpr
Purpose:
	To deallocate the memory allocated to
	a select statement structure.
Parameters:
	expr: the select statement to deallocate memory for
Returns:
	nothing
------------------------------------------------- */
void freeExpr(SELECTSTMT *expr)
{
  freeList(expr->attributes);
  freeList(expr->tables);
  freeList(expr->conditions);
  free(expr);
}

/* -----------------------------------------------
Function name: printList
Purpose:
	print the elements in the list(just for error check)
Parameters:
	p_list: a list
Returns:
	nothing
------------------------------------------------- */

void printList(LIST *p_list)
{
  LIST_ITEM *current;
  char temp[MAXSTMTLENGTH];

  if (p_list == NULL)
  {
    /*printf("\n In printList():\n");*/
    return;
  }

  current = p_list->front;

  strcpy(temp, current->id);
  strcat(temp, "&");
  if(current->aggregate != NULL)
  {
       strcat(temp, current->aggregate);
}
  current = current->next;
  while(current != NULL)
  {
    strcat(temp, " AND ");
    strcat(temp, current->id);
    strcat(temp, "&");
    if(current->aggregate!=NULL)
         strcat(temp, current->aggregate);
    current = current->next;
  }
  fflush(stdout);
}

/* -----------------------------------------------*/

LIST *executesqlstmt(int f_display, int create_flag, int for_drop)
{
  int i;
  LIST *columns;
 
 if(    table_error_flag == 1)
 {
   table_error_flag = 0;
   fprintf(yyout, "\nTRC>");
 }

 printf("\nThe sql statement is : \n%s\n", sqlstmt);

 if(freevar_error_flag == 1)
 {
	fprintf(yyout, "\n\nThe query is illegal since free variable is not in the result!!!!\n");
	freevar_error_flag = 0;
	fprintf(yyout, "\nTRC>");
        return columns;
 }


  fflush(stdout);

  if (strlen(sqlstmt) == 0)
    return NULL;

  /* Save current location to return to if
  sql error occurs. */
  i = setjmp(jmp_continue); 

  /* Execute the following code only if a
  sql error did not occur. */
  if (f_oracle_error == 'F')
  {
    strncpy(sql_statement, sqlstmt, MAXSTMTLENGTH);

    /* Prepare the statement and declare a cursor. */
    /* exec sql whenever sqlerror do sql_error(); */ 


    parse_flag = 1;     /* Set a flag for sql_error(). */
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


    /* Set the bind variables for any placeholders in the
    SQL statement. */
    set_bind_variables();
    

    /* Open the cursor and execute the statement.
     * If the statement is not a query (SELECT), the
     * statement processing is completed after the
     * OPEN.
     */

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



    if (f_display == 0)
    {
      /* Call the function that processes the select-list.
       * If the statement is not a query, this function
       * just returns, doing nothing.
       */
     
        
      process_select_list();


      if(create_flag == 1)  /*for create temp table*/
        fprintf(yyout, "\nTable created.\n\n");

      /* Tell user how many rows processed. */
      for (i = 0; i < 8; i++)
      {
      	if (strncmp(sql_statement, dml_commands[i], 6) == 0)
      	{
          fprintf(yyout, "\n%d row%c processed.\n\n", sqlca.sqlerrd[2],
          sqlca.sqlerrd[2] == 1 ? ' ' : 's');
          break;
        }
      }
    }
    else
      columns = retrieve_columns();
  }
  else
    f_oracle_error = 'F';

  sql_statement[0]='\0';

  if(f_display == 0 && for_drop != 1)
  {
    /*exist_flag = 0;*/
    exist_flag_count = 0;
    forall_flag = 0;
    layers = 0;
    not_exist_flag = 0;

    fprintf(yyout, "TRC> ");
  }

  return columns;
  
}

/* -----------------------------------------------
Function name: retrieve_columns
Purpose:       To place the retrieved column names
	       into a linked list and return the list.

Parameters:
	none

Returns:
	List 	Linked list containing the retrieved
        	column names.
------------------------------------------------- */
LIST *retrieve_columns()
{
	int null_ok;
    	LIST *columns = NULL;

	/* If the SQL statement is a SELECT, describe the
	select-list items.  The DESCRIBE function returns
	their names, datatypes, lengths (including precision
	and scale), and NULL/NOT NULL statuses. */
	
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


	
	/* If F is negative, there were more select-list
	  items than originally allocated by sqlald(). */
	if (select_dp->F < 0)
	{
		fprintf (yyout, "\nToo many select-list items (%d), maximum is %d\n",
	                -(select_dp->F), MAX_ITEMS);
	        return;
	}
	
	/* Set the maximum number of array elements in the
	   descriptor to the number found. */
	select_dp->N = select_dp->F;
	
	    
	/* Turn off high-order bit of datatype (in this example,
	   it does not matter if the column is NOT NULL). */
	sqlnul (&(select_dp->T[0]), &(select_dp->T[0]), &null_ok);
	
	/* Allocate space for the select-list data values.
           sqlald() reserves a pointer location for
           V[i] but does not allocate the full space for
           the pointer.  */

        select_dp->V[0] = (char *) realloc(select_dp->V[0],
				    select_dp->L[0] + 1);

	/* Coerce ALL datatypes except for LONG RAW and NUMBER to
           character. */
        select_dp->T[0] = 1;

	
	/* FETCH each row selected add the column values
	   to the linked list. */
    	/* exec sql whenever not found goto end_select_loop; */ 


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
          if (sqlca.sqlcode == 1403) goto end_select_loop;
          if (sqlca.sqlcode < 0) sql_error();
}



	  /*Append null to the end of the string
	    and add the string to the linked list. */
	  *( select_dp->V[0] + select_dp->L[0])= '\0';
	  columns = addtoback(select_dp->V[0], columns, 'I'); 

    	}

   end_select_loop:
   return columns;
}

/* -----------------------------------------------
Function name: oracle_disconnect
Purpose:       To disconnect from Oracle

Parameters:
        none

Returns:
        nothing
------------------------------------------------- */
void oracle_disconnect()
{
    int i, exetime;

    /* When done, free the memory allocated for
       pointers in the bind and select descriptors. */
  
     for (i = 0; i < MAX_ITEMS; i++)
      {
        if (bind_dp->V[i] != (char *) 0)
            free(bind_dp->V[i]);
        free(bind_dp->I[i]);   /* MAX_ITEMS were allocated. */
        if (select_dp->V[i] != (char *) 0)
            free(select_dp->V[i]);
        free(select_dp->I[i]); /* MAX_ITEMS were allocated. */
      }

    /* Free space used by the descriptors themselves. */
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
      sqlstm.offset = (unsigned int  )81;
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
      sqlstm.offset = (unsigned int  )96;
      sqlstm.cud = sqlcud0;
      sqlstm.sqlest = (unsigned char  *)&sqlca;
      sqlstm.sqlety = (unsigned short)4352;
      sqlstm.occurs = (unsigned int  )0;
      sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


        
    fprintf(yyout, "\nHave a good day!\n");

    /* exec sql whenever sqlerror do sql_error(); */ 

    parse_flag=0;
    
return;

}

/* -----------------------------------------------
Function name: oracle_connect
Purpose:       To connect to Oracle

Parameters:
	none

Returns:
	0      if connects to Oracle successfully
	-1     if unsuccessful
------------------------------------------------- */
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
    sqlstm.offset = (unsigned int  )111;
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
/**********************************************************
   Allocate the BIND and SELECT descriptors using sqlald().
   Also allocate the pointers to indicator variables
   in each descriptor.  The pointers to the actual bind
   variables and the select-list items are realloc'ed in
   the set_bind_variables() or process_select_list()
   routines.  This routine allocates 1 byte for select_dp->V[i]
   and bind_dp->V[i], so the realloc will work correctly.
**********************************************************/
int alloc_descriptors(int size, int max_vname_len, int max_iname_len)
{
    int i;

    /*
    * The first sqlald parameter determines the maximum number of
     * array elements in each variable in the descriptor. In
     * other words, it determines the maximum number of bind
     * variables or select-list items in the SQL statement.
     *
     * The second parameter determines the maximum length of
     * strings used to hold the names of select-list items
     * or placeholders.  The maximum length of column
     * names in ORACLE is 30, but you can allocate more or less
     * as needed.
     *
     * The third parameter determines the maximum length of
     * strings used to hold the names of any indicator
     * variables.  To follow ORACLE standards, the maximum
     * length of these should be 30.  But, you can allocate
     * more or less as needed.
     */
    if ((bind_dp =
            sqlald(size, max_vname_len, max_iname_len)) == (SQLDA *) 0)
    {
        fprintf(stderr,
            "Cannot allocate memory for bind descriptor.");
        return -1;  /* Have to exit in this case. */
    }

    if ((select_dp =
        sqlald (size, max_vname_len, max_iname_len)) == (SQLDA *) 0)
    {
        fprintf(stderr,
            "Cannot allocate memory for select descriptor.");
        return -1;
    }
    select_dp->N = MAX_ITEMS;

    /* Allocate the pointers to the indicator variables, and the
       actual data. */
    for (i = 0; i < MAX_ITEMS; i++) {
        bind_dp->I[i] = (short *) malloc(sizeof (short));
        select_dp->I[i] = (short *) malloc(sizeof(short));
        bind_dp->V[i] = (char *) malloc(1);
        select_dp->V[i] = (char *) malloc(1);
    }
   
   return 0;
}

/*********************************************************/
int set_bind_variables()
{
    int i, n;
    char bind_var[64];

    /* Describe any bind variables (input host variables) */
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
    sqlstm.offset = (unsigned int  )142;
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



    /* If F is negative, there were more bind variables
       than originally allocated by sqlald(). */
    if (bind_dp->F < 0)
    {
        /*printf ("\nToo many bind variables (%d), maximum is %d\n.",
                    -bind_dp->F, MAX_ITEMS);*/
        return;
    }

    /* Set the maximum number of array elements in the
       descriptor to the number found. */
    bind_dp->N = bind_dp->F;

    /* Get the value of each bind variable as a
     * character string.
     *
     * C[i] contains the length of the bind variable
     *      name used in the SQL statement.
     * S[i] contains the actual name of the bind variable
     *      used in the SQL statement.
     *
     * L[i] will contain the length of the data value
     *      entered.
     *
     * V[i] will contain the address of the data value
     *      entered.
     *
     * T[i] is always set to 1 because in this sample program
     *      data values for all bind variables are entered
     *      as character strings.
     *      ORACLE converts to the table value from CHAR.
     *
     * I[i] will point to the indicator value, which is
     *      set to -1 when the bind variable value is "null".
     */
    for (i = 0; i < bind_dp->F; i++)
    {
        /*printf ("\nEnter value for bind variable %.*s:  ",
               (int)bind_dp->C[i], bind_dp->S[i]);*/
        fgets(bind_var, sizeof bind_var, stdin);

        /* Get length and remove the new line character. */
        n = strlen(bind_var) - 1;

        /* Set it in the descriptor. */
        bind_dp->L[i] = n;

        /* (re-)allocate the buffer for the value.
           sqlald() reserves a pointer location for
           V[i] but does not allocate the full space for
           the pointer. */

         bind_dp->V[i] = (char *) realloc(bind_dp->V[i],
                         (bind_dp->L[i] + 1));

        /* And copy it in. */
        strncpy(bind_dp->V[i], bind_var, n);

        /* Set the indicator variable's value. */
        if ((strncmp(bind_dp->V[i], "NULL", 4) == 0) ||
                (strncmp(bind_dp->V[i], "null", 4) == 0))
            *bind_dp->I[i] = -1;
        else
            *bind_dp->I[i] = 0;

        /* Set the bind datatype to 1 for CHAR. */
        bind_dp->T[i] = 1;
    }
}

/* -----------------------------------------------
Function name: process_select_list
Purpose:       To realloc the pointers to the actual bind
	       variables and the select-list items and display
	       the results of the query to yyout.
Parameters:	none

Returns:
	nothing
------------------------------------------------- */
process_select_list()
{
    int i, null_ok, precision, scale;
    

    if ((strncmp(sql_statement, "SELECT", 6) != 0) &&
        (strncmp(sql_statement, "select", 6) != 0))
    {
        select_dp->F = 0;
        return;
    }

    /* If the SQL statement is a SELECT, describe the
        select-list items.  The DESCRIBE function returns
        their names, datatypes, lengths (including precision
        and scale), and NULL/NOT NULL statuses. */

    select_dp->N = MAX_ITEMS;
    /* exec sql describe select list for s into select_dp; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )161;
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


    /* If F is negative, there were more select-list
       items than originally allocated by sqlald(). */
    if (select_dp->F < 0)
    {
        fprintf (yyout, "Too many select-list items (%d), maximum is %d\n",
                -(select_dp->F), MAX_ITEMS);
        return;
    }

    /* Set the maximum number of array elements in the
       descriptor to the number found. */
    select_dp->N = select_dp->F;

    /* Allocate storage for each select-list item.
  
       sqlprc() is used to extract precision and scale
       from the length (select_dp->L[i]).

       sqlnul() is used to reset the high-order bit of
       the datatype and to check whether the column
       is NOT NULL.

       CHAR    datatypes have length, but zero precision and
               scale.  The length is defined at CREATE time.

       NUMBER  datatypes have precision and scale only if
               defined at CREATE time.  If the column
               definition was just NUMBER, the precision
               and scale are zero, and you must allocate
               the required maximum length.

       DATE    datatypes return a length of 7 if the default
               format is used.  This should be increased to
               9 to store the actual date character string.
               If you use the TO_CHAR function, the maximum
               length could be 75, but will probably be less
               (you can see the effects of this in SQL*Plus).

       ROWID   datatype always returns a fixed length of 18 if
               coerced to CHAR.

       LONG and
       LONG RAW datatypes return a length of 0 (zero),
               so you need to set a maximum.  In this example,
               it is 240 characters.

       */
    
    fprintf (yyout, "\n");
    for (i = 0; i < select_dp->F; i++)
    {
        /* Turn off high-order bit of datatype (in this example,
           it does not matter if the column is NOT NULL). */
        sqlnul (&(select_dp->T[i]), &(select_dp->T[i]), &null_ok);

        switch (select_dp->T[i])
        {
            case  1 : /* CHAR datatype: no change in length
                         needed, except possibly for TO_CHAR
                         conversions (not handled here). */
                break;
            case  2 : /* NUMBER datatype: use sqlprc() to
                         extract precision and scale. */
                sqlprc (&(select_dp->L[i]), &precision, &scale);
                      /* Allow for maximum size of NUMBER. */
                if (precision == 0) precision = 40;
                      /* Also allow for decimal point and
                         possible sign. */
                /* convert NUMBER datatype to FLOAT if scale > 0,
                   INT otherwise. */
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
        /* Allocate space for the select-list data values.
           sqlald() reserves a pointer location for
           V[i] but does not allocate the full space for
           the pointer.  */

         if (select_dp->T[i] != 2)
           select_dp->V[i] = (char *) realloc(select_dp->V[i],
                                    select_dp->L[i] + 1);  
         else
           select_dp->V[i] = (char *) realloc(select_dp->V[i],
                                    select_dp->L[i]);  

        /* Print column headings, right-justifying number
            column headings. */
        if (select_dp->T[i] == 2)
           if (scale > 0)
             fprintf (yyout, "%.*s ", select_dp->L[i]+3, select_dp->S[i]);
           else
             fprintf (yyout, "%.*s ", select_dp->L[i], select_dp->S[i]);
        else
            fprintf (yyout, "%-.*s ", select_dp->L[i], select_dp->S[i]);

        /* Coerce ALL datatypes except for LONG RAW and NUMBER to
           character. */
        if (select_dp->T[i] != 24 && select_dp->T[i] != 2)
	    select_dp->T[i] = 1;

        /* Coerce the datatypes of NUMBERs to float or int depending on
           the scale. */
        if (select_dp->T[i] == 2)
          if (scale > 0)
             select_dp->T[i] = 4;  /* float */
          else
             select_dp->T[i] = 3;  /* int */
    }
    fprintf (yyout, "\n");

    /* FETCH each row selected and print the column values. */
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
        sqlstm.offset = (unsigned int  )180;
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



        /* Since each variable returned has been coerced to a
           character string, int, or float very little processing 
           is required here.  This routine just prints out the 
           values on the terminal. */
        for (i = 0; i < select_dp->F; i++)
        {

            if (*select_dp->I[i] < 0)
                if (select_dp->T[i] == 4) 
                  fprintf (yyout, "%-*c ",(int)select_dp->L[i]+3, ' ');
                else
                  fprintf (yyout, "%-*c ",(int)select_dp->L[i], ' ');
            else
                if (select_dp->T[i] == 3)     /* int datatype */
                  fprintf (yyout, "%*d ", (int)select_dp->L[i], 
                                 *(int *)select_dp->V[i]);
                else if (select_dp->T[i] == 4)     /* float datatype */
                  fprintf (yyout, "%*.2f ", (int)select_dp->L[i], 
                                 *(float *)select_dp->V[i]);
                else                          /* character string */
	    	{ 
		 /*Add end of string char to the string. */
	          *( select_dp->V[i] + select_dp->L[i])= '\0'; 
                  fprintf (yyout, "%-*s ", (int)select_dp->L[i], select_dp->V[i]);
		}
        }
	fprintf (yyout, "\n");
    }

  end_select_loop:
  return;
}

/**************************************************/
void help()
{
    puts("\n\nEnter a SQL statement or a PL/SQL block at the SQL> prompt.");
    puts("Statements can be continued over several lines, except");
    puts("within string literals.");
    puts("Terminate a SQL statement with a semicolon.");
    puts("Terminate a PL/SQL block (which can contain embedded semicolons)");
    puts("with a slash (/).");
    puts("Typing \"exit;\" or \"quit;\"  exits the program.");
    puts("You typed \"?\" or \"help\" to get this message.\n\n");
}

/***********************************************/

void sql_error()
{
 /*   int i;*/
    f_oracle_error='T';
    /* ORACLE error handler */
    fprintf (yyout, "\n%.70s\n",sqlca.sqlerrm.sqlerrmc);
    if (parse_flag)
        printf
        ("Parse error at character offset %d in SQL statement.\n",
           sqlca.sqlerrd[4]);
    /* exec sql whenever sqlerror continue; */ 

    /* exec sql rollback work; */ 

{
    struct sqlexd sqlstm;
    sqlstm.sqlvsn = 12;
    sqlstm.arrsiz = 4;
    sqlstm.sqladtp = &sqladt;
    sqlstm.sqltdsp = &sqltds;
    sqlstm.iters = (unsigned int  )1;
    sqlstm.offset = (unsigned int  )199;
    sqlstm.cud = sqlcud0;
    sqlstm.sqlest = (unsigned char  *)&sqlca;
    sqlstm.sqlety = (unsigned short)4352;
    sqlstm.occurs = (unsigned int  )0;
    sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
}


  longjmp(jmp_continue, 1); 
}

/****************************************************************
Function name: addToFront 
Purpose:
	To add an entry to the front of a linked list.
Parameters:
	newelement	string to be added to the linked list
	list		Pointer to the linked list structure
	idFlag		flag that specifies whether the new element
			is to be added as an id or an element
Returns:
	The new list
*****************************************************************/

LIST* addToFront(char *newelement, LIST* list, char idFlag)
{	      
  LIST_ITEM *entry;

  /*printf("\n In addToFront begin");*/
  /* Allocate memory to the new item. */
  if(list == NULL)
  { 
    if ((list = (LIST*)calloc (1, sizeof (LIST))) == NULL) 
    {
      fprintf(stderr, "Not enough memory to allocate list!\n");
      exit(1);
    }
  }

 
  /* Allocate memory to the new item. */
  if ((entry = (LIST_ITEM *)calloc (1, sizeof (LIST_ITEM))) == NULL)
  {
    fprintf(stderr, "Not enough memory to add item to list!\n");
    exit(1);
  }

  
  /* Adjust the pointers to add the element to the front of the list,
   copy the string into the new element, and increase the count of
   the number of elements in the list. */
  if (list->front == NULL)
    list->back  = entry;
  strcpy(entry->id, newelement);
  strcpy(entry->aggregate, "null");
  if (idFlag == 'V' || idFlag == 'U' || idFlag == 'C' || idFlag == 'X' ||
      idFlag == 'A' || idFlag == 'T' || idFlag == 't' || idFlag == 'N' || idFlag == 'W' || idFlag == 'F')
    ++list->count;

  entry->type = idFlag;
  entry->next = list->front;
  entry->prev = NULL;

  if (list->front !=NULL)
    list->front->prev = entry;

  list->front = entry;

  return list;		
}

/* ---------------------------------------------------------------
Function name: addtoback 
Purpose:
	To add an entry to the back of a linked list.
Parameters:
	newelement	string to be added to the linked list
	list		Pointer to the linked list structure
	idFlag		flag that specifies whether the new element
			is to be added as an id or an element
Returns:
	The new list
---------------------------------------------------------------- */
LIST *addtoback(char *newelement, LIST *list, char idFlag)
{
	LIST_ITEM *entry;

	/* Allocate memory to the list structure if it is NULL. */
	if (list == NULL) {
	 	list= NULL;	
		if ((list = (LIST*) calloc(1, sizeof(LIST))) == NULL) {
			fprintf(stderr, "Not enough memory to allocate to list!");
			exit(1);
		}
	}

	/* Allocate memory to the new item. */
	if ((entry = (LIST_ITEM *)malloc (sizeof (LIST_ITEM))) == NULL) {
		fprintf(stderr, "Not enough memory to add item to list!\n");
		exit(1);
	}

	/* Adjust the pointers to add the element to the front of the list,
	   copy the string into the new element, and increase the count of
	   the number of elements in the list. */
	if (list->back == NULL)
		list->front = entry;
	

        /* J for join conditions like OR, AND, AND NOT. */
	if (idFlag == 'I' || idFlag == 'T' || idFlag == 'N' ||
            idFlag == 'E' || idFlag == 'J' || idFlag == 'D')
          strncpy(entry->id, newelement, MAXLENGTH);
        
        if (idFlag == 'I')
	  ++list->count;
	entry->type = idFlag;
	entry->prev = list->back;
	entry->next = NULL;
	if (list->back !=NULL)
		list->back->next = entry;
	list->back = entry;
		
	return list;
}

/* ---------------------------------------------------------------
Function name: addHaving
Purpose:
        To add having condition
Parameters:
        aggregate       aggragate name
        operand1        add operand to the having list
        relop           add operator
        operand2        add operand to the having list
Returns:
        The new list
---------------------------------------------------------------- */

SELECTSTMT* addHaving(char * agg, SELECTSTMT* operand1, char * relop, 
SELECTSTMT*  
operand2)
{
   SELECTSTMT *ncondition;
   char  temp[MAXSTMTLENGTH];
   char * pch;
   /*printf("\nin add having");*/
   /*allocated memory to structure for new condition.*/
   if((ncondition =(SELECTSTMT*) calloc(1, sizeof(SELECTSTMT)))==NULL)
  {
     fprintf(yyout, "not enough memory to allocate to selectstmt!");
    exit(1);
   }
   ncondition->f_error = 'N';
   strcpy(temp, "(");
   pch = strtok(operand1->conditions->front->id,".");
              pch = strtok(NULL," ");
  strcat(temp, pch);
   strcat(temp, ")");
   strcat(temp, relop);
  strcat(temp, operand2->conditions->front->id);
  ncondition->conditions = 
  addAggToFront(agg,temp, NULL, ncondition->conditions,'W');
  /*freeExpr(operand1);
  freeExpr(operand2);*/
  return(ncondition);
  }
/***********************************************************************
     Function name   addEqAttrs
     Purpose         add equation to the new built list of
                     attributes
     Parameters
                 eq: equation contain (+\-\*\/\) operation
                 variables: the selectstmt structure containing VAR_ATTRIBUTE 
   Returns        Pointer to the selectstmt structure containing the new
                  equation

***********************************************************************/
SELECTSTMT *addEqAttrs(SELECTSTMT * eq, SELECTSTMT *variables)
{
  SELECTSTMT *nselect;
  char temp[MAXSTMTLENGTH];

  fflush(stdout);

  if (( nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nselect!");
    exit(1);
  }
  nselect->f_error = 'N';
  strcpy(temp, eq->conditions->front->id);
  if(variables!=NULL)
         nselect->attributes = addToFront(", ",variables->attributes, 
'E');
 nselect->attributes = addToFront(temp, nselect->attributes, 'A');
  return nselect;
}


/************************************************************************
   Function name  addVarAttrs
   Purpose        add VAR_ATTRIBUTE or Vars_Attrs to the new built list of
                  attributes
   Parameters
          var_p: string containing the VAR_ATTRIBUTE
          variables: the selectstmt structure containing VAR_ATTRIBUTE COMMA Vars_Attrs
   Returns        Pointer to the selectstmt structure containing the new
                  VAR_ATTRIBUTE or Vars_Attrs
************************************************************************/
SELECTSTMT *addVarAttrs(char *var_p, char *rename, SELECTSTMT *variables)
{
  SELECTSTMT *nselect;
     
  fflush(stdout);

  if (( nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nselect!");
    exit(1);
  }

 if(strcmp(var_p, "+") == 0||strcmp(var_p, "-") == 0||strcmp(var_p, "/") == 0)
  {
	nselect->f_error = 'E';
	strcpy(nselect->errormsg, "ERROR: Use +, -, or / as attributes!");
	return nselect;
  } 


  nselect->f_error = 'N';

  if (variables != NULL)		
    nselect->attributes = addToFront(", ", variables->attributes, 'E');

  if (rename != NULL)
  {
	strcat(var_p, " AS ");
	strcat(var_p, rename);
  }
    
  nselect->attributes = addToFront(var_p, nselect->attributes , 'A');
  printList(nselect->attributes);
  return nselect;
}
/************************************************************
         Function name  addEqOrder
         Purpose        add equation to the order list  
         Parameters
          var_p1: selectstmt containing the VAR_ATTRIBUTE
          var_p2: the selectstmt structure containing VAR_ATTRIBUTE 
          variables: the selectstmt structure containing order list
   Returns        Pointer to the selectstmt structure containing the new
                  equation
************************************************************/
SELECTSTMT *addEqOrder(SELECTSTMT *var_p1, char *var_p2, SELECTSTMT
*variables)
{
  SELECTSTMT *nselect;
  char temp[MAXSTMTLENGTH];
  if(var_p2 != NULL)
 {
    strcpy(temp, "&");
    strcat(temp, var_p2);
  }
 else
    strcpy(temp, "null");
 fflush(stdout);
 if (( nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) 
          == NULL)
  {
     fprintf(yyout, "not enough memory to allocate to nselect!");
    exit(1);
  }
  nselect->f_error = 'N';

  if (variables != NULL)
    nselect->orderby = addToFront(", ", variables->orderby, 'E');
    nselect->orderby = addAggToFront(temp, var_p1->conditions->front->id, NULL,
nselect->orderby
,
'A');
  return nselect;
}
/*************************************************************
    Function name   addOrder
    Purpose        add var_attribute to the order list
         Parameters
          var_p1: selectstmt containing the VAR_ATTRIBUTE
          var_p2: the selectstmt structure containing VAR_ATTRIBUTE
          variables: the selectstmt structure containing order list
   Returns        Pointer to the selectstmt structure containing the new
                  var_attribute
**************************************************************/
SELECTSTMT *addOrder(char *var_p1, char *var_p2, SELECTSTMT
*variables,char *var_p3)
{
  SELECTSTMT *nselect;
  char temp[MAXSTMTLENGTH];
  if(var_p3!=NULL && var_p2!=NULL)
  {
      strcpy(temp, var_p3);
      strcat(temp, "#");
      strcat(temp, var_p2);
  }
  else if(var_p3!=NULL && var_p2 == NULL)
  {
     strcpy(temp, var_p3);
  }
  else if(var_p3==NULL && var_p2 != NULL)
 {
     strcpy(temp, "&");
     strcat(temp, var_p2);
 }
 else
    strcpy(temp,"null");
 
 fflush(stdout);

  if (( nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nselect!");
    exit(1);
  }
  nselect->f_error = 'N';
        
  if (variables != NULL)
    nselect->orderby = addToFront(", ", variables->orderby, 'E');
    nselect->orderby = addAggToFront(temp, var_p1, NULL, nselect->orderby
,
'A');
  printList(nselect->orderby);
  return nselect;
}
/************************************************************************
      Function name: combine
      Purpose        to return a list of order by
         Parameters
          variables: the selectstmt structure containing order list
    Returns        

************************************************************************/
void combine(SELECTSTMT *variables)
{
     LIST_ITEM * current;
     if(variables->orderby != NULL)
    {
        strcat(sqlstmt, " ORDER BY ");
        current = variables->orderby->front;
        while(current != NULL)
       {
              if(strcmp(current->aggregate, "null")==0)
             {
                  strcat(sqlstmt,  current->id);
                 strcat(sqlstmt, " ");
                 if(strstr(current->id, ",")== NULL)
                     strcat(sqlstmt, "ASC");
                 strcat(sqlstmt, " ");
             }
            else if(strstr(current->aggregate, "#")!=NULL)
            {
                char * pch;
                pch = strtok(current->aggregate, "#");
                if(pch != NULL)
                {
                   strcat(sqlstmt, pch);
                   strcat(sqlstmt, "(");
                   strcat(sqlstmt, current->id);
                   strcat(sqlstmt, ") ");
                 }
                 pch = strtok(NULL, " ");
                 if(pch!=NULL)
                    strcat(sqlstmt, pch);
              }
              else if(strstr(current->aggregate, "&")!= NULL)
              {
                  char *pch;
                  pch = strtok(current->aggregate,"&");
                   if(pch!=NULL)
                  {
                     pch=strtok(current->aggregate,"&");
                     strcat(sqlstmt, current->id);
                     strcat(sqlstmt, " ");
                     strcat(sqlstmt, pch);
                     strcat(sqlstmt," ");
                  }
               }
               else
               {
                   strcat(sqlstmt, current->aggregate);
                   strcat(sqlstmt, "(");
                   strcat(sqlstmt, current->id);
                   strcat(sqlstmt, ") ASC");
                }
                current = current->next;
       }
     }
}
/************************************************************************
   Function name  addVarAttrs2 override
   Purpose        add VAR_ATTRIBUTE or Vars_Attrs to the new built list of
                  attributes
   Parameters
          var_p: string containing the VAR_ATTRIBUTE
          variables: the selectstmt structure containing VAR_ATTRIBUTE 
COMMA Vars_Attrs
   Returns        Pointer to the selectstmt structure containing the new
                  VAR_ATTRIBUTE or Vars_Attrs
************************************************************************/
SELECTSTMT *addVarAttrs2(char *var_p1, char *var_p2, char *rename, SELECTSTMT *variables, char *SIGN)
{
  SELECTSTMT *nselect;
     
  /*printf("\nIn addvar string:  %s", var_p2);*/
   fflush(stdout);

  if (( nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nselect!");
    exit(1);
  }

  nselect->f_error = 'N';
  
  if(SIGN == NULL)
  {
	if (variables != NULL)		
		nselect->attributes = addToFront(", ", variables->attributes, 'E');
	nselect->attributes = addAggToFront(var_p1, var_p2, rename, nselect->attributes , 'A');
  }
  else
  {		
	nselect->attributes = addToFront(SIGN, variables->attributes, 'E');
	nselect->attributes = addAggToFront(var_p1, var_p2, rename, nselect->attributes , 'A');
  }
  return nselect;
}

/********************************************************************
Function name: addAggToFront
Purpose:
	To add an entry to the front of a linked list.
Parameters:
	newelement	string to be added to the linked list
	list		Pointer to the linked list structure
	idFlag		flag that specifies whether the new element
			is to be added as an id or an element
Returns:
	The new list
*****************************************************************/

LIST* addAggToFront(char * aggregate, char *newelement, char *rename, LIST* list, char 
idFlag)
{	      
  LIST_ITEM *entry;


  /* Allocate memory to the new item. */
  if(list == NULL)
  { 
    if ((list = (LIST*)calloc (1, sizeof (LIST))) == NULL) 
    {
      fprintf(stderr, "Not enough memory to allocate list!\n");
      exit(1);
    }
  }

 
  /* Allocate memory to the new item. */
  if ((entry = (LIST_ITEM *)calloc (1, sizeof (LIST_ITEM))) == NULL)
  {
    fprintf(stderr, "Not enough memory to add item to list!\n");
    exit(1);
  }

  
  /* Adjust the pointers to add the element to the front of the list,
   copy the string into the new element, and increase the count of
   the number of elements in the list. */
  if (list->front == NULL)
    list->back  = entry;
  strcpy(entry->id, newelement);

  /*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
  if(rename != NULL)
  strcpy(entry->as, rename);
  
  strcpy(entry->aggregate, aggregate);
  
  if (idFlag == 'V' || idFlag == 'U' || idFlag == 'C' || idFlag == 'X' ||
      idFlag == 'A' || idFlag == 'T' || idFlag == 't' || idFlag == 'N' || 
idFlag == 'W')
    ++list->count;

  entry->type = idFlag;
  entry->next = list->front;
  entry->prev = NULL;

  if (list->front !=NULL)
    list->front->prev = entry;

  list->front = entry;
  return list;		
}


/************************************************************************
   Function name addExitVar 
   Purpose        add VAR_ATTRIBUTE or Vars_Attrs to the new built list of
                  attributes
   Parameters
          variables: the selectstmt structure containing VARIABLE COMMA existsVariables
   Returns        Pointer to the selectstmt structure containing the "*"
 ************************************************************************/

SELECTSTMT* addExistsVar(char *variable, SELECTSTMT *variables)
{
  SELECTSTMT *nselect;
   char       temp[MAXSTMTLENGTH];
  
  /*printf("\nIn addExistvar string\n");*/
  fflush(stdout);

  if (variables == NULL)
  {
    if (( nselect = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
    {
       fprintf(yyout, "not enough memory to allocate to nselect!");
       exit(1);
    }

    nselect->f_error = 'N';
  }
  else
  {
    if(variables->f_error == 'E')
	return variables;
    nselect = variables;
  }

  strcpy(temp, variable);
  strcat(temp, ".*");

     nselect->attributes = addToFront(temp, nselect->attributes, 'X');

  printList(nselect->attributes);
  printList(nselect->tables);
  printList(nselect->conditions);
  return nselect;
}


SELECTSTMT* addExistsVar2(SELECTSTMT *variable, SELECTSTMT *variables)
{ 
  /*printf("\nIn addExistvar string2 \n");*/
  fflush(stdout);

  if(variable->f_error == 'E')
	return variable;

  if(variables->f_error == 'E')
	return variables;

  variables->tables = addToFront(variable->tables->front->id, variables->tables, 'X');

  return variables;
}

/**********************************************************************
  Function name:addPar
  Purpose:      add left par and right part to the new built condition list
  Parameters:
         left_par: string containing the left par
         right_par: string containing the right par
         return_cond:    the selectstmt structure containing the condition
  Returns:      Pointer to the structure containing the new condition
**********************************************************************/

SELECTSTMT* addPar(char* left_par, SELECTSTMT* return_cond, char* right_par)
{

  SELECTSTMT *nPar;
  char       temp[MAXSTMTLENGTH];
   /*allocate memory to structure for new par.*/
  if ((nPar = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to selectstmt!");
    exit(1);
  }

  if(return_cond->f_error == 'E')
  {
	nPar->f_error = 'E';
	strcpy(nPar->errormsg, return_cond->errormsg);
	return nPar;
  }

  nPar->f_error = 'N';

  if(return_cond->conditions != NULL)
  {
	if(return_cond->conditions->front->next == NULL)
	{
		strcpy(temp, left_par);
		strcat(temp, return_cond->conditions->front->id);
		strcat(temp, right_par);
	}
	else if (return_cond->conditions->front->next != NULL)
	{
		LIST_ITEM *ncurrent;
		ncurrent = return_cond->conditions->front;
		strcpy(temp, left_par);
		while(ncurrent != NULL)
		{	
			if(ncurrent->next == NULL)
			{
				strcat(temp, ncurrent->id);
			}
			else if(ncurrent->next != NULL)
			{
				strcat(temp, ncurrent->id);
				if(forall_flag == 1 || forall_flag == 2)
					strcat(temp, " OR ");
				else
					strcat(temp, " AND ");

			}
			ncurrent = ncurrent->next;
		}
		strcat(temp, right_par);
	}

	if(strcmp(return_cond->conditions->front->aggregate,"null")!=0)
		nPar->conditions = addAggToFront(return_cond->conditions->front->aggregate,temp, NULL, nPar->conditions, 'W');
	else
		nPar->conditions = addToFront(temp,nPar->conditions,'W');
   }
  /*freeExpr(return_cond);*/

  return(nPar);
}
/********************************************************************
        Function name: addEquation
        Purpose        add equation to the list
        Parameters
          operand1: selectstmt containing the VAR_ATTRIBUTE
          operand2: the selectstmt structure containing VAR_ATTRIBUTE
          sign:     (+\-\*\/) operator
          variables: the selectstmt structure containing equation
    Returns        Pointer to the selectstmt structure containing the new
                  equation
********************************************************************/
SELECTSTMT *addEquation(SELECTSTMT* operand1, char* sign, SELECTSTMT* 
operand2, int flag)
{
  SELECTSTMT *ncondition;
  char       temp[MAXSTMTLENGTH];
  /*printf("\nIn add condition %s");*/
  /*allocate memory to structure for new condition.*/
  if ((ncondition = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to selectstmt!");
    exit(1);
  }
  ncondition->f_error = 'N';
  if(flag==0)
 {
     strcpy(temp, operand1->conditions->front->id);
    strcat(temp, sign);
    strcat(temp, operand2->conditions->front->id);
  }
  else if(flag==1)
 {
       strcpy(temp, "(");
      strcat(temp, operand1->conditions->front->id);
      strcat(temp, ")");
      strcat(temp, sign);
      strcat(temp, operand2->conditions->front->id);
   }
   else
   {
         strcpy(temp, operand1->conditions->front->id);
         strcat(temp, sign);
         strcat(temp, "(");
         strcat(temp, operand2->conditions->front->id);
         strcat(temp, ")");
   }
   ncondition->conditions = addToFront(temp, ncondition->conditions,'Q');
   /*freeExpr(operand1);
   freeExpr(operand2);*/
   return(ncondition);
 }
/**********************************************************************
  Function name:addcondition
  Purpose:      add one condition to the new built condition list
  Parameters:
         Operand1: string containing the left operand of the condition
         Operand2: string containing the right operand of the condition
         Relop:    string containing the relation operation of the condition

  Returns:      Pointer to the structure containing the new condition
**********************************************************************/
SELECTSTMT *addCondition(SELECTSTMT* operand1, char* relop, SELECTSTMT* operand2, int not_flag)
{
  SELECTSTMT *ncondition;
  char       temp[MAXSTMTLENGTH];
  /*printf("\nIn add condition %s");*/
  /*allocate memory to structure for new condition.*/
  if ((ncondition = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to selectstmt!");
    exit(1);
  }

  ncondition->f_error = 'N';

  if(forall_flag == 0)
  {
    if (not_flag == 0)
      strcpy(temp, operand1->conditions->front->id);
    else
    {
      strcpy(temp, "NOT ");
      strcat(temp, operand1->conditions->front->id);
    }
  }
  else
  {
    if ((not_flag == 0 && forall_flag == 2) || (not_flag == 1 && forall_flag != 2))
      strcpy(temp, operand1->conditions->front->id);
    else 
    {
      strcpy(temp, "NOT ");
      strcat(temp, operand1->conditions->front->id);
    }
  }

  strcat(temp, " ");
  strcat(temp, relop);
  strcat(temp, " ");
  strcat(temp, operand2->conditions->front->id);
    
  ncondition->conditions = addToFront(temp, ncondition->conditions, 'W');
  
  /*freeExpr(operand1);
  freeExpr(operand2);*/
  return(ncondition);
 }

/**********************************************************************
  Function name:addOperand
  Purpose:      add operand to the new built condition list
  Parameters:
         Operand: string containing the left or right operand of the condition
         
   Returns:      Pointer to the structure containing the new condition
  **********************************************************************/

SELECTSTMT* addOperand(char* operand, char type)
{
  SELECTSTMT * noperand;
  
  /*printf("\nIn addOperand: operand: --%s--", operand);*/
  /*allocate memory to structure for new condition.*/
  if ((noperand= (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to selectstmt!");
    exit(1);
  }

  noperand->f_error = 'N';
  noperand->conditions = addToFront(operand, noperand->conditions, type);
  
  return(noperand);
}

/*--------------------------------------------------------------------
Function name: dropTmpTables
Purpose:
         delete any of temporary tables.
Parameters:
	tbl_name: temp tables to be deleted
Returns:
	nothing
------------------------------------------------------------------ */
void dropTmpTables(char *tbl_name)
{
  char temp_sqlstmt[MAXSTMTLENGTH];
  char temp_sqlstmt2[MAXSTMTLENGTH];
  char temp_table_name[MAXLENGTH];

  strcpy(temp_table_name, tbl_name);
  strtok(temp_table_name, " ");

  if (strlen(tbl_name) > 0)
  {
    strcpy(temp_sqlstmt, "DROP TABLE ");
    strcat(temp_sqlstmt, temp_table_name);

    strcpy(temp_sqlstmt2, sqlstmt);
    strcpy(sqlstmt, temp_sqlstmt);
    executesqlstmt(0, 0, 1);
  
    strcpy(sqlstmt, temp_sqlstmt2);
  }
}

/************************************************

Function name: mergeList
Purpose:
	To merge two linked lists.
Parameters:
	list1: The list to be at the front of the merge list
	list2: The list to be at the back of the merged list
Returns:
	The merged list
*************************************************/
LIST *mergeList(LIST *list1, LIST *list2)
{
  LIST *newList;
	
  if (list1 == NULL)
    newList = list2;
  else if (list2 == NULL)
    newList = list1;
  else
  {
    newList = list1;
    list2->front->prev = newList->back;
    newList->back->next = list2->front;
    newList->back = list2->back;
  }
	
  return newList;
}

/********************************************/
#ifndef NULL
#define NULL 0
#endif

/************************************************************************
   Function name Addand_formula
   Purpose       This function deals with logic "and".
               For conditions, it merges the condition list of
                 subformula and that of andformula;
                 For tables, it merges the table list of subformula and
                 that of andformula;
   Parameters
                 subformula: a pointer pointing to a SELECTSTMT type
                             structure of subformula
                 andformula: a pointer pointing to a SELECTSTMT type
                             structure of andformula
   Returns       A pointer pointing to the SELECTSTMT structure which
                 express the result of merged list.
*************************************************************************/

SELECTSTMT *addAndFormula(SELECTSTMT *sub_formula, char* andor, SELECTSTMT *and_formula)
{
  char temp[MAXSTMTLENGTH];
  LIST_ITEM* current;
  /*printf("\n in add and formula");*/

  SELECTSTMT* nand;
  if((nand=(SELECTSTMT*) calloc(1,sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nand in addAndFormula()!");
    exit(1);
  }

  if(sub_formula->f_error == 'E')
  {
	nand->f_error = 'E';
	strcpy(nand->errormsg, sub_formula->errormsg);
	return nand;
  }

  if(and_formula->f_error == 'E')
  {
	nand->f_error = 'E';
	strcpy(nand->errormsg, and_formula->errormsg);
	return nand;
  }

  strcpy(temp, andor);
  if(sub_formula != NULL && and_formula != NULL &&
     sub_formula->conditions == NULL && and_formula->conditions == NULL &&
     join_test(sub_formula, and_formula) == 1)
     {
     nand = join_relations(sub_formula, temp, and_formula);
    return nand;
    }
  else if( and_formula->conditions != NULL &&
           and_formula->conditions->front != NULL &&
           and_formula->conditions->front->type == 'D' &&
           join_test(sub_formula, and_formula) == 1)
  {
    strcat(temp, and_formula->conditions->front->id);
    nand = join_relations(sub_formula, temp, and_formula);
    return nand;
  }
  else
  {
    nand->conditions = mergeList(sub_formula->conditions, and_formula->conditions);
    nand->freevars = mergeList(sub_formula->freevars, and_formula->freevars);
    nand->tables = mergeList(sub_formula->tables, and_formula->tables);
  }

  /*freeExpr(and_formula);*/

  return nand;
}

/*********************************************************
*  Function name: addrelationname
*  Purpose      : change the Tuple expression of tables into
*                 a sql one.
*  parameters   : relationname, variable
*
*  Returns      : a selectstmt structure
***********************************************************/

SELECTSTMT* addRelationname(char* not_str, char* relationname, char* variable)
{
  SELECTSTMT* nrelationname;
  char* temp;
  char  temp_not[MAXLENGTH];

  /*printf("\nIn addRelationname");*/

  if((nrelationname=(SELECTSTMT*) calloc(1,sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nrelationname in addrelationname()!");
    exit(1);
  }

  nrelationname->f_error = 'N'; 
  temp = (char*)malloc(sizeof(char) * (strlen(relationname) + strlen(variable) + 2));

  /* deal with not operation */
  if (not_str != NULL)
  {
    strcpy(temp_not, not_str);  
    uppercase(temp_not);
    nrelationname->conditions = addtoback(temp_not, nrelationname->conditions, 'D'); 
  }

  if (table_test(relationname) == 1)
  {
    strcpy(temp, relationname);
    strcat(temp, " ");
    strcat(temp, variable);
  
    nrelationname->tables = addToFront(temp, nrelationname->tables, 'T'); 
    nrelationname->freevars = addToFront(variable, nrelationname->freevars, 'F');
  }
  else
  {
    nrelationname->f_error = 'E';
    strcpy(nrelationname->errormsg, "\nERROR: Table does not exist!");
    table_error_flag = 1;
  }

  free(temp);

  return nrelationname;
}

/***********************************************************
 * Function name: addorformula
 * Parameters   : andformula, formula
 *
 * purpose      : add "or" to
 *
 ***********************************************************/
SELECTSTMT* addOrFormula(SELECTSTMT* andformula, char* andor, SELECTSTMT* formula)
{
  SELECTSTMT* nor;
  char temp[MAXSTMTLENGTH];
  char agg[MAXSTMTLENGTH];
  
  /*printf("\n In addOrFormula %s", andor);*/

  if((nor=(SELECTSTMT*) calloc(1,sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nrelationname in addrelationname()!");
    exit(1);
  }

  if(andformula->f_error == 'E')
  {
	nor->f_error = 'E';
	strcpy(nor->errormsg, andformula->errormsg);
	return nor;
  }

  if(formula->f_error == 'E')
  {
	nor->f_error = 'E';
	strcpy(nor->errormsg, formula->errormsg);
	return nor;
  }


  /* dealing with OR/AND/AND NOT/ operations */
  strcpy(temp, andor);


  if(andformula != NULL && formula != NULL)
  {
     if(andformula->conditions == NULL && formula->conditions == NULL) 
     {
	if(join_test(andformula, formula) == 1)
		return join_relations(andformula, temp, formula);
	else
	{
		nor->f_error = 'E';
		strcpy(nor->errormsg, "\nError: The schemas of two table are different!!!!  \n\nTRC>");
		return nor;
	}
     }
  }



  /* @@@@@@@@@@@@@@@@@@@@@@@ OR OR OR OR OR @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
  
  if(strcmp(formula->conditions->front->id, "OR")==0)
  {
	if(join_test(andformula, formula) == 1)
	{
		return join_relations(andformula, temp, formula);
	}
	else
	{
		nor->f_error = 'E';
		strcpy(nor->errormsg, "\nError: The schemas of two table are different!!!!  \n\nTRC>");
		return nor;
	}
  }
  if(strcmp(formula->conditions->front->id, "(OR)")==0)
  {
	if(join_test(andformula, formula) == 1)
	    return join_relations(andformula, temp, formula);
	else
	{
		nor->f_error = 'E';
		strcpy(nor->errormsg, "\nError: The schemas of two table are different!!!!  \n\nTRC>");
		return nor;
	}
  }
  /* @@@@@@@@@@@@@@@@@@@@@@@ OR OR OR OR OR @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

  if((nor=(SELECTSTMT*) calloc(1,sizeof(SELECTSTMT))) == NULL)
  {
    fprintf(yyout, "not enough memory to allocate to nor in addormula()!");
    exit(1);
  }

  nor->f_error = 'N';

  if (andformula->conditions == NULL)
    ;  /* do nothing here */
  else
  {
    if(strcmp(andformula->conditions->front->aggregate,"null")!=0)
    {
       strcpy(temp,andformula->conditions->front->aggregate);
       strcat(temp,andformula->conditions->front->id);
      strcpy(agg, andformula->conditions->front->aggregate);
    }
    else
       {
        strcpy(temp, andformula->conditions->front->id);
        strcpy(agg,"null");
    }


    if (forall_flag == 1 || forall_flag == 2)
      strcat(temp, " AND ");
    else
      strcat(temp, " OR ");
  }
  if(strcmp(formula->conditions->front->aggregate,"null")!=0)
  {
     strcat(temp, formula->conditions->front->aggregate);
     strcat(temp, formula->conditions->front->id);
     if(strcmp(agg,"null")==0)
        strcpy(agg, formula->conditions->front->aggregate);
  }
  else
      strcat(temp, formula->conditions->front->id);
  
  if(strcmp(agg,"null")!=0)
      nor->conditions = addAggToFront(agg, temp, NULL, nor->conditions,'W');
  else
      nor->conditions=addToFront(temp,nor->conditions,'W');
  
 
  /*freeExpr(andformula);
  freeExpr(formula);*/
  return nor;
}

/***************************************************************************
 *Function name: Buildexpression
 *Purpose      : building sql statement from Var and Formula
 *Parameters   :
 *              var: a pointer pointing to a SELECTSTMT structure, in which
                    attribute list is already built
 *              formula: a pointer pointing to a SELECTSTMT structure, in which
                         both condition list and table list are built.
 *Return       :sql_statement containing sql statement in string
***************************************************************************/

void buildexpression(SELECTSTMT *var, SELECTSTMT *formula)
{
  LIST_ITEM *current, *p, *q, *k;
  int       loop_count;  
  char      tempStr[MAXSTMTLENGTH];
  char      groupBy[MAXSTMTLENGTH];
  char      havingstmt[MAXSTMTLENGTH];
  int       having_flag =0;
  int       group_flag = 0;
  int       againHave =0;
  int       againSql=0;
   char  * pch;
  if(var != NULL)
      printList(var->attributes);


  fprintf(yyout, "\nin buildexpression()\n ");

  if(formula != NULL)
  {
    printList(formula->tables);
    printList(formula->conditions);
  }
  /* Error handling */
  if (formula == NULL || var == NULL) 
  {
     sqlstmt[0] = '\0';
     fprintf(yyout, "\nStatement error.\n");
     return;
  }
  if (var->f_error == 'E') 
  {
    sqlstmt[0] = '\0';
    fprintf(yyout, "\n%s\n", var->errormsg);
    return;
  }
  if (formula->f_error == 'E') 
  {
    sqlstmt[0] = '\0';
    if(quantifier_error_flag == 1 && quantifier_error_display_flag == 0)
       ;
    else
    {
	fprintf(yyout, "\n%s\n", formula->errormsg);
	if(quantifier_error_flag == 1)
		quantifier_error_display_flag = 0;
    }
    return;
  }
  if(quantifier_error_flag == 1)
  {
	return;
  }

  /* deal with join conditions */
  if (formula->conditions != NULL &&
      formula->conditions->front != NULL &&
      formula->conditions->front->type == 'J')
  {
    buildJoinSQLStmt(var, formula);
    return;
  }

  /* Deal with (exists relationname in relationname) */
  if (var->tables != NULL && var->tables->front != NULL)
  {
      if(var->attributes != NULL)
      {
	int eflag = 1;
	current = var->attributes->front;
	while(current != NULL)
	{
		p = formula->tables->front;
		while(p != NULL)
		{
			char temp[MAXSTMTLENGTH];
			strcpy(temp, p->id);
			strcat(temp, ".*");
			if(strstr(temp, current->id) != NULL)
			{
				eflag = 0;	
			}
			p = p->next;
		}

		if(eflag == 1)
		{
			quantifier_error_flag =1;
		quantifier_error_display_flag = 1;
		return;
		}
		current = current->next;
	}
      }	
   
      strcpy(tempStr, "SELECT distinct "); /*distinct*/
      strcat(tempStr, "*");
      
      strcat(tempStr, " FROM ");
      strcat(tempStr, var->tables->front->id);
      if(var->tables->front->next != NULL)
      {
        current = var->tables->front->next;
	while(current != NULL)
	{
		strcat(tempStr, ", ");
		strcat(tempStr, current->id);
		current = current->next;
	}
      }
      
      if(formula->tables!= NULL)
      {
	current = formula->tables->front;
	while(current != NULL)
	{
		strcat(tempStr, ", ");
		strcat(tempStr, current->id);
		current = current->next;
	}
      }

      strcat(tempStr, " WHERE ");
      q = formula->conditions->front;
      while(q!=NULL && strcmp(q->aggregate, "null")!=0)
      {
          if(strstr(q->id, "OR"))
              strcpy(havingstmt, q->id);
          else
          {
            strcpy(havingstmt, q->aggregate);
            strcat(havingstmt, q->id);
          }
          having_flag = 1;
          if(q->next != NULL)
               strcat(havingstmt, "AND ");
          q = q->next;
      }

      while(q != NULL)
      {
	  if(strcmp(q->aggregate,"null")!=0)
	  {
		if(strstr(q->id,"OR"))
			strcat(havingstmt, q->id);
		else
		{
			strcat(havingstmt, q->aggregate);
			strcat(havingstmt, q->id);
		}
		having_flag =1;
	}
	else
	{ 
		strcat(tempStr, q->id);
	}
	if(q->next !=NULL && strcmp(q->next->aggregate,"null")!=0)
	{   
		if(having_flag == 1)
			strcat(havingstmt, " AND ");
	}
	if(q->next != NULL && strcmp(q->next->aggregate,"null")==0)
	{

		if (forall_flag != 1)
			strcat(tempStr, " AND ");
		else
			strcat(tempStr, " OR ");
	}

	q = q->next;
    }
    if(having_flag==1)
    {
	strcat(tempStr, " Having ");
	strcat(tempStr, havingstmt);
    }
    havingstmt[0]='\0';       

    strcpy(sqlstmt, tempStr);
    freeExpr(var);
    freeExpr(formula);
    return;
  } 


  /* deal with query which contains qantifier */
  if (var->attributes != NULL && var->attributes->front != NULL &&
      var->attributes->front->type == 'X')
  {

    current = var->attributes->back;
    
    if(formula->tables == NULL )
    {
        quantifier_error_flag =1;
	quantifier_error_display_flag = 1;
	return;
    }

    p = formula->tables->back;

    loop_count = 1;
    while(current != NULL)
    { 
    	
      strcpy(tempStr, "SELECT distinct "); /*distinct*/
      strcat(tempStr, current->id);

      if(p == NULL)
      {
        quantifier_error_flag =1;
	quantifier_error_display_flag = 1;
	return;
      }
      
      char temp[MAXSTMTLENGTH];
      strcpy(temp, p->id);
      strcat(temp, ".*");

      if(strstr(temp, current->id) == NULL)
      {
	quantifier_error_flag =1;
	quantifier_error_display_flag = 1;
	return;
      }
      
      strcat(tempStr, " FROM ");
      strcat(tempStr, p->id);

      if (loop_count == 1)
      {
        strcat(tempStr, " WHERE ");
        q = formula->conditions->front;
        while(q!=NULL && strcmp(q->aggregate, "null")!=0)
        {
          if(strstr(q->id, "OR"))
              strcpy(havingstmt, q->id);
          else
          {
            strcpy(havingstmt, q->aggregate);
            strcat(havingstmt, q->id);
          }
          having_flag = 1;
          if(q->next != NULL)
               strcat(havingstmt, "AND ");
          q = q->next;
        }

	while(q != NULL)
	{
		if(strcmp(q->aggregate,"null")!=0)
		{
			if(strstr(q->id,"OR"))
				strcat(havingstmt, q->id);
			else
			{
				strcat(havingstmt, q->aggregate);
				strcat(havingstmt, q->id);
			}
			having_flag =1;
		}
		else
		{ 
			strcat(tempStr, q->id);
		}
		if(q->next !=NULL && strcmp(q->next->aggregate,"null")!=0)
		{   
			if(having_flag == 1)
				strcat(havingstmt, " AND ");
		}
		if(q->next != NULL && strcmp(q->next->aggregate,"null")==0)
		{
			if (forall_flag != 1)
				strcat(tempStr, " AND ");
			else
				strcat(tempStr, " OR ");
		}

		q = q->next;
	}
	if(having_flag==1)
	{
		strcat(tempStr, " Having ");
		strcat(tempStr, havingstmt);
	}
	havingstmt[0]='\0';
    }
    else
    {  
        if (exist_flag == 0 )
        {
          strcat(tempStr, " WHERE EXISTS (");/*EXIST*/
          strcat(tempStr, sqlstmt);
          strcat(tempStr, ")");
        }
        else if(exist_flag == 1)
        {
          strcat(tempStr, " WHERE NOT EXISTS (");/*NOT EXIST*/
          strcat(tempStr, sqlstmt);
          strcat(tempStr, ")");
	  if(exist_flag_count <= 0)
          exist_flag = 0;
        }
        else if(exist_flag == 2)/*FORALL*/
        {
          strcat(tempStr, " WHERE NOT EXISTS (");
          strcat(tempStr, sqlstmt);
          strcat(tempStr, ")");
        }
    }     

      strcpy(sqlstmt, tempStr);

      current = current->prev;
      p = p->prev;
      loop_count++;
    }

    freeExpr(var);
    freeExpr(formula);

    return;
  }

  /* deal with query which does not contain conditions */
  if (formula->conditions==NULL)
  {
    q=var->attributes->front;
    if(strcmp(q->aggregate,"null")==0&&q->type =='A')
    {    strcpy(groupBy, q->id);
    }
    else
   {
       strcpy(groupBy, "null");
   }

    strcpy(sqlstmt,"SELECT distinct "); /*distinct*/
    while(q!=NULL)
    {
      if(strcmp(q->aggregate,"null")!=0 && q->type == 'A')
     {
       strcat(sqlstmt, q->aggregate);    
              strcat(sqlstmt, "(");
		
	      if(strcmp(q->id, "*") == 0 || strcmp(q->id, "/") == 0 || strcmp(q->id, "+") == 0 || strcmp(q->id, "-") == 0)
		pch = q->id;
              else
	      {
		pch = strtok(q->id, ".");
		pch = strtok(NULL," ");
	      }
              strcat(sqlstmt,pch);
              strcat(sqlstmt, ")");
	      if(q->as[0] != '\0')
	      {
		strcat(sqlstmt, " AS ");
		strcat(sqlstmt, q->as);
	      }
         group_flag = 1;
       }
       else 
      {
        if(q->type=='A'||q->type == 'E')
   
          strcat(sqlstmt, q->id);
        
        if (q->type=='V')
             strcat(sqlstmt," * \0");
     }
      
           
      q = q->next;
    }

    p = formula->tables->front;
    strcat(sqlstmt, " FROM \0" );   

    while(p != NULL)
    {
      strcat(sqlstmt, p->id);
      if(p->next != NULL)
        strcat(sqlstmt, ", ");
      p=p->next;
    }
   if(formula->conditions!=NULL)  
    { 
      current=formula->conditions->front;
      while(current!=NULL && strcmp(current->aggregate, "null")!=0)
   {
       
       if(strstr(current->id, "OR"))
          strcat(havingstmt,current->id);
       else
       {
          strcat(havingstmt, current->aggregate);
           strcat(havingstmt, current->id);
       }
       having_flag = 1;
       if(current->next != NULL)
            strcat(havingstmt, "AND ");
       current = current->next;
       }      
    }

    if(( strcmp(groupBy,"null")!=0)&&(group_flag==1 || having_flag ==1))
     {   
          strcat(sqlstmt, " GROUP BY ");
         strcat(sqlstmt, groupBy);
    }
    if(having_flag==1)
    {
        strcat(sqlstmt, "HAVING ");
        strcat(sqlstmt, havingstmt);
    }

    freeExpr(var);
    freeExpr(formula);
    groupBy[0]='\0';
    havingstmt[0]='\0';

    return;
  }
  
  /* deal with general query */
  /*build select clause*/  
  if (var->attributes != NULL && formula->tables != NULL)
  {
    if(strcmp(var->attributes->front->id, "*") != 0)
    {
    

    LIST_ITEM *outercurrent;
    LIST_ITEM *innercurrent;
    outercurrent = formula->freevars->front;
    char freetemp[MAXSTMTLENGTH];
    int outer = 0;
    int inner = 0;
    
    while(outercurrent != NULL)
    {   
	strcpy(freetemp, outercurrent->id);
	strcat(freetemp, ".");

	innercurrent = var->attributes->front;
	while(innercurrent != NULL)
	{
	   if(strstr(innercurrent->id, freetemp) != NULL)
	   {
		inner++;
		break;
	   }

	   innercurrent = innercurrent->next;
	}
	outercurrent = outercurrent->next;
	outer++;
    }

    if(inner != outer)
    {
	freevar_error_flag = 1;
	sqlstmt[0] = '\0';
	return;
    }

    } 


    strncpy(sqlstmt, "SELECT DISTINCT \0", MAXSTMTLENGTH);
    current=var->attributes->front;
    
    if(strcmp(current->aggregate,"null")==0&&current->type =='A')
    {    strcpy(groupBy, current->id);
    }
    else
   {
       strcpy(groupBy, "null");
   }

    while (current != NULL)
    {
      if (current->type=='V')
      {
        strcpy(sqlstmt,"\0");
        
        strncpy(sqlstmt,"SELECT distinct \0" ,MAXSTMTLENGTH); 
        strcat(sqlstmt," * \0");
        break;
      }
      else  if(strcmp(current->aggregate,"null")!=0 && current->type == 
'A')
     {
       strcat(sqlstmt, current->aggregate);
              strcat(sqlstmt, "(");
              pch = strtok(current->id, ".");
              pch = strtok(NULL," ");
              strcat(sqlstmt,pch);
              strcat(sqlstmt, ")");
              group_flag =1;
       }
      else if (current->type=='A' || current->type=='E' || current->type=='X') 
          strcat(sqlstmt, current->id);
      current = current->next;
    }
  
    strcat(sqlstmt," FROM \0");
  
    current=formula->tables->front;
       
    while (current!=NULL)
    {
      strcat(sqlstmt, current->id);
      if (current->next!=NULL)
        strcat(sqlstmt, ", ");
      current=current->next;
    }

    if(formula->conditions!=NULL)
    {
      current=formula->conditions->front;
      printList(formula->conditions);
      while(current!=NULL && strcmp(current->aggregate, "null")!=0)
   {
      if(strstr(current->id,"OR"))
        strcpy(havingstmt, current->id);
     else
      {
       strcpy(havingstmt, current->aggregate);
       strcat(havingstmt, current->id);
      }
       having_flag = 1;
       if(current->next !=NULL  && strcmp(current->aggregate,"null")!=0)
            strcat(havingstmt, " AND ");
       current = current->next;       
       }
     
     if(current != NULL)
     {
      strcat(sqlstmt, " WHERE \0");
      while(current!=NULL)
      {
        if(strcmp(current->aggregate,"null")!=0)
        {
           strcpy(havingstmt,   current->aggregate);
           strcat(havingstmt,  current->id);
           having_flag = 1;
           againHave =1;
         }           
         else
        {  
           strcat(sqlstmt, current->id);
           againSql=1;           
        }
        if(current->next != NULL)
        {
            if(againHave ==1 && 
strcmp(current->next->aggregate,"null")!=0)
                 strcat(havingstmt, " AND ");
         else  if(againSql == 1 && 
strcmp(current->next->aggregate,"null")==0)
             strcat(sqlstmt, " AND ");
       }
         current=current->next;
      }
    }
    }
    if((strcmp(groupBy,"null")!=0)&&(group_flag ==1 ||having_flag == 1))
    {
       strcat(sqlstmt, " Group By ");
       strcat(sqlstmt, groupBy);
    }
    if(having_flag ==1 && strcmp(havingstmt, "null")!=0)
    {
      strcat(sqlstmt, " Having ");
      strcat(sqlstmt, havingstmt);
     }
    freeExpr(var);
    freeExpr(formula);
    havingstmt[0] = '\0';
    groupBy[0] = '\0';

    return;
  }

  sqlstmt[0] = '\0';
  fprintf(yyout, "\nUnknown error during SQL statement build.");
  freeExpr(var);
  freeExpr(formula);

  return;
}


/* -----------------------------------------------
Function name: uppercase
Purpose:
	To change a string into uppercase.
Parameters:
	string: the string to change to uppercase
Returns:
	nothing
------------------------------------------------- */
char* uppercase(char *string)
{
  int i = 0;

  if (string == NULL)
    return NULL;

  while (string[i] != '\0')
  {
    string[i] = toupper(string[i]);
    i++;
  }

  return string;
}

/* --------------------------------------------------
Function name: describeTable
Purpose:
	To display the schema of the specified table.
Parameters:
	tablename: name of the table
Returns:
	nothing
---------------------------------------------------- */
void describeTable(char *tablename)
{
  strcpy(sqlstmt, "SELECT column_name, nullable, data_type, data_length, data_precision, data_scale\n");
  strcat(sqlstmt, "  FROM user_tab_columns\n");
  strcat(sqlstmt, " WHERE table_name = '");
  strcat(sqlstmt, uppercase(tablename));
  strcat(sqlstmt, "'");

  executesqlstmt(0, 0, 0);
}

/****************************************************
Function name: displayTable
Purpose:
	To display the content of the specified table.
Parameters:
	tableName: name of the table
Returns:
	nothing
******************************************************/

void displayTable(char *tableName)
{
  strcpy(sqlstmt, "SELECT * FROM ");
  strcat(sqlstmt, tableName);
  executesqlstmt(0, 0, 0);
}

/*************************************************************************
*
* Function Name : exeoracle()
* purpose: To executes DDL and DML operation.
* Parameters: oracom: the DDL or DML command.
*
*  Return: nothing
*
*************************************************************************/

void exeoracle(char* oracom)
{
  strcpy(sqlstmt, oracom);
  executesqlstmt(0, 0, 0);
}

/***********************************************************************
*
* Function name: addQuantifierForm()
* Parameters: 
*       
*  Returns:
*         the structure containing the SQL statement which stored in condition list
*
***********************************************************************/
SELECTSTMT* addQuantifierForm()
{
  char        temp[MAXSTMTLENGTH];
  SELECTSTMT* nquantifier; 
   
  if ((nquantifier = (SELECTSTMT*) calloc(1, sizeof(SELECTSTMT))) == NULL)
  {
     fprintf(yyout, "not enough memory to allocate to selectstmt!");
     exit(1);
  }

  fprintf(yyout, "in addQuantifierForm()");

  
  if(quantifier_error_flag == 1)
  {
	nquantifier->f_error = 'E';
	strcpy(nquantifier->errormsg, "\nVariable(s) in quantifier is(are) not bound!.\n");
	return nquantifier;
  }

  if(table_error_flag == 1)
  {
	nquantifier->f_error = 'E';
	strcpy(nquantifier->errormsg, " ");
	return nquantifier;
  }
  
  nquantifier->f_error = 'N';

  if (forall_flag == 0)
  {
    switch (exist_flag)
    {
      case 0: 
              strcpy(temp, " EXISTS( ");   /**/
               break;
      case 1: 
               strcpy(temp, "NOT EXISTS( ");
	       exist_flag_count--;
	       if(exist_flag_count<=0)
	       {
		  exist_flag = 0;
	       }
               break;
      case 2:  strcpy(temp, "NOT EXISTS( "); 
               break;
      default: fprintf(yyout, "\nWrong exist_flag value!");
               exit(1);
    }
  }
  else if(forall_flag==2 && not_exist_flag==1)
  {

    strcpy(temp, " EXISTS ( ");
	  not_exist_flag = 0;
  }
  else
     	strcpy(temp, "NOT EXISTS ( "); /*����forallΪnot exist*/

  strcat(temp, sqlstmt);
  strcat(temp, " )\0");
  if(exist_flag_count<=0)
   exist_flag=0;
  nquantifier->conditions = addToFront(temp, nquantifier->conditions, 'W');

  return nquantifier;
}

/*****************************************************************
 * Function name: assignquery
 * Purpose:
 *         To execute a query in the form of a select structure and
 *          store the result in a new table 
 * Parameters: 
 *         table: the name for the temp table
 *  Returns:
 *         nothing
 ******************************************************************/

void assignQuery(char *table)
{
  char temp_sqlstmt[MAXSTMTLENGTH];
  		
  /*  Delete any temporary tables used in the sql statement. */

  /*printf("\n In assignQuery(): table name: %s", table);*/
  strcpy(temp_sqlstmt, sqlstmt);
  if(table_test(table) == 1)  
     dropTmpTables(table);
  
  if (strlen(table) > 0)
  {
    strcpy(sqlstmt, "CREATE TABLE ");
    strcat(sqlstmt, table);
    strcat(sqlstmt, " AS \n");
		
    strcat(sqlstmt, temp_sqlstmt);

    executesqlstmt(0, 1, 0);
  }
}

/*****************************************************************
 * Function name: join_relations
 * Purpose:
 *         
 *         
 * Parameters: 
 *         
 *  Returns:  
 *         
 ******************************************************************/
SELECTSTMT* join_relations(SELECTSTMT* andformula, char* join_type, SELECTSTMT* formula)
{
  /*printf("\n In join_relations");*/

  if ((andformula == NULL || formula == NULL) ||
      (andformula->tables == NULL || formula->tables == NULL) ||
      (andformula->tables->front == NULL || formula->tables->front == NULL))
  {
    andformula->f_error = 'E';
    strcpy(andformula->errormsg, "ERROR: No relation name specified!");
  }

  else if (andformula->f_error == 'E')
    ; /* do nothing here */
  else if (formula->f_error == 'E')
    strcpy(andformula->errormsg, formula->errormsg);
  else
  { 
    LIST_ITEM *current;
    current = formula->tables->front;
    while(current != NULL)
    {
	andformula->tables = addtoback(current->id, andformula->tables, 'T');
	current = current->next;
    }
    andformula->conditions = addtoback(uppercase(join_type), andformula->conditions, 'J');
    andformula->conditions = mergeList(andformula->conditions, formula->conditions);
  }

  return andformula;
}

/*****************************************************************
 * Function name: buildJoinSQLStmt
 * Purpose:
 *         
 *         
 * Parameters: 
 *         
 *  Returns:  
 *         
 ******************************************************************/
void buildJoinSQLStmt(SELECTSTMT *var, SELECTSTMT *formula)
{
  LIST_ITEM *current, *inner_current;
  LIST      *column_list;
  char      table_name[MAXLENGTH];
  char      attribute_name[MAXLENGTH];
  int       found;
  int       count;

  /*printf("\n In buildJoinSQLStmt \n");*/

  /* test colums */
  if (var->attributes == NULL)
  {
    fprintf(yyout, "\n%s\n", "\nERROR: No Attribute is specified!\nTRC>");
    return;
  } 

  if (formula->tables == NULL)
  {
    fprintf(yyout, "\n%s\n", "\nERROR: No table is specified!\nTRC>");
    return;
  } 

  current = formula->tables->front;
  count = 0;      
  while (current != NULL)
  {
    if (current->type == 'T')
      count++;

    current = current->next;
  }

  current = var->attributes->front;
 
  uppercase(current->id);
 
  while (current != NULL)
  {
    parse_attribute(current->id, attribute_name);
    if (current->type == 'A')
    {
      inner_current = formula->tables->front;
      found = 0;      
      while (inner_current != NULL)
      {
        if (inner_current->type == 'T')
        {
          strcpy(table_name, inner_current->id);
          strtok(table_name, " ");
          column_list = retrieve_column_names(table_name);
          
          if (searchlist(attribute_name, column_list->front) == 1)
            found++;
        }
        inner_current = inner_current->next;
      }

      if (found != count)
      {
        fprintf(yyout, "\n%s\n", "\nERROR: Column does not exist in the table!\nTRC>");
        return;
      }
    }

    current = current->next;
  }
    
  /* set up the SQL statement */
  if (formula->conditions == NULL ||
      formula->conditions->front == NULL ||
      formula->conditions->front->type != 'J')
  {
    fprintf(yyout, "\n%s\n", "\nERROR: unknown error in or/and operation!\nTRC>");
    return;
  } 

  sqlstmt[0] = '\0';
  current = formula->tables->front;
  while (current != NULL)
  {
    if (current->type == 'T')
    {
      if (strlen(sqlstmt) == 0)
        strcpy(sqlstmt, "SELECT distinct "); /*distinct*/
      else
        strcat(sqlstmt, "SELECT distinct "); /*distinct*/
 
      inner_current = var->attributes->front;
      while (inner_current != NULL)
      {
        if (inner_current->type == 'A' || inner_current->type == 'E')
          strcat(sqlstmt, inner_current->id);

        inner_current = inner_current->next;
      }

      strcat(sqlstmt, "\n  FROM ");
      strcat(sqlstmt, current->id);
      if (current->next != NULL)
      {
        if (strcmp(formula->conditions->front->id, "OR") == 0)
          strcat(sqlstmt, "\nUNION\n");
        else if (strcmp(formula->conditions->front->id, "AND") == 0)
          strcat(sqlstmt, "\nINTERSECT\n");
        else if (strcmp(formula->conditions->front->id, "ANDNOT") == 0)
          strcat(sqlstmt, "\nMINUS\n");
        else
        {
          fprintf(yyout, "\n%s\n", "\nERROR: unexpected error during or/and operation!\nTRC>");
          return;
        }
      }
    }    
    current = current->next;
  }

  freeExpr(var);
  freeExpr(formula);
}

/*****************************************************************
 * Function name: table_test
 * Purpose:
 *         To check if temptable being built is already exist. 
 *         
 * Parameters: 
 *                  table: the name for the temp table
 *        
 *  Returns:
 *         1: temptable exists
 *         0: temptable does not exists
 ******************************************************************/

int table_test(char* tablename)
{
  char       temp_str[MAXLENGTH];
  char       temp_table_name[MAXLENGTH];
  LIST*      table_colums;
  LIST_ITEM  *current;
  int        length;

  
  if(strlen(tablename) == 0)
    return 0;

  /*printf("\nIn table_test() table name: --%s--", tablename);*/ 
  strcpy(sqlstmt, "SELECT table_name FROM user_tables");
  
  table_colums = executesqlstmt(1, 0, 0);

  strcpy(temp_table_name, tablename);
  strtok(temp_table_name, " ");
  uppercase(temp_table_name); 

  current = table_colums->front;
  while(current != NULL)
  {  
    length = strcspn(current->id, " ");
    strncpy(temp_str, current->id, length);
    temp_str[length] = '\0';
    if(strcmp(temp_str, temp_table_name) == 0)
      return 1;
    else
      current = current->next;
  }

  return 0;  
}

/*****************************************************************
 * Function name: retrieve_column_names
 * Purpose      : To retrieve all of the columns in tablename
 *                and return them in a linked list.
 *         
 * Parameters: 
 *      tablename	the name of the table to retrieve the columns
 *        
 *  Returns:
 *         linked list containing the attributes of the table
 ******************************************************************/
LIST *retrieve_column_names(char *tablename)
{
  LIST* colum;

  strcpy(sqlstmt, "select column_name from user_tab_columns where table_name = '");
  strcat(sqlstmt, uppercase(tablename));
  strcat(sqlstmt, "'");
  
  colum = executesqlstmt(1, 0, 0);
  return colum;
}

/*****************************************************************
 * Function name: searchlist
 * Purpose:       To search the linked list for element.
 * 
 * Parameters:
 * 	element		the element to be searched for
 *         front		the front of the list to be searched
 * 
 * Returns:
 * 	0	Upon not finding element.
 * 	1 	Upon finding element
 ******************************************************************/
int searchlist(char *element, LIST_ITEM *front)
{
  LIST_ITEM *current = front;
  char searchstring[MAXLENGTH], currentstring[MAXLENGTH];

  strcpy(searchstring, element);
  strtok(searchstring, " ");

  while (current != NULL)
  {
    strcpy(currentstring, current->id);
    strtok(currentstring, " ");
    if (strcmp(searchstring, currentstring) == 0)
       return 1;
    current = current->next;
  }

  return 0;
}

/*****************************************************************
Function name: parse_attribute
Purpose:       To remove the attribute name from a string that contains
		the table name followed by the attribute name.
Parameters:
	tabatt		the string containing the tablename followed by
			the attribute separated by a dot
	attribute	the string to place the retrieved attribute
			into
Returns:
      nothing
 ******************************************************************/
void parse_attribute(char *tabatt, char *attribute)
{
  char *foundstring;
  char tempstring[MAXLENGTH];

  strncpy(tempstring, tabatt, MAXLENGTH);

  foundstring = strtok(tempstring, ".");	
  if ((foundstring = strtok(NULL, ".")) != NULL)
    strncpy(attribute, foundstring, MAXLENGTH);
  else
    strncpy(attribute, tabatt, MAXLENGTH);
}

/*****************************************************************
Function name: join_test
Purpose:       
	
Parameters:
	
	
	
	
Returns:
      
 ******************************************************************/
int join_test(SELECTSTMT* formula1, SELECTSTMT* formula2)
{

  /*fprintf(yyout, "\nin join_test()  ");*/
  if (formula1 == NULL || formula2 == NULL ||
      formula1->tables == NULL || formula2->tables == NULL ||
      formula1->tables->front == NULL || formula2->tables->front == NULL)
    return 0;

  if (strcmp(strstr(formula1->tables->front->id, " "), 
             strstr(formula2->tables->front->id, " ")) == 0)
    return 1;

  return 0;
}

/*****************************************************************
 * Function name: renameattribute
 *         
 *    Purpose: Rename the attributes of the original relation
 *         
 *    Parameters: 
 *              str: relationname
 *        variables: the attributes of the relation
 *       expression: the query to be used to build the table
 *
 *    Returns: nothing
 *         
 ******************************************************************/

void renameattribute(char* str, SELECTSTMT* variables)
{
  char table_name[MAXLENGTH];
  char temp_str[MAXLENGTH];
  char temp_str_1[MAXLENGTH];
  char temp_sqlstmt[MAXSTMTLENGTH];
  char temp_sqlstmt_1[MAXSTMTLENGTH];
  LIST_ITEM* current;
  SELECTSTMT* nrename;
  LIST* tab_columns;
  int length;
 
  temp_str[0] = '\0';
  current = variables->attributes->front;
  while(current != NULL)
  {
    strcat(temp_str, current->id);
    current = current->next;
  }
  
  strcpy(table_name, str);
  strcat(table_name, " (");
  strcat(table_name, temp_str);
  strcat(table_name, ")");

  assignQuery(table_name);

  freeExpr(variables);
}

/*****************************************************************/

