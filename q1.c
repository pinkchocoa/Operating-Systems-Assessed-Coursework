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
#include <stdio.h>

#define P_NUM 6
#define R_NUM 4

//need to take in 4 inputs
void getResInput(int avail[R_NUM])
{
    while(printf("Enter the number of total instances of resource type A.\n")
    && scanf("%d", &avail[0]) != 1) //this loops while the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
        
    while(printf("Enter the number of total instances of resource type B.\n")
    && scanf("%d", &avail[1]) != 1) //this loops while the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
        
    while(printf("Enter the number of total instances of resource type C.\n")
    && scanf("%d", &avail[2]) != 1) //this loops while the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
        
    
    while(printf("Enter the number of total instances of resource type D.\n")
    && scanf("%d", &avail[3]) != 1) //this loops while the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
    
}

void getArrayInput(int array[P_NUM][R_NUM])
{
    for(int i = 0; i < P_NUM; i++)
        for(int j = 0; j < R_NUM; j++)
            while(printf("Enter the number for[%d][%d]", i, j) && 
            scanf("%d", &array[i][j]) != 1)
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
}

void printArray(const int array[P_NUM][R_NUM])
{
    for(int i = 0; i < P_NUM; i++)
    {
        for(int j = 0; j < R_NUM; j++)
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

void calMinResource(const int a[P_NUM][R_NUM], int minR[R_NUM])
{
    for(int j = 0; j < R_NUM; j++)
        for(int i = 0; i < P_NUM; i++)
            minR[j]+=a[i][j];
}

void calNeed(const int a[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], int need[P_NUM][R_NUM])
{
    for(int i = 0; i < P_NUM; i++)
        for(int j = 0; j < R_NUM; j++)
            need[i][j] = max[i][j]-a[i][j];
}

void printSeq(const int* r, int size, int flag)
{
    if (flag == 1) //complete sequence
    {
        for(int i = 0; i < P_NUM; i++)
            if (i != P_NUM-1) printf("P%d ->", r[i]);
            else printf("P%d", r[i]);
    }
    else
    {
        for(int i = 0; i < P_NUM; i++)
            if (r[i+1] != -1) printf("P%d ->", r[i]);
            else if(r[i] != -1) printf("P%d", r[i]);
            else break;
    }
}

void safety(const int alloc[P_NUM][R_NUM], 
const int max[P_NUM][R_NUM], const int need[P_NUM][R_NUM], 
const int avail[R_NUM], int safeSeq[P_NUM])
{
    int count = 0;
    int visited[P_NUM] = {0};
    int work[R_NUM] = {0};
    for(int i = 0; i < R_NUM; i++) work[i] = avail[i];
    
    //if count == P_NUM it means that all processes have been ran
    while(count < P_NUM) 
    {
        int flag = 0; //flag to check if we should break or not
        for (int i = 0; i <P_NUM; i++)
        {
            if(visited[i] == 0) //check first unvisited process
            {
                int j = 0;
                for(j = 0; j < R_NUM; j++) //check each resource
                    if(need[i][j] > work[j])
                        break; //need more than current avail
                //this means the process has all the resources it needs
                if(j == R_NUM) 
                {
                    safeSeq[count++]=i; //so we add it to the safeSeq
                    visited[i] = 1; //change change it to visited
                    flag = 1; //at least one process can run
                    for(j=0; j<R_NUM; j++)
                        work[j] += alloc[i][j]; //release allocated
                }
            }
        }
        if (flag == 0) //this means no processes can run
            break;
    }
    if (count < P_NUM) //this means that there is no safe sequence
    {
        printf("unsafe state!\n");
        printf("current avail resource:\n");
        printR(work, R_NUM);
        printf("sequence:\n");
        printSeq(safeSeq, P_NUM, 0);
    }
    else //safe sequence
    {
        printf("safe state!\n");
        printSeq(safeSeq, P_NUM, 1);
    }
}

int main()
{
    int alloc[P_NUM][R_NUM]={
        /*
        {2,1,3,3},
        {2,3,1,2},
        {3,3,3,1},
        {2,1,3,4},
        {3,2,2,5},
        {2,1,2,3},*/
    };
    int max[P_NUM][R_NUM]={
        /*
        {7,3,4,5},
        {8,6,2,1},
        {9,5,5,6},
        {6,4,6,3},
        {8,3,2,4},
        {8,3,2,3},*/
    };
    int avail[R_NUM] = {0};
    int minRes[R_NUM] = {0};
    int need[P_NUM][R_NUM] = {0};
    int total[P_NUM][R_NUM] = {0};
    int safeSeq[P_NUM];
    for(int i = 0; i < P_NUM; i++) safeSeq[i] = -1;
    
    getResInput(avail);
    printf("avail res:\n");
    printR(avail, R_NUM);
    
    printf("alloc:\n");
    getArrayInput(alloc);
    printArray(alloc);
    
    printf("max:\n");
    getArrayInput(max);
    printArray(max);
    
    printf("need:\n");
    calNeed(alloc,max,need);
    printArray(need);
    
    printf("min res:\n");
    calMinResource(alloc, minRes);
    printR(minRes, R_NUM);
    
    safety(alloc,max,need,avail,safeSeq);
    return 0;
}