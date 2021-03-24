/* Start Header
*****************************************************************/
/*!
\file q1.c
\author Jodie Moh
\par email:
\date 
\brief
Write a C programming which is to simulate the functions of the OS
to implement the Banker's algorithm, to detect if the system is in
Safestate or unsafe state.

If it is in the safe state, your Banker’s algorithm need print out
(display) the execution sequences in which these processes may 
complete on the screen. 

If it is in the unsafe state, your Banker’s algorithm need display 
which process it fails at by showing the available resources at 
this point of time, and the processes needed resources at this 
point of time. 
*/
/* End Header
*******************************************************************/
#include <stdio.h> //scanf, printf
#include <stdlib.h> //used for atoi

//too lazy to allocate memory dynamically...
//c programs cannot take variables as array size
#define P_NUM 100
#define R_NUM 100

void getResInput(int avail[R_NUM], const int rsize)
{
    for(int i = 0; i < rsize; i++)
    while(printf("Resource type %d:\n", i)
    && scanf("%d", &avail[i]) != 1) //this loops while the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/    
}

void getArrayInput(int array[P_NUM][R_NUM], const int psize, const int rsize)
{
    for(int i = 0; i < psize; i++)
        for(int j = 0; j < rsize; j++)
            while(printf("Enter the number for[%d][%d]:\n", i, j) && 
            scanf("%d", &array[i][j]) != 1)
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
}

void printFormatting(const int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize)
{
    printf("\n[ PROCESS ]\t[ ALLOCATION ]\t  [ MAX ]\t[ NEED ]\t[ AVAILABLE ]");
    for (int i = 0; i < psize; i++)
    {
        printf("\n Process %d\t   ", i);
        for (int j = 0; j < rsize; j++)
            printf("%d ", alloc[i][j]);
        printf("\t  ");
        for (int j = 0; j < rsize; j++)
            printf("%d ", max[i][j]);
        printf("\t");
        for (int j = 0; j < rsize; j++)
            printf("%d ", need[i][j]);
        printf("\t   ");
        if (i == 0)
            for (int j = 0; j < rsize; j++)
                printf("%d ", avail[j]);
    }
    printf("\n\n");
}

void printSeqFormatting(const int alloc[P_NUM][R_NUM], const int avail[R_NUM], 
const int psize, const int rsize)
{
    printf("\n[ PROCESS ]\t[ ALLOCATION ]\t[ AVAILABLE ]");
    for (int i = 0; i < psize; i++)
    {
        printf("\n Process %d\t   ", i);
        for (int j = 0; j < rsize; j++)
            printf("%d ", alloc[i][j]);
        printf("\t   ");
        if (i == 0)
            for (int j = 0; j < rsize; j++)
                printf("%d ", avail[j]);
    }
    printf("\n\n");
}

void printArray(const int array[P_NUM][R_NUM], const int psize, const int rsize)
{
    for(int i = 0; i < psize; i++)
    {
        for(int j = 0; j < rsize; j++)
            printf("%d ", array[i][j]);
        printf("\n");
    }
}

void printR(const int* r, int size)
{
    for(int j = 0; j < size; j++)
        printf("%d ", r[j]);
    printf("\n");
}

void calMinResource(const int a[P_NUM][R_NUM], int minR[R_NUM], const int psize, const int rsize)
{
    for(int j = 0; j < rsize; j++)
        for(int i = 0; i < psize; i++)
            minR[j]+=a[i][j];
}

void calNeed(const int a[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], const int psize, const int rsize)
{
    for(int i = 0; i < psize; i++)
        for(int j = 0; j < rsize; j++)
            need[i][j] = max[i][j]-a[i][j];
}

void printSeq(const int* r, int size, int flag, const int psize, const int rsize)
{
    if (flag == 1) //complete sequence
    {
        for(int i = 0; i < psize; i++)
            if (i != psize-1) printf("P%d ->", r[i]);
            else printf("P%d", r[i]);
    }
    else
    {
        for(int i = 0; i < psize; i++)
            if (r[i+1] != -1) printf("P%d ->", r[i]);
            else if(r[i] != -1) printf("P%d", r[i]);
            else break;
    }
}

void safety(int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize)
{
    int count = 0;
    int visited[P_NUM] = {0};
    int safeSeq[P_NUM];
    int work[R_NUM] = {0};
    for(int i = 0; i < rsize; i++) work[i] = avail[i];
    for(int i = 0; i < psize; i++) safeSeq[i] = -1;
    
    //if count == psize it means that all processes have been ran
    while(count < psize) 
    {
        int flag = 0; //flag to check if we should break or not
        for (int i = 0; i <psize; i++)
        {
            if(visited[i] == 0) //check first unvisited process
            {
                int j = 0;
                for(j = 0; j < rsize; j++) //check each resource
                    if(need[i][j] > work[j])
                        break; //need more than current avail
                //this means the process has all the resources it needs
                if(j == rsize) 
                {
                    safeSeq[count++]=i; //so we add it to the safeSeq
                    visited[i] = 1; //change change it to visited
                    flag = 1; //at least one process can run
                    for(j=0; j<rsize; j++)
                        work[j] += alloc[i][j]; //release allocated
                        
                    //TODO print out the sequence here
                    //TODO print out the allocated here
                }
            }
        }
        if (flag == 0) //this means no processes can run
            break;
    }
    if (count < psize) //this means that there is no safe sequence
    {
        printf("unsafe state!\n");
        for(int i = 0; i < rsize; i++) work[i] = avail[i];
        for (int i = 0; i < count; i++)
        {
            printf("Running process P%d.\n", safeSeq[i]);
            for(int j=0; j < rsize; j++)
            {
                work[j] += alloc[safeSeq[i]][j]; 
                alloc[safeSeq[i]][j] = 0;
            }
            printSeqFormatting(alloc, work, psize, rsize);
        }

        printf("sequence:\n");
        printSeq(safeSeq, psize, 0, psize, rsize);
    }
    else //safe sequence
    {
        printf("safe state!\n");
        for(int i = 0; i < rsize; i++) work[i] = avail[i];
        for (int i = 0; i <psize; i++)
        {
            printf("Running process P%d.\n", safeSeq[i]);
            for(int j=0; j<rsize; j++)
            {
                work[j] += alloc[safeSeq[i]][j]; 
                alloc[safeSeq[i]][j] = 0;
            }
            printSeqFormatting(alloc, work, psize, rsize);
        }
        printf("sequence:\n");
        printSeq(safeSeq, psize, 1, psize, rsize);
    }
}



void runProgram(const int psize, const int rsize)
{
    int alloc[P_NUM][R_NUM]={};
    int max[P_NUM][R_NUM]={};
    int avail[R_NUM] = {0};
    int minRes[R_NUM] = {0};
    int need[P_NUM][R_NUM] = {0};
    int total[P_NUM][R_NUM] = {0};
    
    printf("\nEnter the available resources.\n");
    getResInput(avail, rsize);
    printf("\nEnter Allocation Matrix.\n");
    getArrayInput(alloc, psize, rsize);
    printf("\nEnter Max Matrix.\n");
    getArrayInput(max, psize, rsize);
    
    calNeed(alloc,max,need, psize, rsize);
    calMinResource(alloc, minRes, psize, rsize);
    
    printFormatting(alloc, max, need, avail, psize, rsize);
    printf("min. resources:\n");
    printR(minRes, rsize);
    printf("\n");
    
    safety(alloc, max, need, avail, psize, rsize);
}

int main(int argc, char* argv[])
{
    int psize = 6;
    int rsize = 4;
    if(argc <= 1) //no arguments
    {
        printf("Process Number: %d, Resource Number: %d", psize, rsize);
    }
    else if(argc == 3)
    {
        //argv[0] is program name
        //./a.exe 5 6
        //argv[0] == "a.exe"
        //argv[1] == "5"
        //argv[2] == "6"
        psize = atoi(argv[1]);
        rsize = atoi(argv[2]);
        printf("Process Number: %d, Resource Number: %d", psize, rsize);
    }
    else
    {
        printf("Two arguments expected.\n");
        printf("Process Number and Resource Number.\n");
        return -1;
    }
    
    runProgram(psize, rsize);
    
    return 0;
}