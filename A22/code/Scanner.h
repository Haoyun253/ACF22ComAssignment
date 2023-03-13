/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Haoyun Deng
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ?Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Integer Literal token */
	SEOF_T,		/* 11: Source end-of-file token */
	FNL_T,      /* 12: Float point Number Literal*/
	VAR_T,      /* 13: Variable Literal Token */
	PER_T,		/* 14: Period Literal Token*/
	ARI_T,		/* 15: Arithemetic Token*/
	REL_T,		/* 16: Relational Token*/
	LOG_T,		/* 17: Logical operator*/
	UND_T,		/* 18: Underscore */
	ASS_T,      /* 19: Assignment Token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_POW} AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum AssignmentOperator { OP_ASS } AssOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	cloud_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	AssOperator assignmentOperator;		/* assignment operator attribute code*/
	EofOperator seofType;				/* source-end-of-file attribute code */
	cloud_int intValue;						/* integer literal attribute (value) */
	cloud_int keywordIndex;					/* keyword index in the keyword table */
	cloud_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	cloud_flout floatValue;					/* floating-point literal attribute (value) */
	cloud_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	cloud_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	cloud_byte flags;			/* Flags information */
	union {
		cloud_int intValue;				/* Integer value */
		cloud_flout floatValue;			/* Float value */
		cloud_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	cloud_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '('
#define CHRCOL4 '\''
#define CHRCOL5 '.'
#define CHRCOL7 '\n'
#define CHRCOL8 '#'

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '('

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	12		/* Error state with no retract */
#define ESWR	13		/* Error state with retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 9

/* TO_DO: Transition table - type of states defined in separate table */
static cloud_int transitionTable[][TABLE_COLUMNS] = {
	/*[A-z], [0-9],    _,    (,    ',   .,  other,   /n,    #
	   L(0),  N(1), U(2), OP(3), Q(4), P(5),  O(6),NL(7),C(8) */
	{     1,     6, ESNR, ESNR,    4, ESWR, ESNR, ESNR,   10}, // S0: NOAS
	{     1,     1,    1,    2,    3,    3,    3,    3,   3}, // S1: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS}, // S2: ASNR (MVID)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS}, // S3: ASWR (VARIABLE)
	{     4,     4,    4,    4,    5,    4,    4,    4,    4}, // S4: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS}, // S5: ASNR (SL)
	{     7,     6,    7,    7,    7,    8,    7,    7,    7}, // S6: NOAS
    {    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,	  FS}, // S7: ASWR (INTEGER)
	{     9,     8,    9,    9,    9,    9,    9,    9,    9}, // S8: NOAS 
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,	  FS}, // S9: ASWR (FLOAT)
	{    10,    10,   10,   10,   10,   10,   10,	10,	  11}, // S10: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,   FS,   FS},  // S11: ASNR (COMMENTS)

};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static cloud_int stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (VAR) - VARIABLE */
	NOFS, /* 04 */
	FSNR, /* 05  - STRING */
	NOFS, /* 06  */
	FSWR, /* 07 - INTEGER */
	NOFS, /*  08 */
	FSWR, /* 09 - FLOAT */
	NOFS, /* 10 */
	FSNR, /* 11 - COMMENTS */
	FSNR, /* 12 (Err1 - no retract) */
	FSWR  /* 13 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
cloud_int startScanner(ReaderPointer psc_buf);
Token tokenizer(cloud_void);
static cloud_int nextClass(cloud_char c);				/* character class function */
static cloud_int nextState(cloud_int, cloud_char);		/* state machine function */
cloud_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(cloud_char* lexeme);

/* Declare accepting states functions */
Token funcVAR	(cloud_char lexeme[]);
Token funcID   (cloud_char lexeme[]);
Token funcKEY	(cloud_char lexeme[]);
Token funcErr	(cloud_char lexeme[]);
Token funcIL	(cloud_char lexeme[]);
Token funcSL    (cloud_char lexeme[]);
Token funcFL    (cloud_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,	/* ID	[02] - Variables */
	funcID,	/* MNID	[03] - Methods */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] - String Literal */
	NULL,	    /* -  [06] */
	funcIL,	    /* IL [07] - Integer Literal*/
	NULL,		/* -   [08] */
	funcFL,	    /* FL [09] - Float Literal*/
	NULL,	    /* - [10] */
	NULL,		/* - [11] - Comment*/
	funcErr,	/* ERR1 [12] - No retract */
	funcErr		/* ERR2 [13] - Retract */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 28

/* TO_DO: Define the list of keywords */
static cloud_char* keywordTable[KWT_SIZE] = {
	"begin",
	"for",
	"while",
	"do",
	"end",
	"if",
	"then",
	"elseif",
	"else",
	"break",
	"catch",
	"try",
	"global",
	"local",
	"return",
	"continue",
	"const",
	"false",
	"finally",
	"function",
	"true",
	"Int",
	"Char",
	"Float",
	"String",
	"Bool",
	"Null",
	"Unsign"
};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	cloud_char indentationCharType;
	cloud_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
cloud_int numScannerErrors;

#endif
