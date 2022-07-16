#pragma once
#include "IR.h"

bool doResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig);