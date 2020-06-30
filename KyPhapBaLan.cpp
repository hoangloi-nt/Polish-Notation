#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node
{
	string Data;
	struct Node* pNext;
};
typedef struct Node NODE;

struct Stack
{
	NODE* Top;
};
typedef struct Stack STACK;

void Init(STACK s)
{
	s.Top = NULL;
}

NODE* GetNode(string x)
{
	NODE* p = new NODE;
	if (p == NULL)
	{
		cout << "Khong du bo nho de cap phat! ";
		system("pause");
		return NULL;
	}
	p->Data = x;
	p->pNext = NULL;
	return p;
}

bool IsEmpty(STACK s)
{
	if (s.Top == NULL) return true;
	return false;
}

bool Push(STACK& s, NODE* p)
{

	if (IsEmpty(s) == true)
	{
		s.Top = p;
		return true;
	}
	p->pNext = s.Top;
	s.Top = p;
	return true;
}

bool Pop(STACK& s, string& x)
{
	if (IsEmpty(s) == true)
	{
		return false;
	}
	NODE* p = s.Top;
	x = p->Data;
	s.Top = s.Top->pNext;
	delete p;
	return true;
}

bool Top(STACK s, string& x)
{

	if (IsEmpty(s) == true)
	{
		return false;
	}
	x = s.Top->Data;
	return true;
}

void XuLy(STACK& s)
{
	ifstream FileIn;
	FileIn.open("input.txt", ios_base::in);

	if (!FileIn)
	{
		cout << "Khong tim thay tap tin input.txt ";
		system("pause");
		return;
	}

	string str;
	getline(FileIn, str);
	FileIn.close();
	
	Init(s);

	string p1, p2, p3;
	int KetQua;
	for (int i = 0; i < str.length(); i++)
	{
		NODE* p = new NODE;
		if (str[i] == '(')
		{
			continue;
		}
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%')
		{
			char* Temp = new char;
			Temp[0] = str[i];
			Temp[1] = '\0';
			string a = Temp;

			p = GetNode(a);
			Push(s, p);
		}

		string Temp;
		int Start;
		int End;

		if (str[i] >= '0' && str[i] <= '9')
		{
			Start = i;

			for (int j = i + 1; j < str.length(); j++)
			{
				if (str[j] < '0' || str[j] > '9')
				{
					End = j;
					i = j;
					break;
				}
			}
			End - 1;
			Temp = str.substr(Start, End - Start);
			p = GetNode(Temp);
			Push(s, p);
		}
		if (str[i] == ')')
		{
			Pop(s, p1);
			Pop(s, p2);
			Pop(s, p3);

			int Num3, Num1;
			Num3 = atoi(p3.c_str());
			Num1 = atoi(p1.c_str());

			if (p2 == "+")
			{
				KetQua = Num3 + Num1;
			}
			else if (p2 == "-")
			{
				KetQua = Num3 - Num1;
			}
			else if (p2 == "*")
			{
				KetQua = Num3 * Num1;
			}
			else if (p2 == "/")
			{
				KetQua = Num3 / Num1;
			}
			else if (p2 == "%")
			{
				KetQua = Num3 % Num1;
			}

			// Đưa lại nó vào trong Stack.
			char chr[20];
			_itoa_s(KetQua, chr, 10);
			Node* q = GetNode((string)chr);
			Push(s, q);
		}
	}

	cout << KetQua << endl;
}


int main()
{
	STACK s;
	XuLy(s);
	system("pause");
	return 1;
}