#include "Make.h"

using namespace std;

map<string, int> g_labels;

Variables* makeMemVariables(TokenList& tokenList)
{
	Variables* vars = new Variables();
	int pos = 0;
	for (auto it = tokenList.begin(); it != tokenList.end(); ++it)
	{
		if (it->getType() == T_MEM)
		{
			string name = (++it)->getValue();
			string value = (++it)->getValue();
			if (variableExists(name, vars))
			{
				throw runtime_error("Semantic error! Variable with name " + name + " already exists.\n");
			}
			Variable* var = new Variable(Variable::MEM_VAR, name, value, pos++);
			vars->push_back(var);
		}
	}
	return vars;
}

Variables* makeRegVariables(TokenList& tokenList)
{
	Variables* vars = new Variables();
	int pos = 0;
	for (auto it = tokenList.begin(); it != tokenList.end(); ++it)
	{
		if (it->getType() == T_REG) {
			string name = (++it)->getValue();
			if (variableExists(name, vars))
			{
				throw runtime_error("Semantic error! Variable with name " + name + " already exists.\n");
			}
			Variable* var = new Variable(Variable::REG_VAR, name, pos++);
			vars->push_back(var);
		}
	}
	return vars;
}

bool variableExists(string s, Variables* vars)
{
	for (auto it = vars->begin(); it != vars->end(); ++it)
	{
		if (s == (*it)->getName())
		{
			return true;
		}
	}
	return false;
}

bool labelExists(string s)
{
	for (auto it = g_labels.begin(); it != g_labels.end(); ++it)
	{
		if (s == (*it).first)
		{
			return true;
		}
	}
	return false;
}

Instructions* makeInstructions(TokenList& tokenList, Variables* rVars)
{
	Instructions* instrs = new Instructions();
	int pos = 0;
	bool fmain = false;
	string s1;
	string s2;
	string s3;
	Variable* var1;
	Variable* var2;
	Variable* var3;
	Variables* dVars;
	Variables* sVars;
	Instruction* instr;

	for (auto it = tokenList.begin(); it != tokenList.end(); ++it)
	{
		if (it->getValue() == "main")
			fmain = true;
		if (fmain)
		{
			switch (it->getType())
			{
			case T_ADD:
				s1 = (++it)->getValue();
				s2 = (++++it)->getValue();
				s3 = (++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
					if ((*vit)->getName() == s2)
						var2 = *vit;
					if ((*vit)->getName() == s3)
						var3 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				sVars->push_back(var2);
				sVars->push_back(var3);
				instr = new Instruction(pos++, I_ADD, *dVars, *sVars);
				instr->setDef(dVars);
				instr->setUse(sVars);
				instrs->push_back(instr);
				break;
			case T_ADDI:
				s1 = (++it)->getValue();
				s2 = (++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
					if ((*vit)->getName() == s2)
						var2 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				sVars->push_back(var2);
				instr = new Instruction(pos++, I_ADDI, *dVars, *sVars);
				instr->setDef(dVars);
				instr->setUse(sVars);
				instrs->push_back(instr);
				break;
			case T_SUB:
				s1 = (++it)->getValue();
				s2 = (++++it)->getValue();
				s3 = (++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
					if ((*vit)->getName() == s2)
						var2 = *vit;
					if ((*vit)->getName() == s3)
						var3 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				sVars->push_back(var2);
				sVars->push_back(var3);
				instr = new Instruction(pos++, I_SUB, *dVars, *sVars);
				instr->setDef(dVars);
				instr->setUse(sVars);
				instrs->push_back(instr);
				break;
			case T_LA:
				s1 = (++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				instr = new Instruction(pos++, I_LA, *dVars, *sVars);
				instr->setDef(dVars);
				instrs->push_back(instr);
				break;
			case T_LW:
				s1 = (++it)->getValue();
				s2 = (++++++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
					if ((*vit)->getName() == s2)
						var2 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				sVars->push_back(var2);
				instr = new Instruction(pos++, I_LW, *dVars, *sVars);
				instr->setDef(dVars);
				instr->setUse(sVars);
				instrs->push_back(instr);
				break;
			case T_LI:
				s1 = (++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				instr = new Instruction(pos++, I_LI, *dVars, *sVars);
				instr->setDef(dVars);
				instrs->push_back(instr);
				break;
			case T_SW:
				s1 = (++it)->getValue();
				s2 = (++++++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
					if ((*vit)->getName() == s2)
						var2 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				sVars->push_back(var1);
				sVars->push_back(var2);
				instr = new Instruction(pos++, I_SW, *dVars, *sVars);
				instr->setUse(sVars);
				instrs->push_back(instr);
				break;
			case T_B:
				s1 = (++it)->getValue();
				dVars = new Variables();
				sVars = new Variables();
				instr = new Instruction(pos++, I_B, *dVars, *sVars);
				instr->setLabel(s1);
				instrs->push_back(instr);
				break;
			case T_BLTZ:
				s1 = (++it)->getValue();
				s2 = (++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				sVars->push_back(var1);
				instr = new Instruction(pos++, I_BLTZ, *dVars, *sVars);
				instr->setUse(sVars);
				instr->setLabel(s2);
				instrs->push_back(instr);
				break;
			case T_NOP:
				dVars = new Variables();
				sVars = new Variables();
				instr = new Instruction(pos++, I_NOP, *dVars, *sVars);
				instrs->push_back(instr);
				break;
			case T_ID:
				s1 = it->getValue();
				if (labelExists(s1))
				{
					throw runtime_error("Semantic error! Label with name " + s1 + " already exists.\n");
				}
				g_labels.insert(pair<string, int>(s1, pos));
				break;
			case T_AND:
				s1 = (++it)->getValue();
				s2 = (++++it)->getValue();
				s3 = (++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
					if ((*vit)->getName() == s2)
						var2 = *vit;
					if ((*vit)->getName() == s3)
						var3 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				sVars->push_back(var2);
				sVars->push_back(var3);
				instr = new Instruction(pos++, I_AND, *dVars, *sVars);
				instr->setDef(dVars);
				instr->setUse(sVars);
				instrs->push_back(instr);
				break;
			case T_SRL:
				s1 = (++it)->getValue();
				s2 = (++++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
					if ((*vit)->getName() == s2)
						var2 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				sVars->push_back(var2);
				instr = new Instruction(pos++, I_SRL, *dVars, *sVars);
				instr->setDef(dVars);
				instr->setUse(sVars);
				instrs->push_back(instr);
				break;
			case T_LUI:
				s1 = (++it)->getValue();
				for (auto vit = rVars->begin(); vit != rVars->end(); ++vit)
				{
					if ((*vit)->getName() == s1)
						var1 = *vit;
				}
				dVars = new Variables();
				sVars = new Variables();
				dVars->push_back(var1);
				instr = new Instruction(pos++, I_LUI, *dVars, *sVars);
				instr->setDef(dVars);
				instrs->push_back(instr);
				break;
			}
		}
	}
	findPS(instrs);
	return instrs;
}

void findPS(Instructions* instrs)
{
	Instruction* ins1;
	Instruction* ins2;
	auto it2 = ++instrs->begin();
	for (auto it1 = instrs->begin(); it1 != --instrs->end(); ++it1, ++it2)
	{
		ins1 = *it1;
		ins2 = *it2;
		Instructions* temp1 = (ins1->getSucc());
		temp1->push_back(ins2);
		ins1->setSucc(temp1);
		Instructions* temp2 = (ins2->getPred());
		temp2->push_back(ins1);
		ins2->setPred(temp2);
	}

	for (auto it = instrs->begin(); it != instrs->end(); ++it)
	{
		ins1 = *it;
		if (ins1->getType() == I_B || ins1->getType() == I_BLTZ)
		{
			Instructions* temp = (ins1->getSucc());
			int pos = g_labels[ins1->getLabel()];
			for (it2 = instrs->begin(); it2 != instrs->end(); ++it2)
			{
				ins2 = *it2;
				if (ins2->getPos() == pos)
				{
					temp->push_back(ins2);
					Instructions* temp2 = (ins2->getPred());
					temp2->push_back(ins1);
					ins2->setPred(temp2);
					break;
				}
			}
			
			ins1->setSucc(temp);
		}
	}
}