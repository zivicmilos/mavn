#include "Output.h"
#include <fstream>

using namespace std;

void writeInFile(Variables* mVars, Variables* rVars, TokenList* tokenList)
{
	bool func = false;
	ofstream outfile("output.s", ofstream::binary);
	for (auto it = tokenList->begin(); it != tokenList->end(); ++it)
	{
		if (it->getType() == T_FUNC)
		{
			outfile << ".globl " << (++it)->getValue() << "\n";
		}
	}
	outfile << '\n';
	if (!mVars->empty())
	{
		outfile << ".data\n";
		for (auto it = mVars->begin(); it != mVars->end(); ++it)
		{
			outfile << (*it)->getName() << ':' << '\t' << ".word " << (*it)->getValue() << '\n';
		}
	}
	outfile << '\n';
	outfile << ".text\n";

	for (auto it = tokenList->begin(); it != tokenList->end(); ++it)
	{
		if (it->getType() == T_FUNC)
			func = true;
		if (func)
		{
			if (it->getType() == T_FUNC)
			{
				outfile << (++it)->getValue() << ':';
			}
			else if (it->getType() != T_FUNC && it->getType() != T_SEMI_COL && it->getType() != T_END_OF_FILE)
			{
				if (it->getType() == T_R_ID)
				{
					for (auto it2 = rVars->begin(); it2 != rVars->end(); ++it2)
					{
						if ((*it2)->getName() == it->getValue())
						{
							outfile << "$t" << (*it2)->getAssignment() << ' ';
						}
					}
				}
				else if (it->getType() == T_COL)
				{
					outfile << it->getValue() << '\n';
				}
				else
				{
					outfile << it->getValue() << ' ';
				}
			}
			else if (it->getType() == T_SEMI_COL)
			{
				outfile << '\n';
			}
		}
	}
}