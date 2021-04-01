/* Start Header
*****************************************************************/
/*!
\file q1.h
\author Jodie Moh
\date 24/03/2021
\brief
This is a header file to q1.c, 
*/
/* End Header
*******************************************************************/
/**
 * @see q1.c, q1testCases.c
*/
/*too lazy to allocate memory dynamically...
c programs cannot take variables as array size*/
#define P_NUM 100 //The maximum process size.
#define R_NUM 100 //The maximum resource size.

//Able to change the process and resource input
int psize = 6; // Process Number, limit 100(P_NUM)
int rsize = 4; // Resource Number, limit 100(R_NUM)

int alloc[P_NUM][R_NUM]={0}; // Allocation Resources Matrix
int max[P_NUM][R_NUM]={0}; // Max Resources Matrix
int avail[R_NUM] = {0}; // Avilable Resources Matrix
int minRes[R_NUM] = {0}; // Minmum Resources
int need[P_NUM][R_NUM] = {0}; // Need Reources Matrix
int total[P_NUM][R_NUM] = {0}; // Total Resources Matrix

void getResInput(int avail[R_NUM], const int rsize);

void getArrayInput(int array[P_NUM][R_NUM], const int psize, const int rsize);

void printArr(const int* r, int size);

void printFormatting(const int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize);

void calMinResource(const int a[P_NUM][R_NUM], int minR[R_NUM], 
const int psize, const int rsize);

void calNeed(const int a[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], 
const int psize, const int rsize);

void printSeq(const int* r, int flag, const int psize);

void safety(int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize);

void getInputs(const int psize, const int rsize);

void runProgram(const int psize, const int rsize, const int setValue);

