#ifndef H_TOPOLOGICAL_SORT
#define H_TOPOLOGICAL_SORT

#include "TList.h"
#include "TStack.h"

struct Condition
{
	Condition(int aFirst, int aSecond)
	{
		first = aFirst;
		second = aSecond;
	}

	int first;
	int second;
};

class TopologicalSort
{
public:
	int* Sort(int count, TList<Condition>* conditions);
};

#endif