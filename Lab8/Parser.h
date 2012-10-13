#ifndef H_PARSER
#define H_PARSER

#include "TopologicalSort.h"
#include <stdio.h>

struct Problem
{
	Problem()
	{
		conditions = new TList<Condition>();
	}

	~Problem()
	{
		delete conditions;
	}

	int count;
	TList<Condition>* conditions;
};

class Parser
{
public:
	Problem* ReadFromFile(FILE* inputFile);
	void PrintResult(int* result, int count);
	void PrintError(const char* message);
};

#endif

