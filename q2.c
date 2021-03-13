#include <stdio.h>

#define MEM_PART 12 //number of memory partitions
#define INPUT_PROC 10 //number of input processes

void getProcessInput(int a[INPUT_PROC])
{
    for(int i = 0; i < INPUT_PROC; i++)
    {
        while(printf("Enter the size of process %d in KB.\n", i)
        && scanf("%d", &a[i]) != 1) //this loops while the input is invalid
        //aka it will ask again
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
    }
}

void printRes(const int m[MEM_PART], const int p[INPUT_PROC], const int f[MEM_PART])
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
void firstFit(const int m[MEM_PART], const int p[INPUT_PROC])
{
    int inUse[MEM_PART];
    //set all as -1 as free
    for(int i = 0; i < MEM_PART; i++) inUse[i] = -1;
    
    for(int j = 0; j < INPUT_PROC; j++)
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
    printRes(m, p, inUse);
}

/*
Best-fit:  Allocate the smallest hole that is big enough; 
must search entire list, unless ordered by size. 
Produces the smallest leftover hole
*/
void bestFit(const int m[MEM_PART], const int p[INPUT_PROC])
{
    int inUse[MEM_PART];
    //set all as -1 as free, otherwise set it to the process that is taken by
    for(int i = 0; i < MEM_PART; i++) inUse[i] = -1;
    //your code here
    printRes(m, p, inUse);
}

/*
Worst-fit:  Allocate the largest hole; 
must also search entire list 
Produces the largest leftover hole
*/
void worstFit(int m[MEM_PART], const int p[INPUT_PROC])
{
    int inUse[MEM_PART];
    int worstIndex = -1;
    int biggestGap = 0;
    //set all as -1 as free, otherwise set it to the process that is taken by
    for(int i = 0; i < MEM_PART; i++) inUse[i] = -1;
    
    for(int j = 0; j < INPUT_PROC; j++)
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
            m[worstIndex] -= p[j];
    }
    printf("\nWorst fit: \n");
    printRes(m, p, inUse);
}

int main()
{
    int memPart[MEM_PART] = {160, 350, 650, 80, 410, 50, 720, 905, 570, 130, 260, 830};
    int processInput[INPUT_PROC] = {0};
    getProcessInput(processInput);
    firstFit(memPart, processInput);
    bestFit(memPart, processInput);
    worstFit(memPart, processInput);
    return 0;
}