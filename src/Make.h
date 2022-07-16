#pragma once
#include "IR.h"
#include "Token.h"
#include "LexicalAnalysis.h"
#include <map>

	Variables* makeMemVariables(TokenList& tokenList);

	Variables* makeRegVariables(TokenList& tokenList);

	bool variableExists(std::string s, Variables* vars);

	bool labelExists(std::string s);

	Instructions* makeInstructions(TokenList& tokenList, Variables* rVars);
	
	void findPS(Instructions* instrs);
