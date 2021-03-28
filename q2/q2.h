#define MEM_NUM 100 //number of memory partitions
#define PROC_NUM 100 //number of input processes

int memPart[MEM_NUM] = {0};
int procPart[PROC_NUM] = {0};
int inUse[MEM_NUM] = {0};
int notUse[MEM_NUM] = {0};

int MEM_PART = 12;
int PROC_PART = 10;

int runProgram(int getInput, int runAll);
int ask();
int runAsk(int x);
void getProcessInput(int a[PROC_NUM], const int size);
void printRes(const int m[MEM_NUM], const int p[PROC_NUM], const int f[MEM_NUM]);
void printInput(int p, int m, int pIdx, int mIdx);
void firstFit(const int m[MEM_NUM], const int p[PROC_NUM]);
void bestFit(const int m[MEM_NUM], const int p[PROC_NUM]);
void worstFit(const int m[MEM_NUM], const int p[PROC_NUM]);
int runAll();