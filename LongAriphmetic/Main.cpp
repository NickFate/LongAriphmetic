
#include <iostream>
#include <string>

using namespace std;

const int chunkSize = 10;


class BigInt
{
private:
	// знак числа
	bool isNegative;
	
	int chunks[chunkSize];

	int smooth = 2;

public:
    // конструктор принимающий строку
	BigInt(string number)
	{
		
		// проверяем знак
		isNegative = false;
		if (number[0] == '-')
		{
			isNegative = true;
			// удаляем 1й символ
			number.erase(0, 1);
		}

		// заполняем массив чисел
		for (int i = 0; i < chunkSize; i++)
		{
			try
			{
				chunks[i] = stoi(number.substr((i)*smooth, smooth));
				cout << stoi(number.substr((i)*smooth, smooth)) << endl;
			}
			catch (const std::exception&)
			{
				chunks[i] = NULL;
			}
			//cout << chunks[chunkSizes - i - 1] << endl;;
		}
		

		/*for (int i = 0; i < 3; i++)
		{
			cout << chunks[i] << endl;
		}*/

		cout << "Задано число: ";
		this->Format();
	}

	void Format()
	{
		if (isNegative)
		{
			cout << '-';
		}

		for (int i = chunkSize - 1; i >= 0; i--)
		{
			if (chunks[i] == NULL)
			{
				continue;
			}

			cout << chunks[i];
		}
		
		cout << endl;
	}

	BigInt operator += (BigInt right)
	{
		
		return *this;
	}

};

void main()
{
	setlocale(LC_ALL, "RUS");

	BigInt n("123456789");
	BigInt n1("111");

	n.Format();

	n += n1;
	n.Format();

}