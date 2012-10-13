#ifndef H_TSTACK
#define H_TSTACK

#include "Common.h"

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

#endif
