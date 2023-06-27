#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <utility>
using namespace std;


int strTodec(string str); // 16진수 -> 10진수
string decTohex(int num); // 10진수 -> 16진수
string decTobin(int num); // 10진수 -> 2진수 

// -----------------------------------------------------------------------------------------------------
// Memory
class Memory {

public:
    uint16_t memory[4096]; // 메모리
    unsigned int mpt; // 메모리 포인터    

    // 메모리 초기화
    Memory() {
        memset(memory, 0, sizeof(memory));
        mpt = 0; 
    }
    // 메모리를 특정 주소부터 0으로 초기화
    void init_pos(int pos) {
        for (int i = pos; i < sizeof(memory); i++)
            memory[i] = 0;
    }

    // 메모리 전체를 임의의 값으로 초기화
    void init_val(int val) {
        memset(memory, val, sizeof(memory));
    }

    // 메모리 포인터 읽기
    void read_pos(int pos) {
        mpt = pos;
    }

    // 현재 메모리 포인터가 가리키는 메모리 읽기
    int16_t readM() { 
        return memory[mpt];
    }

    // 특정 메모리 포인터가 가리키는 메모리 읽기
    int readM(int pos) {
        return memory[pos];
    }

    // 메모리 쓰기
    void writeM(int pos, int val) {
        memory[pos] = val;
    }

    // 특정 주소의 메모리 보기
    void showM(int pos) {
        
        cout << pos << "번째 메모리: " << decTobin(memory[pos]) << endl;

    }

    // 메모리 모두 보기
    void showMall() {
        for(int i = 0; i<= mpt; i++)
        {
            if (memory[i] != 0)
                cout << i << "번째 메모리: " << decTohex(memory[i]) << endl;
            else
                cout << i << "번째 메모리: " << endl;
        } 
    }
    
};
// -----------------------------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------------------------
// CPU
class CPU16 {

public:

    uint16_t AC; // AC 레지스터 값
    unordered_map<string, int> umOpcode; // opcode 명령어의 변환
    
    Memory mem;

    CPU16() {
        AC = 0;
        readCmd();
    }

    // 명령어의 실제 구조 저장
    void readCmd() { 
        umOpcode.insert(make_pair("LDA", 0));  // 0000
        umOpcode.insert(make_pair("STA", 1));  // 0001
        umOpcode.insert(make_pair("ADD", 2));  // 0010
        umOpcode.insert(make_pair("MUL", 3));  // 0011
        umOpcode.insert(make_pair("DIV", 4));  // 0100
        umOpcode.insert(make_pair("MOD", 5));  // 0101
        umOpcode.insert(make_pair("SEA", 15)); // 1111
    }

    // txt 형식의 프로그램 읽기
    void readProg(string filename) {

        ifstream pFile(filename);

        if (pFile.is_open())
        {
            string a, b, line;
            int index;

            while (getline(pFile, line))
            {
                
                index = line.find(" ");
                a = line.substr(0, index); // -> 4bit SEA
                b = line.substr(index+1); // -> 12bit 7EF

                int temp1 = umOpcode.find(a)->second; // 15 
                int temp2 = strTodec(b); // 2031

                mem.writeM(mem.mpt, temp1 * 4096 + temp2); // 메모리에 저장
                mem.mpt++;
            }           
        }
    }


    // 프로그램 계산 step1
    void calc() {
        for (int i = 0; i < mem.mpt; i++) {
            int temp = mem.readM(i); // 메모리를 읽어서 연산자, 피연산자 구분
            int op = temp / 4096;
            int val = temp - 4096 * op;
            func(op, val);
        }

    }
    // 프로그램 계산 step2
    void func(int op, int val) {
        switch (op)
        {
        case 0: //LDA            
            AC = mem.readM(val);
            break;
        case 1: //STA          
            mem.writeM(val, AC);
            mem.mpt = val;
            break;
        case 2: //ADD           
            AC += val;
            break;
        case 3: //MUL            
            AC *= val;
            break;
        case 4: //DIV            
            AC /= val;
            break;
        case 5: //MOD            
            AC %= val;
            break;
        case 15: //SEA          
            AC = val;
            break;
        default:
            break;
        }
    }
    
};
// -----------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------
// 16진수로 표현된 숫자를 10진수로 표현하기
int strTodec(string str)
{
    int num = 0, cnt;
    int length = str.length();

    for (int i = 0; i < length; i++)
    {
        int n = 1;
        int ii = str.at(i) < 65 ? (str.at(i) - 48) : (str.at(i) - 55);
        cnt = length - i - 1;
        for (int k = 0; k < cnt; k++)
        {
            n = n * 16;
        }
        num = num + ii * n;
    }
    return num;
}
// -----------------------------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------------------------
// 10진수로 표현된 숫자를 2진수로 표현하기
string decTobin(int num)
{
    string str, str2, str3, str4;
    int opcode = num / 4096;
    int operand = num - 4096 * (num / 4096);

    switch (opcode)
    {
    case 0:  str2 = "0000";
        break;
    case 1:  str2 = "0001";
        break;
    case 2:  str2 = "0010";
        break;
    case 3:  str2 = "0011";
        break;
    case 4:  str2 = "0100";
        break;
    case 5:  str2 = "0101";
        break;
    case 15: str2 = "1111";
        break;
    default:
        break;
    }

    for (; operand > 0; operand /= 2)
    {
        int a = operand % 2;
        char c = a == 1 ? '1' : '0';
        str.append(1, c);
    }
    reverse(str.begin(), str.end());

    int length = str.length();
    for (int i = 12; i > length; i--)
    {
        str3.append(1, '0');
    }
    str3 = str3 + str;
    str4 = str3.substr(0, 4) + " " + str3.substr(4, 4) + " " + str3.substr(8);
    return str2 + " " + str4;

}
// -----------------------------------------------------------------------------------------------------


// -----------------------------------------------------------------------------------------------------
// 10진수로 표현된 숫자를 16진수로 표현하기
string decTohex(int num)
{
    string str, str2;
    int opcode = num / 4096; 
    int operand = num - 4096 * (num / 4096);

    switch (opcode)
    {
    case 0:  str2 = "LDA";
        break;
    case 1:  str2 = "STA";
        break;
    case 2:  str2 = "ADD";
        break;
    case 3:  str2 = "MUL";
        break;
    case 4:  str2 = "DIV";
        break;
    case 5:  str2 = "MOD";
        break;
    case 15: str2 = "SEA";
        break;
    default:
        break;
    }
    
    for (; operand > 0; operand /= 16)
    {
        int a = operand % 16;
        char c = a < 10 ? (a + '0') : (a + 'A' - 10);
        str.append(1, c);
    }
    reverse(str.begin(), str.end());

    return str2 + " " + str;
}
// -----------------------------------------------------------------------------------------------------
