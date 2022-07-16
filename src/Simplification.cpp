#include "Simplification.h"

using namespace std;

std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int degree)
{
	stack<Variable*>* simpStack = new stack<Variable*>();
	int deg = degree - 1;
	while (deg != 0)
	{
		bool changed = false;

		for (auto it1 = ig->variables->begin(); it1 != ig->variables->end(); ++it1)
		{
			int count = 0;
			for (auto it2 = ig->variables->begin(); it2 != ig->variables->end(); ++it2)
			{
				if (ig->values[(*it1)->getPosition()][(*it2)->getPosition()] == '1')
				{
					++count;
				}
			}
			if (count == deg)
			{
				simpStack->push(*it1);
				(*it1)->setStack(true);
				
				for (auto it2 = ig->variables->begin(); it2 != ig->variables->end(); ++it2)
				{
					if (ig->values[(*it1)->getPosition()][(*it2)->getPosition()] == '1')
					{
						ig->values[(*it1)->getPosition()][(*it2)->getPosition()] = '0';
						ig->values[(*it2)->getPosition()][(*it1)->getPosition()] = '0';
					}
				}
				changed = true;
			}
		}
		if (!changed)
			--deg;
		else
			deg = degree - 1;
	}

	for (auto it1 = ig->variables->begin(); it1 != ig->variables->end(); ++it1)
	{
		for (auto it2 = ig->variables->begin(); it2 != ig->variables->end(); ++it2)
		{
			if (ig->values[(*it1)->getPosition()][(*it2)->getPosition()] == '1')
			{
				return NULL;
			}
		}
	}

	for (auto it1 = ig->variables->begin(); it1 != ig->variables->end(); ++it1)
	{
		if (!(*it1)->getStack())
			simpStack->push(*it1);
	}
	
	return simpStack;
}