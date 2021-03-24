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
#include "q1.h"
#include "q1testCases.c"

int main(int argc, char* argv[])
{
    if(argc <= 1) //no arguments
        runProgram(psize, rsize, 1);
    else if(argc == 2)
    {
        switch(atoi(argv[1]))
        {
            case 1:
                testCase1(); break;
            case 2:
                testCase2(); break;
            case 3:
                testCase3(); break;
            case 4:
                testCase4(); break;
            case 5:
                testCase5(); break;
            case 6:
                testCase6(); break;
            default:
                printf("Invalid test case.\n"); 
                printf("Test cases available: 1 - 6.\n"); 
                break;
        }
    }
    else if(argc == 3)
    {
        psize = atoi(argv[1]);
        rsize = atoi(argv[2]);
        runProgram(psize, rsize, 1);
    }
    else
    {
        printf("One or Two arguments expected.\n");
        printf("One argument: Test Case.\n");
        printf("Two arguments: Process Number and Resource Number.\n");
        return -1;
    }
    
    return 0;
}

void getResInput(int avail[R_NUM], const int rsize)
{
    for(int i = 0; i < rsize; i++)
    while(printf("Resource type %c:\n", i+65)
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

void printArr(const int* r, int size)
{
    for(int j = 0; j < size; j++)
        printf("%d ", r[j]);
}

void printFormatting(const int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize)
{
    printf("\n[ PROCESS ]\t[ ALLOCATION ]\t  [ MAX ]\t[ NEED ]\t[ AVAILABLE ]");
    for (int i = 0; i < psize; i++)
    {
        printf("\n Process %d\t   ", i);
        printArr(alloc[i], rsize);
        printf("\t  ");
        printArr(max[i], rsize);
        printf("\t");
        printArr(need[i], rsize);
        printf("\t   ");
        if (i == 0)
            printArr(avail, rsize);
    }
    printf("\n\n");
}

void calMinResource(const int a[P_NUM][R_NUM], int minR[R_NUM], 
const int psize, const int rsize)
{
    for(int j = 0; j < rsize; j++)
        for(int i = 0; i < psize; i++)
            minR[j]+=a[i][j];
}

void calNeed(const int a[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], 
const int psize, const int rsize)
{
    for(int i = 0; i < psize; i++)
        for(int j = 0; j < rsize; j++)
            need[i][j] = max[i][j]-a[i][j];
}

void printSeq(const int* r, int size, int flag, 
const int psize, const int rsize)
{
    if (flag == 1) //complete sequence
    {
        printf("Safe State.\n");
        for(int i = 0; i < psize; i++)
            if (i != psize-1) printf("P%d -> ", r[i]);
            else printf("P%d\n", r[i]);
    }
    else
    {
        printf("Unsafe State.\n");
        for(int i = 0; i < psize; i++)
            if (r[i+1] != -1) printf("P%d -> ", r[i]);
            else if(r[i] != -1) printf("P%d\n", r[i]);
            else break;
    }
}

void safety(int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM], 
const int avail[R_NUM], const int psize, const int rsize)
{
    int count = 0;
    int visited[P_NUM] = {0};
    int safeSeq[P_NUM];
    int work[R_NUM] = {0};
    int flag = 0;
    for(int i = 0; i < rsize; i++) work[i] = avail[i];
    for(int i = 0; i < psize; i++) safeSeq[i] = -1;
    
    //if count == psize it means that all processes have been ran
    while(count < psize) 
    {
        flag = 0; //flag to check if we should break or not
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
                }
            }
        }
        if (flag == 0) //this means no processes can run
            break;
    }
    for(int i = 0; i < rsize; i++) work[i] = avail[i];
    for (int i = 0; i < count; i++)
    {
        printf("Running process P%d.\n", safeSeq[i]);
        for(int j=0; j < rsize; j++)
        {
            work[j] += alloc[safeSeq[i]][j]; 
            alloc[safeSeq[i]][j] = 0;
            need[safeSeq[i]][j] = 0;
        }
        printFormatting(alloc, max, need, work, psize, rsize);
    }
    printSeq(safeSeq, psize, flag, psize, rsize);
}

void getInputs(const int psize, const int rsize)
{
    printf("\nEnter the available resources.\n");
    getResInput(avail, rsize);
    printf("\nEnter Allocation Matrix.\n");
    getArrayInput(alloc, psize, rsize);
    printf("\nEnter Max Matrix.\n");
    getArrayInput(max, psize, rsize);
}

void runProgram(const int psize, const int rsize, const int setValue)
{
    printf("Process Number: %d, Resource Number: %d", psize, rsize);
    
    if (setValue == 1)
        getInputs(psize, rsize);
    
    calNeed(alloc,max,need, psize, rsize);
    calMinResource(alloc, minRes, psize, rsize);
    
    printFormatting(alloc, max, need, avail, psize, rsize);
    printf("Min. resources:\n");
    printArr(minRes, rsize);
    printf("\n\n");
    
    safety(alloc, max, need, avail, psize, rsize);
}