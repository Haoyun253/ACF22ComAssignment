/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
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
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ?Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern cloud_int line;
extern Token tokenizer();
extern cloud_char* keywordTable[];
cloud_int syntaxErrorNumber = 0;

#define STR_LANGNAME	"Cloud"
#define LANG_WRTE		"print("
#define LANG_READ		"readline("
#define LANG_MAIN		"Main("
#define LANG_FUNC		"function"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_begin,
	KW_for,
	KW_while,
	KW_do,
	KW_end,
	KW_if,
	KW_then,
	KW_elseif,
	KW_else,
	KW_break,
	KW_return,
	KW_const,
	KW_false,
	KW_function,
	KW_true,
	KW_int,
	KW_char,
	KW_float,
	KW_string,
	KW_bool,
	KW_null,
	KW_unsign
};

/* Function definitions */
cloud_void startParser();
cloud_void matchToken(cloud_int, cloud_int);
cloud_void syncErrorHandler(cloud_int);
cloud_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
cloud_void codeSession();
cloud_void parameterSession();
cloud_void parameterVarListDeclarations();
cloud_void optionalStatements();
cloud_void varListDeclarations();
cloud_void varListDeclaration();
cloud_void varListDeclarationPrime();
cloud_void outputStatement();
cloud_void outputVariableList();
cloud_void outputVariableLists();
cloud_void outputVariableListPrime();
cloud_void program();
cloud_void statement();
cloud_void statements();
cloud_void statementsPrime();
cloud_void assignmentStatement();
cloud_void assignmentExpression();
cloud_void arithmeticExpression();
cloud_void arithmeticExpressionDeclaration();
cloud_void arithmeticExpressionDeclarationPrime();
cloud_void IntListDeclaration();
cloud_void FloatListDeclaration();
cloud_void StringListDeclaration();
cloud_void inputStatement();
cloud_void inputVariableList();
cloud_void conditionalExpression();
cloud_void logicalExpression();
cloud_void logicalExpressionDeclaration();
cloud_void logicalExpressionDeclarationPrime();
cloud_void whileStatement();
cloud_void ifStatement();

#endif
