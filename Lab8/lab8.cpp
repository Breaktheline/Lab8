#include <stdlib.h>
#include <stdio.h>

struct ErrorMessages
{
	static const char* MEMORY_ERROR;
	static const char* FILE_OPEN_ERROR;
	static const char* WRONG_INPUT_ERROR;
};

const char* ErrorMessages::MEMORY_ERROR = "Can't allocate memory";
const char* ErrorMessages::FILE_OPEN_ERROR = "Can't open file";
const char* ErrorMessages::WRONG_INPUT_ERROR = "Wrong input format.";

class AppException 
{
public:
	AppException(const char* message)
	{
		_message = message;
	}

	const char* GetMessage() 
	{ 
		return _message;
	};
private:
	const char* _message;
};

template <class T> class TList
{
public:
	TList()
	{
		_count = 0;
		_capacity = 0;
		_elements = NULL;
	};

	TList(T* elements, int length)
	{
		_count = length;
		_capacity = length;
		_elements = elements;
	};

	~TList()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
	};

	void Clear()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
		_count = 0;
		_capacity = 0;
	};

	void Add(T element)
	{
		if (_elements == NULL)
		{
			_elements = (T*) malloc(sizeof(T));
			_capacity = 1;
		}
		else if (_count == _capacity)
		{
			_capacity *= 2;
			_elements = (T*) realloc(_elements, _capacity * sizeof(T));
		}

		if (_elements == NULL)
		{
			throw AppException(ErrorMessages::MEMORY_ERROR);
		}

		_elements[_count] = element;
		_count++;
	};

	void TrimExcess()
	{
		if (_count != _capacity)
		{
			_elements = (T*) realloc(_elements, _count * sizeof(T));
			if (_elements == NULL)
			{
				throw AppException(ErrorMessages::MEMORY_ERROR);
			}
			_capacity = _count;
		}
	};

	int GetCount()
	{
		return _count;
	};

	T operator[] (int i)
	{
		return _elements[i];
	};

	T GetElement(int i)
	{
		return _elements[i];
	};

	void Remove(T element)
	{
		for (int i = 0; i < _count; i++)
		{
			if (element == _elements[i])
			{
				for(int j = i; j < _count - 1; j++)
				{
					_elements[j] = _elements[j + 1];
				}
				_count--;

				return;
			}
		}
	}

	T* GetElements() 
	{
		return _elements;
	}

	void AddRange(TList<T>* elements) 
	{
		int elementsCount = elements->GetCount();
		if (_capacity == 0)
		{
			_elements = (T*) malloc(elementsCount*sizeof(T));
			_capacity = elementsCount;
		}
		else if(elementsCount > _capacity - _count)
		{
			_elements = (T*) realloc(_elements, (_count + elementsCount)*sizeof(T));
			if (_elements == NULL)
			{
				throw AppException(ErrorMessages::MEMORY_ERROR);
			}
			_capacity = _count + elementsCount;
		}

		for(int i = 0; i < elementsCount; i++)
		{
			_elements[_count] = elements->GetElement(i);
			_count++;
		}

	}

private:
	T* _elements;
	int _count;
	int _capacity;
};

template <class T> class TStack
{
public:
	TStack()
	{
		_count = 0;
		_capacity = 0;
		_elements = NULL;
	};

	TStack(T* elements, int length)
	{
		_count = length;
		_capacity = length;
		_elements = elements;
	};

	~TStack()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
	};

	void Clear()
	{
		if (_elements != NULL)
		{
			free(_elements);
		}
		_count = 0;
		_capacity = 0;
	};

	void Push(T element)
	{
		if (_elements == NULL)
		{
			_elements = (T*) malloc(sizeof(T));
			_capacity = 1;
		}
		else if (_count == _capacity)
		{
			_capacity *= 2;
			_elements = (T*) realloc(_elements, _capacity * sizeof(T));
		}

		if (_elements == NULL)
		{
			throw AppException(ErrorMessages::MEMORY_ERROR);
		}

		_elements[_count] = element;
		_count++;
	};

	void TrimExcess()
	{
		if (_count != _capacity)
		{
			_elements = (T*) realloc(_elements, _count * sizeof(T));
			if (_elements == NULL)
			{
				throw AppException(ErrorMessages::MEMORY_ERROR);
			}
			_capacity = _count;
		}
	};

	int GetCount()
	{
		return _count;
	};

	T Pop()
	{
		if (_count == 0)
		{
			return -1;
		}

		T last = _elements[_count-1];
		_count--;
		return last;
	}

private:
	T* _elements;
	int _count;
	int _capacity;
};

struct Condition
{
	Condition()
	{
		first = 0;
		second = 0;
	}

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

int* TopologicalSort::Sort(int count, TList<Condition>* conditions)
{
	_count = count;
	//Prepare data
	CreatePrecursors();
	CreateLinks();
	FillLinksAndPrecursors(conditions);
	AddFirstCandidates();

	//Sort
	int* ordered = SortByOrder();

	//Delete extra data
	DeleteArrays();

	return ordered;
}

//Array has count of precursors for element i.
void TopologicalSort::CreatePrecursors()
{
	_precursors = new int[_count];
	for(int i = 0; i < _count; i++)
	{
		_precursors[i] = 0;
	}
}

//Array of lists. For each i has list of successors.
void TopologicalSort::CreateLinks()
{
	_links = new TList<int>*[_count];
	for (int i = 0; i < _count; i++)
	{
		_links[i] = new TList<int>();
	}
}

//Fill links and precursors using conditions.
void TopologicalSort::FillLinksAndPrecursors( TList<Condition>* conditions )
{
	int conditionsCount = conditions->GetCount();
	for (int i = 0; i < conditionsCount; i++)
	{
		Condition condition = conditions->GetElement(i);
		_links[condition.first]->Add(condition.second);
		_precursors[condition.second]++;
	}
}

//Add first candidates, which has no precursors.
void TopologicalSort::AddFirstCandidates()
{
	_candidates = new TStack<int>();
	for (int i = 0; i < _count; i++)
	{
		if (_precursors[i] == 0)
		{
			_candidates->Push(i);
		}
	}
}

int* TopologicalSort::SortByOrder()
{
	int* ordered = new int[_count];
	int currentOrder = 0;
	//While	has candidates to add
	while (_candidates->GetCount() != 0)
	{
		//Add candidate to ordered
		int toAdd = _candidates->Pop();
		ordered[currentOrder] = toAdd;
		currentOrder++;

		//For each successor of added candidate decrement precursor count and add them to candidates if they have no precursors
		TList<int>* successors = _links[toAdd];
		int successorsCount = successors->GetCount();
		for (int i = 0; i < successorsCount; i++)
		{
			int successor = successors->GetElement(i);
			_precursors[successor]--;
			if (_precursors[successor] == 0)
			{
				_candidates->Push(successor);
			}
		}
	}

	//If can't order return NULL
	if (currentOrder != _count)
	{
		delete ordered;
		return NULL;
	}

	return ordered;
}

void TopologicalSort::DeleteArrays()
{
	delete _precursors;
	delete _candidates;
	for (int i = 0; i < _count; i++)
	{
		delete _links[i];
	}
	delete _links;
}

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
		if (result != NULL)
		{
			delete result;
		}
	}
	catch (AppException e)
	{
		parser.PrintError(e.GetMessage());
	}
	//catch (std::bad_alloc&)
	//{
	//	parser.PrintError(ErrorMessages::MEMORY_ERROR);
	//}
}

int main(int argc, char** argv)
{
	Execute();
}
