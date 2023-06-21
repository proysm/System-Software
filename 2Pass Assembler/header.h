// header.h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;
//using namespace stdext;

struct srcInfo {
	string label, opcode, operand, counter;
}; // vector<srcInfo> srcT;

struct smbInfo {
	string label, address;
}; // vector<smbInfo> symbolT;

struct intInfo {
	string counter, label, opcode, operand;
}; // vector<intInfo> intT;


int strTodec(string str) //16진수로 표현된 문자열을 10진수로 바꿈
{
	int num = 0, cnt;
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		int n = 1;
		int ii = str.at(i) < 65 ? (str.at(i) - 48) : (str.at(i) - 65);
		cnt = length - i - 1;
		for (int k = 0; k < cnt; k++)
		{
			n = n * 16;
		}
		num = num + ii * n;
	}
	return num;
}

int strTohex(string str) // 10진수로 표현된 문자열을 16진수로 바꿈 (표현은 10진수 숫자)
{
	int num = 0, cnt;
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		int n = 1;
		int ii = str.at(i) < 65 ? (str.at(i) - 48) : (str.at(i) - 65);
		cnt = length - i - 1;
		for (int k = 0; k < cnt; k++)
		{
			n = n * 10;
		}
		num = num + ii * n;
	}
	return num;
}

string decTohex(int num) // 10진수로 표현되어있는 16진수를 16진수 표기법으로 표현
{
	string str;
	for (;num>0; num /= 16)
	{
		int a = num % 16;
		char c = a < 10 ? (a + '0') : (a + 'A' - 10);
		str.append(1, c);
	}
	reverse(str.begin(), str.end());
	return str;
}

string make6(string str) // 문자열 "100C" 을 "00100C" 로 바꿔줌 (6자리)
{
	string ss = "";
	int length = str.length();
	for (int i = 6; i > length; i--)
	{
		ss.append(1, '0');
	}
	ss = ss + str;
	return ss;
}

string make2(string str) // 문자열 "C" 을 "0C" 로 바꿔줌 (2자리)
{
	string ss = "";
	int length = str.length();
	for (int i = 2; i > length; i--)
	{
		ss.append(1, '0');
	}
	ss = ss + str;
	return ss;
}

string findStartAd(string startAd, int length)
{
	int num = strTodec(startAd) + length;
	
	return decTohex(num);
}
