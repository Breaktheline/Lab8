#include "Parser.h"

void Parser::PrintError(const char* message) 
{
	printf("%s\n", message);
}

Problem* Parser::ReadFromFile(FILE* inputFile)
{
	if (inputFile == NULL)
	{
		throw AppException(ErrorMessages::FILE_OPEN_ERROR);
	}

	Problem* problem = new Problem();
	int conditionsCount;
	fscanf(inputFile, "%d", &problem->count);
	fscanf(inputFile, "%d", &conditionsCount);

	for(int i = 0; i < conditionsCount; i++)
	{
		Condition condition;
		fscanf(inputFile, "%d", &condition.first);
		fscanf(inputFile, "%d", &condition.second);
		problem->conditions->Add(condition);
	}

	fclose(inputFile);

	return problem;
}

void Parser::PrintResult(int* result, int count)
{
	if (result == NULL)
	{
		printf("%d\n", -1);
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			printf("%d ", result[i]);
		}
		printf("\n");
	}
}
