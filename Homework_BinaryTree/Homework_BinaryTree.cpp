
#include <iostream>

enum incedent
{
	inc_speedLimit,
	inc_singleCarCrash,
	inc_multiCarCrash,
	inc_drunk
};

class Tree
{
private:
	int carN;
	int size;
	incedent* list = nullptr;
	Tree* less = nullptr;
	Tree* more = nullptr;
public:
	Tree()
	{
		carN = 0;
		size = 0;
		list = nullptr;
		less = nullptr;
		more = nullptr;
	}
	Tree(int _carNumber)
	{
		carN = _carNumber;
		size = 0;
		list = nullptr;
		less = nullptr;
		more = nullptr;
	}
	Tree(int _carNumber, incedent m_incedent)
	{
		carN = _carNumber;
		size = 1;
		list = new incedent[size];
		list[0] = m_incedent;
		less = nullptr;
		more = nullptr;
	}
	Tree(int _carNumber, incedent* _list, int _size)
	{
		carN = _carNumber;
		size = _size;
		list = new incedent[size];
		for (int i = 0; i < size; i++)
		{
			list[i] = _list[i];
		}
	}

	void add(incedent _one, int _carN = -1)
	{
		if (_carN == -1)
		{
			_carN = this->carN;
		}
		if (_carN == this->carN)
		{
			if (list == nullptr)
			{
				this->size += 1;
				this->list = new incedent[size];
				this->list[0] = _one;
			}
			else
			{
				incedent* temp = new incedent[size + 1];
				temp[size] = _one;
				for (int i = 0; i < size; i++)
				{
					temp[i] = list[i];
				}
				delete[] list;
				size++;
				list = temp;
				temp = nullptr;
			}
		}
		else if (_carN > this->carN)
		{
			if (more != nullptr)
			{
				(*more).add(_one, _carN);
			}
			else
			{
				more = new Tree(_carN);
				(*more).add(_one);
			}
		}
		else if (_carN < this->carN)
		{
			if (less != nullptr)
			{
				(*less).add(_one, _carN);
			}
			else
			{
				less = new Tree(_carN);
				(*less).add(_one);
			}
		}
	}
	void print()
	{
		for (int i = 0; i < 20; i++)
		{
			std::cout << '-';
		}
		std::cout << '\n';
		std::cout << "CarNumber: " << carN << '\n' << "Incedent list: " << '\n';
		for (int i = 0; i < size; i++)
		{
			std::cout << list[i] << '\n';
		}
	}
	void printAll()
	{
		this->print();
		if (more != nullptr)
		{
			(*more).printAll();
		}
		if (less != nullptr)
		{
			(*less).printAll();
		}
	}
	void printByNumber(int _carNumber)
	{
		if (_carNumber == this->carN)
		{
			this->print();
		}
		else if (_carNumber > this ->carN && more != nullptr)
		{
			(*more).printByNumber(_carNumber);
		}
		else if (_carNumber < this->carN && less != nullptr)
		{
			(*less).printByNumber(_carNumber);
		}
		else
		{
			std::cout << "No this number;\n";
		}
	}
	void printInDiapazon(int _minNumber, int _maxNumber)
	{
		if (_minNumber < this->carN && _maxNumber > this->carN)
		{
			this->print();
		}
		if (more != nullptr && _minNumber < (*more).carN && _maxNumber >(*more).carN)
		{
			(*more).printInDiapazon(_minNumber, _maxNumber);
		}
		if (less != nullptr && _minNumber < (*less).carN && _maxNumber >(*less).carN)
		{
			(*less).printInDiapazon(_minNumber, _maxNumber);
		}
	}


	virtual ~Tree()
	{
		if (more != nullptr)
		{
			(*this->more).~Tree();
			delete[] this->more;
			this->more = nullptr;
		}
		if (less != nullptr)
		{
			(*this->less).~Tree();
			delete[] less;
			less = nullptr;
		}
		if (this->list != nullptr)
		{
			delete[] this->list;
			this->list = nullptr;
		}
	}
};


int main()
{
	std::cout << "test_1:\n";
	Tree test(5, inc_speedLimit);
	test.add(inc_drunk);
	test.add(inc_drunk, 2);
	test.add(inc_singleCarCrash, 6);
	test.add(inc_singleCarCrash, 4);
	test.add(inc_multiCarCrash, 8);
	test.add(inc_multiCarCrash, 7);
	test.printAll();
	std::cout << "test_2:\n";
	test.printByNumber(4);
	std::cout << "test_3:\n";
	test.printInDiapazon(2, 8);
}