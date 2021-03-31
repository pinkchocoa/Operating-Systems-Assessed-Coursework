/* Start Header
*****************************************************************/
/*!
\file q2.c
\author Jodie Moh
\author Zhei Wei
\author Aloysius Wong
\par email:
\date 
\brief
Write a C programming which is to simulate the functions of OS to
implement these three dynamic memory allocation approaches: First-fit, 
Best-fit and Worst-fit and compare the results.

If it is in the safe state, your Banker’s algorithm need print out
(display) the execution sequences in which these processes may 
complete on the screen. 

Given 12 memory partitions available (holes): 160 KB, 350 KB, 650 KB, 
80 KB, 410 KB, 50 KB, 720 KB, 905 KB, 570 KB, 130 KB, 260 KB, and 
830 KB (in order), how would each of the first-fit, best-fit, and 
worst-fit algorithms allocate 10 input processes with different sizes 
(in order)?
*/
/* End Header
*******************************************************************/
#include <stdio.h> /*scanf, printf*/
#include <stdlib.h> /*used for atoi*/
#include "q2.h"
#include "q2testCases.c"

/**
 * @brief This is the main function for the program. 
 * @brief The main function processes if the users wants to use preset testcases, q2testCases.c and also limit to only legal inputs are allowed.
 * @param argc This is refering the number of strings, argument count passed into the program from command line.
 * @param argv This is refering to the array of arguments.
 * @warning Memory and Process max size limit is 100.
 * @note There are only 2 preset test cases available.
 */
int main(int argc, char* argv[])
{
    if(argc <= 1) /*no arguments*/
        runProgram(1);
    else if(argc == 2)
    {
        switch(atoi(argv[1])) /*If the input is illegal*/
        {
            case 1: testCase1(); break;
            case 2: testCase2(); break;
            default:
                printf("Invalid test case.\n"); 
                printf("Test cases available: 1 - 2.\n"); 
                break;
        }
    }
    else if(argc == 3) /*If memory and process part is more than limit values.*/
    {
        MEM_PART = atoi(argv[1]);
        PROC_PART = atoi(argv[2]);
        if (MEM_PART > 100 || PROC_PART > 100 || MEM_PART <= 0 || PROC_PART <= 0)
            printf("There is a limit of 1-100 for both sizes.\n");
        else
            runProgram(1);
    }
    else /*If invalid inputs, the program will keep requesting the same input.*/
    {
        printf("Zero, One or Two arguments expected.\n");
        printf("One argument: Test Case Number.\n");
        printf("Two arguments: Number of Memory Partitions and Processes.\n");
        return -1;
    }
    return 0;
}

/**
 * @brief Getting process input from the user.
 * This process of this function:
 *     - Program request a statement for the user to enter the size of the partition.
 *     - If it is invalid it will ask for the same request statment again.
 *     - It clears the buffer for the next scan.
 *
 * @param a This is an integer a array, it size of this array is refering to the size of the set process.
 * @param size This is a constant integer type of variable that is used for the amount of items needed to be printed as it represent the size.
 * @note If the input is invalid, it will ask again.
 * @see q2.h
 */
void getProcessInput(int a[PROC_NUM], const int size)
{
    int i = 0;
    for(i = 0; i < size; i++) 
    {
        while(printf("\nEnter the size of partition %d in KB:", i)
        && scanf("%d", &a[i]) != 1) /*this loops while the input is invalid
        //aka it will ask again*/
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
    }
}

/**
 * @brief This function is to format and print out the results of the dynamic memory allocation approaches.
 * 
 * @param m This is an integer array that stores memory value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 * @param p This is an integer array that stores process value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 * @param f This is an integer array that is meant to differentiate if the memory part is available or unavailable. 
 */
void printRes(const int m[MEM_NUM], const int p[PROC_NUM], const int f[MEM_NUM])
{
    int i = 0;
    int count = 0;
    for(i = 0; i < PROC_PART; i++) notUse[i] = -1;
    
    for(i = 0; i < MEM_PART; i++)
    {
        if(f[i] == -1) /*free*/
            printf("Partition %-2d of %-3dKB\n", i, m[i]);
        else /*not free*/
        {
            printf("Partition %-2d of %-3dKB contains Processs %-2d of %-3dKB\n", 
            i, m[i], f[i], p[f[i]]);
            notUse[f[i]] = 1;
            count++;
        }
    }
    if (count == PROC_PART)
        printf("All processes have been allocated.\n");
    else
        for(i = 0; i < PROC_PART; i++)
            if (notUse[i] == -1)
                printf("%-3dKB process %-2d must wait, no memory space for it.\n", p[i], i);
    printf("==============================================================\n");
}

/**
 * @brief This function is use to print the remaining input to show the working process after using the dynamic memory allocation approaches. 
 * 
 * @param p This is an integer type variable that request process value.
 * @param m This is an integer type variable that request memory value.
 * @param pIdx This is an integer type variable that request process index value.
 * @param mIdx This is an integer type variable that request process index value.
 */
void printInput(int p, int m, int pIdx, int mIdx)
{
    int i = 0;
    printf("%-3dKB process%2d is put in %-3dKB partition %-2d\n", p, pIdx, m, mIdx);
    printf("This leaves us with partitions:");
    for (i = 0; i < MEM_PART; i++)
        if(inUse[i] == -1)
            printf(" %3dKB ",  memPart[i]);
    printf("\n\n");
}

/*First-fit:  Allocate the first hole that is big enough*/
/**
 * @brief This is one of the dynamic memory allocation approaches: <b>First-Fit</b>.\n
 * The first-fit will fit the data in the memory from the beginning available memory to the last memory. Also the memory space must be at least big enough to house the data.\n
 * First-Fit Algorithm:
 *     - Iterate through Memory parts and Process Part
 *     - Starting and select from the first process part and fit in the a available memory and the memory must be big enough to house the data.
 *     - Then it call for printRes() function to print.
 *     - After inserting the process to the suitable memory, it sets inUse[] array to an integer to indicate that its used.
 *     - The loop will continue.
 * @param m This is an integer array that stores memory value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 * @param p This is an integer array that stores process value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 */
void firstFit(const int m[MEM_NUM], const int p[PROC_NUM])
{
    int i = 0, j = 0;
    printf("\n==============================================================");
    printf("\nStep by Step First fit Assignment: \n");
    /*set all as -1 as free*/
    for(i = 0; i < MEM_PART; i++) inUse[i] = -1;
    
    for(j = 0; j < PROC_PART; j++)
    {
        /*iterate through the memory paritions*/
        for (i = 0; i < MEM_PART; i++)
        {
            if(inUse[i] == -1 && m[i] >= p[j])
            {
                inUse[i] = j; /*set inUse to the process*/
                printInput(p[j], m[i], j, i);
                break;
            }
        }
    }
    /*Uses printRes() function to print*/
    printf("\nSummary for first fit:\n");
    printRes(m, p, inUse);
}

/*
Best-fit:  Allocate the smallest hole that is big enough; 
must search entire list, unless ordered by size. 
Produces the smallest leftover hole
*/
/**
 * @brief This is one of the dynamic memory allocation approaches: <b>Best-Fit</b>.\n
 * Allocate the smallest hole that is big enough must search entire list, unless ordered by size. Produces the smallest leftover hole.\n
 * Best-Fit Algorithm:
 *     - Iterate through Memory parts and Process Part
 *     - Starting and select from the first process part and fit in the a available memory that is closest and bigger to the process value to house the data.
 *     - When selecting the process, the memory parts compares with each other to see with is the best fit for the current selected process value.
 *     - Then it call for printRes() function to print.
 *     - After inserting the process to the suitable memory, it sets inUse[] array to an integer to indicate that its used.
 *     - The loop will continue.
 * @param m This is an integer array that stores memory value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 * @param p This is an integer array that stores process value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 */
void bestFit(const int m[MEM_NUM], const int p[PROC_NUM])
{
    int i = 0, j = 0;
    int s = -1; /* empty, smallest */
    printf("\n==============================================================");
    printf("\nStep by Step Best Fit Assignment: \n");
    
    /*set all as -1 as free, otherwise set it to the process that is taken by*/
    for(i = 0; i < MEM_PART; i++) inUse[i] = -1;

    /*iterrate the input processes*/
    for(j = 0; j < PROC_PART; j++)
    {
        s = -1; /*reset smallest to empty and to use it again*/
        /*iterate through the memory paritions*/
        for (i = 0; i < MEM_PART; i++)
        {
            /*check if memory partition is taken and mem partition is bigger then input process*/
            if(inUse[i] == -1 && m[i] >= p[j])
            {
                if(s == -1) s = i; /*if s is empty store it into smallest*/
                /*if smallest is smaller then the next mem partition then replaces and store in smallest*/
                if(m[i] < m[s]) 
                    s = i;
            }
        }
        /*if smallest not empty then assign the current input process to the smallest mem partiton stored in smallest*/
        if(s != -1)
        {   
            inUse[s] = j; 
            printInput(p[j], m[s], j, s);
        }
    }
    /*Uses printRes() function to print*/
    printf("\nSummary for best fit:\n");
    printRes(m, p, inUse);
}

/*
Worst-fit:  Allocate the largest hole; 
must also search entire list 
Produces the largest leftover hole
*/
/**
 * @brief This is one of the dynamic memory allocation approaches: <b>Worse-Fit</b>.\n
 * Allocate the largest hole must also search entire list. Produces the largest leftover hole.\n
 * Worse-Fit Algorithm:
 *     - Iterate through Memory parts and Process Part
 *     - Starting and select from the first process part and fit in the a available memory that is closest and bigger to the process value to house the data.
 *     - It identifies the biggest available memory by iterating the memory to subtract the selected process. The biggest subtraction value will be selected to house the select process.
 *     - Then it call for printRes() function to print.
 *     - After inserting the process to the suitable memory, it sets inUse[] array to an integer to indicate that its used.
 *     - The loop will continue.
 * @param m This is an integer array that stores memory value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 * @param p This is an integer array that stores process value. It is also constant in order to make its value fix, to prevent changes in the underlying value.
 */
void worstFit(const int m[MEM_NUM], const int p[PROC_NUM])
{
    int worstIndex = -1;
    int biggestGap = 0;
    int i = 0, j = 0;
    printf("\n==============================================================");
    printf("\nStep by Step Worst fit Assignment: \n");
    
    /*set all as -1 as free, otherwise set it to the process that is taken by*/
    for(i = 0; i < MEM_PART; i++) inUse[i] = -1;
    
    for(j = 0; j < PROC_PART; j++)
    {
        worstIndex = -1;
        /*iterate through the memory paritions*/
        for (i = 0; i < MEM_PART; i++)
        {
            /*Check if the memory is not used and process bigger then memory value*/
            if(inUse[i] == -1 && m[i] >= p[j])
            {
                /*Subtract the memory to process and updates the worstIndex which store the biggest subtracted value.*/
                if(worstIndex == -1)
                {
                    biggestGap = m[i] - p[j];
                    worstIndex = i;
                }
                /*If there is another subtracted value bigger, it replaces it.*/
                else if(biggestGap < (m[i] - p[j]))
                {
                    biggestGap = m[i] - p[j];
                    worstIndex = i;
                }
            }
        }
        if(worstIndex != -1)
        {
            inUse[worstIndex] = j;
            printInput(p[j], m[worstIndex], j, worstIndex);
        }
    }
    /*Uses printRes() function to print*/
    printf("\nSummary for worst fit:\n");
    printRes(m, p, inUse);
}

/**
 * @brief This function is to run all 3 dynamic memory allocation approaches. 
 * @see firstFit(), bestFit(), worstFit(), ask()
 */
void runAll()
{
    firstFit(memPart, procPart);
    bestFit(memPart, procPart);
    worstFit(memPart, procPart);
}

/**
 * @brief A selection case where allow the user to select which dynamic memory allocation approaches from the given choices. The user can also request all.
 * @note If the user input is invalid, it will ask again.
 * @param x The input value from the user.
 * @see firstFit(), bestFit(), worstFit()
 */
void runAsk(int x)
{
    switch(x)
    {
        case 0: runAll(); return;
        case 1: firstFit(memPart, procPart); break;
        case 2: bestFit(memPart, procPart); break;
        case 3: worstFit(memPart, procPart); break;
        case 4: return;
        default: printf("Invalid Input\n"); break;
    }
    ask(); 
}

/**
 * @brief A function that prints the statement for runAsk() for dynamic memory allocation approaches choices.
 * @note If the user input is invalid, it will ask again.
 */
void ask()
{
    int x = 0;
    while(printf("\n0 for All\n1 for First Fit\n2 for Best Fit\n3 for Worst Fit\n4 for Exit\nEnter your option: ")
        && scanf("%d", &x) != 1) /*this loops while the input is invalid*/
        /*aka it will ask again*/
            scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
    runAsk(x);
}

/**
 * @brief This function are print statements to request for the user to enter its desire values for memory and process values.
 * 
 * @param getInput Gets the input from the user and store it in this integer type variable.
 */
void runProgram(int getInput)
{
    printf("%d Memory partitions and %d Processes.\n", MEM_PART, PROC_PART);
    
    if(getInput == 1)
    {
        printf("\n\nEnter the memory partitions.");
        getProcessInput(memPart, MEM_PART);
        printf("\n\nEnter the process partitions.");
        getProcessInput(procPart, PROC_PART);
        
    }
    ask();
}