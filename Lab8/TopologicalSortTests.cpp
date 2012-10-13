#include "gtest/gtest.h"
#include "TopologicalSort.h"

TEST(TopologicalSortTest, ShouldOrderIfNoConditions)
{
	TopologicalSort sorter;
	int* ordered = sorter.Sort(3, new TList<Condition>());

	ASSERT_EQ(2, ordered[0]);
	ASSERT_EQ(1, ordered[1]);
	ASSERT_EQ(0, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfOneElement)
{
	TopologicalSort sorter;
	int* ordered = sorter.Sort(1, new TList<Condition>());

	ASSERT_EQ(0, ordered[0]);
}

TEST(TopologicalSortTest, ShouldOrderIfConditionsChangeOrder)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(0, 1));
	conditions->Add(Condition(1, 2));
	int* ordered = sorter.Sort(3, conditions);

	ASSERT_EQ(0, ordered[0]);
	ASSERT_EQ(1, ordered[1]);
	ASSERT_EQ(2, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfConditionsAreLess)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(0, 1));
	int* ordered = sorter.Sort(3, conditions);

	ASSERT_EQ(2, ordered[0]);
	ASSERT_EQ(0, ordered[1]);
	ASSERT_EQ(1, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfConditionsCountAreEquals)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(0, 1));
	conditions->Add(Condition(0, 2));
	conditions->Add(Condition(1, 2));
	int* ordered = sorter.Sort(3, conditions);

	ASSERT_EQ(0, ordered[0]);
	ASSERT_EQ(1, ordered[1]);
	ASSERT_EQ(2, ordered[2]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsForFirstElement)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(5, 4));
	conditions->Add(Condition(1, 5));
	conditions->Add(Condition(5, 0));
	conditions->Add(Condition(5, 2));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(3, ordered[0]);
	ASSERT_EQ(1, ordered[1]);
	ASSERT_EQ(5, ordered[2]);
	ASSERT_EQ(2, ordered[3]);
	ASSERT_EQ(0, ordered[4]);
	ASSERT_EQ(4, ordered[5]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsForSecondElement)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(3, 2));
	conditions->Add(Condition(5, 2));
	conditions->Add(Condition(0, 2));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(5, ordered[0]);
	ASSERT_EQ(4, ordered[1]);
	ASSERT_EQ(3, ordered[2]);
	ASSERT_EQ(1, ordered[3]);
	ASSERT_EQ(0, ordered[4]);
	ASSERT_EQ(2, ordered[5]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsAndOneOrder)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(3, 1));
	conditions->Add(Condition(4, 2));
	conditions->Add(Condition(2, 1));
	conditions->Add(Condition(0, 5));
	conditions->Add(Condition(0, 4));
	conditions->Add(Condition(3, 4));
	conditions->Add(Condition(3, 0));
	conditions->Add(Condition(4, 5));
	conditions->Add(Condition(2, 5));
	conditions->Add(Condition(5, 1));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(3, ordered[0]);
	ASSERT_EQ(0, ordered[1]);
	ASSERT_EQ(4, ordered[2]);
	ASSERT_EQ(2, ordered[3]);
	ASSERT_EQ(5, ordered[4]);
	ASSERT_EQ(1, ordered[5]);
}

TEST(TopologicalSortTest, ShouldOrderIfSeveralConditionsAndSeveralOrders)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(3, 1));
	conditions->Add(Condition(4, 2));
	conditions->Add(Condition(2, 1));
	conditions->Add(Condition(0, 5));
	conditions->Add(Condition(0, 4));
	conditions->Add(Condition(3, 4));
	conditions->Add(Condition(3, 0));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_EQ(3, ordered[0]);
	ASSERT_EQ(0, ordered[1]);
	ASSERT_EQ(4, ordered[2]);
	ASSERT_EQ(2, ordered[3]);
	ASSERT_EQ(1, ordered[4]);
	ASSERT_EQ(5, ordered[5]);
}

TEST(TopologicalSortTest, ShouldNotOrderIfNoAnswer)
{
	TopologicalSort sorter;
	TList<Condition>* conditions = new TList<Condition>();
	conditions->Add(Condition(3, 1));
	conditions->Add(Condition(4, 2));
	conditions->Add(Condition(2, 1));
	conditions->Add(Condition(0, 5));
	conditions->Add(Condition(0, 4));
	conditions->Add(Condition(4, 3));
	conditions->Add(Condition(3, 0));
	int* ordered = sorter.Sort(6, conditions);

	ASSERT_TRUE(ordered == NULL);
}