
#include "CPU16.h";


int main() {	
	
	// CPU 
	CPU16 cpu16;

	// Memory 
	Memory memory;

	cpu16.readProg("PROGA.txt");
	cpu16.calc();
	
	cpu16.mem.showMall();

	return 0;

}