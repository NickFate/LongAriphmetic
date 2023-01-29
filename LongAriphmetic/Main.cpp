
#include <iostream>
#include <string>
// работа с консолью
#include <Windows.h>


using namespace std;

const int chunkSize = 10;


class BigInt
{
private:
	// знак числа
	bool isNegative;
	
	int chunks[chunkSize];

	int smooth = 1;

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

		int delta = number.length() / smooth;

		if ((float)number.length() / smooth != delta)
		{
			delta++;
		}
		
		delta = chunkSize - delta;
		
		// заполняем массив чисел
		for (int i = delta; i < chunkSize; i++)
		{
			chunks[i - delta] = stoi(number.substr((chunkSize - i - 1) * smooth, smooth));
		}
		for (int i = chunkSize - delta; i < chunkSize; i++)
		{
			chunks[i] = NULL;
		}

	}

	void Print()
	{
		bool check = false;

		if (isNegative)
		{
			cout << '-';
		}

		for (int i = chunkSize - 1; i >= 0; i--)
		{
			if (chunks[i] != NULL)
			{
				check = true;
			}
			if (check)
			{
				cout << chunks[i];
			}
		}
		if (!check)
		{
			cout << 0;
		}
		
		cout << endl;
	}

	string ToString()
	{
		string str;
		bool check = false;

		if (isNegative)
		{
			cout << '-';
		}

		for (int i = chunkSize - 1; i >= 0; i--)
		{
			if (chunks[i] != NULL)
			{
				check = true;
			}
			if (check)
			{
				str += to_string(chunks[i]);
			}
		}
		if (!check)
		{
			str += "0";
		}

		return str;
	}

	BigInt operator += (BigInt right)
	{
		if (isNegative)
		{
			return *this;
		}

		for (int i = 0; i < chunkSize; i++)
		{
			chunks[i] += right.chunks[i];
			if (chunks[i] >= pow(10, smooth))
			{
				chunks[i] -= pow(10, smooth);
				chunks[i + 1] += 1;
				chunks[i] = max(0, chunks[i]);
			}
		}

		return *this;
	}

	friend BigInt operator + (BigInt left, BigInt right)
	{
		if (left.isNegative && right.isNegative)
		{
			return BigInt("0");
		}

		BigInt result("0");

		result += left;
		result += right;

		return result;
	}

};


void Tests()
{
	string sum_data[][3] =
	{ 
		{"123456789", "0", "123456789"},
		{"123456789", "111", "123456900"},
		{"111", "123456789", "123456900"}
	};
	

	cout << endl << "===   +=   ===" << endl << endl;

	for (int i = 0; i < 3; i ++)
	{
		cout << "Задано число n1: " << sum_data[i][0] << endl;
		BigInt n1(sum_data[i][0]);
		
		cout << "Задано число n2: " << sum_data[i][1] << endl;
		BigInt n2(sum_data[i][1]);

		cout << "n1 += n2 => ";
		n1 += n2;
		cout << n1.ToString() << endl;

		if (sum_data[i][2] == n1.ToString())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout << "Правильно" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			cout << "Ошибка" << "\a" << endl;
			cout << "i = " << i << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		

		cout << endl;
	}
	cout << endl << "===   +   ===" << endl << endl;


	for (int i = 0; i < 3; i++)
	{
		cout << "Задано число n1: " << sum_data[i][0] << endl;
		BigInt n1(sum_data[i][0]);

		cout << "Задано число n2: " << sum_data[i][1] << endl;
		BigInt n2(sum_data[i][1]);

		cout << "n1 + n2 => ";
		BigInt n0 = n1 + n2;
		cout << n0.ToString() << endl;

		if (sum_data[i][2] == n0.ToString())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			cout << "Правильно" << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			cout << "Ошибка" << "\a" << endl;
			cout << "i = " << i << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}


		cout << endl;
	}

}

void main()
{
	setlocale(LC_ALL, "RUS");

	
	Tests();
	cout << endl;
}