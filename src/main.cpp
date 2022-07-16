/* Autor: Miloš Živić Datum: 10.06.2020. */

#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "IR.h"
#include "Types.h"
#include "Make.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "Simplification.h"
#include "ResourceAllocation.h"
#include "Output.h"

using namespace std;

int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		SyntaxAnalysis syx(lex);
		
		if (syx.Do())
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}


		Variables* mVars = makeMemVariables(lex.getTokenList());
		Variables* rVars = makeRegVariables(lex.getTokenList());
		for (auto it = mVars->begin(); it != mVars->end(); ++it)
		{
			(*it)->printVariable();
		}
		for (auto it = rVars->begin(); it != rVars->end(); ++it)
		{
			(*it)->printVariable();
		}
		
		Instructions* instructions = makeInstructions(lex.getTokenList(), rVars);
		doLivenessAnalysis(instructions);
		for (auto it = instructions->begin(); it != instructions->end(); ++it)
		{
			(*it)->printInstruction();
		}

		InterferenceGraph* ig;

		ig = doInterferenceGraph(instructions, rVars);

		printInterferenceGraph(ig);

		stack<Variable*>* simplificationStack = doSimplification(ig, __REG_NUMBER__);

		ig = doInterferenceGraph(instructions, rVars);

		if (simplificationStack == NULL)
		{
			cout << "Spill detected!\n";
		}
		else
		{
			if (doResourceAllocation(simplificationStack, ig))
			{
				cout << "Resource allocation finished successfully!" << endl;
			}
			else
			{
				throw runtime_error("\nException! Resource allocation failed!\n");
			}
		}

		for (auto it = rVars->begin(); it != rVars->end(); ++it)
		{
			(*it)->printVariable();
		}

		writeInFile(mVars, rVars, &lex.getTokenList());


	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
