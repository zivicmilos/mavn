#include "InterferenceGraph.h"

#include "LivenessAnalysis.h"

using namespace std;

InterferenceGraph* doInterferenceGraph(Instructions* instructions, Variables* variables)
{
	InterferenceGraph* ig = new InterferenceGraph();
	ig->variables = variables;
	ig->size = variables->size();
	ig->values = new char*[ig->size];
	for (int i = 0; i < ig->size; ++i)
		ig->values[i] = new char[ig->size];
	for (int i = 0; i < ig->size; ++i)
	{
		for (int j = 0; j < ig->size; ++j)
		{
			ig->values[i][j] = '0';
		}
	}
	
	for (auto it1 = instructions->begin(); it1 != instructions->end(); ++it1)
	{
		for (auto it2 = ig->variables->begin(); it2 != ig->variables->end(); ++it2)
		{
			for (auto it3 = ig->variables->begin(); it3 != ig->variables->end(); ++it3)
			{
				if (*it2 != *it3)
				{
					if (variableExists((*it2), (*it1)->getDef()) && variableExists((*it3), (*it1)->getOut()))
					{
						ig->values[(*it2)->getPosition()][(*it3)->getPosition()] = '1';
						ig->values[(*it3)->getPosition()][(*it2)->getPosition()] = '1';
					}
				}
			}
		}
	}
	return ig;
}


void freeInterferenceGraph(InterferenceGraph* ig)
{
	for (int i = 0; i < ig->size; ++i)
		delete[] ig->values[i];
	delete[] ig->values;
}


void printInterferenceGraph(InterferenceGraph* ig)
{
	cout << "-----------------------------------------------\n";
	cout << "Interference Graph\n";
	for (int i = 0; i < ig->size; ++i)
	{
		for (int j = 0; j < ig->size; ++j)
		{
			cout << ig->values[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------------------\n";
}