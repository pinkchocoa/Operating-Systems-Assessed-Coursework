/* Start Header
*****************************************************************/
/*!
\file q2.h
\author Jodie Moh
\author Zhei Wei
\author Aloysius Wong
\date 31/03/2021
\brief
This is the header file for q2.c.
*/
/* End Header
*******************************************************************/
#define MEM_NUM 100 /*number of memory partitions*/
#define PROC_NUM 100 /*number of input processes*/

int memPart[MEM_NUM] = {0};
int procPart[PROC_NUM] = {0};
int inUse[MEM_NUM] = {0};
int notUse[MEM_NUM] = {0};

int MEM_PART = 12; /*Maxium memory part*/
int PROC_PART = 10; /*Maxium memory part*/

void runProgram(int getInput);
void ask();
void runAsk(int x);
void getProcessInput(int a[PROC_NUM], const int size);
void printRes(const int m[MEM_NUM], const int p[PROC_NUM], const int f[MEM_NUM]);
void printInput(int p, int m, int pIdx, int mIdx);
void firstFit(const int m[MEM_NUM], const int p[PROC_NUM]);
void bestFit(const int m[MEM_NUM], const int p[PROC_NUM]);
void worstFit(const int m[MEM_NUM], const int p[PROC_NUM]);
void runAll();