#include <stdio.h> /*scanf, printf*/
#include <stdlib.h> /*used for atoi*/
#include "q2.h"

void getProcessInput(int a[PROC_NUM], const int size)
{
    for(int i = 0; i < size; i++)
    {
        while(printf("\nEnter the size of partition %d in KB:", i)
        && scanf("%d", &a[i]) != 1) //this loops while the input is invalid
        //aka it will ask again
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
    }
}

void printRes(const int m[MEM_NUM], const int p[PROC_NUM], const int f[MEM_NUM])
{
    int count = 0;
    for(int i = 0; i < PROC_PART; i++) notUse[i] = -1;
    for(int i = 0; i < MEM_PART; i++)
    {
        if(f[i] == -1) //free
        {
            printf("Hole %d of size %dKB is not in use\n", i, m[i]);
        }
        else //not free
        {
            printf("Hole %d of size %dKB is in use by process %d of size %dKB\n", 
            i, m[i], f[i], p[f[i]]);
            notUse[f[i]] = 1;
            count++;
        }
    }
    if (count == PROC_PART)
        printf("All processes have been allocated.\n");
    else
    {
        for(int i = 0; i < PROC_PART; i++)
        {
            if (notUse[i] == -1)
                printf("Process %d of size %dKB has to wait.\n", i, p[i]);
        }
    }
}

//First-fit:  Allocate the first hole that is big enough
void firstFit(const int m[MEM_NUM], const int p[PROC_NUM])
{
    //set all as -1 as free
    for(int i = 0; i < MEM_PART; i++) inUse[i] = -1;
    
    for(int j = 0; j < PROC_PART; j++)
    {
        //iterate through the memory paritions
        for (int i = 0; i < MEM_PART; i++)
        {
            if(inUse[i] == -1 && m[i] >= p[j])
            {
                inUse[i] = j; //set inUse to the process
                break;
            }
        }
    }
    printf("\n\nFirst fit: \n");
    printRes(m, p, inUse);
}

/*
Best-fit:  Allocate the smallest hole that is big enough; 
must search entire list, unless ordered by size. 
Produces the smallest leftover hole
*/
void bestFit(const int m[MEM_NUM], const int p[PROC_NUM])
{
    int s = -1; // empty, smallest 
    //set all as -1 as free, otherwise set it to the process that is taken by
    for(int i = 0; i < MEM_PART; i++) inUse[i] = -1;

    //iterrate the input processes
    for(int j = 0; j < PROC_PART; j++)
    {
        s = -1; // reset smallest to empty and to use it again
        //iterate through the memory paritions
        for (int i = 0; i < MEM_PART; i++)
        {
            //check if memory partition is taken and mem partition is bigger then input process
            if(inUse[i] == -1 && m[i] >= p[j])
            {
                if(s == -1) s = i; //if s is empty store it into smallest
                if(m[i] < m[s]) // if smallest is smaller then the next mem partition then replaces and store in smallest
                {
                    s = i;
                }
            }
        }
        if(s != -1) inUse[s] = j; //if smallest not empty then assign the current input process to the smallest mem partiton stored in smallest
    }
    printf("\n\nBest Fit: \n");
    printRes(m, p, inUse);
   
}

/*
Worst-fit:  Allocate the largest hole; 
must also search entire list 
Produces the largest leftover hole
*/
void worstFit(const int m[MEM_NUM], const int p[PROC_NUM])
{
    int worstIndex = -1;
    int biggestGap = 0;
    //set all as -1 as free, otherwise set it to the process that is taken by
    for(int i = 0; i < MEM_PART; i++) inUse[i] = -1;
    
    for(int j = 0; j < PROC_PART; j++)
    {
        worstIndex = -1;
        //iterate through the memory paritions
        for (int i = 0; i < MEM_PART; i++)
        {
            if(inUse[i] == -1 && m[i] >= p[j])
            {
                if(worstIndex == -1)
                {
                    biggestGap = m[i] - p[j];
                    worstIndex = i;
                }
                else if(biggestGap < (m[i] - p[j]))
                {
                    biggestGap = m[i] - p[j];
                    worstIndex = i;
                }
            }
        }
        if(worstIndex != -1)
            inUse[worstIndex] = j;
    }
    printf("\n\nWorst fit: \n");
    printRes(m, p, inUse);
}

int runProgram(int getInput)
{
    printf("%d Memory partitions and %d Processes.", MEM_PART, PROC_PART);
    if(getInput == 1)
    {
        printf("\n\nEnter the memory partitions.");
        getProcessInput(memPart, MEM_PART);
        printf("\n\nEnter the process partitions.");
        getProcessInput(procPart, PROC_PART);
        
    }
    firstFit(memPart, procPart);
    bestFit(memPart, procPart);
    worstFit(memPart, procPart);
}

int main(int argc, char* argv[])
{
    if(argc <= 1) /*no arguments*/
        runProgram(1);
    else if(argc == 2)
    {
    }
    else if(argc == 3)
    {
        MEM_PART = atoi(argv[1]);
        PROC_PART = atoi(argv[2]);
        runProgram(1);
    }
    else
    {
        printf("Zero, One or Two arguments expected.\n");
        printf("One argument: Test Case Number.\n");
        printf("Two arguments: Number of Memory Partitions and Processes.\n");
        return -1;
    }
    return 0;
}