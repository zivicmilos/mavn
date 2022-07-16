#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"

class SyntaxAnalysis 
{
public:
	SyntaxAnalysis(LexicalAnalysis &lex);

	bool Do();

private:

	void printSyntaxError(Token token);

	
	void printTokenInfo(Token token);

	
	void eat(TokenType t);

	
	Token getNextToken();

	
	void Q();

	
	void S();

	
	void L();

	
	void E();

	
	LexicalAnalysis& m_lexicalAnalysis;

	
	bool m_errorFound;

	
	TokenList::iterator m_tokenIterator;

	
	Token m_currentToken;

};