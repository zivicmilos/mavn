#include "LivenessAnalysis.h"

void doLivenessAnalysis(Instructions* instructions)
{
	Variables in, out;
	bool same;
	do {
		same = false;
		for (auto it = instructions->rbegin(); it != instructions->rend(); ++it)
		{
			in = *(*it)->getIn();
			out = *(*it)->getOut();
			if (!(*it)->getSucc()->empty())
			{
				for (auto it3 = (*it)->getSucc()->begin(); it3 != (*it)->getSucc()->end(); ++it3)
				{
					(*it)->getOut()->insert((*it)->getOut()->begin(), (*it3)->getIn()->begin(), (*it3)->getIn()->end());
				}
				(*it)->getOut()->sort();
				(*it)->getOut()->unique();
			}
			(*it)->setIn((*it)->getUse());
			for (auto it2 = (*it)->getOut()->begin(); it2 != (*it)->getOut()->end(); ++it2)
			{
				if (!variableExists(*it2, (*it)->getDef()))
				{
					(*it)->getIn()->insert((*it)->getIn()->end(), *it2);
				}
			}
			(*it)->getIn()->sort();
			(*it)->getIn()->unique();
			if (in != *(*it)->getIn() || out != *(*it)->getOut())
			{
				same = true;
			}
		}
	} while (same);
}

bool variableExists(Variable* var, Variables* vars)
{
	for (auto it = vars->begin(); it != vars->end(); ++it)
	{
		if (*it == var)
			return true;
	}
	return false;
}