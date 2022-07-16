#include "ResourceAllocation.h"

using namespace std;

bool doResourceAllocation(stack<Variable*>* simplificationStack, InterferenceGraph* ig)
{
	bool first = true;
	int boja = 0;
	Variables lista;
	while (!simplificationStack->empty())
	{		
		Variable *var = simplificationStack->top();
		simplificationStack->pop();

		if (first) {
			var->setAssignment((Regs)boja++);
			first = false;

		}
		else {
			bool breaked = false;
			Variable* temp;
			for (auto it2 = lista.begin(); it2 != lista.end(); ++it2) {
				temp = *it2;
				int posIt = (*it2)->getPosition();
				int posVar = var->getPosition();

				if (ig->values[posVar][posIt] == '1') {
					if (boja == __REG_NUMBER__)
						return false;
					var->setAssignment((Regs)boja++);
					breaked = true;
					break;
				}
			}
			if (!breaked) {
				var->setAssignment(temp->getAssignment());
			}

		}
		lista.push_back(var);
	}
	return true;
}