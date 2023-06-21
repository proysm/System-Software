#include "header.h"

int main(int argc, char* argv[]) {
	
	// Source File 
	vector<srcInfo> srcT;
	string line, stringBuffer;
	string srcfile, intfile;
	srcfile = "SRCFILE";
	intfile = "INTFILE";

	// Optable
	unordered_map<string, string> opTab;

	// Symbol Table
	vector<smbInfo> symbolT;
	string startAd; // ���α׷� ���� �ּ�
	int locctr;

	// IntFile
	string pLength; // pLength = locctr - startAd
	vector<intInfo> intT; // text record ����

	// Object File
	string objfile;
	objfile = "OBJFILE";
	string orStartAd, // ���ڵ忡 ���Ե� �����ڵ��� �����ּ�
		   obCodes; // �����ڵ� 
	int orLength = 0; // ���ڵ��� ����



	// -------------------------------------------------------------------------------------------------------------------
	// Pass 1
	// -------------------------------------------------------------------------------------------------------------------
	
	// Source File �� �а� label, opcode, operand �и�
	ifstream sFile(srcfile);
	if (sFile.is_open())
	{
		while (getline(sFile, line))
		{
			srcInfo temp;
			temp.label = line.substr(0, 9);
			temp.opcode = line.substr(9, 8);
			temp.operand = line.substr(17);
			
			// label opcode operand ���� ����
			(temp.label).erase(remove((temp.label).begin(), (temp.label).end(), ' '), (temp.label).end());
			(temp.opcode).erase(remove((temp.opcode).begin(), (temp.opcode).end(), ' '), (temp.opcode).end());
			(temp.operand).erase(remove((temp.operand).begin(), (temp.operand).end(), ' '), (temp.operand).end());

			// L2U: �ҹ��� -> �빮�� ���� 
			for (int i = 0; i < (temp.label).size(); i++)
				temp.label[i] = toupper(temp.label[i]);
			for (int i = 0; i < (temp.opcode).size(); i++)
				temp.opcode[i] = toupper(temp.opcode[i]);
			for (int i = 0; i < (temp.operand).size(); i++)
				temp.operand[i] = toupper(temp.operand[i]);
			//vector�� ����
			srcT.emplace_back(temp);
		}
	}
	else
	{
		cout << "������ ������ �� �����ϴ�.";
	}
	
	// Optable�� ����
	ifstream oFile("Optab.txt");
	if (oFile.is_open())
	{
		vector<string> x;
		while (getline(oFile, line))
		{
			istringstream ss(line);
			while (getline(ss, stringBuffer, ','))
			{
				x.push_back(stringBuffer);
			}
			opTab.insert(make_pair(x[0], x[1]));
			x.clear();
		}
		oFile.close();
	}
	
	// ���� �ּ� �ʱ�ȭ -> startAd
	if (srcT[0].opcode == "START")
	{
		startAd = srcT[0].operand;
		locctr = stoi(startAd);
	}
	else
	{
		startAd = "000000";
		locctr = stoi(startAd);
	}
	
	// Source file�� ��� ���̺��� ������ �ּ� ������ �����Ѵ�.
	int num = strTodec(startAd);
	srcT[0].counter = "";
	for (int i = 1; i < srcT.size(); i++)
	{
		string str;
		str = decTohex(num);
		srcT[i].counter = str;
		num += 3;
	}
	
	// Symbol Table �ۼ� : OPCODE�� END�� ������ �ݺ� 
	int i = 1;
	while (srcT[i].opcode != "END")
	{
		smbInfo temp;
		// Symbol Table�� �̹� �ִ� label���� Ȯ��
		for (int j = 0; j < symbolT.size(); j++)
		{
			// �ִٸ� ���� ��ȯ
			if (srcT[i].label == symbolT[j].label) return 0;
		}

		// ���ٸ� Symbol Table�� �ۼ�
		temp.label = srcT[i].label;
		temp.address = srcT[i].counter;
		if (srcT[i].label != "") symbolT.emplace_back(temp);


		// LOCCTR ���
		if (opTab.end() != opTab.find(srcT[i].opcode))locctr += 3;
		else if (srcT[i].opcode == "WORD" || srcT[i].opcode == "RESW") locctr += 3;
		else if (srcT[i].opcode == "RESB")locctr += stoi(srcT[i].operand);
		else if (srcT[i].opcode == "BYTE") locctr += srcT[i].operand.size() - 3;
		else return 0;		
		
		i++;

		// END�� ��ȿ�� label�� �ִ� ������� Ȯ��
		if (srcT[i].opcode == "END" && srcT[i].label != "")
		{
			temp.label = srcT[i].label;
			temp.address = srcT[i].counter;
			symbolT.emplace_back(temp);
		}		
	}
	
	// Symbol Table�� Ȯ���ϱ� ���� ���
	for (int i = 0; i < symbolT.size(); i++)
	{
		cout << symbolT[i].address << " " << symbolT[i].label << "\n";
	}


	// �߰� ���� �ۼ�
	ofstream fout(intfile);
	for (int i = 0; i < srcT.size(); i++)
	{
		if(srcT[i].counter != "") fout << srcT[i].counter << " ";
		if (srcT[i].label != "") fout << srcT[i].label << " ";
		fout << srcT[i].opcode << " " << srcT[i].operand << " " << endl;
	}
	fout.close();

	// ���α׷� ���� ����
	int pl = locctr - stoi(startAd); // 10����
	pLength = decTohex(pl);
	cout << "The length of Program: " << pLength; // 16����



	// -------------------------------------------------------------------------------------------------------------------
	// Pass 2
	// -------------------------------------------------------------------------------------------------------------------

	// �߰� ���� INTFILE �� �д´�.
	ifstream iFile(intfile);
	string progName;
	
	if (iFile.is_open())
	{
		
		string  buff;
		int i = 0;
		while (getline(iFile, line))
		{
			vector<string> vv;
			intInfo temp;	
			istringstream ss(line);
			while (getline(ss, buff, ' ')) vv.push_back(buff);

			if (i == 0)
			{
				progName = vv[1];
				startAd = vv[2];
			}
			else
			{
				if (vv[1] == "RSUB")
				{
					temp.counter = vv[0];
					temp.opcode = vv[1];
					temp.operand = "0000";
				}
				else if (vv.size() == 4)
				{
					temp.counter = vv[0];
					temp.label = vv[1];
					temp.opcode = vv[2];
					temp.operand = vv[3];
				}		
				else if (vv.size() == 3)
				{					
					temp.counter = vv[0];
					temp.opcode = vv[1];
					temp.operand = vv[2];
				}

				intT.emplace_back(temp);
			}
			i++;
		}
	}

	// Object File �ۼ�
	ofstream fout2(objfile);
	
	// H
	fout2 << "H" << progName << make6(startAd) << make6(pLength) << "\n"; 
	// T
	bool flag = true;
	for (int i = 0; i < intT.size(); i++) 
	{

		obCodes.append(opTab[intT[i].opcode]);
		
		if (flag == true) orStartAd = intT[i].counter;
		if (intT[i].opcode == "END") continue;

		if (intT[i].opcode == "RSUB")
		{
			obCodes.append(intT[i].operand);
			orLength += 6;
		}
		else if (intT[i].opcode == "WORD" || intT[i].opcode == "BYTE")
		{
			string ss = make6(decTohex(stoi(intT[i].operand)));
			obCodes.append(ss);
			orLength += 6;
		}
		else if (intT[i].opcode == "RESW") {}
		else
		{
			bool b = false;
			for (int k = 0; k < symbolT.size(); k++)
			{
				if (intT[i].operand == symbolT[k].label)
				{
					obCodes.append(symbolT[k].address);
					orLength += 6;
					b = true;
					break;
				}
			}
			if (b == false)
			{
				obCodes.append("9036");
				orLength += 6;
			}
		}

		if (opTab[intT[i].opcode] == "3C") // J�� ������ ��
		{
			flag = true;
			fout2 << "T" << make6(orStartAd) << make2(decTohex(orLength / 2));
			fout2 << obCodes;

			obCodes = "";
			orLength = 0;
			fout2 << "\n";
		}
		else if (orLength == 60) // �ִ� 1E (half byte)
		{
			flag = true;
			fout2 << "T" << make6(orStartAd) << make2(decTohex(orLength / 2));
			fout2 << obCodes;

			obCodes = ""; // �����ڵ� �ʱ�ȭ
			orLength = 0; // �ڵ� ���� �ʱ�ȭ
			fout2 << "\n"; // �ٹٲ�
		}
		else
		{
			flag = false;
		}

	}
	if (orLength != 60)
	{
		fout2 << "T" << make6(orStartAd) << make2(decTohex(orLength / 2));
		fout2 << obCodes << "\n";
	}

	fout2 << "E" << make6(startAd) << endl; // E
	fout2.close();

	return 0;
}