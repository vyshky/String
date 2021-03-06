#include<iostream>
using namespace std;

#define delimiter "\n---------------------------------------------------------\n"

class String;
String operator+(const String& left, const String& right);

class String
{
	int size;	//Размер строки в байтах
	char* str;	//Указатель на строку в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	// -v возвращает константный указатель (НЕльзя изменить значение по адресу)
	const char* get_str()const//Const указывает на константный метод
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	void set_str()
	{
		cin >> str;
	}
	//			Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << (size == 80 ? "Default" : "Size") << "Constructor:\t" << this << endl;
	}
	String(const char str[])
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)
			this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	//MoveConstructor
	String(String&& other)
	{
		this->size = other.size;
		this->str = other.str; //копируем указатель на массив
		other.str = nullptr;//Указатель на ноль (NULL pointer) - указатель в никуда.
		cout << "MoveConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] this->str;
		cout << "Destructor:\t\t" << this << endl;
	}

	//			Operators:	

	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		cout << "MoveAssignment:\t\t" << this << endl;
		return *this;
	}
	String& operator+=(const String& other)
	{
		return *this = *this + other;
	}

	char& operator[](int i)
	{
		return str[i];
	}
	char& operator[](int i)const
	{
		return str[i];
	}

	//			Methods:
	void print() const
	{
		std::cout << "size:\t" << size << std::endl;
		cout << "str:\t" << str << endl;
	}

};

ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}


String operator+(const String& left, const String& right)
{
	//result это локальная переменная
	String result(left.get_size() + right.get_size() - 1);	//-1 убирает лишний ноль на конце	

	for (int i = 0; i < left.get_size(); i++)
		//*(result.get_str() + i) = *(left.get_str() + i);
		result[i] = left[i];

	for (int i = 0; i < right.get_size(); i++)
	{		
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		result[i + left.get_size() - 1] = right[i];
	}
	return result; // вызывается MoveConstructor и значение копируется в str3, после этого вызывается Destructor для resulte
	//		CPU/RAM
}

bool operator==(const String& left, const String& right)
{
	if (left.get_size() != right.get_size())return false;

	for (int i = 0; i < left.get_size(); i++)
	{
		if (left[i] != right[i])return false;
		if (left[left.get_size() - i] != right[left.get_size() - i])return false;

	}
	return true;
}

bool operator!=(const String& left, const String& right)
{
	return !(left == right);
}

bool operator<(const String& left, const String& right)
{
	return left.get_size() < right.get_size();
}

bool operator>(const String& left, const String& right)
{
	return !(left < right || left.get_size() == right.get_size());
}


//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK

int main()
{
	setlocale(LC_ALL, "Russian");

#ifdef CONSTRUCTORS_CHECK
	String str;		//Default constructor
	str.print();

	String str1 = "Hello";	//Single argument constructor
	str1.print();
	cout << "str1:" << str1 << endl;
	String str2 = str1;		//Copy constructor
	cout << "str2:" << str2 << endl;

	str = str2;		//Copy assignment
	cout << str << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	String str1 = "Hello";
	String str2;
	str1 = str1;
	str1.print();
	cout << "str1:" << str1 << endl;
	cout << "str2:" << str2 << endl;

	int a = 2;
	a = a;
	cout << a << endl;
#endif // ASSIGNMENT_CHECK

	int x = 0;
	String str1 = "Hello  ";
	String str2 = "Hell0  ";

	cout << (str1 == str2) << endl;
	cout << (str1 != str2) << endl;
	cout << (str1 > str2) << endl;
	cout << (str1 < str2) << endl;

	cout << delimiter << endl;
	String str3 = str1 + str2;//Operator + будет выполнять конкатенацию строк(слияние,объединение) строк		
	cout << delimiter << endl;
	cout << str3 << endl;	
	//cout << delimiter << endl;
	//str1 += str2;
	//cout << delimiter << endl;
	//cout << str1 << endl;
	//String str3 = str1;//Copy constructor
	//String str4;
	//str4 = str2;	//Operator=
	return 0;
}
