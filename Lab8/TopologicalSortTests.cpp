#include "gtest/gtest.h"
#include "TopologicalSort.h"
#include "Parser.h"

TEST(TopologicalSortTest, ShouldOrderIfNoConditions)
{
	TopologicalSort sorter;
	int* ordered = sorter.Sort(3, new TList<Condition>());

	ASSERT_EQ(3, ordered[0]);
	ASSERT_EQ(2, ordered[1]);
	ASSERT_EQ(1, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfOneElement)
{
	TopologicalSort sorter;
	int* ordered = sorter.Sort(1, new TList<Condition>());

	ASSERT_EQ(1, ordered[0]);
}

TEST(TopologicalSortTest, ShouldOrderIfConditionsChangeOrder)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(1, 2));
	conditions->Add(Condition(2, 3));
	int* ordered = sorter.Sort(3, conditions);

	ASSERT_EQ(1, ordered[0]);
	ASSERT_EQ(2, ordered[1]);
	ASSERT_EQ(3, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfConditionsAreLess)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(1, 2));
	int* ordered = sorter.Sort(3, conditions);

	ASSERT_EQ(3, ordered[0]);
	ASSERT_EQ(1, ordered[1]);
	ASSERT_EQ(2, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfConditionsCountAreEquals)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(1, 2));
	conditions->Add(Condition(1, 3));
	conditions->Add(Condition(2, 3));
	int* ordered = sorter.Sort(3, conditions);

	ASSERT_EQ(1, ordered[0]);
	ASSERT_EQ(2, ordered[1]);
	ASSERT_EQ(3, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsForFirstElement)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(6, 5));
	conditions->Add(Condition(2, 6));
	conditions->Add(Condition(6, 1));
	conditions->Add(Condition(6, 3));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(4, ordered[0]);
	ASSERT_EQ(2, ordered[1]);
	ASSERT_EQ(6, ordered[2]);
	ASSERT_EQ(3, ordered[3]);
	ASSERT_EQ(1, ordered[4]);
	ASSERT_EQ(5, ordered[5]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsForSecondElement)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(4, 3));
	conditions->Add(Condition(6, 3));
	conditions->Add(Condition(1, 3));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(6, ordered[0]);
	ASSERT_EQ(5, ordered[1]);
	ASSERT_EQ(4, ordered[2]);
	ASSERT_EQ(2, ordered[3]);
	ASSERT_EQ(1, ordered[4]);
	ASSERT_EQ(3, ordered[5]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsAndOneOrder)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(4, 2));
	conditions->Add(Condition(5, 3));
	conditions->Add(Condition(3, 2));
	conditions->Add(Condition(1, 6));
	conditions->Add(Condition(1, 5));
	conditions->Add(Condition(4, 5));
	conditions->Add(Condition(4, 1));
	conditions->Add(Condition(5, 6));
	conditions->Add(Condition(3, 6));
	conditions->Add(Condition(6, 2));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(4, ordered[0]);
	ASSERT_EQ(1, ordered[1]);
	ASSERT_EQ(5, ordered[2]);
	ASSERT_EQ(3, ordered[3]);
	ASSERT_EQ(6, ordered[4]);
	ASSERT_EQ(2, ordered[5]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsAndSeveralOrders)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(4, 2));
	conditions->Add(Condition(5, 3));
	conditions->Add(Condition(3, 2));
	conditions->Add(Condition(1, 6));
	conditions->Add(Condition(1, 5));
	conditions->Add(Condition(4, 5));
	conditions->Add(Condition(4, 1));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(4, ordered[0]);
	ASSERT_EQ(1, ordered[1]);
	ASSERT_EQ(5, ordered[2]);
	ASSERT_EQ(3, ordered[3]);
	ASSERT_EQ(2, ordered[4]);
	ASSERT_EQ(6, ordered[5]);
}

TEST(TopologicalSortTest, ShouldNotOrderIfNoAnswer)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(4, 2));
	conditions->Add(Condition(5, 3));
	conditions->Add(Condition(3, 2));
	conditions->Add(Condition(1, 6));
	conditions->Add(Condition(1, 5));
	conditions->Add(Condition(5, 4));
	conditions->Add(Condition(4, 1));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_TRUE(ordered == NULL);
}

TEST(ParserTest, ShouldReadInfoFromFile)
{
	FILE* input = fopen("Tests/in", "w");
	fprintf(input, "%d %d\n", 6, 5);

	fprintf(input, "%d %d\n", 4, 2);
	fprintf(input, "%d %d\n", 5, 3);
	fprintf(input, "%d %d\n", 3, 2);
	fprintf(input, "%d %d\n", 1, 6);
	fprintf(input, "%d %d\n", 1, 7);

	fclose(input);

	input = fopen("Tests/in", "r");
	Parser parser;
	Problem* problem = parser.ReadFromFile(input);

	ASSERT_EQ(6, problem->count);
	ASSERT_EQ(5, problem->conditions->GetCount());
	ASSERT_EQ(4, problem->conditions->GetElement(0).first);
	ASSERT_EQ(2, problem->conditions->GetElement(0).second);
	ASSERT_EQ(5, problem->conditions->GetElement(1).first);
	ASSERT_EQ(3, problem->conditions->GetElement(1).second);
	ASSERT_EQ(3, problem->conditions->GetElement(2).first);
	ASSERT_EQ(2, problem->conditions->GetElement(2).second);
	ASSERT_EQ(1, problem->conditions->GetElement(3).first);
	ASSERT_EQ(6, problem->conditions->GetElement(3).second);
	ASSERT_EQ(1, problem->conditions->GetElement(4).first);
	ASSERT_EQ(7, problem->conditions->GetElement(4).second);

	fclose(input);
}