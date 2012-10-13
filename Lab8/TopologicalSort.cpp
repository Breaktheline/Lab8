#include "TopologicalSort.h"

int* TopologicalSort::Sort(int count, TList<Condition>* conditions)
{
	int* precursors = new int[count];
	for(int i = 0; i < count; i++)
	{
		precursors[i] = 0;
	}

	TList<int>** links = new TList<int>*[count];
	for (int i = 0; i < count; i++)
	{
		links[i] = new TList<int>();
	}

	int conditionsCount = conditions->GetCount();
	for (int i = 0; i < conditionsCount; i++)
	{
		Condition condition = conditions->GetElement(i);
		links[condition.first]->Add(condition.second);
		precursors[condition.second]++;
	}

	TStack<int>* candidates = new TStack<int>();
	for (int i = 0; i < count; i++)
	{
		if (precursors[i] == 0)
		{
			candidates->Push(i);
		}
	}

	int* ordered = new int[count];
	int currentOrder = 0;
	while (candidates->GetCount() != 0)
	{
		int toAdd = candidates->Pop();
		ordered[currentOrder] = toAdd;
		currentOrder++;

		TList<int>* successors = links[toAdd];
		int successorsCount = successors->GetCount();
		for (int i = 0; i < successorsCount; i++)
		{
			int successor = successors->GetElement(i);
			precursors[successor]--;
			if (precursors[successor] == 0)
			{
				candidates->Push(successor);
			}
		}
	}

	if (currentOrder != count)
	{
		return NULL;
	}

	return ordered;
}
