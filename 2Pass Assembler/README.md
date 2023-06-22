# 2Pass Assembler

### 입력
1. 소스파일(SIC) 
- SIC 시뮬레이터에서 사용하는 소스파일 형식 그대로 사용

![SIC]<image/sourcefile.png>

2. OPTAB
- 소스파일에서 사용된 opcode를 포함하도록 자유롭게 파일 형태로 작성
- 각 라인은 "LDA 00" 처럼

### 출력
1. SYMTAB
메모리 상에 위치. 반드시 파일로 출력할 필요는 없으나 보고서에 나타나야 함
(1) 파일로 출력하거나 (2) SYMTAB 구조 및 내용을 출력하는 실행 화면 캡처
2. INTFILE : 중간파일
Pass1의 출력으로, 파일 형태로 출력되어야 함
3. OBJFILE
Pass2의 출력으로, 파일 형태로 출력되어야 함

사용언어
C++