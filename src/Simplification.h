#pragma once

#include <stack>

#include "IR.h"


std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int degree);