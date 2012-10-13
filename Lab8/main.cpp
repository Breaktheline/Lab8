
#include "gtest/gtest.h"

#include "TopologicalSort.h";
#include "Parser.h";

void Execute(FILE* inputFile = stdin)
{
	Parser parser;
	TopologicalSort topologicalSort;
	try
	{
		Problem* problem = parser.ReadFromFile(inputFile);
		int* result = topologicalSort.Sort(problem->count, problem->conditions);
		parser.PrintResult(result, problem->count);
		delete problem;
		delete result;
	}
	catch (AppException e)
	{
		parser.PrintError(e.GetMessage());
	}
	catch (std::bad_alloc& e)
	{
		parser.PrintError(ErrorMessages::MEMORY_ERROR);
	}
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();

	//Execute();
}

