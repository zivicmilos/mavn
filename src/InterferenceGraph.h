#pragma once
#include "IR.h"

InterferenceGraph* doInterferenceGraph(Instructions* instructions, Variables* variables);


void freeInterferenceGraph(InterferenceGraph* ig);


void printInterferenceGraph(InterferenceGraph* ig);