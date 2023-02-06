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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ?Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
#define SET_BIT7	0x08
#define SET_BIT6	0x04
#define SET_BIT5	0x02
#define SET_BIT4	0x01

#define RESET_BIT7	0xF7	
#define RESET_BIT6	0xFB	
#define RESET_BIT5	0xFD	
#define RESET_BIT4	0xFE

#define CHK_BIT7	0x08
#define CHK_BIT6	0x04
#define CHK_BIT5	0x02
#define CHK_BIT4	0x01
/* TO_DO: BIT 7: FUL = Full */
/* TO_DO: BIT 6: EMP: Empty */
/* TO_DO: BIT 5: REL = Relocation */
/* TO_DO: BIT 4: END = EndOfBuffer */

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	cloud_int mark;			/* the offset to the mark position (in chars) */
	cloud_int read;			/* the offset to the get a char position (in chars) */
	cloud_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	cloud_char*	content;			/* pointer to the beginning of character array (character buffer) */
	cloud_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	cloud_int		increment;			/* character array increment factor */
	cloud_int		mode;				/* operational mode indicator */
	cloud_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	cloud_int		histogram[NCHAR];	/* Statistics of chars */
	cloud_int		numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(cloud_int, cloud_int, cloud_int);
ReaderPointer	readerAddChar		(ReaderPointer const, cloud_char);
cloud_bool		readerClear		    (ReaderPointer const);
cloud_bool		readerFree		    (ReaderPointer const);
cloud_bool		readerIsFull		(ReaderPointer const);
cloud_bool		readerIsEmpty		(ReaderPointer const);
cloud_bool		readerSetMark		(ReaderPointer const, cloud_int);
cloud_int		readerPrint		    (ReaderPointer const);
cloud_int		readerLoad			(ReaderPointer const, FILE* const);
cloud_bool		readerRecover		(ReaderPointer const);
cloud_bool		readerRetract		(ReaderPointer const);
cloud_bool		readerRestore		(ReaderPointer const);
/* Getters */
cloud_char		readerGetChar		(ReaderPointer const);
cloud_char*	readerGetContent	(ReaderPointer const, cloud_int);
cloud_int		readerGetPosRead	(ReaderPointer const);
cloud_int		readerGetPosWrte	(ReaderPointer const);
cloud_int		readerGetPosMark	(ReaderPointer const);
cloud_int		readerGetSize		(ReaderPointer const);
cloud_int		readerGetInc		(ReaderPointer const);
cloud_int		readerGetMode		(ReaderPointer const);
cloud_byte		readerGetFlags		(ReaderPointer const);
cloud_int		readerShowStat		(ReaderPointer const);
cloud_int		readerNumErrors		(ReaderPointer const);

#endif
