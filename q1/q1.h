//too lazy to allocate memory dynamically...
//c programs cannot take variables as array size
#define P_NUM 100
#define R_NUM 100

int psize = 6;
int rsize = 4;
int alloc[P_NUM][R_NUM]={};
int max[P_NUM][R_NUM]={};
int avail[R_NUM] = {0};
int minRes[R_NUM] = {0};
int need[P_NUM][R_NUM] = {0};
int total[P_NUM][R_NUM] = {0};

void getResInput(int avail[R_NUM], const int rsize);

void getArrayInput(int array[P_NUM][R_NUM], const int psize, const int rsize);

void printArr(const int* r, int size);

void printFormatting(const int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize);

void printSeqFormatting(const int alloc[P_NUM][R_NUM], const int avail[R_NUM], 
const int psize, const int rsize);

void calMinResource(const int a[P_NUM][R_NUM], int minR[R_NUM], 
const int psize, const int rsize);

void calNeed(const int a[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], 
const int psize, const int rsize);

void printSeq(const int* r, int size, int flag, 
const int psize, const int rsize);

void safety(int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize);

void getInputs(const int psize, const int rsize);

void runProgram(const int psize, const int rsize, const int setValue);

