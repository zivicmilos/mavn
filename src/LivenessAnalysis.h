#pragma once
#include "IR.h"

void doLivenessAnalysis(Instructions* instructions);

bool variableExists(Variable* var, Variables* vars);