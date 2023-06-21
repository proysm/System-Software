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


int strTodec(string str) //16������ ǥ���� ���ڿ��� 10������ �ٲ�
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

int strTohex(string str) // 10������ ǥ���� ���ڿ��� 16������ �ٲ� (ǥ���� 10���� ����)
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

string decTohex(int num) // 10������ ǥ���Ǿ��ִ� 16������ 16���� ǥ������� ǥ��
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

string make6(string str) // ���ڿ� "100C" �� "00100C" �� �ٲ��� (6�ڸ�)
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

string make2(string str) // ���ڿ� "C" �� "0C" �� �ٲ��� (2�ڸ�)
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
