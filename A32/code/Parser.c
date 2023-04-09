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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

cloud_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
cloud_void matchToken(cloud_int tokenCode, cloud_int tokenAttribute) {
	cloud_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
cloud_void syncErrorHandler(cloud_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
cloud_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
cloud_void program() {
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == KW_function) {
			matchToken(KW_T, KW_function);			
			matchToken(MNID_T, NO_ATTR);
			printf("%s%s\n", STR_LANGNAME, ": Main Method parsed");
			parameterSession();
			codeSession();
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
cloud_void parameterSession() {
	parameterVarListDeclarations();
	matchToken(RPR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Parameter Session parsed");
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
cloud_void parameterVarListDeclarations() {
	switch (lookahead.code) {
	case VAR_T:
		varListDeclarations();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Parameter Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
cloud_void codeSession() {
	optionalStatements();
	matchToken(KW_T, KW_end);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
cloud_void optionalStatements() {
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == KW_end)
			break;
	case VAR_T:
	case MNID_T:
		statements();
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
cloud_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
cloud_void statementsPrime() {
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType == KW_end)
			break;
	case MNID_T:
	case VAR_T:
		statements();
		break;
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
cloud_void statement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
			case KW_int:
				matchToken(KW_T, KW_int);
				varListDeclarations();
				matchToken(EOS_T, NO_ATTR);
				printf("%s%s\n", STR_LANGNAME, ": Int Variable List Declaration parsed");
				printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration parsed");
				printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
				break;
			case KW_float:
				matchToken(KW_T, KW_float);
				varListDeclarations();
				matchToken(EOS_T, NO_ATTR);
				printf("%s%s\n", STR_LANGNAME, ": Float Variable List Declaration parsed");
				printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration parsed");
				printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
				break;
			case KW_string:
				matchToken(KW_T, KW_string);
				varListDeclarations();
				matchToken(EOS_T, NO_ATTR);
				printf("%s%s\n", STR_LANGNAME, ": String Variable List Declaration parsed");
				printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration parsed");
				printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
				break;
			case KW_while:
				matchToken(KW_T, KW_while);
				whileStatement();
				break;
			break;
			case KW_if:
				matchToken(KW_T, KW_if);
				ifStatement();
				break;
			break;
			default:
				printError();
		}
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 9) == 0) {
			inputStatement();
		}
		break;
	case VAR_T:
		varListDeclaration();
		matchToken(ASS_T, NO_ATTR);
		assignmentStatement();
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}



cloud_void assignmentStatement() {
	assignmentExpression();
	printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

cloud_void assignmentExpression() {
	arithmeticExpression();
	printf("%s%s\n", STR_LANGNAME, ": Assignment expression parsed");
}

cloud_void arithmeticExpression() {
	arithmeticExpressionDeclaration();
	arithmeticExpressionDeclarationPrime();
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic expression parsed");
}

cloud_void arithmeticExpressionDeclaration() {
	switch (lookahead.code)
	{
	case ARI_T:
		switch (lookahead.attribute.arithmeticOperator) 
		{
		case OP_ADD:
			printf("%s%s\n", STR_LANGNAME, ": Additive expression parsed");
			break;
		case OP_SUB:
			printf("%s%s\n", STR_LANGNAME, ": Subtraction expression parsed");
			break;
		case OP_MUL:
			printf("%s%s\n", STR_LANGNAME, ": Multiplicative expression parsed");
			break;
		case OP_DIV:
			printf("%s%s\n", STR_LANGNAME, ": Division expression parsed");
			break;
		case OP_POW:
			printf("%s%s\n", STR_LANGNAME, ": Power expression parsed");
			break;
		}
		matchToken(ARI_T, NO_ATTR);
		break;
	default:
		;
	}
	switch (lookahead.code)
	{
		case VAR_T:
			varListDeclaration();
			break;
		case INL_T:
			IntListDeclaration();
			break;
		case FNL_T:
			FloatListDeclaration();
			break;
		case STR_T:
			StringListDeclaration();
			break;
		default:
			printError();
	}
}

cloud_void arithmeticExpressionDeclarationPrime() {
	switch (lookahead.code)
	{
	case ARI_T:
		arithmeticExpression();
		printf("%s%s\n", STR_LANGNAME, ": Primary arithmetic expression parsed");
		break;
	default:
		;
	}
}

cloud_void ifStatement() {
	matchToken(LPR_T, NO_ATTR);
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_true:
			printf("%s%s\n", STR_LANGNAME, ": True expression parsed");
			matchToken(KW_T, KW_true);
			break;
		case KW_false:
			printf("%s%s\n", STR_LANGNAME, ": False expression parsed");
			matchToken(KW_T, KW_false);
			break;
		default:
			printError();
		}
		break;
	default:
		logicalExpression();
	}
	matchToken(RPR_T, NO_ATTR);
	matchToken(KW_T, KW_then);
	codeSession();
	printf("%s%s\n", STR_LANGNAME, ": Then statement parsed");
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_else:
			matchToken(KW_T, KW_else);
			codeSession();
			printf("%s%s\n", STR_LANGNAME, ": Else statement parsed");
			break;
		case KW_elseif:
			matchToken(KW_T, KW_elseif);
			ifStatement();
			printf("%s%s\n", STR_LANGNAME, ": Elseif statement parsed");
			break;
		default:
			;
		}
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": If statement parsed");
}

cloud_void whileStatement() {
	matchToken(LPR_T, NO_ATTR);
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_true:
			printf("%s%s\n", STR_LANGNAME, ": True expression parsed");
			matchToken(KW_T, KW_true);
			break;
		case KW_false:
			printf("%s%s\n", STR_LANGNAME, ": False expression parsed");
			matchToken(KW_T, KW_false);
			break;
		default:
			printError();
		}
		break;
	default:
		logicalExpression();
	}
	matchToken(RPR_T, NO_ATTR);
	codeSession();
	printf("%s%s\n", STR_LANGNAME, ": While loop statement parsed");
}

cloud_void logicalExpression() {
	logicalExpressionDeclaration();
	logicalExpressionDeclarationPrime();
	printf("%s%s\n", STR_LANGNAME, ": Logical expression parsed");
}

cloud_void logicalExpressionDeclaration() {
	switch (lookahead.code)
	{
	case LOG_T:
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_NOT:
			printf("%s%s\n", STR_LANGNAME, ": Not logical expression parsed");
			break;
		default:
			printError();
		}
		matchToken(LOG_T, NO_ATTR);
		break;
	default:
		;
	}

	conditionalExpression();
	printf("%s%s\n", STR_LANGNAME, ": Conditional expression parsed");

}

cloud_void logicalExpressionDeclarationPrime() {
	switch (lookahead.code)
	{
	case LOG_T:
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_AND:
			printf("%s%s\n", STR_LANGNAME, ": And logical expression parsed");
			matchToken(LOG_T, NO_ATTR);
			logicalExpression();
			break;
		case OP_OR:
			printf("%s%s\n", STR_LANGNAME, ": Or logical expression parsed");
			matchToken(LOG_T, NO_ATTR);
			logicalExpression();
			break;
		default:
			printError();
		}
		break;
	default:
		;
	}
}

cloud_void conditionalExpression() {
	switch (lookahead.code)
	{
	case VAR_T:
		varListDeclaration();
		break;
	case INL_T:
		IntListDeclaration();
		break;
	case FNL_T:
		FloatListDeclaration();
		break;
	case STR_T:
		StringListDeclaration();
		break;
	default:
		printError();
	}

	switch (lookahead.code)
	{
	case REL_T:
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_EQ:
			printf("%s%s\n", STR_LANGNAME, ": Equal conditional expression parsed");
			break;
		case OP_NE:
			printf("%s%s\n", STR_LANGNAME, ": Not equal conditional expression parsed");
			break;
		case OP_GT:
			printf("%s%s\n", STR_LANGNAME, ": Greater than conditional expression parsed");
			break;
		case OP_LT:
			printf("%s%s\n", STR_LANGNAME, ": Less than conditional expression parsed");
			break;
		}
		matchToken(REL_T, NO_ATTR);
		break;
	default:
		printError();
	}

	switch (lookahead.code)
	{
	case VAR_T:
		varListDeclaration();
		break;
	case INL_T:
		IntListDeclaration();
		break;
	case FNL_T:
		FloatListDeclaration();
		break;
	case STR_T:
		StringListDeclaration();
		break;
	default:
		printError();
	}

}



/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
cloud_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	outputVariableLists();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

cloud_void outputVariableLists() {
	outputVariableList();
	outputVariableListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Output variable lists parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
cloud_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

cloud_void outputVariableListPrime() {
	switch (lookahead.code)
	{
	case COM_T:
		matchToken(COM_T, NO_ATTR);
		switch (lookahead.code)
		{
		case STR_T:
		case VAR_T:
			outputVariableLists();
			break;
		default:
			printError();
		}
		break;
	default:
		;
	}
}

cloud_void inputStatement() {
	matchToken(MNID_T, NO_ATTR);
	inputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

cloud_void inputVariableList() {
	switch (lookahead.code) {
	case VAR_T:
		varListDeclarations();
		break;
	default:
		printError();
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Input variable list parsed");
}

cloud_void varListDeclarations() {
	varListDeclaration();
	varListDeclarationPrime();
}

cloud_void varListDeclaration() {
	matchToken(VAR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Variable Identifier parsed");
}

cloud_void varListDeclarationPrime() {
	switch (lookahead.code)
	{
	case COM_T:
		matchToken(COM_T, NO_ATTR);
		if (lookahead.code == VAR_T)
			varListDeclarations();
		else {
			printError();
		}
		break;
	default:
		;
	}
}

cloud_void IntListDeclaration() {
	matchToken(INL_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Integer Identifier parsed");
}

cloud_void FloatListDeclaration() {
	matchToken(FNL_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Float Identifier parsed");
}

cloud_void StringListDeclaration() {
	matchToken(STR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": String Identifier parsed");
}