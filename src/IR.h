/* Autor: Miloš Živić Datum: 10.06.2020. */

#ifndef __IR__
#define __IR__

#include <iostream>
#include "Types.h"


/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign), m_stack(false) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign), m_stack(false) {}
	Variable(VariableType type, std::string name, int pos) : m_type(type), m_name(name), m_position(pos), m_assignment(no_assign), m_stack(false) {}
	Variable(VariableType type, std::string name, std::string value, int pos) : m_type(type), m_name(name), m_value(value), m_position(pos), m_assignment(no_assign), m_stack(false) {}
	void printVariable()
	{
		std::cout << "(Name: " << m_name << ", Pos: " << m_position << ", Assignment: " << m_assignment << ")" << std::endl;
	}
	std::string getName()
	{
		return m_name;
	}

	int getPosition()
	{
		return m_position;
	}

	Regs getAssignment()
	{
		return m_assignment;
	}

	void setAssignment(Regs r)
	{
		m_assignment = r;
	}

	std::string getValue()
	{
		return m_value;
	}

	void setStack(bool s)
	{
		m_stack = s;
	}

	bool getStack()
	{
		return m_stack;
	}
private:
	VariableType m_type;
	std::string m_name;
	int m_position;
	Regs m_assignment;
	std::string m_value;
	bool m_stack;
};


/**
 * This type represents list of variables from program code.
 */
typedef std::list<Variable*> Variables;


/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}
	void printInstruction()
	{
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "Position: " << m_position << std::endl;
		std::cout << "Type: " << m_type << std::endl;
		std::cout << "DEF: " << std::endl;
		for (auto it = m_def.begin(); it != m_def.end(); ++it)
		{
			std::cout << (*it)->getName() << std::endl;
		}
		std::cout << "USE: " << std::endl;
		for (auto it = m_use.begin(); it != m_use.end(); ++it)
		{
			std::cout << (*it)->getName() << std::endl;
		}
		std::cout << "PRED: " << std::endl;
		for (auto it = m_pred.begin(); it != m_pred.end(); ++it)
		{
			std::cout << (*it)->getPos() << std::endl;
		}
		std::cout << "SUCC: " << std::endl;
		for (auto it = m_succ.begin(); it != m_succ.end(); ++it)
		{
			std::cout << (*it)->getPos() << std::endl;
		}
		std::cout << "IN: " << std::endl;
		for (auto it = m_in.begin(); it != m_in.end(); ++it)
		{
			std::cout << (*it)->getName() << std::endl;
		}
		std::cout << "OUT: " << std::endl;
		for (auto it = m_out.begin(); it != m_out.end(); ++it)
		{
			std::cout << (*it)->getName() << std::endl;
		}
		std::cout << "-----------------------------------------------" << std::endl;
	}
	void setUse(Variables* vars)
	{
		m_use = *vars;
	}

	void setDef(Variables* vars)
	{
		m_def = *vars;
	}

	void setIn(Variables* vars)
	{
		m_in = *vars;
	}

	void setOut(Variables* vars)
	{
		m_out = *vars;
	}

	Variables* getIn()
	{
		return &m_in;
	}

	Variables* getOut()
	{
		return &m_out;
	}

	void setSucc(std::list<Instruction*>* ins)
	{
		m_succ = *ins;
	}

	void setPred(std::list<Instruction*>* ins)
	{
		m_pred = *ins;
	}

	std::list<Instruction*>* getSucc()
	{
		return &m_succ;
	}

	std::list<Instruction*>* getPred()
	{
		return &m_pred;
	}

	int getPos()
	{
		return m_position;
	}

	InstructionType getType()
	{
		return m_type;
	}

	std::string getLabel()
	{
		return label;
	}

	void setLabel(std::string s)
	{
		label = s;
	}

	Variables* getUse()
	{
		return &m_use;
	}

	Variables* getDef()
	{
		return &m_def;
	}

private:
	int m_position;
	InstructionType m_type;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;
	std::string label;
};


/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;

typedef struct
{
	Variables* variables;
	char** values;
	int size;
} InterferenceGraph;

#endif
