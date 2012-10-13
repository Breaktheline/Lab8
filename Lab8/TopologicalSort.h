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
private:
	void CreatePrecursors();
	void CreateLinks();
	void FillLinksAndPrecursors(TList<Condition>* conditions);
	void AddFirstCandidates();
	int* SortByOrder();
	void DeleteArrays();

	int _count;
	TList<int>** _links;
	int* _precursors;
	TStack<int>* _candidates;
};

#endif