#include <stdio.h>
#include "q2.h"

void getProcessInput(int a[PROC_NUM])
{
    for(int i = 0; i < PROC_PART; i++)
    {
        while(printf("Enter the size of process %d in KB.\n", i)
        && scanf("%d", &a[i]) != 1) //this loops while the input is invalid
        //aka it will ask again
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
    }
}

void printRes(const int m[MEM_NUM], const int p[PROC_NUM], const int f[MEM_NUM])
{
    for(int i = 0; i < MEM_PART; i++)
    {
        if(f[i] == -1) //free
            printf("Hole %d of size %dKB is not in use\n", i, m[i]);
        else //not free
        {
            printf("Hole %d of size %dKB is in use by process %d of size %dKB\n", 
            i, m[i], f[i], p[f[i]]);
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
    printf("\nFirst fit: \n");
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
    printf("\nBest Fit: \n");
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
    printf("\nWorst fit: \n");
    printRes(m, p, inUse);
}

int main()
{
    getProcessInput(processInput);
    firstFit(memPart, processInput);
    bestFit(memPart, processInput);
    worstFit(memPart, processInput);
    return 0;
}